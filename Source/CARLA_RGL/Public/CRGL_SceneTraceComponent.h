#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include <span>
#include "CRGL_SceneTraceComponent.generated.h"



class FCRGL_Node;



struct FRayCastResult
{
	TArray<int32_t> Hit;
	TArray<FVector3f> HitPosition;
};



class FCRGL_LIDAR
{
	FCRGL_Node ray_poses;
	FCRGL_Node ray_ranges;
	FCRGL_Node lidar_transform;
	FCRGL_Node raytrace;
	FCRGL_Node points_compact;
	FCRGL_Node points_yield;
	FCRGL_Node raytrace_yield;
	FCRGL_Node compact_yield;
	FCRGL_Node point_cloud_transform;
	FCRGL_Node format;

public:

	void SetRayTransforms(std::span<const rgl_mat3x4f> transforms);
	void SetRayRange(float maximum, float minimum = 0.0F);
	void SetYield(std::span<const rgl_field_t> fields);
	void SetTransform(rgl_mat3x4f transform);
	void SetAngularNoise(float std_dev);
	void SetDistanceNoise(float std_dev_base, float std_dev_rise_per_meter);
	void SetRayCastResultFlags();
	void SetRayDirections(std::span<FVector3f> directions);
	void SetNoiseParams();
	void Finalize();
	FRayCastResult Run();

};




UCLASS()
class ACRGL_SceneTraceComponent :
	public AActor
{
	GENERATED_BODY()
public:

	ACRGL_SceneTraceComponent(const FObjectInitializer& Initializer);

	void BeginPlay() override;
	void EndPlay(EEndPlayReason::Type) override;

	virtual void Tick(float DT) override;

private:

	void InitializeRayTracingGraph();

	FCRGL_LIDAR ImplLIDAR;

};
