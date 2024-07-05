#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include "CRGL_Node.generated.h"




class FCRGL_Node :
	public FCarlaRGLHandleMixin<rgl_node_t>
{
public:

	static FCRGL_Node CreateRayTransforms(
		const rgl_mat3x4f& transform);

	static FCRGL_Node CreateRayTransforms(
		const FTransform& transform);

	static FCRGL_Node CreateRayRingIDs(
		const int32_t* ids,
		size_t count);

	static FCRGL_Node CreateRaysFromMat3x4F(
		const rgl_mat3x4f* transforms,
		size_t count);

	static FCRGL_Node CreateRayRange(
		const rgl_vec2f* ranges,
		size_t count);

	static FCRGL_Node CreateRayTimeOffsets(
		const float* offsets,
		size_t count);

	static FCRGL_Node CreatePointsTransform(
		const rgl_mat3x4f& transform);

	static FCRGL_Node CreatePointsFormat(
		const rgl_field_t* fields,
		size_t count);

	static FCRGL_Node CreatePointsYield(
		const rgl_field_t* fields,
		size_t count);

	static FCRGL_Node CreatePointsCompact();

	static FCRGL_Node CreatePointsCompactByField(
		rgl_field_t field);

	static FCRGL_Node CreatePointsSpatialMerge(
		const rgl_field_t* fields,
		size_t count);

	static FCRGL_Node CreatePointsTemporalMerge(
		const rgl_field_t* fields,
		size_t count);

	static FCRGL_Node CreatePointsFromArray(
		const void* points,
		size_t point_count,
		const rgl_field_t* fields,
		size_t field_count);

	static FCRGL_Node CreatePointsRadarPostProcess(
		const rgl_radar_scope_t* radar_scopes,
		int32_t radar_scopes_count,
		float ray_azimuth_step,
		float ray_elevation_step,
		float frequency,
		float power_transmitted,
		float cumulative_device_gain,
		float received_noise_mean,
		float received_noise_st_dev);

	static FCRGL_Node CreatePointsFilterGround(
		const rgl_vec3f& sensor_up_vector,
		float ground_angle_threshold);

	static FCRGL_Node CreateGaussianNoiseAngularRay(
		float mean,
		float std_dev,
		rgl_axis_t axis);

	static FCRGL_Node CreateGaussianNoiseAngularHitPoint(
		float mean,
		float std_dev,
		rgl_axis_t axis);

	static FCRGL_Node CreateGaussianNoiseDistance(
		float mean,
		float std_dev,
		float std_dev_rise_per_meter);

	static FCRGL_Node CreateRayTrace(
		FCRGL_Scene& scene);

	static FCRGL_Node CreateRayTrace();



	void SetRayTransforms(
		const rgl_mat3x4f& transform);

	void SetRayTransforms(
		const FTransform& transform);

	void SetRayRingIDs(
		const int32_t* ids,
		size_t count);

	void SetRayFromMat3x4F(
		const rgl_mat3x4f* transforms,
		size_t count);

	void SetRayRange(
		const rgl_vec2f* ranges,
		size_t count);

	void SetRayTimeOffsets(
		const float* offsets,
		size_t count);

	void SetPointsTransform(
		const rgl_mat3x4f& transform);

	void SetPointsFormat(
		const rgl_field_t* fields,
		size_t count);

	void SetPointsYield(
		const rgl_field_t* fields,
		size_t count);

	void SetPointsCompactByField(
		rgl_field_t field);

	void SetPointsSpatialMerge(
		const rgl_field_t* fields,
		size_t count);

	void SetPointsTemporalMerge(
		const rgl_field_t* fields,
		size_t count);

	void SetPointsFromArray(
		const void* points,
		size_t point_count,
		const rgl_field_t* fields,
		size_t field_count);

	void SetPointsRadarPostProcess(
		const rgl_radar_scope_t* radar_scopes,
		int32_t radar_scopes_count,
		float ray_azimuth_step,
		float ray_elevation_step,
		float frequency,
		float power_transmitted,
		float cumulative_device_gain,
		float received_noise_mean,
		float received_noise_st_dev);

	void SetPointsFilterGround(
		const rgl_vec3f& sensor_up_vector,
		float ground_angle_threshold);

	void SetGaussianNoiseAngularRay(
		float mean,
		float std_dev,
		rgl_axis_t axis);

	void SetGaussianNoiseAngularHitPoint(
		float mean,
		float std_dev,
		rgl_axis_t axis);

	void SetGaussianNoiseDistance(
		float mean,
		float std_dev,
		float std_dev_rise_per_meter);
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
