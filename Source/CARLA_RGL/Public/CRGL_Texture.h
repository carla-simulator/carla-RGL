#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"



namespace RGL
{
	class CARLA_RGL_API FTexture :
		public FRGLHandleMixin<rgl_texture_t, rgl_texture_destroy>
	{
	public:
	};
}