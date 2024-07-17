#include "CRGL_Common.h"



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
		const auto mat = Transform.ToMatrixWithScale();
		const auto& m = mat.M;
		return
		{ {
			(float)m[0][0], (float)m[1][0], (float)m[2][0], (float)m[3][0],
			(float)m[0][1], (float)m[1][1], (float)m[2][1], (float)m[3][1],
			(float)m[0][2], (float)m[1][2], (float)m[2][2], (float)m[3][2]
		} };
	}

	rgl_vec3f ToRGLVector(const FVector3f& Vector)
	{
		auto x = Vector.X;
		auto y = Vector.Y;
		auto z = Vector.Z;
		return { { x, y, z} };
	}

	rgl_vec3i ToRGLVector(const FIntVector3& Vector)
	{
		auto x = Vector.X;
		auto y = Vector.Y;
		auto z = Vector.Z;
		return { { x, y, z} };
	}

	FTransform ToUETransform(const rgl_mat3x4f& Transform)
	{
		auto M = FMatrix::Identity;
		for (size_t i = 0; i != 3; ++i)
			for (size_t j = 0; j != 4; ++j)
				M.M[i][j] = Transform.value[i][j];
		return FTransform(M);
	}

	FVector3f ToUEVector(const rgl_vec3f& Vector)
	{
		auto [x, y, z] = Vector.value;
		return FVector3f(x, y, z);
	}

	FIntVector3 ToUEVector(const rgl_vec3i& Vector)
	{
		auto [x, y, z] = Vector.value;
		return FIntVector3(x, y, z);
	}
}