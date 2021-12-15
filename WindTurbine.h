#pragma once
#ifndef WINDTURBINE_H
#define WINDTURBINE_H
#include "RenewableSources.h"

class WindTurbine : public RenewableSources
{
public:
	sf::Sprite m_Sprite;
	WindTurbine();
	virtual void spawn();
	virtual sf::Sprite getSprite();

protected:
	
};

#endif