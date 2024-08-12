#include "CRGL_Graph.h"
#include "CRGL_Node.h"



namespace RGL
{
	void FGraph::Run(FNode& node)
	{
		CheckRGLResult(rgl_graph_run(node.GetHandle()));
	}

	void FGraph::Destroy(FNode& node)
	{
		CheckRGLResult(rgl_graph_destroy(node.GetHandle()));
	}

	std::pair<int32_t, int32_t> FGraph::GetResultSize(
		FNode& node,
		EField field)
	{
		int32_t size, size_of;
		CheckRGLResult(rgl_graph_get_result_size(
			node.GetHandle(),
			(rgl_field_t)field,
			&size,
			&size_of));
		return std::make_pair(size, size_of);
	}

	void FGraph::GetResultData(
		FNode& node,
		EField field,
		void* data)
	{
		CheckRGLResult(rgl_graph_get_result_data(
			node.GetHandle(),
			(rgl_field_t)field,
			data));
	}

	void FGraph::AddChild(
		FNode& parent,
		FNode& child)
	{
		CheckRGLResult(rgl_graph_node_add_child(
			parent.GetHandle(),
			child.GetHandle()));
	}

	void FGraph::RemoveChild(
		FNode& parent,
		FNode& child)
	{
		CheckRGLResult(rgl_graph_node_remove_child(
			parent.GetHandle(),
			child.GetHandle()));
	}

	void FGraph::SetPriority(
		FNode& node,
		int32_t priority)
	{
		CheckRGLResult(rgl_graph_node_set_priority(
			node.GetHandle(),
			priority));
	}

	int32_t FGraph::GetPriority(FNode& node)
	{
		int32_t r;
		CheckRGLResult(rgl_graph_node_get_priority(
			node.GetHandle(),
			&r));
		return r;
	}
}