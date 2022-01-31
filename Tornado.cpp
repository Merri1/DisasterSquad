#include "Tornado.h"
#include <iostream>

Tornado::Tornado()
{
    Disaster();
}


void Tornado::spawn(int(&levelArray)[36][64])
{
    Disaster::spawn(levelArray);
    m_spriteTexture = TextureHolder::GetTexture(
        "graphics/tornado2.png");
    m_disasterSprite.setTexture(m_spriteTexture);
    m_disasterSprite.setOrigin(8, 10);
    m_disasterSprite.setPosition(m_position);

}

sf::Sprite Tornado::getSprite()
{
    return m_disasterSprite;
}
