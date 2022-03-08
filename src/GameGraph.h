#ifndef GAMEGRAPH
#define GAMEGRAPH
#include "GraphEdge.h"
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

class GameGraph
{
public:
	GameGraph();
	void addEdge(int start, int end);
	std::vector<GraphEdge> getNeighbours(int start);
	int getGraphOrder();
	void generateGraphFromFile(int (&levelArray)[36][64], int tilesX, int tilesY, int level);

protected:
	std::vector<std::vector<GraphEdge>> adjacencyListVector;
	int graphOrder;
};
#endif
