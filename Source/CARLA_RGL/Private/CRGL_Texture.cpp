#include "CRGL_Texture.h"

ACRGL_Texture::ACRGL_Texture(const FObjectInitializer& Initializer)
{
}

void ACRGL_Texture::Initialize(const void* Data, int32_t Width, int32_t Height)
{
	CheckRGLResult(rgl_texture_create(&texture, Data, Width, Height));
}
