#include "GameGraph.h"

GameGraph::GameGraph(int N)
{
	// Resize the adjacency vector to be the size of N
	adjacencyListVector.resize(N);
}

void GameGraph::addEdge(int start, int end)
{
	bool edgeExists = false;
	
	// Cycle through edges from starting point passed intot his function
	for (GraphEdge e : adjacencyListVector[start])
	{
		// If an exisiting edge has the same endpoint as the passed vlaue then the edge already exists
		if (e.getEdgeTo() == end)
		{
			edgeExists = true;
		}
	}

	// If the edge does not already exist add it in both directions
	if (!edgeExists)
	{
		adjacencyListVector[start].push_back(GraphEdge(start, end));
		adjacencyListVector[start].push_back(GraphEdge(end, start));
	}
}

std::vector<GraphEdge> GameGraph::getNeighbours(int start)
{
	// Return a vector of edges coming out of a node
	return adjacencyListVector[start];
}

