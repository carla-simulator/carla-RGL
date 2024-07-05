#include "CRGL_Mesh.h"
#include <vector>

ACRGL_Mesh::ACRGL_Mesh(const FObjectInitializer& Initializer)
{
}

FCRGL_Mesh FCRGL_Mesh::FromUEMesh(
	UStaticMesh* mesh,
	uint32 lod_index)
{
	auto RenderData = mesh->GetRenderData();
	check(RenderData);
	auto& LODResource = RenderData->LODResources[lod_index];
	auto& VertexBuffers = LODResource.VertexBuffers;
	auto& PositionBuffer = VertexBuffers.PositionVertexBuffer;
	auto& IndexBuffer = LODResource.IndexBuffer;
	auto IndexCount = IndexBuffer.GetNumIndices();
	auto VertexCount = PositionBuffer.GetNumVertices();
	auto IndexBufferSize = IndexCount * sizeof(uint32);
	auto VertexBufferSize = VertexCount * sizeof(FVector3f);
	std::vector<rgl_vec3f> vertices(VertexCount);
	std::vector<rgl_vec3i> indices(IndexCount);
	for (size_t i = 0; i != indices.size() / 3; ++i)
		for (size_t j = 0; j != 3; ++j)
			vertices[i].value[j] = IndexBuffer.GetIndex(i * 3 + j);
	for (size_t i = 0; i != vertices.size(); ++i)
	{
		auto v = PositionBuffer.VertexPosition(i);
		for (size_t j = 0; j != 3; ++j)
			vertices[i].value[j] = v[j];
	}
	return FCRGL_Mesh::Create(
		vertices.data(),
		vertices.size(),
		indices.data(),
		indices.size());
}

FCRGL_Mesh FCRGL_Mesh::Create(
	std::span<const rgl_vec3f> vertices,
	std::span<const rgl_vec3i> indices)
{
	return Create(
		vertices.data(),
		vertices.size(),
		indices.data(),
		indices.size());
}

FCRGL_Mesh FCRGL_Mesh::Create(
	const rgl_vec3f* vertices,
	int32_t vertex_count,
	const rgl_vec3i* indices,
	int32_t index_count)
{
	FCRGL_Mesh r = { };
	CheckRGLResult(rgl_mesh_create(
		r.GetHandlePtr(),
		vertices, vertex_count,
		indices, index_count));
	return r;
}

void FCRGL_Mesh::SetTextureUVs(const rgl_vec2f* uvs, int32_t count)
{
	CheckRGLResult(rgl_mesh_set_texture_coords(
		GetHandle(),
		uvs,
		count));
}

void FCRGL_Mesh::UpdateVertices(const rgl_vec3f* vertices, int32_t count)
{
	CheckRGLResult(rgl_mesh_update_vertices(
		GetHandle(),
		vertices,
		count));
}

bool FCRGL_Mesh::IsAlive()
{
	bool r = false;
	CheckRGLResult(rgl_mesh_is_alive(
		GetHandle(),
		&r));
	return r;
}
