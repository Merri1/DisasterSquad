#include "Wildfire.h"
#include <iostream>


Wildfire::Wildfire()
{
	Disaster();
}


void Wildfire::spawn(int (&levelArray)[36][64])
{
    m_soundVolume = 50;
    g_wildfireSoundBuffer.loadFromFile("sounds/fire.wav");
    m_disasterSound.setBuffer(g_wildfireSoundBuffer);
    m_disasterSound.setVolume(m_soundVolume);
    
    Disaster::spawn(levelArray);
    m_spriteTexture = TextureHolder::GetTexture(
        "graphics/wildfire.png");
    m_disasterSprite.setTexture(m_spriteTexture);
    m_disasterSprite.setOrigin(8, 10);
    m_disasterSprite.setPosition(m_position);
    //m_disasterSound.play();
}

sf::Sprite Wildfire::getSprite()
{
    return m_disasterSprite;
}


