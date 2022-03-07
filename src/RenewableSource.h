#ifndef RENEWABLESOURCE_H
#define RENEWABLESOURCE_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "TextureHolder.h"
#include <random>

using namespace sf;
using namespace std;

class RenewableSource
{
public:
 
    RenewableSource(string type);
    void setSprite();
    void update(float elapsedTime, float spriteTime);
    bool getSpawnStatus();
    void spawn(int x, int y);
    Sprite getSprite();
    bool isSelected();
    bool isPlaced();
    bool isSuitable();
    void setSuitable(bool suitable);
    void select(bool Selected);
    void setPositionX(int x);
    void setPositionY(int y);
    int getPositionX();
    int getPositionY();
    string getType();
    int getPower();
    int getTime();
    int getEnviro();
    int getHealth();

protected:

    Sprite m_Sprite;
    Texture m_Texture;
    Vector2f m_position;

    bool m_spawned = false;
    bool m_isSelected;
    bool m_placed;
    bool m_suitable;
    int m_positionX;
    int m_positionY;
    int m_health;
    string m_type;
    int m_enviroFactor;
    int m_power;
    int m_buildTime;
};
#endif