//methods TODO:
//inherits from
/*

*/

//Wind turbine
//Solar panel
//Recycling Plant

//Shop data
//Shop UI

#include "Shop.h"
#include <SFML/Graphics/Sprite.hpp>
using namespace sf;

Shop::Shop()
{
	m_positionX = 150;
	m_positionY = 2;
	m_position.x = m_positionX;
	m_position.y = m_positionY;

	m_Sprite.setPosition(m_positionX, m_positionY);
	m_Sprite.setTexture(TextureHolder::GetTexture("graphics/wind_turbine_buy_button.png"));

	m_isSelected = false;
	m_isPlaced = false;
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







