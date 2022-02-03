#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include "SFML/Audio.hpp"

using namespace sf;

class SoundManager
{
public:
	SoundManager();
	void click();
	SoundBuffer& getFireBuffer();
	SoundBuffer& getTornadoBuffer();
	void gameMusic();

private:
	SoundBuffer m_fireSoundBuffer;
	SoundBuffer m_tornadoSoundBuffer;
	SoundBuffer m_gameMusicBuffer;
	SoundBuffer m_clickSoundBuffer;

	Sound m_clickSound;
	Sound m_fireSound;
	Sound m_tornadoSound;
	Sound m_gameMusicSound;
};
#endif