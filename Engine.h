#pragma once
#ifndef ENGINE_H
#define ENGINE_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Game.h"
#include "TextureHolder.h"
#include "Responder.h"
#include "Disaster.h"
#include "Wildfire.h"
#include "GridManager.h"
#include <random>
#include <list>

class Engine
{
public:
    Engine();
    void init();
    void run();
    void render();
    void update();
    void checkCollisions();
    void clean(); // Reset variables, remove objects. Level 1 = 1 responder, level 2 = 2 responders at start
    // Functions here
    
protected:
    Game game;
    sf::Texture m_backgroundTexture;
    Responder* m_responder1;
    Responder* m_responder2;
    Responder* m_responder3;
    Responder* m_responder4;
    RenewableSource* m_renewableSource1;
    RenewableSource* m_renewableSource2;
    RenewableSource* m_renewableSource3;
    Disaster* m_disaster1;
    Disaster* m_disaster2;
    Disaster* m_disaster3;
    Disaster* m_disaster4;
    Vector2f resolution;
    VertexArray virtualGrid;
    GridManager grid;
    std::list<Disaster*> lpDisasters;
};
#endif
