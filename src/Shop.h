#ifndef SHOP_H
#define SHOP_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "TextureHolder.h"

using namespace sf;

class Shop
{
public:

    Sprite m_Sprite;
    Texture m_Texture;
    Vector2f m_Resolution;
    Vector2i m_position;

    Shop(int x, int y);

    int getPositionX();
    int getPositionY();
    void spawn(int x, int y);
    bool isSelected();
    void setSprite(int shopType);
    void Placed(int postionX, int positionY);
    //void Placed(bool Placed);
    void select(bool Selected);
    float getRotation();

    Sprite getSprite();

protected:
    bool m_ID;
    bool m_isSelected;
    bool m_isPlaced;
    int m_positionX;
    int m_positionY;

};
#endif
