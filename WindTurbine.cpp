#include "WindTurbine.h"
#include <iostream>

WindTurbine::WindTurbine()
{
    RenewableSources();
}


void WindTurbine::spawn()
{

	m_position.x = m_positionX;
	m_position.y = m_positionY;


	m_Sprite.setOrigin(8, 8);
	m_Sprite.setPosition(m_positionX, m_positionY);
	//m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/Shop_collision_box.png"));
	m_Sprite.setTexture(TextureHolder::GetTexture("graphics/menu_icon.png"));
	//m_Sprite.setTextureRect(sf::IntRect{ 16, 16, 16, 20 });

}

sf::Sprite WindTurbine::getSprite()
{
    return m_Sprite;
}


