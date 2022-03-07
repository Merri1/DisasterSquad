#ifndef WINDTURBINE_H
#define WINDTURBINE_H
#include "RenewableSource.h"

class WindTurbine : public RenewableSource
{
public:
	sf::Sprite m_Sprite;
	WindTurbine();
	void update();
	void setSprite();

protected:
	int m_positionX;
	int m_positionY;
};

#endif