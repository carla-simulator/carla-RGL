#pragma once
#include "rgl/api/core.h"



DECLARE_LOG_CATEGORY_EXTERN(LogCarlaRGL, Log, Log);



#ifdef _WIN32
#define CARLA_RGL_ENSURE_EBO __declspec(empty_bases)
#else
#define CARLA_RGL_ENSURE_EBO
#endif



namespace RGL
{

	void CheckRGLResult(int32_t status);



	rgl_mat3x4f ToRGLTransform(
		const FTransform& Transform);

	rgl_vec3f ToRGLVector(
		const FVector3f& Vector);

	rgl_vec3i ToRGLVector(
		const FIntVector3& Vector);

	FTransform ToUETransform(
		const rgl_mat3x4f& Transform);

	FVector3f ToUEVector(
		const rgl_vec3f& Vector);

	FIntVector3 ToUEVector(
		const rgl_vec3i& Vector);



	template <typename T, auto Dtor>
	class CARLA_RGL_ENSURE_EBO FRGLHandleMixin
	{
		T handle;
	public:

		constexpr bool IsValid() const
		{
			return GetHandle() != nullptr;
		}

		constexpr auto GetHandle() const
		{
			return handle;
		}

		constexpr FRGLHandleMixin() :
			handle()
		{
		}

		constexpr FRGLHandleMixin(FRGLHandleMixin&& other) noexcept :
			handle(other.handle)
		{
			other.handle = nullptr;
		}

		FRGLHandleMixin& operator=(FRGLHandleMixin&& other) noexcept
		{
			this->~FRGLHandleMixin();
			new (this) FRGLHandleMixin(std::move(other));
			return *this;
		}

		FRGLHandleMixin(const FRGLHandleMixin&) = delete;
		FRGLHandleMixin& operator=(const FRGLHandleMixin&) = delete;

		~FRGLHandleMixin()
		{
			if constexpr (Dtor != nullptr)
			{
				if (handle)
				{
					Dtor(handle);
					handle = nullptr;
				}
			}
		}

	protected:

		constexpr auto GetHandlePtr()
		{
			return &handle;
		}

		constexpr auto GetHandlePtr() const
		{
			return &handle;
		}
	};



	template <rgl_field_t>
	struct FCRGLFieldToTypeHelper;

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_XYZ_VEC3_F32>
	{
		using Type = FVector3f;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_INTENSITY_F32>
	{
		using Type = float;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_IS_HIT_I32>
	{
		using Type = int32;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_IS_GROUND_I32>
	{
		using Type = int32;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_RAY_IDX_U32>
	{
		using Type = uint32;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_ENTITY_ID_I32>
	{
		using Type = int32;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_DISTANCE_F32>
	{
		using Type = float;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_AZIMUTH_F32>
	{
		using Type = float;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_ELEVATION_F32>
	{
		using Type = float;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_RING_ID_U16>
	{
		using Type = int16;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_RETURN_TYPE_U8>
	{
		using Type = uint8;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_TIME_STAMP_F64>
	{
		using Type = double;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_ABSOLUTE_VELOCITY_VEC3_F32>
	{
		using Type = FVector3f;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_RELATIVE_VELOCITY_VEC3_F32>
	{
		using Type = FVector3f;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_RADIAL_SPEED_F32>
	{
		using Type = float;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_POWER_F32>
	{
		using Type = float;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_RCS_F32>
	{
		using Type = float;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_NOISE_F32>
	{
		using Type = float;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_SNR_F32>
	{
		using Type = float;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_NORMAL_VEC3_F32>
	{
		using Type = float;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_INCIDENT_ANGLE_F32>
	{
		using Type = float;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_RAY_POSE_MAT3x4_F32>
	{
		using Type = rgl_mat3x4f;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_LASER_RETRO_F32>
	{
		using Type = float;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_PADDING_8>
	{
		using Type = uint8;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_PADDING_16>
	{
		using Type = uint16;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_PADDING_32>
	{
		using Type = uint32;
	};

	template <>
	struct FCRGLFieldToTypeHelper<RGL_FIELD_DYNAMIC_FORMAT>
	{
		using Type = uint8;
	};

	template <rgl_field_t Field>
	using FCRGLFieldToType = typename FCRGLFieldToTypeHelper<Field>::Type;

}