#include "CRGL_SceneTraceComponent.h"
#include "CRGL_Graph.h"
#include "CRGL_Scene.h"
#include "CRGL_Node.h"



ACRGL_SceneTraceComponent::ACRGL_SceneTraceComponent(
  const FObjectInitializer& Initializer)
{
}

void ACRGL_SceneTraceComponent::BeginPlay()
{
}

void ACRGL_SceneTraceComponent::EndPlay(EEndPlayReason::Type Unused)
{
}

void ACRGL_SceneTraceComponent::Tick(float DT)
{
}

void ACRGL_SceneTraceComponent::InitializeRayTracingGraph()
{
}



void FCRGL_LIDAR::SetRayTransforms(std::span<const rgl_mat3x4f> transforms)
{
}

void FCRGL_LIDAR::SetRayRange(float maximum, float minimum)
{
}

void FCRGL_LIDAR::SetYield(std::span<const rgl_field_t> fields)
{
}

void FCRGL_LIDAR::SetTransform(rgl_mat3x4f transform)
{
}

void FCRGL_LIDAR::SetAngularNoise(float std_dev)
{
}

void FCRGL_LIDAR::SetDistanceNoise(float std_dev_base, float std_dev_rise_per_meter)
{
}

void FCRGL_LIDAR::SetRayCastResultFlags()
{
}

void FCRGL_LIDAR::SetRayDirections(std::span<FVector3f> directions)
{
}

void FCRGL_LIDAR::SetNoiseParams()
{
}

void FCRGL_LIDAR::Finalize()
{
	const rgl_field_t DefaultFields[] = { RGL_FIELD_IS_HIT_I32, RGL_FIELD_XYZ_VEC3_F32 };
	const auto DefaultFieldCount = sizeof(DefaultFields) / sizeof(DefaultFields[0]);
	const rgl_mat3x4f Identity[] = { ToRGLTransform(FTransform::Identity) };
	const rgl_vec2f range[] = { {0.0F, 1.0F} };

	ray_poses = FCRGL_Node::CreateRaysFromMat3x4F(Identity, 1);
	ray_ranges = FCRGL_Node::CreateRayRange(range, 1);
	lidar_transform = FCRGL_Node::CreateRayTransforms(Identity[0]);
	raytrace = FCRGL_Node::CreateRayTrace();
	points_compact = FCRGL_Node::CreatePointsCompact();
	points_yield = FCRGL_Node::CreatePointsYield(DefaultFields, DefaultFieldCount);
	raytrace_yield = FCRGL_Node::CreatePointsYield(DefaultFields, DefaultFieldCount);
	compact_yield = FCRGL_Node::CreatePointsYield(DefaultFields, DefaultFieldCount);
	point_cloud_transform = FCRGL_Node::CreatePointsTransform(Identity[0]);
	format = FCRGL_Node::CreatePointsFormat(nullptr, 0);

	FCRGL_Graph::AddChild(ray_poses, ray_ranges);
	FCRGL_Graph::AddChild(ray_ranges, lidar_transform);
	FCRGL_Graph::AddChild(compact_yield, points_yield);
	FCRGL_Graph::AddChild(point_cloud_transform, points_yield);
	FCRGL_Graph::AddChild(ray_poses, ray_ranges);
}

FRayCastResult FCRGL_LIDAR::Run()
{
	FRayCastResult r = {};
	FCRGL_Graph::Run(ray_poses);
	return r;
}
