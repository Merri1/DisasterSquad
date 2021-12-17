#include "Pathfinding.h"
#include <iostream>
using namespace std;

// This class is to utilize BFS (breadth-first) for our graph classes.
Pathfinding::Pathfinding()
{

}

vector<int> Pathfinding::BFS(GameGraph &g, int start, int target)
{
	previous.clear();
	queue.clear();
	visited.clear();
	path.clear();

	// Resize previous vector to graph size
	previous.resize(g.getGraphOrder());

	// Add starting node to queue
	queue.push_back(start);

	// Set previous node of start to be itself
	previous[start] = start;

	// Keep looping until we've visited the target node
	while (!containsElement(visited, target)) 
	{
		int current;

		if (!queue.empty())
		{
			// If queue has entries remove the first and store in current
			current = queue.front();
			queue.erase(queue.begin());
		}
		else
		{
			cout << "No path found" << endl;
			// If the queue has no entries (no path) retrun empty vector
			path.clear();
			return path;
		}

		// Check if current node has been added to visited
		if (!containsElement(visited, current))
		{
			// Add current node to visited vector
			visited.push_back(current);
			
			// Check all the neighbours of current node
			for (GraphEdge edge : g.getNeighbours(current))
			{
				if (!containsElement(visited, edge.getEdgeEnd()))
				{
					// If a neighbour node hasn't been visited add it to queue
					queue.push_back(edge.getEdgeEnd());
					// Update previous vector to keep track of where we came from to get to this node
					previous[edge.getEdgeEnd()] = current;
				}
			}
		}
	}

	// Add target node to path vector 
	int node = previous[target];
	path.push_back(target);

	// Iterate through path vector to generate path from start to target nodes
	while (node != start)
	{
		path.push_back(node);
		node = previous[node];
	}

	// Add start node to path vector
	path.push_back(start);

	// Reverse path vector so it is now in the correct order
	reverse(path.begin(), path.end());

	return path;
}

bool Pathfinding::containsElement(vector<int> vec, int element)
{
	for (int n : vec)
	{
		if (n == element)
		{
			return true;
			break;
		}
	}
	return false;
}

void Pathfinding::generatePath()
{

}
