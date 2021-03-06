#include "Disaster.h"
#include <iostream>
using namespace sf;

SoundBuffer Disaster::g_wildfireSoundBuffer;
SoundBuffer Disaster::g_tornadoSoundBuffer;


Disaster::Disaster()
{
    srand(time(NULL));
}

void Disaster::spawn(int (&levelArray)[36][64])
{
    m_health = MAX_HEALTH;
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
            
            levelArray[tileY][tileX] = 1;
            srand(time(NULL));
            break;
        }
    }

    m_disasterSound.play();
    m_disasterSound.setLoop(true);
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

sf::Vector2f Disaster::getPosition()
{
    return m_position;
}

sf::Sprite Disaster::getSprite(float elapsedTime)
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
    m_health -= damage;
    m_disasterSprite.setScale(m_health/1000, m_health/1000);
    
    if ((int)m_health % 100 == 0)
    {
        m_soundVolume -= m_soundVolume/10;
    }
    m_disasterSound.setVolume(m_soundVolume);
}

void Disaster::destroyDisaster()
{
    m_disasterSound.stop();
    m_spawned = false;
    m_health = 0;
}