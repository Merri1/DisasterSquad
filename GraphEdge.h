#pragma once
#ifndef GRAPHEDGE
#define GRAPHEDGE

class GraphEdge
{
public:
	GraphEdge(int start, int end);
	int getEdgeFrom();
	int getEdgeTo();

protected:
	int start;
	int end;
	const int weight = 1;
};
#endif
