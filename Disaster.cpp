//methods TODO:

/*
//fire()
//flood()
//natural disaster etc etc
*/
#include "Disaster.h"
#include <iostream>

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


