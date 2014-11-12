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

    bool MusicToggle;

	ControlAudio();
	~ControlAudio();

    void Pause(int channel_id){ Mix_Pause(channel_id); };
    void Resume(int channel_id){ Mix_Resume(channel_id); };
    void SetVolume(int volume, int id);
	void LoadAudio();
	void PlayMusic( int song );
	void PlaySoundEffect( int effect );
	void PauseMusic();
	void ResumeMusic();
	void GetFadeStatusMusic();
    void QuerySpec();
    void Reset(int frequency = 44100, Uint16 format = MIX_DEFAULT_FORMAT, int channels = 2, int chunksize = 1024);
    void Render();

    //Tells you if music is actively playing, or not.
    //Note: Does not check if the channel has been paused.
    //Returns : Zero if the music is not playing, or 1 if it is playing
    int IsPlaying(){ return Mix_PlayingMusic(); };

    //Tells you if music is paused, or not.
    //Note: Does not check if the music was been halted after it was paused, which may seem a little weird.
    //Returns : Zero if music is not paused. 1 if it is paused.
    int IsPaused(){ return Mix_PausedMusic(); }
    
    bool ToggleMusic(){ return MusicToggle = !MusicToggle; };
    bool State(){ return MusicToggle; };
};

extern ControlAudio Audio;