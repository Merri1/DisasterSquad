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

    m_Sprite.setOrigin(8, 8);
	m_Sprite.setPosition(m_positionX, m_positionY);
	m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_collision_box.png"));
	m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_spritesheet.png"));
	m_Sprite.setTextureRect(sf::IntRect{ 16, 16, 16, 20 });

	m_isSelected = false;
	m_isMoving = false;
}

int Responder::getPositionX()
{
	return m_position.x;
}

int Responder::getPositionY()
{
	return m_position.y;
}


void Responder::moveTo(int X, int Y)
{	
	m_isSelected = false;
	m_isMoving = true;
	m_DestinationX = X;
	m_DestinationY = Y;
<<<<<<< Updated upstream

	// Moving West.
	if (m_DestinationX > m_positionX) {
		
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_collision_box.png"));
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_spritesheet.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 16, 144, 16, 20 });
	}
	// Moving East.
	else if (m_DestinationX < m_positionX) {

		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_collision_box.png"));
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_spritesheet.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 16, 80, 16, 20 });
	}
	// Moving South.
	else if (m_DestinationY > m_positionY) {

		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_collision_box.png"));
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_spritesheet.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 16, 16, 16, 20 });
	}
	// Moving North.
	else if (m_DestinationY < m_positionY) {

		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_collision_box.png"));
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_spritesheet.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 16, 208, 16, 20 });
	}
=======
>>>>>>> Stashed changes
}

void Responder::spawn(int x, int y)
{
	// Place the player in the middle of the arena
	m_positionX = x;
	m_positionY = y;
}

bool Responder::isSelected() {
	return m_isSelected;

}
void Responder::select(bool Selected)
{
	m_isSelected = Selected;
}

void Responder::update(float elapsedTime)
{
	if (m_isMoving)
	{		
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
		
		if(m_positionX == m_DestinationX && m_positionY == m_DestinationY)
		{
			m_isMoving = false;
		}
	}

	m_position.x = m_positionX;
	m_position.y = m_positionY;

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




//1024x576 64/36 tile maps size
