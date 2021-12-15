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
    void getX();
    void getY();
    bool getSpawnStatus();
    virtual void spawn();
    virtual sf::Sprite getSprite();
    int getHealth();
    bool isAlive();
    void updateHealth(int damage);
    void chanceToSpread(sf::Vector2f);
    sf::Vector2f getPosition();
    sf::Vector2f m_position;
   // int m_positionX;
   // int m_positionY;

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