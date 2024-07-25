#include "CRGL_Common.h"
#pragma optimize("", off)


namespace RGL
{
	void CheckRGLResult(int32_t status)
	{
		if (status == RGL_SUCCESS)
			return;
		const TCHAR* error;
		switch (status)
		{
		case RGL_INVALID_ARGUMENT:
			error = TEXT("RGL_INVALID_ARGUMENT");
			break;
		case RGL_INVALID_STATE:
			error = TEXT("RGL_INVALID_STATE");
			break;
		case RGL_LOGGING_ERROR:
			error = TEXT("RGL_LOGGING_ERROR");
			break;
		case RGL_INVALID_API_OBJECT:
			error = TEXT("RGL_INVALID_API_OBJECT");
			break;
		case RGL_INVALID_FILE_PATH:
			error = TEXT("RGL_INVALID_FILE_PATH");
			break;
		case RGL_TAPE_ERROR:
			error = TEXT("RGL_TAPE_ERROR");
			break;
		case RGL_UDP_ERROR:
			error = TEXT("RGL_UDP_ERROR");
			break;
		case RGL_ROS2_ERROR:
			error = TEXT("RGL_ROS2_ERROR");
			break;
		case RGL_INVALID_PIPELINE:
			error = TEXT("RGL_INVALID_PIPELINE");
			break;
		case RGL_INITIALIZATION_ERROR:
			error = TEXT("RGL_INITIALIZATION_ERROR");
			break;
		case RGL_NOT_IMPLEMENTED:
			error = TEXT("RGL_NOT_IMPLEMENTED");
			break;
		case RGL_INTERNAL_EXCEPTION:
			error = TEXT("RGL_INTERNAL_EXCEPTION");
			break;
		default:
			error = TEXT("");
			break;
		}

		const char* error_string = "";
		rgl_get_last_error_string(&error_string);
		FString error_string_temp = error_string;

		UE_LOG(
			LogCarlaRGL,
			Log,
			TEXT("Encountered Robotec GPU Lidar error \"%s\": %s"),
			error,
			*error_string_temp);
		check(false);
	}



	rgl_mat3x4f ToRGLTransform(
		const FTransform& Transform)
	{
		rgl_mat3x4f r = { };
		const auto mat = Transform.ToMatrixWithScale();
		const auto& m = mat.M;
		for (size_t i = 0; i != 3; ++i)
			for (size_t j = 0; j != 4; ++j)
				r.value[i][j] = m[j][i];
		return r;
	}

	rgl_vec3f ToRGLVector(const FVector& Vector)
	{
		return ToRGLVector(FVector3f(Vector));
	}

	rgl_vec3f ToRGLVector(const FVector3f& Vector)
	{
		const auto x = Vector.X;
		const auto y = Vector.Y;
		const auto z = Vector.Z;
		return { { x, y, z } };
	}

	rgl_vec3i ToRGLVector(const FIntVector3& Vector)
	{
		const auto x = Vector.X;
		const auto y = Vector.Y;
		const auto z = Vector.Z;
		return { { x, y, z } };
	}

	FTransform ToUETransform(const rgl_mat3x4f& Transform)
	{
		auto M = FMatrix::Identity;
		for (size_t i = 0; i != 3; ++i)
			for (size_t j = 0; j != 4; ++j)
				M.M[j][i] = Transform.value[i][j];
		return FTransform(M);
	}

	FVector3f ToUEVector(const rgl_vec3f& Vector)
	{
		const auto [x, y, z] = Vector.value;
		return FVector3f(x, y, z);
	}

	FIntVector3 ToUEVector(const rgl_vec3i& Vector)
	{
		const auto [x, y, z] = Vector.value;
		return FIntVector3(x, y, z);
	}
}

#pragma optimize("", on)