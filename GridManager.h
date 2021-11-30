#pragma once
#ifndef GRIDMANAGER_H
#define GRIDMANAGER_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Game.h"
#include "TextureHolder.h"
#include "Responder.h"

class GridManager
{
public:
	GridManager();
	void initGrid(VertexArray& rVA, int worldWidth, int worldHeight);
private:
	const int TILE_SIZE = 16;
	const int VERTS_IN_QUAD = 4;

};
#endif
