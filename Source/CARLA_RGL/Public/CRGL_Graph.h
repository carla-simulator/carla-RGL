#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"



namespace RGL
{
	class FNode;

	class CARLA_RGL_API FGraph
	{
	public:
		static void Run(
			FNode& node);

		static void Destroy(
			FNode& node);

		static std::pair<int32_t, int32_t> GetResultSize(
			FNode& node,
			rgl_field_t field);

		static void GetResultData(
			FNode& node,
			rgl_field_t field,
			void* data);

		template <
			rgl_field_t Field,
			template <typename> typename ArrayT = std::vector>
		static auto GetResult(
			FNode& node)
		{
			using T = FCRGLFieldToType<Field>;
			ArrayT<T> r;
			auto [size, size_of] = GetResultSize(node, Field);
			check(size_of == sizeof(T));
			r.resize(size);
			GetResultData(node, Field, r.data());
			return r;
		}

		template <
			rgl_field_t Field,
			template <typename> typename ArrayT = TArray>
		static auto GetResultUE(
			FNode& node)
		{
			using T = FCRGLFieldToType<Field>;
			ArrayT<T> r;
			auto [size, size_of] = GetResultSize(node, Field);
			check(size_of == sizeof(T));
			r.SetNum(size);
			GetResultData(node, Field, r.GetData());
			return r;
		}

		static void AddChild(
			FNode& parent,
			FNode& child);

		static void RemoveChild(
			FNode& parent,
			FNode& child);

		static void SetPriority(
			FNode& node,
			int32_t priority);

		static int32_t GetPriority(
			FNode& node);
	};
}