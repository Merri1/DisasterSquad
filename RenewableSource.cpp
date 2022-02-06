//methods TODO:
//inherits from

#include "RenewableSource.h"
#include <iostream>
using namespace sf;
using namespace std;

RenewableSource::RenewableSource(string type) {

    m_type = type;
    m_position.x = m_positionX;
    m_position.y = m_positionY;
    
    m_Sprite.setOrigin(8, 16);
    m_Sprite.setPosition(m_positionX, m_positionY);
    m_Sprite.setTexture(TextureHolder::GetTexture("graphics/wind_turbine_spritesheet.png"));
    m_Sprite.setTextureRect(IntRect{ 16, 0, 16, 32 });

    m_isSelected = false;
    m_placed = false;

    // Assign attributes based on building type.
    if (m_type == "solar") {

        m_Sprite.setTexture(TextureHolder::GetTexture("graphics/solar_panel_spritesheet.png"));
        m_Sprite.setTextureRect(IntRect{ 16, 9, 26, 23 });

        m_health = 50;
        m_enviroFactor = 2;
        m_power = 1;
        m_buildTime = 5000;
    }

    if (m_type == "turbine") {

        m_Sprite.setTexture(TextureHolder::GetTexture("graphics/wind_turbine_spritesheet.png"));
        m_Sprite.setTextureRect(IntRect{ 16, 0, 16, 32 });

        m_health = 80;
        m_enviroFactor = 5;
        m_power = 2;
        m_buildTime = 7500;
    }

    else if (m_type == "recycling") {

        m_Sprite.setTexture(TextureHolder::GetTexture("graphics/recycling_centre_spritesheet.png"));
        m_Sprite.setTextureRect(IntRect{ 16, 10, 22, 22 });

        m_health = 100;
        m_enviroFactor = 10;
        m_power = 0;
        m_buildTime = 10000;
    }
}

// Spawn building at coordinates.
void RenewableSource::spawn(int x, int y) {

    m_positionX = x;
    m_positionY = y;
    m_Sprite.setPosition(m_positionX, m_positionY);
}

// Update position of the building.
void RenewableSource::update(float elapsedTime) {

    m_position.x = m_positionX;
    m_position.y = m_positionY;
    m_Sprite.setPosition(m_positionX, m_positionY);
}

// Set sprite according to type and if placed.
void RenewableSource::setSprite() 
{
  
}

Sprite RenewableSource::getSprite()
{
    return m_Sprite;
}

bool RenewableSource::getSpawnStatus() {
    return m_spawned;
}

bool RenewableSource::isPlaced() {
    return m_placed;
}

bool RenewableSource::isSuitable() {
    return m_suitable;
}

void RenewableSource::setSuitable(bool suitable) {
    m_suitable = suitable;
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

void RenewableSource::setPositionX(int x) {
    m_position.x = x;
}

void RenewableSource::setPositionY(int y) {
    m_position.y = y;
}

int RenewableSource::getPositionX()
{
    return m_position.x;
}

int RenewableSource::getPositionY()
{
    return m_position.y;
}

bool RenewableSource::isSelected()
{
    return m_isSelected;
}

void RenewableSource::select(bool Selected)
{
    m_isSelected = Selected;
}