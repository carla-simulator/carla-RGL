#include "CRGL_Entity.h"
#include "CRGL_Texture.h"
#include "CRGL_Scene.h"
#include "CRGL_Mesh.h"



namespace RGL
{
	FEntity FEntity::Create(const FMesh& Mesh)
	{
		FEntity r = { };
		CheckRGLResult(rgl_entity_create(
			r.GetHandlePtr(),
			nullptr,
			Mesh.GetHandle()));
		return r;
	}

	FEntity FEntity::Create(
		const FScene& Scene,
		const FMesh& Mesh)
	{
		FEntity r = { };
		CheckRGLResult(rgl_entity_create(
			r.GetHandlePtr(),
			Scene.GetHandle(),
			Mesh.GetHandle()));
		return r;
	}

	void FEntity::SetPose(const rgl_mat3x4f& Transform)
	{
		CheckRGLResult(rgl_entity_set_pose(
			GetHandle(),
			&Transform));
	}

	void FEntity::SetPose(const FTransform& Transform)
	{
		auto M3x4 = ToRGLTransform(Transform);
		SetPose(M3x4);
	}

	void FEntity::SetID(int32_t ID)
	{
		CheckRGLResult(rgl_entity_set_id(GetHandle(), ID));
	}

	void FEntity::SetIntensityTexture(const FTexture& FTexture)
	{
#if 0
		CheckRGLResult(rgl_entity_set_intensity_texture(
			GetHandle(),
			FTexture.GetHandle()));
#else
		check(false);
#endif
	}

	void FEntity::SetLaserRetro(float Retro)
	{
		CheckRGLResult(rgl_entity_set_laser_retro(GetHandle(), Retro));
	}

	bool FEntity::IsAlive()
	{
		bool r = false;
		if (GetHandle() == nullptr)
			return false;
		CheckRGLResult(rgl_entity_is_alive(GetHandle(), &r));
		return r;
	}
}