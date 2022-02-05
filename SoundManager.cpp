#include "Soundmanager.h"

SoundManager::SoundManager()
{
	m_fireSoundBuffer.loadFromFile("sounds/fire.wav");
	m_tornadoSoundBuffer.loadFromFile("sounds/tornado.wav");
	m_gameMusicBuffer.loadFromFile("sounds/game-music.ogg");
	m_clickSoundBuffer.loadFromFile("sounds/click.ogg");
	m_buttonSelectedBuffer.loadFromFile("sounds/button_selected.wav");
	m_errorSelectingBuffer.loadFromFile("sounds/cannot_select.wav");


	//m_fireSound.setBuffer(m_fireSoundBuffer);
	//m_tornadoSound.setBuffer(m_tornadoSoundBuffer);
	m_gameMusicSound.setBuffer(m_gameMusicBuffer);
	m_clickSound.setBuffer(m_clickSoundBuffer);
	m_buttonSelectedSound.setBuffer(m_buttonSelectedBuffer);
	m_errorSelectingSound.setBuffer(m_errorSelectingBuffer);
}

void SoundManager::click()
{
	m_clickSound.play();
}

void SoundManager::shopClick()
{
	m_buttonSelectedSound.play();
}

void SoundManager::errorClick()
{
	m_errorSelectingSound.play();
}

void SoundManager::gameMusic()
{
	m_gameMusicSound.setVolume(20);
	m_gameMusicSound.play();
	m_gameMusicSound.setLoop(true);
}

SoundBuffer& SoundManager::getFireBuffer()
{
	return m_fireSoundBuffer;
}

SoundBuffer& SoundManager::getTornadoBuffer()
{
	return m_tornadoSoundBuffer;
}

