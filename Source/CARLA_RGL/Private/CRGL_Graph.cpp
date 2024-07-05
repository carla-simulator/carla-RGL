#include "CRGL_Graph.h"
#include "CRGL_Node.h"

void FCRGL_Graph::Run(FCRGL_Node& node)
{
	CheckRGLResult(rgl_graph_run(node.GetHandle()));
}

void FCRGL_Graph::Destroy(FCRGL_Node& node)
{
	CheckRGLResult(rgl_graph_destroy(node.GetHandle()));
}

std::pair<int32_t, int32_t> FCRGL_Graph::GetResultSize(
	FCRGL_Node& node,
	rgl_field_t field)
{
	int32_t size, size_of;
	CheckRGLResult(rgl_graph_get_result_size(
		node.GetHandle(),
		field,
		&size,
		&size_of));
	return std::make_pair(size, size_of);
}

void FCRGL_Graph::GetResultData(
	FCRGL_Node& node,
	rgl_field_t field,
	void* data)
{
	CheckRGLResult(rgl_graph_get_result_data(
		node.GetHandle(),
		field,
		data));
}

std::vector<uint8_t> FCRGL_Graph::GetResult(
	FCRGL_Node& node,
	rgl_field_t field)
{
	std::vector<uint8_t> r;
	auto [size, size_of] = GetResultSize(node, field);
	r.resize(size * size_of);
	GetResultData(node, field, r.data());
	return r;
}

void FCRGL_Graph::AddChild(
	FCRGL_Node& parent,
	FCRGL_Node& child)
{
	CheckRGLResult(rgl_graph_node_add_child(
		parent.GetHandle(),
		child.GetHandle()));
}

void FCRGL_Graph::RemoveChild(
	FCRGL_Node& parent,
	FCRGL_Node& child)
{
	CheckRGLResult(rgl_graph_node_remove_child(
		parent.GetHandle(),
		child.GetHandle()));
}

void FCRGL_Graph::SetPriority(
	FCRGL_Node& node,
	int32_t priority)
{
	CheckRGLResult(rgl_graph_node_set_priority(
		node.GetHandle(),
		priority));
}

int32_t FCRGL_Graph::GetPriority(FCRGL_Node& node)
{
	int32_t r;
	CheckRGLResult(rgl_graph_node_get_priority(
		node.GetHandle(),
		&r));
	return r;
}



ACRGL_Graph::ACRGL_Graph(const FObjectInitializer& Initializer)
{
}