#include "CRGL_Node.h"
#include "CRGL_Scene.h"



namespace RGL
{
	bool FNode::IsAlive() const
	{
		bool result;
		if (GetHandle() == nullptr)
			return false;
		CheckRGLResult(rgl_node_is_alive(GetHandle(), &result));
		return result;
	}

	FNode FNode::CreateRayTransforms(const rgl_mat3x4f& transform)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_rays_transform(r.GetHandlePtr(), &transform));
		return r;
	}

	FNode FNode::CreateRayTransforms(const FTransform& transform)
	{
		return CreateRayTransforms(ToRGLTransform(transform));
	}

	FNode FNode::CreateRayRingIDs(const int32_t* ids, size_t count)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_rays_set_ring_ids(r.GetHandlePtr(), ids, count));
		return r;
	}

	FNode FNode::CreateRaysFromMat3x4F(const rgl_mat3x4f* transforms, size_t count)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_rays_from_mat3x4f(r.GetHandlePtr(), transforms, count));
		return r;
	}

	FNode FNode::CreateRayRange(const rgl_vec2f* ranges, size_t count)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_rays_set_range(r.GetHandlePtr(), ranges, count));
		return r;
	}

	FNode FNode::CreateRayTimeOffsets(const float* offsets, size_t count)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_rays_set_time_offsets(r.GetHandlePtr(), offsets, count));
		return r;
	}

	FNode FNode::CreatePointsTransform(const rgl_mat3x4f& transform)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_points_transform(r.GetHandlePtr(), &transform));
		return r;
	}

	FNode FNode::CreatePointsFormat(const rgl_field_t* fields, size_t count)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_points_format(r.GetHandlePtr(), fields, count));
		return r;
	}

	FNode FNode::CreatePointsYield(const rgl_field_t* fields, size_t count)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_points_yield(r.GetHandlePtr(), fields, count));
		return r;
	}

	FNode FNode::CreatePointsCompactByField(rgl_field_t field)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_points_compact_by_field(r.GetHandlePtr(), field));
		return r;
	}

	FNode FNode::CreatePointsSpatialMerge(const rgl_field_t* fields, size_t count)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_points_spatial_merge(r.GetHandlePtr(), fields, count));
		return r;
	}

	FNode FNode::CreatePointsTemporalMerge(const rgl_field_t* fields, size_t count)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_points_temporal_merge(r.GetHandlePtr(), fields, count));
		return r;
	}

	FNode FNode::CreatePointsFromArray(
		const void* points,
		size_t point_count,
		const rgl_field_t* fields,
		size_t field_count)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_points_from_array(r.GetHandlePtr(), points, point_count, fields, field_count));
		return r;
	}

	FNode FNode::CreatePointsRadarPostProcess(
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
		FNode r = { };
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

	FNode FNode::CreatePointsFilterGround(
		const rgl_vec3f& sensor_up_vector,
		float ground_angle_threshold)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_points_filter_ground(
			r.GetHandlePtr(),
			&sensor_up_vector,
			ground_angle_threshold));
		return r;
	}

	FNode FNode::CreateGaussianNoiseAngularRay(
		float mean,
		float std_dev,
		rgl_axis_t axis)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_gaussian_noise_angular_ray(
			r.GetHandlePtr(),
			mean,
			std_dev,
			axis));
		return r;
	}

	FNode FNode::CreateGaussianNoiseAngularHitPoint(
		float mean,
		float std_dev,
		rgl_axis_t axis)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_gaussian_noise_angular_hitpoint(
			r.GetHandlePtr(),
			mean,
			std_dev,
			axis));
		return r;
	}

	FNode FNode::CreateGaussianNoiseDistance(
		float mean,
		float std_dev,
		float std_dev_rise_per_meter)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_gaussian_noise_distance(
			r.GetHandlePtr(),
			mean,
			std_dev,
			std_dev_rise_per_meter));
		return r;
	}

	FNode FNode::CreateRayTrace(
		FScene& scene)
	{
		FNode r = { };
		CheckRGLResult(rgl_node_raytrace(r.GetHandlePtr(), scene.GetHandle()));
		return r;
	}

	FNode FNode::CreateRayTrace()
	{
		FNode r = { };
		CheckRGLResult(rgl_node_raytrace(r.GetHandlePtr(), nullptr));
		return r;
	}

	void FNode::SetRayTransforms(
		const rgl_mat3x4f& transform)
	{
		CheckRGLResult(rgl_node_rays_transform(GetHandlePtr(), &transform));
	}

	void FNode::SetRayTransforms(
		const FTransform& transform)
	{
		return SetRayTransforms(ToRGLTransform(transform));
	}

	void FNode::SetRayRingIDs(
		const int32_t* ids,
		size_t count)
	{
		CheckRGLResult(rgl_node_rays_set_ring_ids(GetHandlePtr(), ids, count));
	}

	void FNode::SetRaysFromMat3x4F(
		const rgl_mat3x4f* transforms,
		size_t count)
	{
		CheckRGLResult(rgl_node_rays_from_mat3x4f(GetHandlePtr(), transforms, count));
	}

	void FNode::SetRayRange(
		const rgl_vec2f* ranges,
		size_t count)
	{
		CheckRGLResult(rgl_node_rays_set_range(GetHandlePtr(), ranges, count));
	}

	void FNode::SetRayTimeOffsets(
		const float* offsets,
		size_t count)
	{
		CheckRGLResult(rgl_node_rays_set_time_offsets(GetHandlePtr(), offsets, count));
	}

	void FNode::SetPointsTransform(
		const rgl_mat3x4f& transform)
	{
		CheckRGLResult(rgl_node_points_transform(GetHandlePtr(), &transform));
	}

	void FNode::SetPointsFormat(
		const rgl_field_t* fields,
		size_t count)
	{
		CheckRGLResult(rgl_node_points_format(GetHandlePtr(), fields, count));
	}

	void FNode::SetPointsYield(
		const rgl_field_t* fields,
		size_t count)
	{
		CheckRGLResult(rgl_node_points_yield(GetHandlePtr(), fields, count));
	}

	void FNode::SetPointsCompactByField(
		rgl_field_t field)
	{
		CheckRGLResult(rgl_node_points_compact_by_field(GetHandlePtr(), field));
	}

	void FNode::SetPointsSpatialMerge(
		const rgl_field_t* fields,
		size_t count)
	{
		CheckRGLResult(rgl_node_points_spatial_merge(GetHandlePtr(), fields, count));
	}

	void FNode::SetPointsTemporalMerge(
		const rgl_field_t* fields,
		size_t count)
	{
		CheckRGLResult(rgl_node_points_temporal_merge(GetHandlePtr(), fields, count));
	}

	void FNode::SetPointsFromArray(
		const void* points,
		size_t point_count,
		const rgl_field_t* fields,
		size_t field_count)
	{
		CheckRGLResult(rgl_node_points_from_array(GetHandlePtr(), points, point_count, fields, field_count));
	}

	void FNode::SetPointsRadarPostProcess(
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

	void FNode::SetPointsFilterGround(
		const rgl_vec3f& sensor_up_vector,
		float ground_angle_threshold)
	{
		CheckRGLResult(rgl_node_points_filter_ground(
			GetHandlePtr(),
			&sensor_up_vector,
			ground_angle_threshold));
	}

	void FNode::SetGaussianNoiseAngularRay(
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

	void FNode::SetGaussianNoiseAngularHitPoint(
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

	void FNode::SetGaussianNoiseDistance(
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

	void FNode::SetRayTrace(FScene& scene)
	{
		CheckRGLResult(rgl_node_raytrace(
			GetHandlePtr(),
			scene.GetHandle()));
	}

	void FNode::SetRayTrace()
	{
		CheckRGLResult(rgl_node_raytrace(
			GetHandlePtr(),
			nullptr));
	}

	void FNode::AddChild(const FNode& child)
	{
		CheckRGLResult(
			rgl_graph_node_add_child(
				GetHandle(),
				child.GetHandle()));
	}

	void FNode::RemoveChild(const FNode& child)
	{
		CheckRGLResult(
			rgl_graph_node_remove_child(
				GetHandle(),
				child.GetHandle()));
	}
}