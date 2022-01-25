//methods TODO:

/*
//fire()
//flood()
//natural disaster etc etc
*/
#include "Disaster.h"
#include <iostream>
using namespace sf;

Disaster::Disaster()
{
    srand(time(NULL));
   // m_position.x = m_positionX;
   //m_position.y = m_positionY;
}

void Disaster::spawn(int (&levelArray)[36][64])
{
    m_health = 1000;
    m_spawned = true;
    m_disasterSprite.setScale(1,1);

    while (true)
    {
        m_position.x = rand() % 1024;
        m_position.y = rand() % 576;
        
        int tileX = m_position.x / 16;
        int tileY = m_position.y / 16;

        if (levelArray[tileY][tileX] == 0)
        {
            m_position.x = tileX * 16 + 8;
            m_position.y = tileY * 16 + 8;
            break;
        }
    }

    std::cout << "x = " << m_position.x << " and y = " << m_position.y;
    

}

bool Disaster::getSpawnStatus()
{

    return m_spawned;

}

void Disaster::setSpawnStatus()
{
    if (getHealth() == 0)
    {
        m_spawned == false;
    }
    else
    {
        m_spawned == true;
    }
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

int Disaster::getHealth()
{
    return m_health;
}

bool Disaster::isAlive()
{
    return(m_health > 0);
}


void Disaster::updateHealth(int damage)
{
    if (m_health <= 200)
    {
        m_spawned = false;
        m_health == 0;
    }
    else
    {
        m_health -= damage;
        m_disasterSprite.scale(0.99, 0.99);
    }  
}
