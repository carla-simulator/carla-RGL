#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include <span>
#include "CRGL_Mesh.generated.h"



class FCRGL_Mesh :
	public FCarlaRGLHandleMixin<rgl_mesh_t>
{
public:

	static FCRGL_Mesh FromUEMesh(
		UStaticMesh* mesh,
		uint32 lod_index = 0);

	static FCRGL_Mesh Create(
		std::span<const rgl_vec3f> vertices,
		std::span<const rgl_vec3i> indices);

	static FCRGL_Mesh Create(
		const rgl_vec3f* vertices, int32_t vertex_count,
		const rgl_vec3i* indices, int32_t index_count);
	
	void SetTextureUVs(const rgl_vec2f* uvs, int32_t count);
	void UpdateVertices(const rgl_vec3f* vertices, int32_t count);
	bool IsAlive();
};



UCLASS()
class ACRGL_Mesh :
	public AActor
{
	GENERATED_BODY()
public:
	ACRGL_Mesh(const FObjectInitializer& Initializer);
};
