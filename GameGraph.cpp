#include "GameGraph.h"

using namespace std;

GameGraph::GameGraph()
{

}

void GameGraph::addEdge(int start, int end)
{
	bool edgeExists = false;

	// Cycle through edges from starting point passed intot his function
	for (GraphEdge e : adjacencyListVector[start])
	{
		// If an exisiting edge has the same endpoint as the passed vlaue then the edge already exists
		if (e.getEdgeEnd() == end)
		{
			edgeExists = true;
		}
	}

	// If the edge does not already exist add it in both directions
	if (!edgeExists)
	{
		adjacencyListVector[start].push_back(GraphEdge(start, end));
		adjacencyListVector[end].push_back(GraphEdge(end, start));
	}
}

vector<GraphEdge> GameGraph::getNeighbours(int start)
{
	// Return a vector of edges coming out of a node
	return adjacencyListVector[start];
}

int GameGraph::getGraphOrder()
{
	return graphOrder;
}

void GameGraph::generateGraphFromFile(int tilesX, int tilesY, int level)
{
	graphOrder = tilesX * tilesY;

	// Resize the adjacency vector to be the size of N
	adjacencyListVector.resize(graphOrder);

	string filename;

	if (level == 1)
	{
		filename = "GrasslandsASCIImap.txt";
	}
	else if (level == 2)
	{
		filename = "test.txt";
	}

	ifstream inputFile(filename);

	// Go back to the start of the file
	//inputFile.clear();
	//inputFile.seekg(0, ios::beg);


	// Loop through the file and store all the values in the 2d array
	string row;
	int y = 0;

	while (inputFile >> row)
	{
		for (int x = 0; x < tilesX; x++)
		{
			const char val = row[x];
			levelArray[y][x] = atoi(&val);
		}

		y++;
	}

	for (int i = 0; i < tilesY; i++)
	{
		for (int j = 0; j < tilesX; j++)
		{
			cout << levelArray[i][j];

			// Check top left corner add ones below and to right
			if (i < tilesY - 1 && j < tilesX - 1)
			{
				if (levelArray[i][j] == 0 && levelArray[i][j + 1] == 0)
				{
					this->addEdge(i * tilesY + j, (i * tilesY) + j + 1);
				}

				if (levelArray[i][j] == 0 && levelArray[i + 1][j] == 0)
				{
					this->addEdge(i * tilesY + j, (i + 1) * tilesY + j);
				}
			}

			// Check last row second last element
			if (i == tilesY && j < tilesX)
			{
				if (levelArray[i][j] == 0 && levelArray[i][j + 1] == 0)
				{
					this->addEdge(i * tilesY + j, (i * tilesY) + j + 1);
				}
			}

			if (j == tilesX - 1 && i < tilesY)
			{
				if (levelArray[i][j] == 0 && levelArray[i + 1][j] == 0)
				{
					this->addEdge(i * tilesY + j, (i + 1) * tilesY + j);
				}
			}
		}
		cout << endl;
	}

	// close the file
	inputFile.close();
}
