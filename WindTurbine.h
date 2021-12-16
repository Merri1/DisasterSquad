#pragma once
#ifndef WINDTURBINE_H
#define WINDTURBINE_H
#include "RenewableSource.h"

class WindTurbine : public RenewableSource
{
public:
	sf::Sprite m_Sprite;
	WindTurbine();
	virtual void spawn();
	virtual sf::Sprite getSprite();

protected:
	
};

#endif