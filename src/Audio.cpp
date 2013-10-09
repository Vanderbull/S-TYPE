#include "Audio.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <Windows.h>
using namespace std;

ControlAudio Audio;

// TODO: Fix this function.

 
ControlAudio::ControlAudio()
{
	LoadAudio();
	/*
	SDL_version compile_version;
	const SDL_version *link_version=Mix_Linked_Version();
	SDL_MIXER_VERSION(&compile_version);

	cout << "compiled with SDL_mixer version: " << +compile_version.major << "." << +compile_version.minor << "." << +compile_version.patch;
	cout << "compiled with SDL_mixer version: " << +link_version->major << "." << +link_version->minor << "." << +link_version->patch;

	// load support for the OGG and MOD sample/music formats
	int flags=MIX_INIT_OGG|MIX_INIT_MOD;
	int initted=Mix_Init(flags);
	if(initted&flags != flags) {
		cout << "Mix_Init: Failed to init required ogg and mod support!\n" << "Mix_Init: " << Mix_GetError() << endl;
	}
	
	// start SDL with audio support
	if(SDL_Init(SDL_INIT_AUDIO)==-1) {
		cout << "SDL_Init: " << SDL_GetError() << endl;
		exit(1);
	}
	// open 44.1KHz, signed 16bit, system byte order,
	//      stereo audio, using 1024 byte chunks
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
		cout << "Mix_OpenAudio: " << Mix_GetError() << endl;
		exit(2);
	}

	Mix_Music *music = NULL;
	Mix_Music *musicMenu = NULL;
	Mix_Music *musicOutro = NULL;
	
	Mix_Chunk *Fireball = NULL; 
	Mix_Chunk *Hit = NULL; 
	Mix_Chunk *Punch = NULL; 
	Mix_Chunk *Laugh = NULL; 
	Mix_Chunk *Morph = NULL;
	Mix_Chunk *Boss = NULL;
	Mix_Chunk *FireBallExplode = NULL;

	LoadAudio();
	state_ = 1;
	*/
/*
	while ( Mix_PlayingMusic() == 1 )
{
// get and print the audio format in use
int numtimesopened, frequency, channels;
Uint16 format;
numtimesopened=Mix_QuerySpec(&frequency, &format, &channels);
if(!numtimesopened) {
    printf("Mix_QuerySpec: %s\n",Mix_GetError());
}
else {
    char *format_str="Unknown";
    switch(format) {
        case AUDIO_U8: format_str="U8"; break;
        case AUDIO_S8: format_str="S8"; break;
        case AUDIO_U16LSB: format_str="U16LSB"; break;
        case AUDIO_S16LSB: format_str="S16LSB"; break;
        case AUDIO_U16MSB: format_str="U16MSB"; break;
        case AUDIO_S16MSB: format_str="S16MSB"; break;
    }
    printf("opened=%d times  frequency=%dHz  format=%s  channels=%d",
            numtimesopened, frequency, format_str, channels);
}
printf("volume is now : %d\n", Mix_VolumeMusic(1));
}
Mix_FreeMusic( musica ) ;
*/
	donkey = 0;
}

void ControlAudio::LoadAudio()
{
	if(donkey == 1)
		return;

	/*
	if(SDL_Init(SDL_INIT_AUDIO)==-1) {
		cout << "SDL_Init: " << SDL_GetError() << endl;
		exit(1);
	}
	*/

	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
		cout << "Mix_OpenAudio: " << Mix_GetError() << endl;
		exit(2);
	}
	//Load the music 
	music = Mix_LoadMUS( "Music/music.ogg" ); 
	MenuMusic_ = Mix_LoadMUS( "Music/MenuMusic.ogg" );

	OutroMusic_ = Mix_LoadMUS( "Music/OutroMusic.ogg" );

	// load all sound
	SfxHit_ = Mix_LoadWAV( "Music/SfxHit.ogg" );

	donkey = 1;
}

int ControlAudio::IsPlaying()
{
	state_ = 0;
	return state_;
}
int ControlAudio::GetState()
{
	return state_;
}

void ControlAudio::PlayMusic( int song )
{
	if( song == MUSIC_START )
	{
		Mix_PlayMusic( music, -1 );
	}
	else if( song == MUSIC_MENU )
	{
		// play music forever
		// Mix_Music *music; // I assume this has been loaded already
		if(Mix_PlayMusic(MenuMusic_, -1)==-1) {
			printf("Mix_PlayMusic: %s\n", Mix_GetError());
			// well, there's no music, but most games don't break without music...
		}
	}
	else if( song == MUSIC_OUTRO )
	{
		Mix_PlayMusic( OutroMusic_, -1 );
	}

}
void ControlAudio::PlaySoundEffect( int effect )
{
	if( effect == SOUND_HIT )
	{
			Mix_PlayChannel( -1, SfxHit_, 0 );
	}
	else if( effect == SOUND_GETS_HIT )
	{
			Mix_PlayChannel( -1, SfxHit_, 0 );
	}
}

void ControlAudio::PauseMusic()
{
	static int once = 0;
	if( once != 1)
	{
		Mix_FadeOutMusic(3000);
		//Mix_PauseMusic();
		once = 1;
	}
}

void ControlAudio::UnpauseMusic()
{
	if( Mix_PausedMusic() == 1 )
	{
		Mix_ResumeMusic();
	}
}
