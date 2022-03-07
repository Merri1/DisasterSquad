#include "Responder.h"
#include <iostream>
#include <vector>

// Our main characters. Initialize starting variables, set starting textures.
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
	m_Sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/character_animations/responder_collision_box.png"));
	m_Sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/character_animations/responder_spritesheet_new.png"));
	m_Sprite.setTextureRect(sf::IntRect{ 16, 16, 16, 20 });

	m_isSelected = false;
	m_isMoving = false;
}

// Get current position (vector) of responder.
Vector2f Responder::getPosition()
{
	return m_position;
}

// Get x position of responder.
int Responder::getPositionX()
{
	return m_position.x;
}

// Get y position of responder.
int Responder::getPositionY()
{
	return m_position.y;
}

// Set responder to selected flag (for sprite animation).
void Responder::setSelected(bool s) {
	m_isSelected = s;
}

// Move to current position using Merri's pathfinding system.
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

// New responder spawn coordinates.
void Responder::spawn(int x, int y)
{
	// Place the player in the middle of the arena
	m_positionX = x;
	m_positionY = y;
}

// Check if responder is currently selected.
bool Responder::isSelected() {
	return m_isSelected;
}

// Select responder for highlighting.
void Responder::select(bool Selected)
{
	m_isSelected = Selected;
	
	// If clicked by the player, switch to front facing highlight.
	if (m_isSelected == true) {

		m_Sprite.setTextureRect(sf::IntRect{ 16, 48, 16, 20 });
	}
}

// Every frame, update the position of our character. Pass in movement time and animation time.
void Responder::update(float elapsedTime, float spriteTime)
{
	if (m_isMoving)
	{
		if (m_currentTile == m_destinationTile || m_pathToFollow.empty())
		{
			m_isMoving = false;

			// If stopped, reset animation back to standing.
			// Reset moving East.
			if (m_direction == 0) 
			{
				m_Sprite.setTextureRect(sf::IntRect{ 16, 144, 16, 20 });
			}
			// Reset moving West.
			else if (m_direction == 1)
			{
				m_Sprite.setTextureRect(sf::IntRect{ 16, 80, 16, 20 });
			}
			// Reset moving South.
			else if (m_direction == 2)
			{
				m_Sprite.setTextureRect(sf::IntRect{ 16, 16, 16, 20 });
			}
			// Reset moving North.
			else if (m_direction == 3)
			{
				m_Sprite.setTextureRect(sf::IntRect{ 16, 208, 16, 20 });
			}
		}
		else
		{
			m_deltaDistance += 2;

			// Check if moving East
			if (m_pathToFollow.front() == m_currentTile + 1)
			{
				m_direction = 0;
				m_positionX += 2;
				m_Sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/character_animations/responder_collision_box.png"));
				m_Sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/character_animations/responder_spritesheet_new.png"));

				// Animate sprite moving East.
				if (spriteTime < 125)
				{
					m_Sprite.setTextureRect(sf::IntRect{ 16, 144, 16, 20 });
				}
				else if (spriteTime >= 125 && spriteTime < 250)
				{
					m_Sprite.setTextureRect(sf::IntRect{ 48, 144, 16, 20 });
				}
				else if (spriteTime >= 250 && spriteTime < 375)
				{
					m_Sprite.setTextureRect(sf::IntRect{ 80, 144, 16, 20 });
				}
				else if (spriteTime >= 375)
				{
					m_Sprite.setTextureRect(sf::IntRect{ 112, 144, 16, 20 });
				}
			}
			// Esle check if moving West
			else if (m_pathToFollow.front() == m_currentTile - 1)
			{
				m_direction = 1;
				m_positionX -= 2;
				m_Sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/character_animations/responder_collision_box.png"));
				m_Sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/character_animations/responder_spritesheet_new.png"));

				// Animate sprite moving West.
				if (spriteTime < 125)
				{
					m_Sprite.setTextureRect(sf::IntRect{ 16, 80, 16, 20 });
				}
				else if (spriteTime >= 125 && spriteTime < 250)
				{
					m_Sprite.setTextureRect(sf::IntRect{ 48, 80, 16, 20 });
				}
				else if (spriteTime >= 250 && spriteTime < 375)
				{
					m_Sprite.setTextureRect(sf::IntRect{ 80, 80, 16, 20 });
				}
				else if (spriteTime >= 375)
				{
					m_Sprite.setTextureRect(sf::IntRect{ 112, 80, 16, 20 });
				}
			}

			// Check if moving South
			if (m_pathToFollow.front() == m_currentTile + 64)
			{
				m_direction = 2;
				m_positionY += 2;
				m_Sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/character_animations/responder_collision_box.png"));
				m_Sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/character_animations/responder_spritesheet_new.png"));

				// Animate sprite moving South.
				if (spriteTime < 125)
				{
					m_Sprite.setTextureRect(sf::IntRect{ 16, 16, 16, 20 });
				}
				else if (spriteTime >= 125 && spriteTime < 250)
				{
					m_Sprite.setTextureRect(sf::IntRect{ 48, 16, 16, 20 });
				}
				else if (spriteTime >= 250 && spriteTime < 375)
				{
					m_Sprite.setTextureRect(sf::IntRect{ 80, 16, 16, 20 });
				}
				else if (spriteTime >= 375)
				{
					m_Sprite.setTextureRect(sf::IntRect{ 112, 16, 16, 20 });
				}
			}

			// Else check if moving North
			else if (m_pathToFollow.front() == m_currentTile - 64)
			{
				m_direction = 3;
				m_positionY -= 2;
				m_Sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/character_animations/responder_collision_box.png"));
				m_Sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/character_animations/responder_spritesheet_new.png"));

				// Animate sprite moving North.
				if (spriteTime < 125)
				{
					m_Sprite.setTextureRect(sf::IntRect{ 16, 208, 16, 20 });
				}
				else if (spriteTime >= 125 && spriteTime < 250)
				{
					m_Sprite.setTextureRect(sf::IntRect{ 48, 208, 16, 20 });
				}
				else if (spriteTime >= 250 && spriteTime < 375)
				{
					m_Sprite.setTextureRect(sf::IntRect{ 80, 208, 16, 20 });
				}
				else if (spriteTime >= 375)
				{
					m_Sprite.setTextureRect(sf::IntRect{ 112, 208, 16, 20 });
				}
			}

			if (m_deltaDistance > 16)
			{
				m_positionY = (m_positionY / 16 * 16 + 8);
				m_positionX = (m_positionX / 16 * 16 + 8);

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

// Get rotation of the responder.
float Responder::getRotation()
{
	return m_Sprite.getRotation();
}

// Get responder sprite image.
Sprite Responder::getSprite()
{
	return m_Sprite;
}

// Get current health of responder.
int Responder::getHealth()
{
	return m_Health;
}

// Check if responder is currently moving.
bool Responder::getIsMoving()
{
	return m_isMoving;
}
