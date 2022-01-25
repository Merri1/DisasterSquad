#include "WindTurbine.h"
#include <iostream>

WindTurbine::WindTurbine() : RenewableSource() {

	m_Sprite.setPosition(m_positionX, m_positionY);
	m_Sprite.setOrigin(5, 5);
	m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/wind_turbine_spritesheet.png"));

	m_isSelected = false;
}

void WindTurbine::update() {

}

void WindTurbine::setSprite() {

	if (m_type == "turbine") {
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/wind_turbine_spritesheet.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 16, 0, 16, 32 });
	}
	else if (m_isSelected == false) {
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/wind_turbine_spritesheet.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 16, 48, 32, 80 });
	}

}