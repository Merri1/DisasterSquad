#ifndef DISASTER_H
#define DISASTER_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "TextureHolder.h"
#include "SoundManager.h"
#include <random>


class Disaster
{
public:
    Disaster();
    void update();
    void getX();
    void getY();
    bool getSpawnStatus();
    void setSpawnStatus();
    void destroyDisaster();
    virtual void spawn(int (&levelArray)[36][64]);
    virtual sf::Sprite getSprite();
    int getHealth();
    bool isAlive();
    void updateHealth(int damage);
    void chanceToSpread(sf::Vector2f);
    sf::Vector2f getPosition();
    sf::Vector2f m_position;
    static SoundBuffer g_wildfireSoundBuffer; // Global variable
    static SoundBuffer g_tornadoSoundBuffer;

protected:
    const float MAX_HEALTH = 1000;
    Sound m_disasterSound;
    float m_soundVolume;
    int m_difficultyChance; // Chance of spreading depending on selected difficulty 
    float m_health;
    bool m_spawned = false;
    sf::Sprite m_disasterSprite;
    sf::Texture m_spriteTexture;
};
#endif