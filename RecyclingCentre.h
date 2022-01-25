#pragma once
#ifndef RECYCLINGCENTRE_H
#define RECYCLINGCENTRE_H
#include "RenewableSource.h"

class RecyclingCentre : public RenewableSource
{
public:
	sf::Sprite m_Sprite;
	RecyclingCentre();
	virtual void spawn(int x, int y);
	virtual sf::Sprite getSprite();

protected:
	int m_positionX;
	int m_positionY;

};

#endif