#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include "CRGL_Node.generated.h"




class FCRGL_Node :
	public FCarlaRGLHandleMixin<rgl_node_t>
{
public:

	void Initialize();

	void SetRayTransforms();
	void SetRayRingIDs();
	void SetRayFromMat3x4F();
	void SetRayRange();
	void SetRayTimeOffsets();

	void SetPointsTransforms();
	void SetPointsFormat();
	void SetPointsYield();
	void SetPointsCompactByField();
	void SetPointsSpatialMerge();
	void SetPointsTemporalMerge();
	void SetPointsFromArray();
	void SetPointsRadarPostProcess();
	void SetPointsFilterGround();
	void SetPointsGaussianNoiseAngularRay();
	void SetPointsGaussianNoiseAngularHitPoint();
	void SetPointsGaussianNoiseDistance();
	bool IsAlive();

	void SetRaytrace();
	void SetRaytraceConfigureVelocity();
	void SetRaytraceConfigureDistortion();
	void SetRaytraceConfigureNonHits();

	void RunGraph();
	void DestroyGraph();
};



UCLASS()
class ACRGL_Node :
	public AActor,
	public FCRGL_Node
{
	GENERATED_BODY()
public:

	ACRGL_Node(
		const FObjectInitializer& Initializer);

};
