#include "CRGL_Node.h"
#include "CRGL_Scene.h"

FCRGL_Node FCRGL_Node::CreateRayTransforms(const rgl_mat3x4f& transform)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_rays_transform(r.GetHandlePtr(), &transform));
	return r;
}

FCRGL_Node FCRGL_Node::CreateRayTransforms(const FTransform& transform)
{
	return CreateRayTransforms(ToRGLTransform(transform));
}

FCRGL_Node FCRGL_Node::CreateRayRingIDs(const int32_t* ids, size_t count)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_rays_set_ring_ids(r.GetHandlePtr(), ids, count));
	return r;
}

FCRGL_Node FCRGL_Node::CreateRaysFromMat3x4F(const rgl_mat3x4f* transforms, size_t count)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_rays_from_mat3x4f(r.GetHandlePtr(), transforms, count));
	return r;
}

FCRGL_Node FCRGL_Node::CreateRayRange(const rgl_vec2f* ranges, size_t count)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_rays_set_range(r.GetHandlePtr(), ranges, count));
	return r;
}

FCRGL_Node FCRGL_Node::CreateRayTimeOffsets(const float* offsets, size_t count)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_rays_set_time_offsets(r.GetHandlePtr(), offsets, count));
	return r;
}

FCRGL_Node FCRGL_Node::CreatePointsTransform(const rgl_mat3x4f& transform)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_points_transform(r.GetHandlePtr(), &transform));
	return r;
}

FCRGL_Node FCRGL_Node::CreatePointsFormat(const rgl_field_t* fields, size_t count)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_points_format(r.GetHandlePtr(), fields, count));
	return r;
}

FCRGL_Node FCRGL_Node::CreatePointsYield(const rgl_field_t* fields, size_t count)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_points_yield(r.GetHandlePtr(), fields, count));
	return r;
}

FCRGL_Node FCRGL_Node::CreatePointsCompact()
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_points_compact(r.GetHandlePtr()));
	return r;
}

FCRGL_Node FCRGL_Node::CreatePointsCompactByField(rgl_field_t field)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_points_compact_by_field(r.GetHandlePtr(), field));
	return r;
}

FCRGL_Node FCRGL_Node::CreatePointsSpatialMerge(const rgl_field_t* fields, size_t count)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_points_spatial_merge(r.GetHandlePtr(), fields, count));
	return r;
}

FCRGL_Node FCRGL_Node::CreatePointsTemporalMerge(const rgl_field_t* fields, size_t count)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_points_temporal_merge(r.GetHandlePtr(), fields, count));
	return r;
}

FCRGL_Node FCRGL_Node::CreatePointsFromArray(
	const void* points,
	size_t point_count,
	const rgl_field_t* fields,
	size_t field_count)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_points_from_array(r.GetHandlePtr(), points, point_count, fields, field_count));
	return r;
}

FCRGL_Node FCRGL_Node::CreatePointsRadarPostProcess(
	const rgl_radar_scope_t* radar_scopes,
	int32_t radar_scopes_count,
	float ray_azimuth_step,
	float ray_elevation_step,
	float frequency,
	float power_transmitted,
	float cumulative_device_gain,
	float received_noise_mean,
	float received_noise_st_dev)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_points_radar_postprocess(
		r.GetHandlePtr(),
		radar_scopes,
		radar_scopes_count,
		ray_azimuth_step,
		ray_elevation_step,
		frequency,
		power_transmitted,
		cumulative_device_gain,
		received_noise_mean,
		received_noise_st_dev));
	return r;
}

FCRGL_Node FCRGL_Node::CreatePointsFilterGround(
	const rgl_vec3f& sensor_up_vector,
	float ground_angle_threshold)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_points_filter_ground(
		r.GetHandlePtr(),
		&sensor_up_vector,
		ground_angle_threshold));
	return r;
}

FCRGL_Node FCRGL_Node::CreateGaussianNoiseAngularRay(
	float mean,
	float std_dev,
	rgl_axis_t axis)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_gaussian_noise_angular_ray(
		r.GetHandlePtr(),
		mean,
		std_dev,
		axis));
	return r;
}

FCRGL_Node FCRGL_Node::CreateGaussianNoiseAngularHitPoint(
	float mean,
	float std_dev,
	rgl_axis_t axis)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_gaussian_noise_angular_hitpoint(
		r.GetHandlePtr(),
		mean,
		std_dev,
		axis));
	return r;
}

FCRGL_Node FCRGL_Node::CreateGaussianNoiseDistance(
	float mean,
	float std_dev,
	float std_dev_rise_per_meter)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_gaussian_noise_distance(
		r.GetHandlePtr(),
		mean,
		std_dev,
		std_dev_rise_per_meter));
	return r;
}

FCRGL_Node FCRGL_Node::CreateRayTrace(
	FCRGL_Scene& scene)
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_raytrace(r.GetHandlePtr(), scene.GetHandle()));
	return r;
}

FCRGL_Node FCRGL_Node::CreateRayTrace()
{
	FCRGL_Node r = { };
	CheckRGLResult(rgl_node_raytrace(r.GetHandlePtr(), nullptr));
	return r;
}




void FCRGL_Node::SetRayTransforms(
	const rgl_mat3x4f& transform)
{
	CheckRGLResult(rgl_node_rays_transform(GetHandlePtr(), &transform));
}

void FCRGL_Node::SetRayTransforms(
	const FTransform& transform)
{
	return SetRayTransforms(ToRGLTransform(transform));
}

void FCRGL_Node::SetRayRingIDs(
	const int32_t* ids,
	size_t count)
{
	CheckRGLResult(rgl_node_rays_set_ring_ids(GetHandlePtr(), ids, count));
}

void FCRGL_Node::SetRayFromMat3x4F(
	const rgl_mat3x4f* transforms,
	size_t count)
{
	CheckRGLResult(rgl_node_rays_from_mat3x4f(GetHandlePtr(), transforms, count));
}

void FCRGL_Node::SetRayRange(
	const rgl_vec2f* ranges,
	size_t count)
{
	CheckRGLResult(rgl_node_rays_set_range(GetHandlePtr(), ranges, count));
}

void FCRGL_Node::SetRayTimeOffsets(
	const float* offsets,
	size_t count)
{
	CheckRGLResult(rgl_node_rays_set_time_offsets(GetHandlePtr(), offsets, count));
}

void FCRGL_Node::SetPointsTransform(
	const rgl_mat3x4f& transform)
{
	CheckRGLResult(rgl_node_points_transform(GetHandlePtr(), &transform));
}

void FCRGL_Node::SetPointsFormat(
	const rgl_field_t* fields,
	size_t count)
{
	CheckRGLResult(rgl_node_points_format(GetHandlePtr(), fields, count));
}

void FCRGL_Node::SetPointsYield(
	const rgl_field_t* fields,
	size_t count)
{
	CheckRGLResult(rgl_node_points_yield(GetHandlePtr(), fields, count));
}

void FCRGL_Node::SetPointsCompactByField(
	rgl_field_t field)
{
	CheckRGLResult(rgl_node_points_compact_by_field(GetHandlePtr(), field));
}

void FCRGL_Node::SetPointsSpatialMerge(
	const rgl_field_t* fields,
	size_t count)
{
	CheckRGLResult(rgl_node_points_spatial_merge(GetHandlePtr(), fields, count));
}

void FCRGL_Node::SetPointsTemporalMerge(
	const rgl_field_t* fields,
	size_t count)
{
	CheckRGLResult(rgl_node_points_temporal_merge(GetHandlePtr(), fields, count));
}

void FCRGL_Node::SetPointsFromArray(
	const void* points,
	size_t point_count,
	const rgl_field_t* fields,
	size_t field_count)
{
	CheckRGLResult(rgl_node_points_from_array(GetHandlePtr(), points, point_count, fields, field_count));
}

void FCRGL_Node::SetPointsRadarPostProcess(
	const rgl_radar_scope_t* radar_scopes,
	int32_t radar_scopes_count,
	float ray_azimuth_step,
	float ray_elevation_step,
	float frequency,
	float power_transmitted,
	float cumulative_device_gain,
	float received_noise_mean,
	float received_noise_st_dev)
{
	CheckRGLResult(rgl_node_points_radar_postprocess(
		GetHandlePtr(),
		radar_scopes,
		radar_scopes_count,
		ray_azimuth_step,
		ray_elevation_step,
		frequency,
		power_transmitted,
		cumulative_device_gain,
		received_noise_mean,
		received_noise_st_dev));
}

void FCRGL_Node::SetPointsFilterGround(
	const rgl_vec3f& sensor_up_vector,
	float ground_angle_threshold)
{
	CheckRGLResult(rgl_node_points_filter_ground(
		GetHandlePtr(),
		&sensor_up_vector,
		ground_angle_threshold));
}

void FCRGL_Node::SetGaussianNoiseAngularRay(
	float mean,
	float std_dev,
	rgl_axis_t axis)
{
	CheckRGLResult(rgl_node_gaussian_noise_angular_ray(
		GetHandlePtr(),
		mean,
		std_dev,
		axis));
}

void FCRGL_Node::SetGaussianNoiseAngularHitPoint(
	float mean,
	float std_dev,
	rgl_axis_t axis)
{
	CheckRGLResult(rgl_node_gaussian_noise_angular_hitpoint(
		GetHandlePtr(),
		mean,
		std_dev,
		axis));
}

void FCRGL_Node::SetGaussianNoiseDistance(
	float mean,
	float std_dev,
	float std_dev_rise_per_meter)
{
	CheckRGLResult(rgl_node_gaussian_noise_distance(
		GetHandlePtr(),
		mean,
		std_dev,
		std_dev_rise_per_meter));
}



ACRGL_Node::ACRGL_Node(const FObjectInitializer& Initializer)
{
}
