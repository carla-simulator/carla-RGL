#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"




namespace RGL
{
	class FMesh;
	class FTexture;
	class FScene;

	class CARLA_RGL_API FEntity :
		public FHandleMixin<rgl_entity_t, rgl_entity_destroy>
	{
	public:

		FEntity() = default;
		FEntity(FEntity&&) = default;
		FEntity& operator=(FEntity&&) = default;
		~FEntity() = default;

		static FEntity Create(
			const FMesh& Mesh);

		static FEntity Create(
			const FScene& Scene,
			const FMesh& Mesh);

		void SetPose(const rgl_mat3x4f& Transform);
		void SetPose(const FTransform& Transform);
		void SetID(int32_t ID);
		void SetIntensityTexture(const FTexture& FTexture);
		void SetLaserRetro(float Retro);
		bool IsAlive();
	};
}