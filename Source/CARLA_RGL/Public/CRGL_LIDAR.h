#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include "CRGL_Entity.h"
#include "CRGL_Mesh.h"
#include "CRGL_Node.h"



namespace RGL
{
	class FSceneContext;

	USTRUCT()
	struct CARLA_RGL_API FLIDARPatternLibrary
	{
		static std::vector<rgl_mat3x4f> GetDefault();
		static std::vector<rgl_mat3x4f> GetVelodyneHDL64ES2(float SpinRateHz = 20.0);
	};

	class CARLA_RGL_API FLIDAR
	{
	public:

		FLIDAR() = default;
		FLIDAR(FLIDAR&&) = default;
		FLIDAR& operator=(FLIDAR&&) = default;
		~FLIDAR() = default;

		explicit FLIDAR(
			FSceneContext* Scene);

		explicit FLIDAR(
			FSceneContext* Scene,
			std::span<const rgl_mat3x4f> Pattern);

		void Trace();

	private:

		FSceneContext* Scene;

	};
}
