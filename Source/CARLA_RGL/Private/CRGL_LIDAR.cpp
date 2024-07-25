#include "CRGL_LIDAR.h"

namespace RGL
{
	FLIDAR::FLIDAR(
		FSceneContext* InScene)
	{
		new (this) FLIDAR(
			InScene,
			FLIDARPatternLibrary::GetDefault());
	}

	FLIDAR::FLIDAR(
		FSceneContext* InScene,
		std::span<const rgl_mat3x4f> Pattern) :
		Scene(InScene)
	{
	}

	void FLIDAR::Trace()
	{
	}

	std::vector<rgl_mat3x4f> FLIDARPatternLibrary::GetDefault()
	{
		std::vector<rgl_mat3x4f> r;

		return r;
	}

	std::vector<rgl_mat3x4f> FLIDARPatternLibrary::GetVelodyneHDL64ES2(
		float SpinRateHz)
	{
		std::vector<rgl_mat3x4f> Pattern;
		const auto DetectorCount = 64;
		const auto AzimuthalFOV = PI * 2.0;
		const auto ElevationMax = 0.034906585;
		const auto ElevationMin = -0.432841654;
		const auto ElevationStepSize = (ElevationMax - ElevationMin) / DetectorCount;
		auto Elevation = ElevationMin;
		for (size_t i = 0; i != DetectorCount; ++i)
		{
			auto R = FRotator(Elevation);
			auto Q = R.Quaternion();
			auto M = Q.ToMatrix();
			auto T = FTransform(M);
			auto m = ToRGLTransform(T);
			Elevation += ElevationStepSize;
			Pattern.push_back(m);
		}
		return Pattern;
	}
}