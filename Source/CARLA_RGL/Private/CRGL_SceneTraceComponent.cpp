#include "CRGL_SceneTraceComponent.h"
#include "CRGL_Graph.h"
#include "CRGL_Scene.h"
#include "CRGL_Mesh.h"
#include "CRGL_Node.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"



ARGLLIDAR::ARGLLIDAR(
  const FObjectInitializer& Initializer) :
	Super(Initializer)
{
}

void ARGLLIDAR::BeginPlay()
{
	Super::BeginPlay();
	
	const auto MinPitch = -15.0F;
	const auto MaxPitch = 15.0F;
	const auto MinYaw = -15.0F;
	const auto MaxYaw = 15.0F;
	const auto Width = 16;
	const auto Height = 16;
	const auto PitchStep = (MaxPitch - MinPitch) / Height;
	const auto YawStep = (MaxYaw - MinYaw) / Width;

	for (auto Pitch = MinPitch; Pitch <= MaxPitch; Pitch += PitchStep)
	{
		for (auto Yaw = MinYaw; Yaw <= MaxYaw; Yaw += YawStep)
		{
			auto M = FTransform(
				FRotator(Pitch, Yaw, 0.0F),
				FVector::ZeroVector,
				FVector::OneVector);
			Pattern.push_back(
				RGL::ToRGLTransform(M));
		}
	}
}

void ARGLLIDAR::EndPlay(EEndPlayReason::Type Unused)
{
	Super::EndPlay(Unused);
	RGL::FGraph::Destroy(Nodes.RayPoses);
}

void ARGLLIDAR::Tick(float dt)
{
	rgl_cleanup();
	EnumerateSceneEntities();
	SetupTaskGraph();
	auto Result = RayCast();
	for (size_t i = 0; i != Pattern.size(); ++i)
	{
		const auto Start = RGL::ToUETransform(Pattern[i]).GetLocation();
		const auto End = FVector(Result.HitPosition[i]);
		if (Result.Hit[i])
			DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	}
}

FLIDARResult ARGLLIDAR::RayCast()
{
	FLIDARResult Result = {};
	using RGL::FGraph;
	auto Transform = GetTransform();
	Nodes.LIDARTransform.SetRayTransforms(Transform);
	FGraph::Run(Nodes.PointsYield);
	Result.Hit = FGraph::GetResultUE<RGL_FIELD_IS_HIT_I32, TArray>(
		Nodes.PointsYield);
	Result.HitDistances = FGraph::GetResultUE<RGL_FIELD_DISTANCE_F32, TArray>(
		Nodes.PointsYield);
	Result.HitPosition = FGraph::GetResultUE<RGL_FIELD_XYZ_VEC3_F32, TArray>(
		Nodes.PointsYield);
	return Result;
}

void ARGLLIDAR::RayCast(FLIDARResult& OutResult)
{
	OutResult = RayCast();
}

void ARGLLIDAR::PrintRayCastResult(const FLIDARResult& Result)
{
	UE_LOG(LogCarlaRGL, Log, TEXT("Hits:"));
	for (auto& p : Result.Hit)
		UE_LOG(LogCarlaRGL, Log, TEXT("%i"), p);
	UE_LOG(LogCarlaRGL, Log, TEXT("Hit Distances:"));
	for (auto& p : Result.HitDistances)
		UE_LOG(LogCarlaRGL, Log, TEXT("%f"), p);
	UE_LOG(LogCarlaRGL, Log, TEXT("Hit Positions:"));
	for (auto& p : Result.HitPosition)
	{
		auto x = p.X;
		auto y = p.Y;
		auto z = p.Z;
		UE_LOG(LogCarlaRGL, Log, TEXT("(%f, %f, %f)"), x, y, z);
	}
}

void ARGLLIDAR::UpdatePoses()
{
}

void ARGLLIDAR::EnumerateSceneEntities()
{
	UE_LOG(LogCarlaRGL, Log, TEXT(__FUNCTION__));

	using RGL::FMesh;
	using RGL::FEntity;

	auto World = GetWorld();

	TArray<AActor*> Found;
	UGameplayStatics::GetAllActorsOfClass(
		World,
		AStaticMeshActor::StaticClass(),
		Found);

	Meshes.Empty();
	Entities.Empty();
	Meshes.Reserve(Found.Num());
	Entities.Reserve(Found.Num());
	for (auto Actor : Found)
	{
		auto Transform = Actor->GetTransform();
		auto SMA = Cast<AStaticMeshActor>(Actor);
		if (SMA == nullptr)
			continue;
		Meshes.Add(FMesh::FromStaticMeshActor(SMA));
		Entities.Add(FEntity::Create(Meshes.Last()));
		Entities.Last().SetPose(Transform);
#if 0
		const auto M = Transform.ToMatrixWithScale();
		const auto& m = M.M;
		UE_LOG(LogCarlaRGL, Log, TEXT("%s Transform:"), *Actor->GetName());
		UE_LOG(LogCarlaRGL, Log, TEXT("(%f, %f, %f, %f)"), m[0][0], m[1][0], m[2][0], m[3][0]);
		UE_LOG(LogCarlaRGL, Log, TEXT("(%f, %f, %f, %f)"), m[0][1], m[1][1], m[2][1], m[3][1]);
		UE_LOG(LogCarlaRGL, Log, TEXT("(%f, %f, %f, %f)"), m[0][2], m[1][2], m[2][2], m[3][2]);
		UE_LOG(LogCarlaRGL, Log, TEXT("(%f, %f, %f, %f)"), m[0][3], m[1][3], m[2][3], m[3][3]);
#endif
	}

	UE_LOG(
		LogCarlaRGL, Log,
		TEXT("Found %u meshes in world 0x%p"),
		Meshes.Num(), World);

}

void ARGLLIDAR::SetupTaskGraph()
{
	UE_LOG(LogCarlaRGL, Log, TEXT(__FUNCTION__));

	using RGL::FNode;
	using RGL::FGraph;
	using RGL::ToRGLTransform;

	constexpr rgl_vec2f Ranges[] = { 0.0F, 10000.0F };

	constexpr rgl_field_t Fields[] =
	{
		RGL_FIELD_IS_HIT_I32,
		RGL_FIELD_DISTANCE_F32,
		RGL_FIELD_XYZ_VEC3_F32
	};

	const auto Transform = GetTransform();
	const auto loc = Transform.GetLocation();
	const auto rot = Transform.GetRotation().Euler();
	const auto mat = Transform.ToMatrixWithScale();
	const auto& m = mat.M;

#if 0
	UE_LOG(LogCarlaRGL, Log, TEXT("LIDAR Position: (%f, %f, %f)"), loc.X, loc.Y, loc.Z);
	UE_LOG(LogCarlaRGL, Log, TEXT("LIDAR Rotation: (%f, %f, %f)"), rot.X, rot.Y, rot.Z);
	UE_LOG(LogCarlaRGL, Log, TEXT("LIDAR Transform:"));
	UE_LOG(LogCarlaRGL, Log, TEXT("(%f, %f, %f, %f)"), m[0][0], m[1][0], m[2][0], m[3][0]);
	UE_LOG(LogCarlaRGL, Log, TEXT("(%f, %f, %f, %f)"), m[0][1], m[1][1], m[2][1], m[3][1]);
	UE_LOG(LogCarlaRGL, Log, TEXT("(%f, %f, %f, %f)"), m[0][2], m[1][2], m[2][2], m[3][2]);
	UE_LOG(LogCarlaRGL, Log, TEXT("(%f, %f, %f, %f)"), m[0][3], m[1][3], m[2][3], m[3][3]);
#endif

	Nodes.RayPoses = FNode::CreateRaysFromMat3x4F(Pattern);
	Nodes.LIDARTransform = FNode::CreateRayTransforms(Transform);
	Nodes.RayRanges = FNode::CreateRayRange(Ranges);
	Nodes.RayTrace = FNode::CreateRayTrace();
	Nodes.PointsYield = FNode::CreatePointsYield(Fields);

	FGraph::AddChild(Nodes.RayPoses, Nodes.RayRanges);
	FGraph::AddChild(Nodes.RayRanges, Nodes.LIDARTransform);
	FGraph::AddChild(Nodes.LIDARTransform, Nodes.RayTrace);
	FGraph::AddChild(Nodes.RayTrace, Nodes.PointsYield);
}
