#pragma once
#ifndef RENEWABLESOURCE_H
#define RENEWABLESOURCE_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

class RenewableSource
{
public:
    RenewableSource();
    sf::Vector2f getPosition();
    void moveTo(sf::Vector2f);
    void spawn(sf::Vector2f);
    void turbine();
    void solar();
    void recycling();
    enum renewableType{WIND, SOLAR, RECYCLING};
    // Check renewable source can be placed on a tile (later)

protected:
    renewableType m_type;
    bool m_ID;
    bool m_isSelected();
    sf::Vector2f m_position;
};
#endif