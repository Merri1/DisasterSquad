#pragma once
#ifndef DISASTER_H
#define DISASTER_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "TextureHolder.h"
#include <random>

class Disaster
{
public:
    Disaster();
    void update();
    bool getSpawnStatus();
    virtual void spawn();
    virtual sf::Sprite getSprite();
    void chanceToSpread(sf::Vector2f);
    sf::Vector2f getPosition();
    sf::Vector2f m_position;

    // These are now converted to subclasses for each disaster type
    // Keep these here for now as a reminder for write up padding
    //void fire();
    //void flood();
    //void drought();

protected:
    int m_difficultyChance; // Chance of spreading depending on selected difficulty 
    int m_health;
    bool m_spawned = false;
    sf::Sprite m_disasterSprite;
    sf::Texture m_spriteTexture;
};
#endif