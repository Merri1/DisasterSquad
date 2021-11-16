#pragma once
#ifndef DISASTER_H
#define DISASTER_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

class Disaster
{
public:
    Disaster();
    void fire();
    void flood();
    void drought();
    void chanceToSpread(sf::Vector2f);  

protected:
    int m_difficultyChance; // Chance of spreading depending on selected difficultu 
    int m_health;
    sf::Vector2f m_position;
};
#endif