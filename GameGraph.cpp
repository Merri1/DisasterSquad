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

void GameGraph::generateGraphFromFile(int(&levelArray)[36][64], int tileCols, int tileRows, int level)
{
	graphOrder = tileCols * tileRows;

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
		for (int x = 0; x < tileCols; x++)
		{
			const char val = row[x];
			levelArray[y][x] = atoi(&val);
		}

		y++;
	}

	for (int i = 0; i < tileRows; i++)
	{
		for (int j = 0; j < tileCols; j++)
		{
			// Check top left corner add ones below and to right
			if (i < tileRows - 1 && j < tileCols - 1)
			{
				if (levelArray[i][j] == 0 && levelArray[i][j + 1] == 0)
				{
					this->addEdge(i * tileCols + j, (i * tileCols) + j + 1);
				}

				if (levelArray[i][j] == 0 && levelArray[i + 1][j] == 0)
				{
					this->addEdge(i * tileCols + j, (i + 1) * tileCols + j);
				}
			}

			// Check last row second last element
			if (i == tileRows - 1 && j < tileCols - 1)
			{
				if (levelArray[i][j] == 0 && levelArray[i][j + 1] == 0)
				{
					this->addEdge(i * tileCols + j, (i * tileCols) + j + 1);
				}
			}

			if (j == tileCols - 1 && i < tileRows - 1)
			{
				if (levelArray[i][j] == 0 && levelArray[i + 1][j] == 0)
				{
					this->addEdge(i * tileCols + j, (i + 1) * tileCols + j);
				}
			}
		}
	}

	// close the file
	inputFile.close();
}
