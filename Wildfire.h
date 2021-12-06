#pragma once
#ifndef WILDFIRE_H
#define WILDFIRE_H
#include "Disaster.h"

class Wildfire : public Disaster
{
public:
	Wildfire();

protected:
	sf::Sprite m_wildfireSprite;
	sf::Texture m_wildfireTexture;
};

#endif