//methods TODO:
//inherits from
/*

*/


#include "RenewableSources.h"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
using namespace sf;
using namespace std;

RenewableSources::RenewableSources()
{

}

void RenewableSources::spawn()
{

    m_spawned = true;
    m_position.x = 500;
    m_position.y = 300;

    cout << "x = " << m_position.x << " and y = " << m_position.y;


}

bool RenewableSources::getSpawnStatus()
{

    return m_spawned;

}

void RenewableSources::update()
{
    // Update the disaster
}

int RenewableSources::getPositionX()
{
    return m_position.x;
}

int RenewableSources::getPositionY()
{
    return m_position.y;
}

sf::Sprite RenewableSources::getSprite()
{
    return m_disasterSprite;
}


bool RenewableSources::isSelected()
{
    cout << "Turbine Selected";
    return m_isSelected;

}

void RenewableSources::select(bool Selected)
{
    m_isSelected = Selected;
}








