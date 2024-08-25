#include "CRGL_Mesh.h"
#include "Engine/StaticMeshActor.h"
#include "Rendering/SkeletalMeshRenderData.h"
#include "Animation/SkeletalMeshActor.h"
#include "StaticMeshAttributes.h"
#include "StaticMeshResources.h"
#include "StaticMeshLODResourcesAdapter.h"
#include <vector>



namespace RGL
{
	static constexpr rgl_vec3f CubeVertices[] =
	{
		{ -1.0, -1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ 1.0,  1.0, -1.0 },
		{ -1.0,  1.0, -1.0 },
		{ -1.0, -1.0,  1.0 },
		{ 1.0, -1.0,  1.0 },
		{ 1.0,  1.0,  1.0 },
		{ -1.0,  1.0,  1.0 },
	};

	static constexpr rgl_vec3i CubeIndices[] =
	{
		{ 0, 3, 1 },
		{ 3, 2, 1 },
		{ 1, 2, 5 },
		{ 2, 6, 5 },
		{ 5, 6, 4 },
		{ 6, 7, 4 },
		{ 4, 7, 0 },
		{ 7, 3, 0 },
		{ 3, 7, 2 },
		{ 7, 6, 2 },
		{ 4, 0, 5 },
		{ 0, 1, 5 }
	};

	FMesh FMesh::CreateCube()
	{
		return Create(CubeVertices, CubeIndices);
	}

	FMesh FMesh::CreateCube(FTransform Transform)
	{
		rgl_vec3f Vertices[8];
		for (size_t i = 0; i != 8; ++i)
		{
			auto V = FVector(ToUEVector(CubeVertices[i]));
			V = Transform.TransformVector(V);
			Vertices[i] = ToRGLVector(FVector3f(V));
		}
		return Create(Vertices, CubeIndices);
	}

	FMesh FMesh::FromUEMesh(
		UStaticMesh* StaticMesh,
		uint32_t LODIndex)
	{
		check(StaticMesh);
		auto RenderData = StaticMesh->GetRenderData();

		check(RenderData);
		check(RenderData->LODResources.IsValidIndex(LODIndex));

		auto& LODResource = RenderData->LODResources[LODIndex];

		FStaticMeshLODResourcesMeshAdapter Adapter(&LODResource);

		std::vector<rgl_vec3f> Vertices(Adapter.VertexCount());
		std::vector<rgl_vec3i> Indices(Adapter.TriangleCount());

		for (size_t i = 0; i != Indices.size(); ++i)
			Indices[i] = ToRGLVector(Adapter.GetTriangle(i));

		for (size_t i = 0; i != Vertices.size(); ++i)
			Vertices[i] = ToRGLVector(FVector3f(Adapter.GetVertex(i)));

		return FMesh::Create(Vertices, Indices);
	}

	FMesh FMesh::FromStaticMeshActor(
		AStaticMeshActor* StaticMeshActor,
		uint32_t LODIndex)
	{
		auto SMC = StaticMeshActor->GetStaticMeshComponent();
		check(SMC);
		auto SM = SMC->GetStaticMesh();
		check(SM);
		return FromUEMesh(SM, LODIndex);
	}

	FMesh FMesh::FromSkeletalMeshActor(
		ASkeletalMeshActor* SkeletalMeshActor,
		uint32_t LODIndex)
	{
		auto SMC = SkeletalMeshActor->GetSkeletalMeshComponent();
		check(SMC);
		auto RenderData = SMC->GetSkeletalMeshRenderData();
		check(RenderData);
		auto& LOD = RenderData->LODRenderData[LODIndex];
		auto VertexCount = LOD.GetNumVertices();
		return FMesh();
	}

	FMesh FMesh::Create(
		std::span<const rgl_vec3f> vertices,
		std::span<const rgl_vec3i> indices)
	{
		return Create(
			vertices.data(),
			vertices.size(),
			indices.data(),
			indices.size());
	}

	FMesh FMesh::Create(
		const rgl_vec3f* vertices,
		int32_t vertex_count,
		const rgl_vec3i* indices,
		int32_t index_count)
	{
		FMesh r = { };
		CheckRGLResult(rgl_mesh_create(
			r.GetHandlePtr(),
			vertices, vertex_count,
			indices, index_count));
		return r;
	}

	void FMesh::SetTextureUVs(const rgl_vec2f* uvs, int32_t count)
	{
		CheckRGLResult(rgl_mesh_set_texture_coords(
			GetHandle(),
			uvs,
			count));
	}

	void FMesh::UpdateVertices(const rgl_vec3f* vertices, int32_t count)
	{
		CheckRGLResult(rgl_mesh_update_vertices(
			GetHandle(),
			vertices,
			count));
	}

	bool FMesh::IsAlive()
	{
		bool r = false;
		if (GetHandle() == nullptr)
			return false;
		CheckRGLResult(rgl_mesh_is_alive(
			GetHandle(),
			&r));
		return r;
	}
}