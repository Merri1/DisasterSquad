#ifndef RESPONDER_H
#define RESPONDER_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "TextureHolder.h"

using namespace sf;
using namespace std;


class Responder
{
public:
    

    Responder();
    Vector2f getPosition();
    int getPositionX();
    int getPositionY();
    //void getSprite();
    void moveTo(vector<int> pathToDestination);
    //void moveTo(int X, int Y);
    void spawn(int x, int y);
    //void fightDisaster();
    int getHealth();
    float getRotation();
    Sprite getSprite();
    bool isSelected();
    bool getIsMoving();
    void setSelected(bool s);
    void select(bool Selected);
    void update(float elapsedTime);
  
   

protected:
    const int START_SPEED = 1;
    const int START_HEALTH = 100;

    Sprite m_Sprite;
    Texture m_Texture;
    Vector2f m_Resolution;
    Vector2f m_position;

    // What size is the current arena
    IntRect m_Area;
    bool m_isMoving;
    int m_Speed;
    int m_Health;
    int m_MaxHealth;
    int m_direction;
    bool m_ID;
    bool m_isSelected;
    int m_positionX;
    int m_positionY;
    int m_destinationTile;
    int m_currentTile;
    float m_speed;
    vector<int> m_pathToFollow;
    int m_deltaDistance = 0;

    int m_DestinationX;
    int m_DestinationY;
};
#endif
