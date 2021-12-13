//methods TODO:

/*
//fire()
//flood()
//natural disaster etc etc
*/
#include "Disaster.h"

Disaster::Disaster()
{
    srand(time(NULL));
}

void Disaster::spawn()
{
    m_health = 100;
    m_spawned = true;
    m_position.x = rand() % 1024;
    m_position.y = rand() % 576;
    m_spriteTexture = TextureHolder::GetTexture(
        "graphics/wildfire.png");
    m_disasterSprite.setTexture(m_spriteTexture);
    m_disasterSprite.setOrigin(8, 8);
    m_disasterSprite.setPosition(m_position);
}

bool Disaster::getSpawnStatus()
{
    return m_spawned;
}

void Disaster::update()
{
    // Update the disaster
}

sf::Vector2f Disaster::getPosition()
{
    return m_position;
}

sf::Sprite Disaster::getSprite()
{
    return m_disasterSprite;
}


