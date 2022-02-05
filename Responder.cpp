#include "Responder.h"
#include <iostream>
#include <vector>

Responder::Responder()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
	m_positionX = 408;
	m_positionY = 314;
	m_position.x = m_positionX;
	m_position.y = m_positionY;
	m_direction = 0;

	m_Sprite.setOrigin(8, 14);
	m_Sprite.setPosition(m_positionX, m_positionY);
	m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_collision_box.png"));
	m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_spritesheet.png"));
	m_Sprite.setTextureRect(sf::IntRect{ 16, 16, 16, 20 });

	m_isSelected = false;
	m_isMoving = false;
}

Vector2f Responder::getPosition()
{
	return m_position;
}

int Responder::getPositionX()
{
	return m_position.x;
}

int Responder::getPositionY()
{
	return m_position.y;
}

void Responder::setSelected(bool s) {
	m_isSelected = s;
}


void Responder::moveTo(vector<int> pathToDestination)
{
	m_pathToFollow = pathToDestination;

	m_isSelected = false;
	m_isMoving = true;

	// Pop first tile of path vector (store first then erase) as current tile
	if (!m_pathToFollow.empty())
	{
		m_currentTile = m_pathToFollow.front();
		// Store last tile in path vector as destination
		m_destinationTile = m_pathToFollow.back();
		
		m_pathToFollow.erase(m_pathToFollow.begin());
	}
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
	
	if (m_isSelected == true) {
		
		if (m_direction == 0) {
			m_Sprite.setTextureRect(sf::IntRect{ 16, 48, 16, 20 });
		}
		else if (m_direction == 1) {
			m_Sprite.setTextureRect(sf::IntRect{ 144, 16, 16, 20 });
		}
		else if (m_direction == 2) {
			m_Sprite.setTextureRect(sf::IntRect{ 16, 112, 16, 20 });
		}
		else {
			m_Sprite.setTextureRect(sf::IntRect{ 16, 176, 16, 20 });
		}
	}
	else {
		if (m_direction == 0) {
			m_Sprite.setTextureRect(sf::IntRect{ 16, 16, 16, 20 });
		}
		else if (m_direction == 1) {
			m_Sprite.setTextureRect(sf::IntRect{ 16, 208, 16, 20 });
		}
		else if (m_direction == 2) {
			m_Sprite.setTextureRect(sf::IntRect{ 16, 80, 16, 20 });
		}
		else {
			m_Sprite.setTextureRect(sf::IntRect{ 16, 144, 16, 20 });
		}
	}
}

void Responder::update(float elapsedTime)
{
	if (m_isMoving)
	{
		if (m_currentTile == m_destinationTile || m_pathToFollow.empty())
		{
			m_isMoving = false;
		}
		else
		{
			m_deltaDistance += 2;

			// Check if moving East
			if (m_pathToFollow.front() == m_currentTile + 1)
			{
				m_positionX += 2;
				m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_collision_box.png"));
				m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_spritesheet.png"));
				m_Sprite.setTextureRect(sf::IntRect{ 16, 144, 16, 20 });
			}
			// Esle check if moving West
			else if (m_pathToFollow.front() == m_currentTile - 1)
			{
				m_positionX -= 2;
				m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_collision_box.png"));
				m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_spritesheet.png"));
				m_Sprite.setTextureRect(sf::IntRect{ 16, 80, 16, 20 });
			}

			// Check if moving South
			if (m_pathToFollow.front() == m_currentTile + 64)
			{
				m_positionY += 2;
				m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_collision_box.png"));
				m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_spritesheet.png"));
				m_Sprite.setTextureRect(sf::IntRect{ 16, 16, 16, 20 });
			}
			// Else check if moving North
			else if (m_pathToFollow.front() == m_currentTile - 64)
			{
				m_positionY -= 2;
				m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_collision_box.png"));
				m_Sprite.setTexture(TextureHolder::GetTexture("graphics/character_animations/responder_spritesheet.png"));
				m_Sprite.setTextureRect(sf::IntRect{ 16, 208, 16, 20 });
			}

			if (m_deltaDistance > 16)
			{
				m_positionY = m_positionY / 16 * 16 + 8;
				m_positionX = m_positionX / 16 * 16 + 8;

				if (!m_pathToFollow.empty())
				{
					m_currentTile = m_pathToFollow.front();
					m_pathToFollow.erase(m_pathToFollow.begin());
					m_deltaDistance = 0;
				}
			}
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
