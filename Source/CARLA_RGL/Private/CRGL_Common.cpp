#include "CRGL_Common.h"



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
	UE_LOG(
		LogCarlaRGL,
		Log,
		TEXT("Encountered Robotec GPU Lidar error: \"%s\""),
		error);
	check(false);
}



rgl_mat3x4f ToRGLTransform(
	const FTransform& Transform)
{
	rgl_mat3x4f r = { };
	const auto m = Transform.ToMatrixWithScale();
	for (int i = 0; i != 3; ++i)
		for (int j = 0; j != 4; ++j)
			r.value[i][j] = (float)m.M[i][j];
	return r;
}
