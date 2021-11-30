#include "Responder.h"
#include <iostream>

Responder::Responder()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
	m_positionX = 400;
	m_positionY = 300;
	m_position.x = m_positionX;
	m_position.y = m_positionY;
	
	std::cout << m_positionX << " - " << m_positionY << "\n";
	m_Texture = (TextureHolder::GetTexture(
		"graphics/player.png"));



    m_Sprite.setOrigin(8, 8);
	m_Sprite.setPosition(m_positionX, m_positionY);
	m_Sprite.setTexture(m_Texture);

	m_isSelected = false;
	m_isMoving = false;



}

int Responder::getPositionX()
{
	std::cout << m_position.x << " Get vector X coord\n";
	return m_position.x;
}

int Responder::getPositionY()
{
	std::cout << m_positionY << " Get Y coord\n";
	return m_position.y;
}


void Responder::moveTo(int X, int Y)
{
	std::cout << "Move To responder function \n";
	
	m_isSelected = false;
	m_isMoving = true;
	m_DestinationX = X;
	m_DestinationY = Y;

	std::cout << "Dest x: " << m_DestinationX << "  Dest y: " << m_DestinationY << "\n";

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
		std::cout << "Moving...\n";
		std::cout << m_positionX << " x  -  " << m_positionY << "\n";
		
		if(m_positionX != m_DestinationX) 
		{
			if(m_DestinationX > m_positionX) 
			{
				m_positionX += m_Speed; // * t.asSeconds();
				
				if(m_positionX > m_DestinationX)
				{
					m_positionX = m_DestinationX;
				}
			}
			else if(m_DestinationX < m_positionX) 
			{
				m_positionX -= m_Speed; //+ t.asSeconds();

				if(m_positionX < m_DestinationX)
				{
					m_positionX = m_DestinationX;
				}
			}
		}

		if(m_positionY != m_DestinationY)
		{
			if(m_DestinationY > m_positionY)
			{
				m_positionY += m_Speed; // * t.asSeconds();

				if(m_positionY > m_DestinationY)
				{
					m_positionY = m_DestinationY;
				}
			}
			else if(m_DestinationY < m_positionY)
			{
				m_positionY -= m_Speed; // * t.asSeconds();

				if(m_positionY < m_DestinationY)
				{
					m_positionY = m_DestinationY;
				}
			}
		}
		else
		{
			m_isMoving = false;
		}
	}

	m_position.x = m_positionX;
	m_position.y = m_positionY;

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




//1024x576 64/36 tile maps size
