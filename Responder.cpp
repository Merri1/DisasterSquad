#include "Responder.h"


Responder::Responder()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
	m_positionX = 700;
	m_positionY = 500;
	
	m_Texture = (TextureHolder::GetTexture(
		"graphics/player.png"));



    m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_positionX, m_positionY);
	m_Sprite.setTexture(m_Texture);

	m_isSelected = false;



}

int Responder::getPositionX()
{
	return m_positionX;


}

int Responder::getPositionY()
{
	return m_positionY;
}


void Responder::moveTo(int X, int Y)
{
	m_isMoving = true;
	m_DestinationX = X;
	m_DestinationY = Y;



}

void Responder::spawn(int x, int y)
{
	// Place the player in the middle of the arena
	m_positionX = x;
	m_positionY = y;



}
//Moves responder too new clicked position and checks if player is already at that position.

bool Responder::isSelected() {
	return m_isSelected;

}
void Responder::Select(bool Selected)
{
	m_isSelected = Selected;
}
void Responder::update(Time t)
{
	if (m_isMoving)
	{
		
		if (m_positionX != m_DestinationX) 
		{
			if (m_DestinationX > m_positionX) {
				
				m_positionX += m_Speed * t.asMilliseconds();

			}
			else {

				m_positionX -= m_Speed * t.asMilliseconds();

			}

		}
		if (m_positionY != m_DestinationY)
		{
			if (m_DestinationY > m_positionY) {

				m_positionY += m_Speed * t.asMilliseconds();

			}
			else {

				m_positionY -= m_Speed * t.asMilliseconds();

			}

		}
	

	}
	m_Sprite.setPosition(m_positionX, m_positionY);


}

float Responder::getRotation()
{
	return m_Sprite.getRotation();
}

Sprite Responder::getSprite()
{

	return m_Sprite;
}



int Responder::getHealth()
{
	return m_Health;
}




//1024 x576 64/36 tile maps size