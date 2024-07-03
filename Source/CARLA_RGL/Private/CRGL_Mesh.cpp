#include "CRGL_Mesh.h"

ACRGL_Mesh::ACRGL_Mesh(const FObjectInitializer& Initializer)
{
}

void FCRGL_Mesh::Initialize(
	const rgl_vec3f* vertices, int32_t vertex_count,
	const rgl_vec3i* indices, int32_t index_count)
{
	CheckRGLResult(rgl_mesh_create(
		&mesh,
		vertices, vertex_count,
		indices, index_count));
}

void FCRGL_Mesh::SetTextureUVs(const rgl_vec2f* uvs, int32_t count)
{
	CheckRGLResult(rgl_mesh_set_texture_coords(GetHandle(), uvs, count));
}

void FCRGL_Mesh::UpdateVertices(const rgl_vec3f* vertices, int32_t count)
{
	CheckRGLResult(rgl_mesh_update_vertices(GetHandle(), vertices, count));
}

bool FCRGL_Mesh::IsAlive()
{
	bool r = false;
	CheckRGLResult(rgl_mesh_is_alive(GetHandle(), &r));
	return r;
}
