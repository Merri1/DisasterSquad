#include "Shop.h"
#include <SFML/Graphics/Sprite.hpp>
using namespace sf;

Shop::Shop(int x, int y){

	m_positionX = x;
	m_positionY = y;
	m_position.x = m_positionX;
	m_position.y = m_positionY;

	m_Sprite.setPosition(m_positionX, m_positionY);
	m_Sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/ui/shop_buy_spritesheet.png"));

	m_isSelected = false;
	m_isPlaced = false;
}

void Shop::setSprite(int shopType) {

	// For buying responders.
	if (shopType == 0) {
		m_Sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/ui/shop_buy_spritesheet.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 0, 0, 40, 40 });
	}
	// For buying wind turbines.
	else if (shopType == 1) {
		m_Sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/ui/shop_buy_spritesheet.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 40, 0, 40, 40 });
	}
	else if (shopType == 2) {
		m_Sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/ui/shop_buy_spritesheet.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 0, 40, 40, 40 });
	}
	else if (shopType == 3) {
		m_Sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/ui/shop_buy_spritesheet.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 40, 40, 40, 40 });
	}
}

int Shop::getPositionX()
{
	return m_position.x;
}

int Shop::getPositionY()
{
	return m_position.y;
}

void Shop::spawn(int x, int y)
{
	
	m_positionX = x;
	m_positionY = y;
}

bool Shop::isSelected() {
	return m_isSelected;
}

void Shop::select(bool Selected)
{
	m_isSelected = Selected;
}

void Shop::Placed(int X, int Y)
{
	m_isSelected = false;
}

float Shop::getRotation()
{
	return m_Sprite.getRotation();
}

Sprite Shop::getSprite()
{
	return m_Sprite;
}


