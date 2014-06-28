#include "Audio.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <Windows.h>
using namespace std;

// 1. this should go into every .cpp , after all header inclusions
#ifdef _WIN32
#ifdef _DEBUG
   #include <crtdbg.h>
   #undef THIS_FILE
   static char THIS_FILE[] = __FILE__;
   #define new       new( _NORMAL_BLOCK, __FILE__, __LINE__)
   #define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif

ControlAudio Audio;
 
ControlAudio::ControlAudio()
{
	cout << "Creating the Audio controller..." << endl;
	for( int i=0; i < 3; i++ )
	{
		Playlist[i] = NULL;
	}
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024)==-1) 
	{
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
	{
		cout << "Supported chunk decoder: [" << Mix_GetChunkDecoder(i) << "]" << endl;
	}

	LoadAudio();
}

void ControlAudio::LoadAudio()
{
	Playlist[0] = Mix_LoadMUS( "Music/sea_battles_in_space.ogg" );
	Playlist[1] = Mix_LoadMUS( "Music/Let_the_Machines_do_the_Whistling_instrumental.ogg" );
	Playlist[2] = Mix_LoadMUS( "Music/all_will_be_well.ogg" );

	Sfx[0] = Mix_LoadWAV( "Sfx/laser_blaster.ogg" );
	Sfx[1] = Mix_LoadWAV( "Sfx/blaster_explosion.ogg" );
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
	if( effect == E_AUDIO::FIRE_LASER )
	{
			Mix_PlayChannel( -1, Sfx[0], 0 );
	}
	if( effect == E_AUDIO::EXPLOSION )
	{
			Mix_PlayChannel( -1, Sfx[1], 0 );
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
	std::cout << "Destroying ControlAudio object..." << endl;

	// Removing reference to loaded Sound Tracks
	for( int i=0; i < (sizeof Playlist / sizeof Playlist[0]); i++ )
	{
		Playlist[i] = NULL;
	}
	
	// Removing reference to loaded SFX
	for( int i=0; i < (sizeof Sfx / sizeof Sfx[0]); i++ )
	{
		Sfx[i] = NULL;
	}
}

void GetFadeStatusMusic()
{ 	
// check the music fade status
switch(Mix_FadingMusic()) {
    case MIX_NO_FADING:
        cout << "Not fading music." << endl;
        break;
    case MIX_FADING_OUT:
        cout << "Fading out music." << endl;
        break;
    case MIX_FADING_IN:
        cout << "Fading in music." << endl;
        break;
	}
}
