#include "CRGL_LIDAR.h"
#include "CRGL_Graph.h"
#include "CRGL_Scene.h"

/*

	Pattern ->
	LIDARTransform ->
	RayRanges ->
	NoiseAngularRay ->
	NoiseAngularHitPoint ->
	NoiseDistance ->
	RayTrace

*/

static TAutoConsoleVariable<int32> CRGLDrawDebug(
	TEXT("crgl.Debug.DrawTraces"),
	0,
	TEXT("Whether to draw traces."));

namespace RGL
{
	void FLIDAR::CheckGraphEdges()
	{
		check(Nodes.Pattern.IsValid());
		auto Prev = &Nodes.Pattern;

		auto Connect = [&Prev](auto& Child)
		{
			FGraph::AddChild(*Prev, Child);
			Prev = &Child;
		};

		auto TryConnect = [&Prev, Connect](auto& Child)
		{
			if (Child.IsValid())
				Connect(Child);
		};
		
		TryConnect(Nodes.RayRanges);
		TryConnect(Nodes.LIDARTransform);
		check(Nodes.RayTrace.IsValid());
		Connect(Nodes.RayTrace);
		TryConnect(Nodes.NoiseAngularRay);
		TryConnect(Nodes.NoiseAngularHitPoint);
		TryConnect(Nodes.NoiseDistance);
		TryConnect(Nodes.PointsYield);
	}

	FLIDAR::FLIDAR() :
		LastTransform(),
		Nodes(),
		RayCount(0),
		PointsYieldHitMask(false),
		PointsYieldHitDistances(false),
		PointsYieldHitPositions(false),
		Scene(&FSceneContext::GetDefaultScene())
	{
	}

	FLIDAR::FLIDAR(
		FSceneContext& Scene,
		const FLIDAROptions& Options) :
		LastTransform(),
		Nodes(),
		RayCount(0),
		PointsYieldHitMask(false),
		PointsYieldHitDistances(false),
		PointsYieldHitPositions(false),
		Scene(&Scene)
	{
		SetPattern(Options.Pattern);
		Nodes.RayTrace.SetRayTrace(Scene);
		if (!Options.EnabledPointsYieldFields.empty())
		{
			for (auto Field : Options.EnabledPointsYieldFields)
			{
				switch (Field)
				{
				case EField::IsHitI32:
					PointsYieldHitMask = true;
					break;
				case EField::DistanceF32:
					PointsYieldHitDistances = true;
					break;
				case EField::XYZVec3F32:
					PointsYieldHitPositions = true;
					break;
				default:
					UE_LOG(LogCarlaRGL, Error, TEXT("Unknown or unsupported field type for PointsYieldNode."));
					check(false);
				}
			}
			Nodes.PointsYield.SetPointsYield(Options.EnabledPointsYieldFields);
		}
	}

	FLIDAR::~FLIDAR()
	{
	}

	void FLIDAR::SetTransform(FTransform NewTransform)
	{
		SetTransform(RGL::ToRGLTransform(NewTransform));
	}

	void FLIDAR::SetTransform(Float3x4 NewTransform)
	{
		const auto L = (const float*)NewTransform.value;
		const auto R = (const float*)LastTransform.value;
		for (size_t i = 0; i != 12; ++i)
		{
			if (std::abs(L[i] - R[i]) > 1e-5)
			{
				Nodes.LIDARTransform.SetRayTransforms(NewTransform);
				LastTransform = NewTransform;
				break;
			}
		}
	}

	void FLIDAR::SetPattern(std::span<const Float3x4> Pattern)
	{
		Nodes.Pattern.SetRaysFromMat3x4F(Pattern);
		RayCount = Pattern.size();
	}

	void FLIDAR::SetRayRanges(std::span<const Float2> Ranges)
	{
		Nodes.RayRanges.SetRayRange(Ranges);
	}

	void FLIDAR::SetRayRanges(float Min, float Max)
	{
		std::vector<rgl_vec2f> Ranges(RayCount);
		for (auto& e : Ranges)
			e = { { Min, Max } };
		SetRayRanges(Ranges);
	}

	void FLIDAR::SetGaussianNoiseAngularRay(float Mean, float Sigma, EAxis::Type Axis)
	{
		rgl_axis_t RGLAxis;
		switch (Axis)
		{
		case EAxis::X:
			RGLAxis = RGL_AXIS_X;
		case EAxis::Y:
			RGLAxis = RGL_AXIS_Y;
		case EAxis::Z:
			RGLAxis = RGL_AXIS_Z;
		default:
			abort();
		}
		Nodes.NoiseAngularRay.SetGaussianNoiseAngularRay(Mean, Sigma, RGLAxis);
	}

	void FLIDAR::SetGaussianNoiseAngularHitPoint(float Mean, float Sigma, EAxis::Type Axis)
	{
		rgl_axis_t RGLAxis;
		switch (Axis)
		{
		case EAxis::X:
			RGLAxis = RGL_AXIS_X;
		case EAxis::Y:
			RGLAxis = RGL_AXIS_Y;
		case EAxis::Z:
			RGLAxis = RGL_AXIS_Z;
		default:
			abort();
		}
		Nodes.NoiseAngularRay.SetGaussianNoiseAngularHitPoint(Mean, Sigma, RGLAxis);
	}

	void FLIDAR::SetGaussianNoiseDistance(float Mean, float Sigma, float SigmaRisePerMeter)
	{
		Nodes.NoiseAngularRay.CreateGaussianNoiseDistance(Mean, Sigma, SigmaRisePerMeter);
	}

	void FLIDAR::SetYieldPoints(std::span<const RGL::EField> Fields)
	{
		Nodes.PointsYield.SetPointsYield(Fields);
	}

	void FLIDAR::Commit()
	{
		CheckGraphEdges();
	}

	void FLIDAR::Trace()
	{
		if (Scene->HasPendingUpdate())
		{
			Scene->Update();
			// Scene->Minimize();
		}
		FGraph::Run(Nodes.Pattern);
	}

	FLIDARResult FLIDAR::GetResult()
	{
		FLIDARResult Result = {};
		if (Nodes.PointsYield.IsValid())
		{
			Result.HitMask = FGraph::GetResultUE<EField::IsHitI32>(Nodes.PointsYield);
			Result.HitDistances = FGraph::GetResultUE<EField::DistanceF32>(Nodes.PointsYield);
			Result.HitPositions = FGraph::GetResultUE<EField::XYZVec3F32>(Nodes.PointsYield);
		}

		if (CRGLDrawDebug.GetValueOnAnyThread()) [[unlikely]]
		{
			auto Pattern = FLIDARPatternLibrary::GetDefault();
			Result.DebugDraw(GWorld.GetReference(), ToUETransform(LastTransform), Pattern);
		}

		return Result;
	}



	std::vector<Float3x4> FLIDARPatternLibrary::GetDefault(
		FIntPoint Shape,
		FVector2f MaxAngle,
		FVector2f MinAngle)
	{
		std::vector<Float3x4> r;
		const auto MaxPitch = MaxAngle.X;
		const auto MaxYaw = MaxAngle.Y;
		const auto MinPitch = MinAngle.X;
		const auto MinYaw = MinAngle.Y;
		const auto PitchStep = (MaxPitch - MinPitch) / (float)Shape.Y;
		const auto YawStep = (MaxYaw - MinYaw) / (float)Shape.X;
		r.reserve(Shape.X * Shape.Y);
		for (auto Pitch = MinPitch; Pitch <= MaxPitch; Pitch += PitchStep)
		{
			for (auto Yaw = MinYaw; Yaw <= MaxYaw; Yaw += YawStep)
			{
				auto M = FTransform(
					FQuat::MakeFromEuler({ Pitch, Yaw, 0.0F }),
					FVector::ZeroVector,
					FVector::OneVector);
				r.push_back(
					RGL::ToRGLTransform(M));
			}
		}
		return r;
	}

	std::vector<Float3x4> FLIDARPatternLibrary::GetVelodyneHDL64ES2(
		float SpinRateHz)
	{
		std::vector<Float3x4> Pattern;
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



	void FLIDARResult::DebugDraw(
		UWorld* World,
		const FTransform& LIDARTransform,
		std::span<const Float3x4> Pattern)
	{
		check(HitMask.Num() == HitPositions.Num());

		auto M = LIDARTransform.ToMatrixWithScale();
		for (size_t i = 0; i != HitMask.Num(); ++i)
		{
			auto Start = RGL::ToUETransform(Pattern[i]).GetLocation();
			Start = M.TransformPosition(Start);
			if (HitMask[i])
			{
				auto End = FVector(HitPositions[i]);
				DrawDebugLine(World, Start, End, FColor::Red);
			}
			else
			{
				auto End = M.TransformPosition(FVector::ForwardVector * 10.0F);
				DrawDebugLine(World, Start, End, FColor::Blue);
			}
		}
	}



	FLIDAROptions FLIDAROptions::Default()
	{
		FLIDAROptions r = {};
		r.EnabledPointsYieldFields = DefaultPointFields;
		return r;
	}
}