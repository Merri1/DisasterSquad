#include "GridManager.h"

GridManager::GridManager()
{

}

void GridManager::initGrid(VertexArray& virtualGridVA, int worldWidth, int worldHeight)
{
	int tilesWide = worldWidth / TILE_SIZE;
	int tilesHigh = worldHeight / TILE_SIZE;

	virtualGridVA.setPrimitiveType(Quads);
	virtualGridVA.resize(tilesWide * tilesHigh * VERTS_IN_QUAD);

	int currentVertex = 0;

	for(int w = 0; w < tilesWide; w++)
	{
		for (int h = 0; h < tilesHigh; h++)
		{
			virtualGridVA[currentVertex + 0].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			virtualGridVA[currentVertex + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
			virtualGridVA[currentVertex + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
			virtualGridVA[currentVertex + 3].position = Vector2f(w * TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);

			// Testing grid position
			/*
			if (h%3 ==0)
			{
				virtualGridVA[currentVertex + 0].texCoords = Vector2f(0, 0);
				virtualGridVA[currentVertex + 1].texCoords = Vector2f(16, 0);
				virtualGridVA[currentVertex + 2].texCoords = Vector2f(16, 16);
				virtualGridVA[currentVertex + 3].texCoords = Vector2f(0, 16);
			}
			*/
		}

		currentVertex += VERTS_IN_QUAD;
	}
}