#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include <chrono>



namespace RGL
{
	class CARLA_RGL_API FScene :
		public FHandleMixin<rgl_scene_t, nullptr>
	{
	public:

		void SetTime(uint64_t nanoseconds);
		void SetTime(std::chrono::nanoseconds nanoseconds);

	};
}