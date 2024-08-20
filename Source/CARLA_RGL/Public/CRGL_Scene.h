#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include <chrono>
#include <vector>
#include <atomic>
#include <shared_mutex>
#include <unordered_map>



class AStaticMeshActor;
class ASkeletalMeshActor;



namespace RGL
{
	class FEntity;
	class FMesh;



	class CARLA_RGL_API FScene :
		public FHandleMixin<rgl_scene_t, nullptr>
	{
	public:

		void SetTime(uint64_t nanoseconds);
		void SetTime(std::chrono::nanoseconds nanoseconds);

	};



	class CARLA_RGL_API FSceneContext :
		public FScene
	{
		static constexpr auto NilIndex = UINT32_MAX;
		using MeshIndex = uint32_t;
		using EntityIndex = uint32_t;

		struct FStringHasher
		{
			inline auto operator()(const FString& Text) const
			{
				using C = FString::ElementType;
				using S = std::basic_string_view<C>;
				return std::hash<S>()(S(*Text, Text.Len()));
			}
		};

		struct UpdateInfo
		{
			enum : uint32_t
			{
				UPDATED_BIT = 1U
			};

			std::atomic<uint32_t> Mask;
			uint32_t Next;
		};

		std::unordered_map<FString, FMesh, FStringHasher> UniqueMeshes;
		std::unordered_map<AActor*, EntityIndex> ActorToEntity;
		std::vector<AActor*> Actors;
		std::vector<FEntity> Entities;
		mutable std::shared_mutex ActorToEntityLock;

		// Multi-threaded transform update event queue:
		std::vector<std::unique_ptr<UpdateInfo>> ChangedCtrl;
		std::atomic_uint32_t ChangedHead;
		std::atomic_uint32_t ChangedTail;

		std::atomic_size_t RefCount;

		static uint32_t IDToIndex(uint32_t ID);
		EntityIndex GetEntityIndex(AActor* Actor) const;
		FEntity& GetEntity(AActor* Actor);
		void OnActorTransformChanged(AActor* Actor);

	public:

		static FSceneContext& GetDefaultScene();

		FSceneContext();
		FSceneContext(const FSceneContext&) = delete;
		FSceneContext& operator=(const FSceneContext&) = delete;
		~FSceneContext() = default;

		void RegisterActor(AActor* Actor);
		void RegisterWorld(UWorld* World);
		void RegisterStaticMeshActor(AStaticMeshActor* Actor);
		void RegisterSkeletalMeshActor(ASkeletalMeshActor* Actor);
		bool HasPendingUpdate();
		void Update();
		void Minimize();

		void OnSceneViewerCreated();
		void OnSceneViewerDestroyed();
	};
}