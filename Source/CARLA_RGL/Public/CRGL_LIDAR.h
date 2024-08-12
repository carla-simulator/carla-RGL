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
		static std::vector<Float3x4> GetDefault(
			FIntPoint Shape = FIntPoint(16, 16),
			FVector2f MaxAngle = FVector2f(30.0F, 30.0F),
			FVector2f MinAngle = FVector2f(-30.0F, -30.0F));

		static std::vector<Float3x4> GetVelodyneHDL64ES2(
			float SpinRateHz = 20.0);
	};

	struct FLIDARResult
	{
		TArray64<FVector3f> HitPositions;
		TArray64<float> HitDistances;
		TArray64<int32> HitMask;

		void DebugDraw(
			UWorld* World,
			const FTransform& LIDARTransform,
			std::span<const Float3x4> Pattern);
	};

	struct FLIDAROptions
	{
		static constexpr EField DefaultPointFields[] =
		{
			EField::XYZVec3F32,
			EField::DistanceF32,
			EField::IsHitI32
		};

		std::span<const Float3x4> Pattern;
		std::span<const EField> EnabledPointsYieldFields = DefaultPointFields;

		static FLIDAROptions Default();
	};

	class CARLA_RGL_API FLIDAR
	{
	public:

		FLIDAR();
		FLIDAR(FLIDAR&&) = default;
		FLIDAR& operator=(FLIDAR&&) = default;
		~FLIDAR();

		explicit FLIDAR(
			FSceneContext& Scene,
			const FLIDAROptions& Options);

		void SetTransform(FTransform NewTransform);
		void SetTransform(Float3x4 NewTransform);
		void SetPattern(std::span<const Float3x4> Pattern);
		void SetRayRanges(std::span<const Float2> Ranges);
		void SetRayRanges(float Min, float Max);
		void SetGaussianNoiseAngularRay(float Mean, float Sigma, EAxis::Type Axis);
		void SetGaussianNoiseAngularHitPoint(float Mean, float Sigma, EAxis::Type Axis);
		void SetGaussianNoiseDistance(float Mean, float Sigma, float SigmaRisePerMeter);
		void SetYieldPoints(std::span<const RGL::EField> Fields);
		void Commit();
		void Trace();
		FLIDARResult GetResult();

		constexpr auto& GetSceneContext() { return *Scene; }
		constexpr auto& GetSceneContext() const { return *Scene; }

	private:

		void CheckGraphEdges();

		Float3x4 LastTransform;
		struct
		{
			FNode
				Pattern,
				RayRanges,
				LIDARTransform,
				RayTrace,
				NoiseAngularRay,
				NoiseAngularHitPoint,
				NoiseDistance,
				PointsYield;
		} Nodes;
		size_t RayCount;
		bool
			PointsYieldHitMask : 1,
			PointsYieldHitDistances : 1,
			PointsYieldHitPositions : 1;
		FSceneContext* Scene;

	};
}
