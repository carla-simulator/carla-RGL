#include "CRGL_SceneTraceComponent.h"
#include "CRGL_Graph.h"
#include "CRGL_Scene.h"
#include "CRGL_Mesh.h"
#include "CRGL_Node.h"
#include "Engine/StaticMeshActor.h"



static const FTransform TestTransforms[] =
{
	FTransform(FQuat::Identity, FVector(10.000000, 80.000000, 9.500100), FVector::OneVector),
	FTransform(FQuat::Identity, FVector(10.000000, -120.000000, 9.500100), FVector::OneVector),
	FTransform(FQuat::Identity, FVector(-90.000000, -20.000000, 9.500100), FVector::OneVector),
	FTransform(FQuat::Identity, FVector(110.000000, -20.000000, 9.500100), FVector::OneVector),
	FTransform(FQuat::Identity, FVector(10.000000, -20.000000, 109.500100), FVector::OneVector),
	FTransform(FQuat::Identity, FVector(10.000000, -20.000000, -90.499900), FVector::OneVector),
};



ACRGL_SceneTraceComponent::ACRGL_SceneTraceComponent(
  const FObjectInitializer& Initializer) :
	Super(Initializer)
{
}

void ACRGL_SceneTraceComponent::BeginPlay()
{
	UE_LOG(LogCarlaRGL, Log, TEXT(__FUNCTION__));
	Super::BeginPlay();
}

void ACRGL_SceneTraceComponent::EndPlay(EEndPlayReason::Type Unused)
{
	UE_LOG(LogCarlaRGL, Log, TEXT(__FUNCTION__));
	Super::EndPlay(Unused);
}

void ACRGL_SceneTraceComponent::Tick(float DT)
{
	Super::Tick(DT);
	
	auto SMT = FCRGL_Mesh::EnumerateStaticMeshes(GetWorld());
	
	TArray<FCRGL_Mesh> Meshes;
	TArray<FCRGL_Entity> Entities;
	
	Meshes.SetNum(SMT.Num());
	Entities.SetNum(SMT.Num());

	for (size_t i = 0; i != SMT.Num(); ++i)
	{
		auto& [Mesh, Transform] = SMT[i];
		Meshes[i] = std::move(Mesh);
	}

	for (size_t i = 0; i != SMT.Num(); ++i)
	{
		auto& [Mesh, Transform] = SMT[i];
		Entities[i] = FCRGL_Entity::Create(Meshes[i]);
	}

	for (size_t i = 0; i != SMT.Num(); ++i)
	{
		auto& [Mesh, Transform] = SMT[i];
		Entities[i].SetPose(Transform);
	}

	for (auto& Mesh : Meshes)
	{
		check(Mesh.IsAlive());
	}

	for (auto& Entity : Entities)
	{
		check(Entity.IsAlive());
	}
	
	auto Transform = GetTransform();
	UE_LOG(LogCarlaRGL, Log, TEXT(__FUNCTION__));
	
	constexpr rgl_vec2f Ranges[] = { 0.0F, 1000.0F };

	const rgl_mat3x4f Identity[] =
	{
		ToRGLTransform(FTransform::Identity)
	};

	const rgl_mat3x4f RayTransforms[] =
	{
		ToRGLTransform(Transform)
	};
	
	const auto loc = Transform.GetLocation();
	const auto rot = Transform.GetRotation().Euler();
	const auto mat = Transform.ToMatrixWithScale();
	const auto& m = mat.M;

	UE_LOG(LogCarlaRGL, Log, TEXT("LIDAR Position: (%f, %f, %f)"), loc.X, loc.Y, loc.Z);
	UE_LOG(LogCarlaRGL, Log, TEXT("LIDAR Rotation: (%f, %f, %f)"), rot.X, rot.Y, rot.Z);
	UE_LOG(LogCarlaRGL, Log, TEXT("LIDAR Transform:"));
	UE_LOG(LogCarlaRGL, Log, TEXT("(%f, %f, %f, %f)"), m[0][0], m[1][0], m[2][0], m[3][0]);
	UE_LOG(LogCarlaRGL, Log, TEXT("(%f, %f, %f, %f)"), m[0][1], m[1][1], m[2][1], m[3][1]);
	UE_LOG(LogCarlaRGL, Log, TEXT("(%f, %f, %f, %f)"), m[0][2], m[1][2], m[2][2], m[3][2]);
	UE_LOG(LogCarlaRGL, Log, TEXT("(%f, %f, %f, %f)"), m[0][3], m[1][3], m[2][3], m[3][3]);

	auto ray_poses = FCRGL_Node::CreateRaysFromMat3x4F(RayTransforms);
	auto raytrace = FCRGL_Node::CreateRayTrace();
	FCRGL_Graph::AddChild(ray_poses, raytrace);
	FCRGL_Graph::Run(raytrace);

	FRayCastResult Results = {};

	// Results.Hit = FCRGL_Graph::GetResult<int32>(
	// 	raytrace,
	// 	RGL_FIELD_IS_HIT_I32);

	Results.HitPosition = FCRGL_Graph::GetResult<rgl_vec3f>(
		raytrace,
		RGL_FIELD_XYZ_VEC3_F32);

	for (auto& p : Results.Hit)
	{
		UE_LOG(LogCarlaRGL, Log, TEXT("%i"), p);
	}

	for (auto& p : Results.HitPosition)
	{
		auto [x, y, z] = p.value;
		UE_LOG(LogCarlaRGL, Log, TEXT("(%f, %f, %f)"), x, y, z);
	}

	FCRGL_Graph::Destroy(raytrace);
}

FRayCastResult ACRGL_SceneTraceComponent::RayCast()
{
	return FRayCastResult();
}