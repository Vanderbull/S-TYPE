#include "Audio.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

//#include <SDL.h>
//#include <SDL_mixer.h>
#include <iostream>
using namespace std;

#include "../Game.h"
// 1. this should go into every .cpp , after all header inclusions
#ifdef _WIN32
    #include <Windows.h>
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
    QuerySpec();
	LoadAudio();
    Reset();
    cout << "Resetting with default value" << endl;
    Reset(22050);
}

void ControlAudio::SetVolume(int /*volume*/, int /*id*/)
{
    //BUG When activating this
    //Mix_VolumeChunk(Sfx[id], volume);
}

void ControlAudio::LoadAudio()
{
	Playlist[0] = Mix_LoadMUS( "assets/sfx/sea_battles_in_space.ogg" );
	Playlist[1] = Mix_LoadMUS( "assets/sfx/Let_the_Machines_do_the_Whistling_instrumental.ogg" );
	Playlist[2] = Mix_LoadMUS( "assets/sfx/all_will_be_well.ogg" );
    Playlist[3] = Mix_LoadMUS("assets/sfx/time.ogg");
    Playlist[4] = Mix_LoadMUS("assets/sfx/listen/04.ogg");

	Sfx[0] = Mix_LoadWAV( "assets/sfx/laser_blaster.ogg" );
    Sfx[1] = Mix_LoadWAV( "assets/sfx/blaster_explosion.ogg");
    Sfx[2] = Mix_LoadWAV( "assets/sfx/pew_pew.ogg");
}

void ControlAudio::PlayMusic( int song )
{
	//If there is no music playing
    if( Mix_PlayingMusic() == 0 )
    {
        Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
		if(Mix_PlayMusic(Playlist[song], -1)==-1)
		{
			std::cout << "Mix_PlayMusic: " << Mix_GetError() << endl;
		}
		else
		{
			std::cout << "Mix_PlayMusic is playing song number " << song << endl;
		}
	}
}

void ControlAudio::PlaySoundEffect( int effect )
{
	if( effect == E_AUDIO::LASER )
	{
        Mix_VolumeChunk(Sfx[0], 10);
		Mix_PlayChannel( -1, Sfx[0], 0 );
	}
	if( effect == E_AUDIO::EXPLOSION )
	{
        Mix_VolumeChunk(Sfx[1], 10);
		Mix_PlayChannel( -1, Sfx[1], 0 );
	}
    if (effect == 10)
    {
        Mix_PlayChannel(-1, Sfx[2], 0);
    }
}

void ControlAudio::PauseMusic()
{
    Mix_PauseMusic();
}

void ControlAudio::ResumeMusic()
{
	Mix_ResumeMusic();
}

ControlAudio::~ControlAudio()
{
	std::cout << "Destroying ControlAudio object..." << endl;

	// Removing reference to loaded Sound Tracks
	for( unsigned int i=0; i < (sizeof Playlist / sizeof Playlist[0]); i++ )
	{
		Playlist[i] = NULL;
	}

	// Removing reference to loaded SFX
	for( unsigned int i=0; i < (sizeof Sfx / sizeof Sfx[0]); i++ )
	{
		Sfx[i] = NULL;
	}
}

void ControlAudio::GetFadeStatusMusic()
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

void ControlAudio::QuerySpec()
{
/*
    // get and print the audio format in use
    int numtimesopened, frequency, channels;
    Uint16 format;
    numtimesopened = Mix_QuerySpec(&frequency, &format, &channels);
    if (!numtimesopened) {
        printf("Mix_QuerySpec: %s\n", Mix_GetError());
    }
    else {
        char *format_str = "Unknown";
        switch (format) {
        case AUDIO_U8: format_str = "U8"; break;
        case AUDIO_S8: format_str = "S8"; break;
        case AUDIO_U16LSB: format_str = "U16LSB"; break;
        case AUDIO_S16LSB: format_str = "S16LSB"; break;
        case AUDIO_U16MSB: format_str = "U16MSB"; break;
        case AUDIO_S16MSB: format_str = "S16MSB"; break;
        }
        cout << "opened=" << numtimesopened << " times " << "frequency=" << frequency << " Hz " << "format=" << format_str << " channels=" << channels << endl;
    }
*/
}
void ControlAudio::Reset(int frequency, Uint16 format, int channels, int chunksize)
{
    cout << "Resetting the audio device..." << endl;
    Mix_CloseAudio();
    if (Mix_OpenAudio(frequency, format, channels, chunksize) == -1)
    {
        cout << "Mix_OpenAudio: " << Mix_GetError() << endl;
        exit(2);
    }
    else
    {
        std::cout << "Opening audio mixer with MIX_DEFAULT_FORMAT" << endl;
    }
    QuerySpec();
}
void ControlAudio::Render()
{
    Gfx.RenderText("Rendering the Audio controller...",0,100);
    int frequency, channels;
    Uint16 format;
    Mix_QuerySpec(&frequency, &format, &channels);
    std::string ControlText;
    ControlText = "Frequency: ";
    ControlText.append(std::to_string(frequency).c_str());
    ControlText.append(",Format:");
    ControlText.append(std::to_string(format).c_str());
    ControlText.append(",Channels:");
    ControlText.append(std::to_string(channels).c_str());
    Gfx.RenderText(ControlText.c_str(),0,20);
}
