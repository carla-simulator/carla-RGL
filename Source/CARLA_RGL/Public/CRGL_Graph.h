#pragma once
#include "CoreMinimal.h"
#include "CRGL_Common.h"
#include "CRGL_Graph.generated.h"



class FCRGL_Node;



class FCRGL_Graph
{
public:
	static void Run(
		FCRGL_Node& node);

	static void Destroy(
		FCRGL_Node& node);

	static std::pair<int32_t, int32_t> GetResultSize(
		FCRGL_Node& node,
		rgl_field_t field);

	static void GetResultData(
		FCRGL_Node& node,
		rgl_field_t field,
		void* data);

	template <typename T>
	static std::vector<T> GetResult(
		FCRGL_Node& node,
		rgl_field_t field)
	{
		std::vector<T> r;
		auto [size, size_of] = GetResultSize(node, field);
		r.resize(size * size_of / sizeof(T));
		GetResultData(node, field, r.data());
		return r;
	}

	static void AddChild(
		FCRGL_Node& parent,
		FCRGL_Node& child);

	static void RemoveChild(
		FCRGL_Node& parent,
		FCRGL_Node& child);

	static void SetPriority(
		FCRGL_Node& node,
		int32_t priority);

	static int32_t GetPriority(
		FCRGL_Node& node);
};



UCLASS()
class ACRGL_Graph :
  public AActor
{
	GENERATED_BODY()
public:

	ACRGL_Graph(const FObjectInitializer& Initializer);

	void Run();
	void Destroy();
	void GetResultSize();
	void GetResultData();
	void GetResult();
	void AddChild();
	void RemoveChild();
	void SetPriority();
	void GetPriority();

private:

};
