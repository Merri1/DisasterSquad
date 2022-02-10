#include "Tornado.h"
#include <iostream>

Tornado::Tornado()
{
    Disaster();
}

// Spawn method for tornado, pass in map coordinates.
void Tornado::spawn(int(&levelArray)[36][64])
{
    m_soundVolume = 80;
    g_tornadoSoundBuffer.loadFromFile("sounds/tornado.wav");
    m_disasterSound.setBuffer(g_tornadoSoundBuffer);
    m_disasterSound.setVolume(m_soundVolume);
    
    Disaster::spawn(levelArray);
    m_spriteTexture = TextureHolder::GetTexture("graphics/tornado_spritesheet.png");
    m_disasterSprite.setTexture(m_spriteTexture);
    m_disasterSprite.setTextureRect(sf::IntRect{0, 0, 16, 16});
    m_disasterSprite.setOrigin(8, 8);
    m_disasterSprite.setPosition(m_position);
}

// Change sprite based on frame.
sf::Sprite Tornado::getSprite(float elapsedTime)
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

