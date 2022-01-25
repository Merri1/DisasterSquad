//methods TODO:
//inherits from

#include "RenewableSource.h"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
using namespace sf;
using namespace std;

RenewableSource::RenewableSource() {

}

void RenewableSource::spawn(std::string type, int health, int enviro, int power, int time, int x, int y) {

    m_type = type;
    m_health = health;
    m_enviroFactor = enviro;
    m_power = power;
    m_buildTime = time;
    m_positionX = x;
    m_positionY = y;
}

bool RenewableSource::getSpawnStatus() {
    return m_spawned;
}

bool RenewableSource::isPlaced() {
    return m_placed;
}

void RenewableSource::update() {
    // Update the disaster
}

int RenewableSource::getHealth() {
    return m_health;
}

std::string RenewableSource::getType() {
    return m_type;
}

int RenewableSource::getEnviro() {
    return m_enviroFactor;
}

int RenewableSource::getPower() {
    return m_power;
}

int RenewableSource::getTime() {
    return m_buildTime;
}

int RenewableSource::getPositionX()
{
    return m_position.x;
}

int RenewableSource::getPositionY()
{
    return m_position.y;
}

sf::Sprite RenewableSource::getSprite()
{
    return m_disasterSprite;
}

bool RenewableSource::isSelected()
{
    cout << "Turbine Selected";
    return m_isSelected;
}

void RenewableSource::select(bool Selected)
{
    m_isSelected = Selected;
}








