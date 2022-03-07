#include "Wildfire.h"
#include <iostream>


Wildfire::Wildfire()
{
	Disaster();
}

// Spawn method for wildfire, pass in map coordinates.
void Wildfire::spawn(int (&levelArray)[36][64])
{
    m_soundVolume = 50;
    g_wildfireSoundBuffer.loadFromFile("../assets/sounds/fire.wav");
    m_disasterSound.setBuffer(g_wildfireSoundBuffer);
    m_disasterSound.setVolume(m_soundVolume);
    
    Disaster::spawn(levelArray);
    m_spriteTexture = TextureHolder::GetTexture("../assets/graphics/disasters/wildfire_spritesheet.png");
    m_disasterSprite.setTexture(m_spriteTexture);
    m_disasterSprite.setOrigin(8, 8);
    m_disasterSprite.setPosition(m_position);
    //m_disasterSound.play();
}

// Change sprite based on frame.
sf::Sprite Wildfire::getSprite(float elapsedTime)
{
    if (elapsedTime < 125)
    {
        m_disasterSprite.setTextureRect(sf::IntRect{ 0, 0, 16, 16 });
    }
    else if (elapsedTime >= 125 && elapsedTime < 250)
    {
        m_disasterSprite.setTextureRect(sf::IntRect{ 16, 0, 16, 16 });
    }
    else if (elapsedTime >= 250 && elapsedTime < 375)
    {
        m_disasterSprite.setTextureRect(sf::IntRect{ 32, 0, 16, 16 });
    }
    else if (elapsedTime >= 375)
    {
        m_disasterSprite.setTextureRect(sf::IntRect{ 48, 0, 16, 16 });
    }
    return m_disasterSprite;
}



