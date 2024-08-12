#include "CRGL_Scene.h"
#include "CRGL_Entity.h"
#include "CRGL_Mesh.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"



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

	FSceneContext& FSceneContext::GetDefaultScene()
	{
		static FSceneContext Scene;
		return Scene;
	}

	FSceneContext::FSceneContext() :
		RegisteredActors(),
		Meshes(),
		Entities(),
		EntityMap(),
		Changed(),
		Changed2(),
		ChangedLock(),
		AnyChanged()
	{
		Changed.reserve(4096 / sizeof(AActor*));
		Changed2.reserve(Changed.capacity());
	}

	void FSceneContext::RegisterActor(AActor* Actor)
	{
		if (auto SM = Cast<AStaticMeshActor>(Actor))
		{
			return RegisterStaticMeshActor(SM);
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

	void FSceneContext::RegisterStaticMeshActor(AStaticMeshActor* SMA)
	{
		RegisteredActors.push_back(SMA);
		Meshes.push_back(FMesh::FromStaticMeshActor(SMA));
		Entities.push_back(FEntity::Create(*this, Meshes.back()));
		auto& Entity = Entities.back();
		auto ID = (int32_t)Entities.size();
		Entity.SetPose(SMA->GetTransform());
		Entity.SetID(ID);
		EntityMap.insert({ SMA, ID });
		auto Root = SMA->GetRootComponent();
		Root->TransformUpdated.AddLambda([this](
			USceneComponent* UpdatedComponent,
			EUpdateTransformFlags UpdateTransformFlags,
			ETeleportType Teleport)
		{
			auto Owner = UpdatedComponent->GetOwner();
			std::scoped_lock Guard(ChangedLock);
			Changed.push_back(Owner);
		});
	}

	bool FSceneContext::HasPendingUpdate()
	{
		return AnyChanged.load(std::memory_order::acquire);
	}

	void FSceneContext::Update()
	{
		std::scoped_lock Guard(ChangedLock);
		std::swap(Changed, Changed2);
		for (auto Actor : Changed)
		{
			auto i = EntityMap.find(Actor);
			if (i == EntityMap.end())
			{
				continue;
			}
			auto ID = i->second;
			check(ID < Entities.size());
			auto& Entity = Entities[ID];
			Entity.SetPose(Actor->GetTransform());
		}
		Changed.clear();
		AnyChanged.store(false, std::memory_order::relaxed);
	}

	void FSceneContext::Minimize()
	{
		auto size = RegisteredActors.size();
		for (size_t i = 0; i != size;)
		{
			auto Actor = RegisteredActors[i];
			if (::IsValid(Actor)) [[likely]]
			{
				++i;
				continue;
			}
			Entities[i].Destroy();
			Entities.erase(Entities.begin() + i);
			EntityMap.erase(Actor);
			RegisteredActors[i] = RegisteredActors[size - 1];
			--size;
		}
		RegisteredActors.resize(size);
	}
}