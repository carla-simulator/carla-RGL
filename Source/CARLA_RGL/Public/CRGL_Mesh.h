#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include <span>



class AStaticMeshActor;



class FCRGL_Mesh :
	public FCarlaRGLHandleMixin<rgl_mesh_t>
{
public:

	FCRGL_Mesh() = default;
	FCRGL_Mesh(FCRGL_Mesh&&) = default;
	FCRGL_Mesh& operator=(FCRGL_Mesh&&) = default;
	~FCRGL_Mesh();

	static FCRGL_Mesh CreateCube();

	static FCRGL_Mesh CreateCube(
		FTransform Transform);

	static FCRGL_Mesh FromUEMesh(
		UStaticMesh* mesh,
		uint32 lod_index = 0);

	static FCRGL_Mesh FromStaticMeshActor(
		AStaticMeshActor* mesh,
		uint32 lod_index = 0);

	static FCRGL_Mesh Create(
		std::span<const rgl_vec3f> vertices,
		std::span<const rgl_vec3i> indices);

	static FCRGL_Mesh Create(
		const rgl_vec3f* vertices, int32_t vertex_count,
		const rgl_vec3i* indices, int32_t index_count);

	static TArray<std::pair<FCRGL_Mesh, FTransform>> EnumerateStaticMeshes(UWorld* World);
	
	void SetTextureUVs(const rgl_vec2f* uvs, int32_t count);
	void UpdateVertices(const rgl_vec3f* vertices, int32_t count);
	bool IsAlive();
	void Destroy();

};