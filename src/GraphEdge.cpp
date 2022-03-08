#include "GraphEdge.h"

GraphEdge::GraphEdge(int start, int end)
{
	m_start = start;
	m_end = end;
}

int GraphEdge::getEdgeEnd()
{
	return m_end;
}

int GraphEdge::getEdgeStart()
{
	return m_start;
}