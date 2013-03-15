#pragma once
#include <SDL_mixer.h>

// @date 2012-08-07

enum{	MUSIC_START, MUSIC_MENU, MUSIC_OUTRO, SOUND_MORPH, SOUND_HIT, SOUND_FIRE, 
		SOUND_GETS_HIT, SOUND_DIE, SOUND_BOSS, SOUND_FIREBALL_EXPLODE };

/// <summary>A class that controls the audio</summary>
class ControlAudio
{
public:
	ControlAudio();

	bool LoadFiles();

	Mix_Music *Music_;

	Mix_Music *music; 
	Mix_Music *musicMenu;
	Mix_Music *musicOutro;
	
	Mix_Chunk *Fireball; 
	Mix_Chunk *Hit; 
	Mix_Chunk *Punch; 
	Mix_Chunk *Laugh; 
	Mix_Chunk *Morph;
	Mix_Chunk *Boss;
	Mix_Chunk *FireBallExplode;

	bool MusicOn;
	bool MusicPaused;
	bool BossEffect;

	bool LevelSong, MenuSong, OutroSong;

	void PlayMusic( int song );
	void PlaySoundEffect( int effect );
	void PauseMusic();
	void UnpauseMusic();
	void PlayIntroSong();
	void PlayLevelSong();
};

extern ControlAudio Audio;