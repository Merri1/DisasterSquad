#include "RecyclingCentre.h"
#include <iostream>

RecyclingCentre::RecyclingCentre()
{
	RenewableSource();
}

void RecyclingCentre::spawn(int x, int y) {
	m_position.x = x;
	m_position.y = y;

	m_Sprite.setPosition(m_positionX, m_positionY);
	// m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/wind_turbine_spritesheet.png"));
}

sf::Sprite RecyclingCentre::getSprite()
{
	return m_Sprite;
}


