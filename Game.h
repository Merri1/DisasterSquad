#pragma once
#ifndef GAME_H
#define GAME_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "Responder.h"
#include "RenewableSource.h"

class Game
{
public:
    Game();
    void init();      // Init game variables based on difficulty level chosen in Engine
    void mainMenu();  // Menu system to do here
    void showRules();
    float getPollution();
    float getPollutionRatePlus();
    float getPollutionRateMinus();
    sf::Texture switchLevel();

protected:
    sf::Texture m_backgroundTexture;
    float m_pollution;  // Calculated based on delta time
    double m_pollutionRatePlus;
    double m_pollutionRateMinus;
};
#endif