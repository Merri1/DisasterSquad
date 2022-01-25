#pragma once
#ifndef SOLARPANEL_H
#define SOLARPANEL_H
#include "RenewableSource.h"

class SolarPanel : public RenewableSource
{
public:
	sf::Sprite m_Sprite;
	SolarPanel();
	virtual void spawn(int x, int y);
	virtual sf::Sprite getSprite();

protected:
	int m_positionX;
	int m_positionY;
};

#endif#pragma once
