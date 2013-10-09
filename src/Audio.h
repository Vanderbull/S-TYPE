#pragma once
#include <SDL_mixer.h>

// @date 2012-08-07

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

/// <summary>A class that controls the audio</summary>
class ControlAudio
{
public:
	Mix_Music *music; 
	Mix_Music *MenuMusic_;
	Mix_Music *OutroMusic_;
	 
	Mix_Chunk *SfxHit_;
	int donkey;

	ControlAudio();
	~ControlAudio(){};

	void LoadAudio();
	int IsPlaying();
	int GetState();
	void PlayMusic( int song );
	void PlaySoundEffect( int effect );
	void PauseMusic();
	void UnpauseMusic();
private:
	int state_;
};

extern ControlAudio Audio;