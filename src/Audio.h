#pragma once
#include <SDL_mixer.h>

enum E_AUDIO{	
	FIRE_LASER = 4,
	EXPLOSION = 5
};

class ControlAudio
{
public:

	Mix_Music *Playlist[100];
	Mix_Chunk *Sfx[100];

	ControlAudio();
	~ControlAudio();

	void LoadAudio();
	void PlayMusic( int song );
	void PlaySoundEffect( int effect );
	void PauseMusic();
	void UnpauseMusic();
	void GetFadeStatusMusic();
};

extern ControlAudio Audio;