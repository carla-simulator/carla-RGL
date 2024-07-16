#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include <span>



class UStaticMesh;
class AStaticMeshActor;


namespace RGL
{
	class CARLA_RGL_API FMesh :
		public FRGLHandleMixin<rgl_mesh_t, rgl_mesh_destroy>
	{
	public:

		FMesh() = default;
		FMesh(FMesh&&) = default;
		FMesh& operator=(FMesh&&) = default;
		~FMesh() = default;

		static FMesh CreateCube();

		static FMesh CreateCube(
			FTransform Transform);

		// Load mesh data from a UStaticMesh
		static FMesh FromUEMesh(
			UStaticMesh* mesh,
			uint32 lod_index = 0);

		// Load mesh data from an AStaticMeshActor.
		static FMesh FromStaticMeshActor(
			AStaticMeshActor* mesh,
			uint32 lod_index = 0);

		static FMesh Create(
			std::span<const rgl_vec3f> vertices,
			std::span<const rgl_vec3i> indices);

		static FMesh Create(
			const rgl_vec3f* vertices, int32_t vertex_count,
			const rgl_vec3i* indices, int32_t index_count);

		void SetTextureUVs(const rgl_vec2f* uvs, int32_t count);
		void UpdateVertices(const rgl_vec3f* vertices, int32_t count);
		bool IsAlive();

	};
}