#include "Wildfire.h"
#include <iostream>

Wildfire::Wildfire()
{
	Disaster();
}


void Wildfire::spawn()
{
    Disaster::spawn();
    m_spriteTexture = TextureHolder::GetTexture(
        "graphics/wildfire.png");
    m_disasterSprite.setTexture(m_spriteTexture);
    m_disasterSprite.setOrigin(8, 8);
    m_disasterSprite.setPosition(m_position);
    
}

sf::Sprite Wildfire::getSprite()
{
    return m_disasterSprite;
}


