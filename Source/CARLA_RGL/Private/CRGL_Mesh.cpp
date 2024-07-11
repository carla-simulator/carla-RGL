#include "CRGL_Mesh.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"
#include "StaticMeshAttributes.h"
#include "StaticMeshResources.h"
#include "RawMesh.h"
#include <vector>

static const rgl_vec3f CubeVertices[] =
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

FCRGL_Mesh::~FCRGL_Mesh()
{
	if (IsAlive())
		Destroy();
}

FCRGL_Mesh FCRGL_Mesh::CreateCube()
{
	return Create(CubeVertices, CubeIndices);
}

FCRGL_Mesh FCRGL_Mesh::CreateCube(FTransform Transform)
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

FCRGL_Mesh FCRGL_Mesh::FromUEMesh(
	UStaticMesh* Mesh,
	uint32 LODIndex)
{
	check(Mesh);
	auto RenderData = Mesh->GetRenderData();
	
	check(RenderData);
	check(RenderData->LODResources.IsValidIndex(LODIndex));
	
	auto& LODResource = RenderData->LODResources[LODIndex];
	auto& VertexBuffers = LODResource.VertexBuffers;
	auto& PositionBuffer = VertexBuffers.PositionVertexBuffer;
	auto& IndexBuffer = LODResource.IndexBuffer;

	check(PositionBuffer.IsInitialized());
	check(PositionBuffer.GetAllowCPUAccess());
	check(IndexBuffer.IsInitialized());
	check(IndexBuffer.GetAllowCPUAccess());

	auto IndexBufferView = IndexBuffer.GetArrayView();
	
	auto IndexCount = IndexBuffer.GetNumIndices();
	auto VertexCount = PositionBuffer.GetNumVertices();
	auto TriangleCount = Mesh->GetNumTriangles(LODIndex);
	
	std::vector<uint32> TriangleOffsets;
	std::vector<const FStaticMeshSection*> Sections;

	uint32 Offset = 0;
	TriangleOffsets.reserve(LODResource.Sections.Num());
	Sections.reserve(LODResource.Sections.Num());
	for (auto& Section : LODResource.Sections)
	{
		TriangleOffsets.push_back(Offset);
		Offset += Section.NumTriangles;
		Sections.push_back(&Section);
	}
	TriangleOffsets.push_back(TriangleCount);

	auto GetTriangleSection = [&](uint32& Index) -> const FStaticMeshSection&
	{
		auto ISection = std::upper_bound(
			TriangleOffsets.begin(),
			TriangleOffsets.end(),
			Index) - 1;
		auto SectionIndex = std::distance(TriangleOffsets.begin(), ISection);
		Index -= TriangleOffsets[SectionIndex];
		return *Sections[SectionIndex];
	};

	auto GetTriangle = [&](uint32 Index)
	{
		const auto& TriangleSection = GetTriangleSection(Index);
		return rgl_vec3i
		{{
			(int32)IndexBufferView[TriangleSection.FirstIndex + Index * 3 + 0],
			(int32)IndexBufferView[TriangleSection.FirstIndex + Index * 3 + 1],
			(int32)IndexBufferView[TriangleSection.FirstIndex + Index * 3 + 2]
		}};
	};

	std::vector<rgl_vec3f> Vertices;
	std::vector<rgl_vec3i> TriangleIndices;

	Vertices.reserve(TriangleCount * 3);
	TriangleIndices.reserve(TriangleCount);
	for (uint32 TriangleIndex = 0; TriangleIndex != TriangleCount; ++TriangleIndex)
	{
		const auto Triangle = GetTriangle(TriangleIndex);
		for (uint32 i = 0; i != 3; ++i)
		{
			const FVector3f Vertex = PositionBuffer.VertexPosition(Triangle.value[i]);
			Vertices.push_back(
			{{
				Vertex[0],
				Vertex[1],
				Vertex[2]
			}});
		}
		TriangleIndices.push_back(Triangle);
	}
	
	return FCRGL_Mesh::Create(
		Vertices.data(),
		Vertices.size(),
		TriangleIndices.data(),
		TriangleIndices.size());
}

FCRGL_Mesh FCRGL_Mesh::FromStaticMeshActor(AStaticMeshActor* mesh, uint32 lod_index)
{
	auto SMC = mesh->GetStaticMeshComponent();
	check(SMC);
	auto SM = SMC->GetStaticMesh();
	check(SM);
	return FromUEMesh(SM, lod_index);
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

TArray<std::pair<FCRGL_Mesh, FTransform>> FCRGL_Mesh::EnumerateStaticMeshes(
	UWorld* World)
{
	TArray<std::pair<FCRGL_Mesh, FTransform>> out;
	TArray<AActor*> found;
	UGameplayStatics::GetAllActorsOfClass(
		World,
		AStaticMeshActor::StaticClass(),
		found);
	out.Reserve(found.Num());
	for (size_t i = 0; i != found.Num(); ++i)
	{
		auto SMA = Cast<AStaticMeshActor>(found[i]);
		if (!SMA)
			continue;
		auto Mesh = FromStaticMeshActor(SMA, 0);
		out.Add(std::make_pair(std::move(Mesh), SMA->GetTransform()));
	}
	return out;
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
	if (GetHandle() == nullptr)
		return false;
	CheckRGLResult(rgl_mesh_is_alive(
		GetHandle(),
		&r));
	return r;
}

void FCRGL_Mesh::Destroy()
{
	CheckRGLResult(rgl_mesh_destroy(GetHandle()));
	*GetHandlePtr() = nullptr;
}
