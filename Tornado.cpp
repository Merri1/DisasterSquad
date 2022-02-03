#include "Tornado.h"
#include <iostream>

Tornado::Tornado()
{
    Disaster();
}


void Tornado::spawn(int(&levelArray)[36][64])
{
    g_tornadoSoundBuffer.loadFromFile("sounds/tornado.wav");
    m_disasterSound.setBuffer(g_tornadoSoundBuffer);
    m_disasterSound.setVolume(80);
    
    Disaster::spawn(levelArray);
    m_spriteTexture = TextureHolder::GetTexture(
        "graphics/tornado.png");
    m_disasterSprite.setTexture(m_spriteTexture);
    m_disasterSprite.setOrigin(8, 10);
    m_disasterSprite.setPosition(m_position);

}

sf::Sprite Tornado::getSprite()
{
    return m_disasterSprite;
}

