#pragma once
#include <SDL_mixer.h>

enum{	
	MUSIC_START, 
	MUSIC_MENU, 
	MUSIC_OUTRO, 
	SOUND_MORPH, 
	SOUND_HIT, 
	SOUND_FIRE, 
	SOUND_GETS_HIT, 
	SOUND_DIE, 
	SOUND_BOSS, 
	SOUND_FIREBALL_EXPLODE 
};

class ControlAudio
{
public:
	Mix_Music *music; 
	Mix_Music *MenuMusic_;
	Mix_Music *OutroMusic_;
	Mix_Music *Playlist[3];
	 
	Mix_Chunk *SfxHit_;
	int donkey;

	ControlAudio();
	~ControlAudio();

	void LoadAudio();
	int GetState();
	void PlayMusic( int song );
	void PlaySoundEffect( int effect );
	void PauseMusic();
	void UnpauseMusic();
private:
	int state_;
};

extern ControlAudio Audio;