#include "Audio.h"
#include <SDL.h>
#include <SDL_mixer.h>

ControlAudio Audio;

// TODO: Fix this function.

 
ControlAudio::ControlAudio()
{
 
 	
SDL_version compile_version;
const SDL_version *link_version=Mix_Linked_Version();
SDL_MIXER_VERSION(&compile_version);
printf("compiled with SDL_mixer version: %d.%d.%d\n", 
        compile_version.major,
        compile_version.minor,
        compile_version.patch);
printf("running with SDL_mixer version: %d.%d.%d\n", 
        link_version->major,
        link_version->minor,
        link_version->patch);

// load support for the OGG and MOD sample/music formats
int flags=MIX_INIT_OGG|MIX_INIT_MOD;
int initted=Mix_Init(flags);
if(initted&flags != flags) {
    printf("Mix_Init: Failed to init required ogg and mod support!\n");
    printf("Mix_Init: %s\n", Mix_GetError());
    // handle error
}

 	
// start SDL with audio support
if(SDL_Init(SDL_INIT_AUDIO)==-1) {
    printf("SDL_Init: %s\n", SDL_GetError());
    exit(1);
}
// open 44.1KHz, signed 16bit, system byte order,
//      stereo audio, using 1024 byte chunks
if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
    printf("Mix_OpenAudio: %s\n", Mix_GetError());
    exit(2);
}
	Mix_Music *musica = NULL;

musica = Mix_LoadMUS( "Music/musicMenu.ogg" );

	Mix_PlayMusic( musica, 0 ) ;

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
		Mix_PlayMusic( music, -1 );
		LevelSong = true;
		MenuSong = false;
		OutroSong = false;
	
	}
	else if( song == MUSIC_MENU )
	{
		Mix_PlayMusic( musicMenu, -1 );
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
			Mix_PlayChannel( -1, Laugh, 0 );
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
	PlayMusic( 1 );
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
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096 ) == -1 ) 
	{
		return false; 
	} 

	//Load the music 
	music = Mix_LoadMUS( "Music/music.wav" ); 
	musicMenu = Mix_LoadMUS( "Music/musicMenu.ogg" );
	musicOutro = Mix_LoadMUS( "Music/musicOutro.wav" );

	// load all sound
	Morph = Mix_LoadWAV( "Music/Morph.wav" );
	Hit = Mix_LoadWAV( "Music/Hit.wav" );
	Punch = Mix_LoadWAV( "Music/Punch.wav" );
	Laugh =  Mix_LoadWAV( "Music/Laugh.wav" );
	Boss = Mix_LoadWAV( "Music/Boss.wav" );
	Fireball = Mix_LoadWAV( "Music/FireBall.ogg" );
	FireBallExplode = Mix_LoadWAV( "Music/FireballExplode.ogg" );
	
	//If there was a problem loading the sound effects 
	if( ( Fireball == NULL ) || ( Hit == NULL ) || 
		( Punch == NULL ) || ( Laugh == NULL ) || 
		( Boss == NULL ) || ( Morph == NULL ) ||
		( FireBallExplode == NULL ) ) 
	{ 
		return false; 
	} 
	Mix_VolumeMusic(1);
	//If everything loaded fine 
	return true; 
}

void ControlAudio::PauseMusic()
{
	Mix_FadeOutMusic(300);
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
