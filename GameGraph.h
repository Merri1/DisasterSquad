#pragma once
#ifndef GAMEGRAPH
#define GAMEGRAPH
#include <vector>
#include <algorithm>
#include "GraphEdge.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class GameGraph
{
public:
	GameGraph(int N);
	void addEdge(int start, int end);
	std::vector<GraphEdge> getNeighbours(int start);

protected:
	std::vector<std::vector<GraphEdge>> adjacencyListVector;
};
#endif // !GAMEGRAPH
