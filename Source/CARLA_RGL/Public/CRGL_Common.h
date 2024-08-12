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
	using Int3 = rgl_vec3i;
	using Float2 = rgl_vec2f;
	using Float3 = rgl_vec3f;
	using Float3x4 = rgl_mat3x4f;

	enum class EField : std::underlying_type_t<rgl_field_t>
	{
		XYZVec3F32 = RGL_FIELD_XYZ_VEC3_F32,
		IntensityF32 = RGL_FIELD_INTENSITY_F32,
		IsHitI32 = RGL_FIELD_IS_HIT_I32,
		IsGroundI32 = RGL_FIELD_IS_GROUND_I32,
		RayIdxU32 = RGL_FIELD_RAY_IDX_U32,
		EntityIdI32 = RGL_FIELD_ENTITY_ID_I32,
		DistanceF32 = RGL_FIELD_DISTANCE_F32,
		AzimuthF32 = RGL_FIELD_AZIMUTH_F32,
		ElevationF32 = RGL_FIELD_ELEVATION_F32,
		RingIdU16 = RGL_FIELD_RING_ID_U16,
		ReturnTypeU8 = RGL_FIELD_RETURN_TYPE_U8,
		TimeStampF64 = RGL_FIELD_TIME_STAMP_F64,
		AbsoluteVelocityVec3F32 = RGL_FIELD_ABSOLUTE_VELOCITY_VEC3_F32,
		RelativeVelocityVec3F32 = RGL_FIELD_RELATIVE_VELOCITY_VEC3_F32,
		RadialSpeedF32 = RGL_FIELD_RADIAL_SPEED_F32,
		PowerF32 = RGL_FIELD_POWER_F32,
		RCSF32 = RGL_FIELD_RCS_F32,
		NoiseF32 = RGL_FIELD_NOISE_F32,
		SNRF32 = RGL_FIELD_SNR_F32,
		NormalVec3F32 = RGL_FIELD_NORMAL_VEC3_F32,
		IncidentAngleF32 = RGL_FIELD_INCIDENT_ANGLE_F32,
		RayPoseMat3x4F32 = RGL_FIELD_RAY_POSE_MAT3x4_F32,
		LaserRetroF32 = RGL_FIELD_LASER_RETRO_F32,
		Padding8 = RGL_FIELD_PADDING_8,
		Padding16 = RGL_FIELD_PADDING_16,
		Padding32 = RGL_FIELD_PADDING_32,
		DynamicFormat = RGL_FIELD_DYNAMIC_FORMAT,
	};

	void CheckRGLResult(int32_t status);



	Float3x4 ToRGLTransform(
		const FTransform& Transform);

	rgl_vec3f ToRGLVector(
		const FVector& Vector);

	rgl_vec3f ToRGLVector(
		const FVector3f& Vector);

	rgl_vec3i ToRGLVector(
		const FIntVector3& Vector);

	FTransform ToUETransform(
		const Float3x4& Transform);

	FVector3f ToUEVector(
		const rgl_vec3f& Vector);

	FIntVector3 ToUEVector(
		const rgl_vec3i& Vector);



	template <typename T, auto Dtor>
	class CARLA_RGL_ENSURE_EBO FHandleMixin
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

		constexpr FHandleMixin() :
			handle()
		{
		}

		constexpr FHandleMixin(FHandleMixin&& other) noexcept :
			handle(other.handle)
		{
			other.handle = nullptr;
		}

		FHandleMixin& operator=(FHandleMixin&& other) noexcept
		{
			this->~FHandleMixin();
			new (this) FHandleMixin(std::move(other));
			return *this;
		}

		FHandleMixin(const FHandleMixin&) = delete;
		FHandleMixin& operator=(const FHandleMixin&) = delete;

		void Destroy()
		{
			if constexpr (Dtor != nullptr)
				Dtor(handle);
			handle = nullptr;
		}

		~FHandleMixin()
		{
			if (handle != nullptr)
				Destroy();
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
		using Type = Float3x4;
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
	using FFieldToType = typename FCRGLFieldToTypeHelper<Field>::Type;

}