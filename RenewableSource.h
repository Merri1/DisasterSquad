#pragma once
#ifndef RENEWABLESOURCE_H
#define RENEWABLESOURCE_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "TextureHolder.h"
#include <random>

class RenewableSource
{
public:
    RenewableSource();
    void update();
    bool getSpawnStatus();
    virtual void spawn();
    virtual sf::Sprite getSprite();
    bool isSelected();
    void select(bool Selected);
    int getPositionX();
    int getPositionY();

    sf::Vector2f m_position;
    int m_positionX;
    int m_positionY;

    // These are now converted to subclasses for each disaster type
    // Keep these here for now as a reminder for write up padding
    //void fire();
    //void flood();
    //void drought();

protected:
    bool m_spawned = false;
    bool m_isSelected;
    sf::Sprite m_disasterSprite;
    sf::Texture m_spriteTexture;
};
#endif