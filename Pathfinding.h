#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <vector>
#include "GameGraph.h"
#include "GraphEdge.h"

using namespace std;

class Pathfinding
{
public:
	Pathfinding();
	vector<int> BFS(GameGraph &g, int start, int target);
	bool containsElement(vector<int> vec, int x);
	void generatePath();

protected:
	vector<int> visited;
	vector<int> queue;
	vector<int> previous;
	vector<int> path;
};
#endif

