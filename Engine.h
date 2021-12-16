#pragma once
#ifndef ENGINE_H
#define ENGINE_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "GameGraph.h"
#include "Pathfinding.h"
#include "TextureHolder.h"
#include "Responder.h"
#include "Disaster.h"
#include "Wildfire.h"
#include "Shop.h"
#include "RenewableSource.h"
#include "WindTurbine.h"

#include <random>
#include <list>

class Engine
{
public:
    Engine();
    void init();
    void run();
    void render();
    void draw();
    void update();
    void checkSelected();
    void eventManager(Event& e);
    void collisonDetection();
    void battleDisaster(Responder* responder, Disaster* disaster);
    void clean(); // Reset variables, remove objects. Level 1 = 1 responder, level 2 = 2 responders at start
    // Functions here
    


protected:
    const int FRAMERATE = 60;
    const int TILESIZE = 16;
    const Vector2i RESOLUTION = Vector2i(1024, 576);
    
    float m_elapsedTime;
    float m_pollutionTotal;
    float m_pollutionRate;
    float m_goldTotal;
    float m_goldRate;
    int camZoom;

    int m_powerTotal;

    //Game game;
    Texture m_backgroundTexture;
    Responder* m_responder1;
    Responder* m_responder2;
    Responder* m_responder3;
    Responder* m_responder4;

    RenewableSource* m_renewableSource1;
    RenewableSource* m_renewableSource2;
    RenewableSource* m_renewableSource3;

    Responder* responder;  // CHANGE THIS LATER AND USE ABOVE RESPONDERS

    Disaster* m_disaster1;
    Disaster* m_disaster2;
    Disaster* m_disaster3;
    Disaster* m_disaster4;

    Shop* m_WindTurbineBuy;
    Shop* m_ResponderBuy;


    Shop* m_shop1;
    //VertexArray virtualGrid;
    //GridManager grid;
    GameGraph graph;
    Pathfinding pathfind;
    std::list<Disaster*> lpDisasters;
    std::list<Responder*> lpResponders;
    std::list<Shop*> lpShop;
    std::list<RenewableSource*> lpRenew;

    //std::list<Shop*> lpShop;
    RenderWindow m_window;
    View m_mainView;
    View m_guiView;
    Texture m_textureBackground;
    Sprite m_background;
    Sprite m_spriteCrosshair;
    Vector2f m_mousePositionMain;
    Vector2f m_mousePositionGUI;
    Sprite m_spriteMainCollisionBox;
    Sprite m_spriteGUICollisionBox;
    Sprite m_spriteHeatBar;
    Sprite m_spriteHeatTitle;
    Sprite m_spritePollutionBar;
    Sprite m_spritePollutionTitle;
    Sprite m_spritePollutionLevel;
    Sprite m_spriteHeatLevel;
    Sprite m_spriteUIBar;
    Sprite m_spriteMenuBar;
    Sprite m_spritePower;
    TextureHolder m_textureHolder;
    Font ka1Font;
    Text m_displayIncome;
    Text m_displayPower;
    Text m_displayHeat;
    Text m_displayPollution;

    bool okayNewResponder;

};
#endif
