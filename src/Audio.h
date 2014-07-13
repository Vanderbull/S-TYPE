#pragma once
#include <SDL_mixer.h>

enum E_AUDIO{	
	LASER = 4,
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
    void QuerySpec();
    void Reset(int frequency = 44100, Uint16 format = MIX_DEFAULT_FORMAT, int channels = 2, int chunksize = 1024);
    void Render();
};

extern ControlAudio Audio;