#include "Audio.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <Windows.h>
using namespace std;

ControlAudio Audio;
 
ControlAudio::ControlAudio()
{
	for( int i=0; i < 3; i++ )
	{
		Playlist[i] = NULL;
	}
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
		cout << "Mix_OpenAudio: " << Mix_GetError() << endl;
		exit(2);
	}
	else
	{
		std::cout << "Opening audio mixer with MIX_DEFAULT_FORMAT" << endl;
	}
    int i;
	const int total = Mix_GetNumChunkDecoders();
	for (i = 0; i < total; i++)
		printf("Supported chunk decoder: [%s]\n", Mix_GetChunkDecoder(i));

	cin.get();
	LoadAudio();
}

void ControlAudio::LoadAudio()
{
	std::cout << "Loading audio..." << endl;

	Playlist[0] = Mix_LoadMUS( "Music/MenuMusic.ogg" );
	Playlist[1] = Mix_LoadMUS( "Music/Let_the_Machines_do_the_Whistling_instrumental.ogg" );
	Playlist[2] = Mix_LoadMUS( "Music/Coffin_Ships.ogg" );

	music = Mix_LoadMUS( "Music/MenuMusic.ogg" );

	MenuMusic_ = Mix_LoadMUS( "Music/MenuMusic.ogg" );

	OutroMusic_ = Mix_LoadMUS( "Music/Coffin_Ships.ogg" );

	SfxHit_ = Mix_LoadWAV( "Music/SfxHit.ogg" );
}

int ControlAudio::GetState()
{
	return state_;
}

void ControlAudio::PlayMusic( int song )
{
	//If there is no music playing
    if( Mix_PlayingMusic() == 0 )
    {
		if(Mix_PlayMusic(Playlist[song], -1)==-1) 
		{
			std::cout << "Mix_PlayMusic: " << Mix_GetError() << endl;
			cin.get();
		}
		else
		{
			std::cout << "Mix_PlayMusic is playing song number " << song << endl;
		}
	}
}
void ControlAudio::PlaySoundEffect( int effect )
{
	Mix_PlayChannel( -1, SfxHit_, 0 );
	if( effect == SOUND_HIT )
	{
			Mix_PlayChannel( -1, SfxHit_, 10 );
	}
	else if( effect == SOUND_GETS_HIT )
	{
			Mix_PlayChannel( -1, SfxHit_, 0 );
	}
}

void ControlAudio::PauseMusic()
{
	if( Mix_PlayingMusic() == 1 )
	{
		Mix_FadeOutMusic(3000);
	}
}

void ControlAudio::UnpauseMusic()
{
	if( Mix_PausedMusic() == 1 )
	{
		Mix_ResumeMusic();
	}
}
ControlAudio::~ControlAudio()
{
	std::cout << "Destroying ControlAudio object" << endl;
	for( int i=0; i < 3; i++ )
	{
		Playlist[i] = NULL;
	}
}
