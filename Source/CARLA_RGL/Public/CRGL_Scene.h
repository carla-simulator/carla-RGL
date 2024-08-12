#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include <mutex>
#include <chrono>
#include <vector>
#include <atomic>
#include <unordered_map>



namespace RGL
{
	class FEntity;
	class FMesh;



	template <typename K, typename V>
	using HashMap = std::unordered_map<K, V>;



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
		using EntityID = size_t;

		std::vector<AActor*> RegisteredActors;
		std::vector<FEntity> Entities;
		std::vector<FMesh> Meshes;
		HashMap<AActor*, size_t> EntityMap;
		std::vector<AActor*> Changed;
		std::vector<AActor*> Changed2;

		alignas (std::hardware_destructive_interference_size)
		std::mutex ChangedLock;
		std::atomic_bool AnyChanged;

	public:

		static FSceneContext& GetDefaultScene();

		FSceneContext();
		FSceneContext(const FSceneContext&) = delete;
		FSceneContext& operator=(const FSceneContext&) = delete;
		~FSceneContext() = default;

		void RegisterActor(AActor* Actor);
		void RegisterWorld(UWorld* World);
		void RegisterStaticMeshActor(AStaticMeshActor* SMA);
		bool HasPendingUpdate();
		void Update();
		void Minimize();

	};
}