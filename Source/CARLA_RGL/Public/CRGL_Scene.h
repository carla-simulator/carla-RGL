#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"



namespace RGL
{
	class CARLA_RGL_API FScene :
		public FRGLHandleMixin<rgl_scene_t, nullptr>
	{
	public:

		void SetTime(uint64_t nanoseconds);

	};
}