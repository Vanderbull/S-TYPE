#include "Audio.h"
#include <SDL_mixer.h>

// @date 2012-08-07

ControlAudio Audio;

// TODO: Fix this function.

 
ControlAudio::ControlAudio()
{
	Mix_Music *music = NULL;
	Mix_Music *musicMenu = NULL;
	Mix_Music *musicOutro = NULL;
	
	Mix_Chunk *Fireball = NULL; 
	Mix_Chunk *Hit = NULL; 
	Mix_Chunk *Punch = NULL; 
	Mix_Chunk *Dontknow = NULL; 
	Mix_Chunk *Morph = NULL;
	Mix_Chunk *Boss = NULL;
	Mix_Chunk *FireBallExplode = NULL;

	MusicOn = false;
	MusicPaused = false;

	bool check = false;
	LevelSong = false;
	MenuSong = false;
	BossEffect = false;
	OutroSong = false;

	check = LoadFiles();
}

void ControlAudio::PlayMusic( int song )
{
	if( song == MUSIC_START )
	{
		//Mix_PlayMusic( music, -1 );
		LevelSong = true;
		MenuSong = false;
		OutroSong = false;
	
	}
	else if( song == MUSIC_MENU )
	{
		//Mix_PlayMusic( musicMenu, -1 );
		MenuSong = true;
		LevelSong = false;
		OutroSong = false;
	}
	else if( song == MUSIC_OUTRO )
	{
		//Mix_PlayMusic( musicOutro, -1 );
		MenuSong = false;
		LevelSong = false;
		OutroSong = true;
	}

}
void ControlAudio::PlaySoundEffect( int effect )
{
	if( effect == SOUND_MORPH )
	{
			Mix_PlayChannel( -1, Morph, 0 );
	}
	else if( effect == SOUND_HIT )
	{
			Mix_PlayChannel( -1, Punch, 0 );
	}
	else if( effect == SOUND_FIRE )
	{
			Mix_PlayChannel( -1, Fireball, 0 );
	}
	else if( effect == SOUND_GETS_HIT )
	{
			Mix_PlayChannel( -1, Hit, 0 );
	}
	else if( effect == SOUND_DIE )
	{
			Mix_PlayChannel( -1, Dontknow, 0 );
	}
	else if( effect == SOUND_BOSS )
	{
			Mix_PlayChannel( -1, Boss, 0 );
	}
	else if( effect == SOUND_FIREBALL_EXPLODE )
	{
		Mix_PlayChannel( -1, FireBallExplode, 0 );
	}
}

void ControlAudio::PlayIntroSong()
{
	if( LevelSong == true )
	{
		PauseMusic();
	}
	if( MenuSong == false )
	{
		PlayMusic( 1 );
	}
}
void ControlAudio::PlayLevelSong()
{

}

bool ControlAudio::LoadFiles()
{
	if( Mix_OpenAudio( 22500, MIX_DEFAULT_FORMAT, 2, 800 ) == -1 ) 
	{ 
		return false; 
	} 

	//Load the music 
	music = Mix_LoadMUS( "Music/music.wav" ); 
	musicMenu = Mix_LoadMUS( "Music/musicMenu.wav" );
	musicOutro = Mix_LoadMUS( "Music/musicOutro.wav" );

	// load all sound
	Morph = Mix_LoadWAV( "Music/Morph.wav" );
	Hit = Mix_LoadWAV( "Music/Hit.wav" );
	Punch = Mix_LoadWAV( "Music/Punch.wav" );
	Dontknow =  Mix_LoadWAV( "Music/Dontknow.wav" );
	Boss = Mix_LoadWAV( "Music/Boss.wav" );
	Fireball = Mix_LoadWAV( "Music/FireBall.wav" );
	FireBallExplode = Mix_LoadWAV( "Music/FireballExplode.wav" );
	
	//If there was a problem loading the sound effects 
	if( ( Fireball == NULL ) || ( Hit == NULL ) || 
		( Punch == NULL ) || ( Dontknow == NULL ) || 
		( Boss == NULL ) || ( Morph == NULL ) ||
		( FireBallExplode == NULL ) ) 
	{ 
		return false; 
	} 
	
	//If everything loaded fine 
	return true; 
}

void ControlAudio::PauseMusic()
{
	Mix_PauseMusic();
	MusicPaused = true;
}

void ControlAudio::UnpauseMusic()
{
	if( Mix_PausedMusic() == 1 )
	{
		Mix_ResumeMusic();
		MusicPaused = false;
	}
}
