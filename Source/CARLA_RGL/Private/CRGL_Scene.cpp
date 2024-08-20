#include "CRGL_Scene.h"
#include "CRGL_Entity.h"
#include "CRGL_Mesh.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"
#include "Animation/SkeletalMeshActor.h"



namespace RGL
{
	void FScene::SetTime(uint64_t nanoseconds)
	{
		CheckRGLResult(rgl_scene_set_time(GetHandle(), nanoseconds));
	}

	void FScene::SetTime(std::chrono::nanoseconds nanoseconds)
	{
		SetTime(nanoseconds.count());
	}

	uint32_t FSceneContext::IDToIndex(uint32_t ID)
	{
		check(ID != 0);
		return ID - 1;
	}

	FSceneContext::EntityIndex FSceneContext::GetEntityIndex(AActor* Actor) const
	{
		ActorToEntityLock.lock_shared();
		auto i = ActorToEntity.find(Actor);
		ActorToEntityLock.unlock_shared();
		return IDToIndex(i->second);
	}

	FEntity& FSceneContext::GetEntity(AActor* Actor)
	{
		return Entities[GetEntityIndex(Actor)];
	}

	void FSceneContext::OnActorTransformChanged(AActor* Actor)
	{
		auto Index = GetEntityIndex(Actor);
		if (false && IsInGameThread())
		{
			// Fast path, single-threaded:
			auto& Entity = Entities[Index];
			Entity.SetPose(Actor->GetTransform());
			return;
		}
		else
		{
			// Slow path, multi-threaded:

			// Check if the target actor has already been marked:
			auto& InfoMask = ChangedCtrl[Index]->Mask;
			if ((InfoMask.fetch_or(1U, std::memory_order::acquire) & UpdateInfo::UPDATED_BIT) != 0)
				return;

			// Add it to the queue:
			auto Last = ChangedTail.exchange(Index, std::memory_order::acquire);
			if (Last == NilIndex)
			{
				ChangedHead.store(Index, std::memory_order::release);
				return;
			}
			else
			{
				ChangedCtrl[Last]->Next = Index;
				std::atomic_thread_fence(std::memory_order::release);
			}
		}
	}

	FSceneContext& FSceneContext::GetDefaultScene()
	{
		static FSceneContext Scene;
		return Scene;
	}

	FSceneContext::FSceneContext() :
		UniqueMeshes(),
		ActorToEntity(),
		Actors(),
		Entities(),
		RefCount(),
		ChangedCtrl(),
		ChangedHead(NilIndex),
		ChangedTail(NilIndex),
		ActorToEntityLock()
	{
	}

	void FSceneContext::RegisterActor(AActor* Actor)
	{
		if (auto Static = Cast<AStaticMeshActor>(Actor))
		{
			return RegisterStaticMeshActor(Static);
		}
		else if (auto Skeletal = Cast<ASkeletalMeshActor>(Actor))
		{
			return RegisterSkeletalMeshActor(Skeletal);
		}
		else
		{
			check(false);
		}
	}

	void FSceneContext::RegisterWorld(UWorld* World)
	{
		TArray<AActor*> Found;
		UGameplayStatics::GetAllActorsOfClass(
			World,
			AStaticMeshActor::StaticClass(),
			Found);
		for (auto Actor : Found)
			RegisterStaticMeshActor(Cast<AStaticMeshActor>(Actor));
	}

	void FSceneContext::RegisterStaticMeshActor(AStaticMeshActor* Actor)
	{
		auto SMC = Actor->GetStaticMeshComponent();
		check(SMC);
		auto SM = SMC->GetStaticMesh();
		FString MeshID;
		SM->GetMeshId(MeshID);
		auto& UniqueMesh = UniqueMeshes[MeshID];
		if (!UniqueMesh.IsValid())
			UniqueMesh = FMesh::FromUEMesh(SM);
		Actors.push_back(Actor);
		Entities.push_back(FEntity::Create(*this, UniqueMesh));
		ChangedCtrl.push_back(
			std::unique_ptr<UpdateInfo>(
				new UpdateInfo{ 0, NilIndex }));
		auto& Entity = Entities.back();
		auto ID = (int32_t)Entities.size();
		Entity.SetPose(Actor->GetTransform());
		Entity.SetID(ID);
		{
			std::scoped_lock guard(ActorToEntityLock);
			ActorToEntity.insert({ Actor, ID });
		}
		auto Root = Actor->GetRootComponent();
		Root->TransformUpdated.AddLambda([this](
			USceneComponent* UpdatedComponent,
			EUpdateTransformFlags UpdateTransformFlags,
			ETeleportType Teleport)
		{
			auto Owner = UpdatedComponent->GetOwner();
			check(Owner);
			OnActorTransformChanged(Owner);
		});
	}

	void FSceneContext::RegisterSkeletalMeshActor(ASkeletalMeshActor* Actor)
	{
		unimplemented();
	}

	bool FSceneContext::HasPendingUpdate()
	{
		return ChangedTail.load(std::memory_order_acquire) != NilIndex;
	}

	void FSceneContext::Update()
	{
		auto Head = ChangedHead.load(std::memory_order_acquire);
		auto Tail = ChangedTail.exchange(NilIndex, std::memory_order_acquire);
		check(Head != NilIndex);
		check(Tail != NilIndex);

		for (;;)
		{
			auto Actor = Actors[Head];
			auto& Ctrl = *ChangedCtrl[Head];

			do
			{
				Ctrl.Mask.store(0, std::memory_order_release);
				Entities[Head].SetPose(Actor->GetTransform());
			} while (Ctrl.Mask.load(std::memory_order_acquire) != 0);

			if (Head == Tail)
				break;

			for (;;)
			{
				Head = ChangedCtrl[Head]->Next;
				if (Head != NilIndex)
					break;
				FGenericPlatformProcess::Yield();
				std::atomic_thread_fence(std::memory_order_acquire);
			}
		}
	}

	void FSceneContext::Minimize()
	{
	}

	void FSceneContext::OnSceneViewerCreated()
	{
		(void)RefCount.fetch_add(1, std::memory_order::release);
	}

	void FSceneContext::OnSceneViewerDestroyed()
	{
		if (RefCount.fetch_sub(1, std::memory_order::acquire) == 1)
		{
			UniqueMeshes.clear();
			ActorToEntity.clear();
			Actors.clear();
			Entities.clear();
			ChangedCtrl.clear();
		}
		RGL::CheckRGLResult(rgl_cleanup());
	}
}