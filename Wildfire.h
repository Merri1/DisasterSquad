#ifndef WILDFIRE_H
#define WILDFIRE_H
#include "Disaster.h"

class Wildfire : public Disaster
{
public:
	Wildfire();
	virtual void spawn(int (&levelArray)[36][64]);
	virtual sf::Sprite getSprite(float elapsedTime);

protected:
	
};

#endif