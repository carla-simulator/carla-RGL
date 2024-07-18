#include "CRGL_Scene.h"



namespace RGL
{
	void FScene::SetTime(uint64_t nanoseconds)
	{
		CheckRGLResult(rgl_scene_set_time(GetHandle(), nanoseconds));
	}

	void FScene::SetTime(std::chrono::nanoseconds nanoseconds)
	{
		SetTime(nanoseconds.count());
	}
}