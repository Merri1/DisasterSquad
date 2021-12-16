//methods TODO:
//inherits from
/*

*/


#include "RenewableSource.h"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
using namespace sf;
using namespace std;

RenewableSource::RenewableSource()
{

}

void RenewableSource::spawn()
{

    m_spawned = true;
    m_position.x = 500;
    m_position.y = 300;

    cout << "x = " << m_position.x << " and y = " << m_position.y;


}

bool RenewableSource::getSpawnStatus()
{

    return m_spawned;

}

void RenewableSource::update()
{
    // Update the disaster
}

int RenewableSource::getPositionX()
{
    return m_position.x;
}

int RenewableSource::getPositionY()
{
    return m_position.y;
}

sf::Sprite RenewableSource::getSprite()
{
    return m_disasterSprite;
}


bool RenewableSource::isSelected()
{
    cout << "Turbine Selected";
    return m_isSelected;

}

void RenewableSource::select(bool Selected)
{
    m_isSelected = Selected;
}








