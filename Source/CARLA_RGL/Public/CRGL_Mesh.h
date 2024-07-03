#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include "CRGL_Mesh.generated.h"



class FCRGL_Mesh :
	public FCarlaRGLHandleMixin<rgl_mesh_t>
{
public:

	void Initialize(
		const rgl_vec3f* vertices, int32_t vertex_count,
		const rgl_vec3i* indices, int32_t index_count);
	void SetTextureUVs(const rgl_vec2f* uvs, int32_t count);
	void UpdateVertices(const rgl_vec3f* vertices, int32_t count);
	bool IsAlive();

	constexpr auto GetHandle()const { return mesh; }

private:
	rgl_mesh_t mesh;
};



UCLASS()
class ACRGL_Mesh :
	public AActor,
	public FCRGL_Mesh
{
	GENERATED_BODY()
public:
	ACRGL_Mesh(const FObjectInitializer& Initializer);
};
