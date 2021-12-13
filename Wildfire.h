#pragma once
#ifndef WILDFIRE_H
#define WILDFIRE_H
#include "Disaster.h"

class Wildfire : public Disaster
{
public:
	Wildfire();
	virtual void spawn();
	virtual sf::Sprite getSprite();

protected:
	
};

#endif