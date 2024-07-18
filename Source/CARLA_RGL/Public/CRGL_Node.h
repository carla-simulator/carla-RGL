#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include <span>



namespace RGL
{
	class CARLA_RGL_API FNode :
		public FHandleMixin<rgl_node_t, nullptr>
	{
	public:

		bool IsAlive() const;



		static FNode CreateRayTransforms(
			const rgl_mat3x4f& transform);



		static FNode CreateRayTransforms(
			const FTransform& transform);



		static FNode CreateRayRingIDs(
			const int32_t* ids,
			size_t count);

		inline static FNode CreateRayRingIDs(
			std::span<const int32_t> ids)
		{
			return CreateRayRingIDs(ids.data(), ids.size());
		}



		static FNode CreateRaysFromMat3x4F(
			const rgl_mat3x4f* transforms,
			size_t count);

		inline static FNode CreateRaysFromMat3x4F(
			std::span<const rgl_mat3x4f> transforms)
		{
			return CreateRaysFromMat3x4F(transforms.data(), transforms.size());
		}



		static FNode CreateRayRange(
			const rgl_vec2f* ranges,
			size_t count);

		inline static FNode CreateRayRange(
			std::span<const rgl_vec2f> ranges)
		{
			return CreateRayRange(ranges.data(), ranges.size());
		}



		static FNode CreateRayTimeOffsets(
			const float* offsets,
			size_t count);

		inline static FNode CreateRayTimeOffsets(
			std::span<const float> offsets)
		{
			return CreateRayTimeOffsets(offsets.data(), offsets.size());
		}



		static FNode CreatePointsTransform(
			const rgl_mat3x4f& transform);



		static FNode CreatePointsFormat(
			const rgl_field_t* fields,
			size_t count);

		inline static FNode CreatePointsFormat(
			std::span<const rgl_field_t> fields)
		{
			return CreatePointsFormat(fields.data(), fields.size());
		}



		static FNode CreatePointsYield(
			const rgl_field_t* fields,
			size_t count);

		inline static FNode CreatePointsYield(
			std::span<const rgl_field_t> fields)
		{
			return CreatePointsYield(fields.data(), fields.size());
		}



		static FNode CreatePointsCompactByField(
			rgl_field_t field);



		static FNode CreatePointsSpatialMerge(
			const rgl_field_t* fields,
			size_t count);

		inline static FNode CreatePointsSpatialMerge(
			std::span<const rgl_field_t> fields)
		{
			return CreatePointsSpatialMerge(fields.data(), fields.size());
		}



		static FNode CreatePointsTemporalMerge(
			const rgl_field_t* fields,
			size_t count);

		inline static FNode CreatePointsTemporalMerge(
			std::span<const rgl_field_t> fields)
		{
			return CreatePointsTemporalMerge(fields.data(), fields.size());
		}



		static FNode CreatePointsFromArray(
			const void* points,
			size_t point_count,
			const rgl_field_t* fields,
			size_t field_count);

		static FNode CreatePointsRadarPostProcess(
			const rgl_radar_scope_t* radar_scopes,
			int32_t radar_scopes_count,
			float ray_azimuth_step,
			float ray_elevation_step,
			float frequency,
			float power_transmitted,
			float cumulative_device_gain,
			float received_noise_mean,
			float received_noise_st_dev);

		static FNode CreatePointsFilterGround(
			const rgl_vec3f& sensor_up_vector,
			float ground_angle_threshold);

		static FNode CreateGaussianNoiseAngularRay(
			float mean,
			float std_dev,
			rgl_axis_t axis);

		static FNode CreateGaussianNoiseAngularHitPoint(
			float mean,
			float std_dev,
			rgl_axis_t axis);

		static FNode CreateGaussianNoiseDistance(
			float mean,
			float std_dev,
			float std_dev_rise_per_meter);

		static FNode CreateRayTrace(
			class FScene& scene);

		static FNode CreateRayTrace();



		void SetRayTransforms(
			const rgl_mat3x4f& transform);



		void SetRayTransforms(
			const FTransform& transform);



		void SetRayRingIDs(
			const int32_t* ids,
			size_t count);

		void SetRayRingIDs(
			std::span<const int32_t> ids)
		{
			SetRayRingIDs(ids.data(), ids.size());
		}



		void SetRaysFromMat3x4F(
			const rgl_mat3x4f* transforms,
			size_t count);

		void SetRaysFromMat3x4F(
			std::span<const rgl_mat3x4f> transforms)
		{
			SetRaysFromMat3x4F(transforms.data(), transforms.size());
		}



		void SetRayRange(
			const rgl_vec2f* ranges,
			size_t count);

		void SetRayRange(
			std::span<const rgl_vec2f> ranges)
		{
			SetRayRange(ranges.data(), ranges.size());
		}



		void SetRayTimeOffsets(
			const float* offsets,
			size_t count);

		void SetRayTimeOffsets(
			std::span<const float> offsets)
		{
			SetRayTimeOffsets(offsets.data(), offsets.size());
		}



		void SetPointsTransform(
			const rgl_mat3x4f& transform);



		void SetPointsFormat(
			const rgl_field_t* fields,
			size_t count);

		void SetPointsFormat(
			std::span<const rgl_field_t> fields)
		{
			SetPointsFormat(fields.data(), fields.size());
		}



		void SetPointsYield(
			const rgl_field_t* fields,
			size_t count);

		void SetPointsYield(
			std::span<const rgl_field_t> fields)
		{
			SetPointsYield(fields.data(), fields.size());
		}



		void SetPointsCompactByField(
			rgl_field_t field);



		void SetPointsSpatialMerge(
			const rgl_field_t* fields,
			size_t count);

		void SetPointsSpatialMerge(
			std::span<const rgl_field_t> fields)
		{
			SetPointsSpatialMerge(fields.data(), fields.size());
		}



		void SetPointsTemporalMerge(
			const rgl_field_t* fields,
			size_t count);

		void SetPointsTemporalMerge(
			std::span<const rgl_field_t> fields)
		{
			SetPointsTemporalMerge(fields.data(), fields.size());
		}



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



		void SetRayTrace(
			class FScene& scene);

		void SetRayTrace();



		void AddChild(const FNode& child);

		void RemoveChild(const FNode& child);

	};
}