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
    virtual void spawn(std::string type, int health, int enviro, int power, int time, int x, int y);
    virtual sf::Sprite getSprite();
    bool isSelected();
    bool isPlaced();
    void select(bool Selected);
    int getPositionX();
    int getPositionY();
    std::string getType();
    int getPower();
    int getTime();
    int getEnviro();
    int getHealth();

    sf::Vector2f m_position;
    int m_positionX;
    int m_positionY;

protected:
    bool m_spawned = false;
    bool m_isSelected;
    bool m_placed;
    int m_health;
    std::string m_type;
    int m_enviroFactor;
    int m_power;
    int m_buildTime;
    sf::Sprite m_disasterSprite;
    sf::Texture m_spriteTexture;
};
#endif