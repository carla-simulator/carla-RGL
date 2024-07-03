#include "CRGL_Entity.h"
#include "CRGL_Texture.h"
#include "CRGL_Scene.h"
#include "CRGL_Mesh.h"

ACRGL_Entity::ACRGL_Entity(const FObjectInitializer& Initializer)
{
}

void FCRGL_Entity::Initialize(const ACRGL_Scene& Scene, const ACRGL_Mesh& Mesh)
{
	CheckRGLResult(rgl_entity_create(
		&GetHandleRef(),
		Scene.GetHandle(),
		Mesh.GetHandle()));
}

void FCRGL_Entity::SetPose(const FTransform& Transform)
{
	rgl_mat3x4f transform;
	CheckRGLResult(rgl_entity_set_pose(GetHandle(), &transform));
}

void FCRGL_Entity::SetID(int32_t ID)
{
	CheckRGLResult(rgl_entity_set_id(GetHandle(), ID));
}

void FCRGL_Entity::SetIntensityTexture(const ACRGL_Texture& Texture)
{
	CheckRGLResult(rgl_entity_set_intensity_texture(GetHandle(), Texture.GetHandle()));
}

void FCRGL_Entity::SetLaserRetro(float Retro)
{
	CheckRGLResult(rgl_entity_set_laser_retro(GetHandle(), Retro));
}

bool FCRGL_Entity::IsAlive()
{
	bool r = false;
	CheckRGLResult(rgl_entity_is_alive(GetHandle(), &r));
	return r;
}
