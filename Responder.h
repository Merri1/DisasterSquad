#pragma once
#ifndef RESPONDER_H
#define RESPONDER_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

class Responder
{
public:
    Responder();
    sf::Vector2f getPosition();
    void getSprite();
    void moveTo(sf::Vector2f);
    void spawn(sf::Vector2f);
    void update();
    void fightDisaster();

protected:
    int m_health;
    int m_attack;
    bool m_ID;
    bool m_isSelected();
    sf::Vector2f m_position;
    float m_speed;
};
#endif