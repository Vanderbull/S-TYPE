#include "Intro.h"
#include <SDL.h>
#include "Game.h"

// @date 2012-08-07
/*
void DancingDragon::SetFrame()
{
	if( Frame == 21 )
	{
		DancingDragon::Frame = 0;
	}
	else
	{
		DancingDragon::Frame++;
	}
}

void DancingDragon::SetClips()
{
	for( int index = 0; index < 23; index++ )
	{
		DancingDragon::Clips[ index ].x = index * DancingDragon::Width;
		DancingDragon::Clips[ index ].y = 0;
		DancingDragon::Clips[ index ].h = DancingDragon::Height;
		DancingDragon::Clips[ index ].w = DancingDragon::Width;
	}
}

DancingDragon::DancingDragon( int Surface )
{
	DancingDragon::Frame = 0;
	DancingDragon::PrevFrame = 0;
	DancingDragon::StateCounter = 0;
	DancingDragon::xPos = 0;
	DancingDragon::yPos = 0;
	DancingDragon::surface = Surface;
	DancingDragon::Width = 64;
	DancingDragon::Height = 64;
	DancingDragon::SetClips();
	DancingDragon::AnimationTimestamp = GetTickCount();
}
*/
// sets up the intro where the dudes talk
IntroTalk::IntroTalk( int Surface )
{
	xPos = 100;
	yPos = 200;
	Height = 128;
	Width = 128;
	surface = Surface;
	Frame = 0;
	for( int i = 0; i < 3; i++ )
	{
		srcClips[ i ].x = i * Width;
		srcClips[ i ].y = 0;
		srcClips[ i ].w = Width;
		srcClips[ i ].h = Height;
	}

	CenturionTalks[ 0 ] = "Please all mighty gods help me revenge my family and get my sister back.";
	CenturionTalks[ 1 ] = "I will do anything you ask as long as I get my belowed sister back from those demons.";
	CenturionTalks[ 2 ] = "";
	CenturionTalks[ 3 ] = "My humanity was lost the minute my family was butchered.";
	CenturionTalks[ 4 ] = "";
	CenturionTalks[ 5 ] = "";
	CenturionTalks[ 6 ] = "";
	CenturionTalks[ 7 ] = "I swear to return and claim my humanity back.";

	ZeusTalks[ 0 ]		= "";
	ZeusTalks[ 1 ]		= "";
	ZeusTalks[ 2 ]		= "My son, I hear your prayers. I will fullfill your wishes, but just so you know your humanity will be lost in the process.";
	ZeusTalks[ 3 ]		= "";
	ZeusTalks[ 4 ]		= "OK, Centurion you will get the powers of an ancient god, the possibility to transform into beasts";
	ZeusTalks[ 5 ]		= "This is however nothing you control and you might turn into the beast at any time along your journey.";
	ZeusTalks[ 6 ]		= "Now go Centurion and rescue your sister before your humanity is totally lost and you no longer care.";
	ZeusTalks[ 7 ]		= "";


	CounterWords = 0;
	CounterNextTalker = 0;
	Counter = 0;

	Centurion = true;
	Zeus = false;
	MyDude_Demon = false;
	FirstLine = true;
	SecondLine = false;
	ThirdLine = false;
	Fifth = false;
	Sixth = false;
	Seventh = false;

	Letter = 0;
	LetterHeight = 30;
	LetterWidth = 0;
	y = 20;
	Line = 0;
}

// draws a black background
void IntroTalk::DrawBackground()
{
	SDL_FillRect(gamestate.BackBuffer, NULL, SDL_MapRGB(gamestate.BackBuffer->format, 0,0,0));
}

// all the talking
void IntroTalk::DoTalk()
{
	int DialogScene = 0;

	//The color of the font
	SDL_Color textColor = { 255, 255, 255 };
	SDL_Event input;
	
	SDL_Rect destRect = { Width/2, Height/2, Width, Height };

	bool ZeusDialog[8] = {false,false,true,false,true,true,true,false};
	bool CenturionDialog[8] = {true,true,false,true,false,false,false,true};

	std::string Dialog[10];
	LetterHeight  = 0;

	while( DialogScene < 8 )
	{
		DrawBackground();

		if( CenturionDialog[DialogScene] )
		{
			if( Letter < CenturionTalks[ DialogScene ].length() )
			{
				if( Letter < 40 )
				{
					Dialog[0] += CenturionTalks[ DialogScene ][ Letter++ ];
				}
				else
				{
					Dialog[1] += CenturionTalks[ DialogScene ][ Letter++ ];
					LetterHeight = 1;
				}
			}
			else
			{
				LetterHeight = 0;
				Dialog[0] = "";
				Dialog[1] = "";
				Letter = 0;
				DialogScene++;
			}
			SDL_BlitSurface(	gamestate.GetSurface( surface ), &srcClips[ CENTURION ], 
								gamestate.BackBuffer, &destRect );	
			IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, Dialog[LetterHeight].c_str(), textColor );
			gamestate.apply_surface( 40,LetterHeight*40+300, IntroSurfaces[ 0 ], gamestate.BackBuffer );
		}
		if( ZeusDialog[DialogScene] )
		{
			if( Letter < ZeusTalks[ DialogScene ].length() )
			{
				if(Letter < 40)
				{
					Dialog[0] += ZeusTalks[ DialogScene ][ Letter++ ];
				}
				else
				{
					Dialog[1] += ZeusTalks[ DialogScene ][ Letter++ ];
					LetterHeight = 1;
				}
			}
			else
			{
				LetterHeight = 0;
				Dialog[0] = "";
				Dialog[1] = "";
				Letter = 0;
				DialogScene++;
			}
			SDL_BlitSurface(	gamestate.GetSurface( surface ), &srcClips[ ZEUS ], 
								gamestate.BackBuffer, &destRect );
			IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, Dialog[LetterHeight].c_str(), textColor );
			gamestate.apply_surface( 40,LetterHeight*40+300, IntroSurfaces[ 0 ], gamestate.BackBuffer );
		}

		SDL_PollEvent( &input );
		if( input.type == SDL_KEYDOWN )
		{
			switch( input.key.keysym.sym )
			{
				case SDLK_SPACE:
					DialogScene = 8;
			} break;
		}
		gamestate.FLIP();
		Sleep(50);
	}
	gamestate.GameCondition = GS_LEVEL1;
}
	

	

