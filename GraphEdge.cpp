#include "GraphEdge.h"

GraphEdge::GraphEdge(int start, int end)
{
	start = start;
	end = end;
}

int GraphEdge::getEdgeTo()
{
	return end;
}

int GraphEdge::getEdgeFrom()
{
	return start;
}