#pragma once
#ifndef RESPONDER_H
#define RESPONDER_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "TextureHolder.h"

using namespace sf;


class Responder
{
public:
    const float START_SPEED = 1;
    const float START_HEALTH = 100;

    Sprite m_Sprite;
    Texture m_Texture;
    Vector2f m_Resolution;
    Vector2i m_position;
    
    // What size is the current arena
    IntRect m_Area;

    Responder();
    int getPositionX();
    int getPositionY();
    //void getSprite();
    void moveTo(int postionX, int positionY);
    void spawn(int x, int y);
    void fightDisaster();
    int getHealth();
    float getRotation();
    Sprite getSprite();
    bool isSelected();
    void select(bool Selected);
    void update(float elapsedTime);
    int getAttack();

protected:
    bool m_isMoving;
    int m_Speed;
    int m_Health;
    int m_MaxHealth;
    int m_attack;
    int m_direction;
    bool m_ID;
    bool m_isSelected;
    int m_positionX;
    int m_positionY;
    int m_DestinationX;
    int m_DestinationY;
    float m_speed;
};
#endif
