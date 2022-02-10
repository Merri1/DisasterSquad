#ifndef TORNADO_H
#define TORNADO_H
#include "Disaster.h"

class Tornado : public Disaster
{
public:
	Tornado();
	virtual void spawn(int(&levelArray)[36][64]);
	virtual sf::Sprite getSprite(float elapsedTime);

protected:

};

#endif