#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include "SFML/Audio.hpp"

using namespace sf;

class SoundManager
{
public:
	SoundManager();
	void click();
	void shopClick();
	void errorClick();
	void solarSound();
	void turbineSound();
	void recyclingSound();
	SoundBuffer& getFireBuffer();
	SoundBuffer& getTornadoBuffer();
	void gameMusic();

private:
	SoundBuffer m_fireSoundBuffer;
	SoundBuffer m_tornadoSoundBuffer;
	SoundBuffer m_solarSoundBuffer;
	SoundBuffer m_turbineSoundBuffer;
	SoundBuffer m_recyclingSoundBuffer;
	SoundBuffer m_gameMusicBuffer;
	SoundBuffer m_clickSoundBuffer;
	SoundBuffer m_buttonSelectedBuffer;
	SoundBuffer m_errorSelectingBuffer;

	Sound m_clickSound;
	Sound m_fireSound;
	Sound m_tornadoSound;
	Sound m_solarSound;
	Sound m_turbineSound;
	Sound m_recyclingSound;
	Sound m_gameMusicSound;
	Sound m_buttonSelectedSound;
	Sound m_errorSelectingSound;
};
#endif