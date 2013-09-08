#include "Global\Global.h"
#include "MainMenu.h" 
#include <SDL.h>

enum BName {
	RESUME_GAME,
	NEW_GAME,
	LOAD_GAME,
	SAVE_GAME,
	OPTIONS,
	UNKNOWN,
	CREDITS,
	QUIT_GAME
};

//return by value
SDL_Rect Rectangle(int XPos, int YPos, int Width, int Height)
{
	SDL_Rect Rect;
	Rect.h = Height;
	Rect.w = Width;
	Rect.x = XPos;
	Rect.y = YPos;
	
	return Rect;
}

//Use like this:
//SDL_Rect myRect = Rectangle(5, 5, 50, 20);

//return by reference
void Rectangle(SDL_Rect &Rect, int XPos, int YPos, int Width, int Height)
{
	Rect.h = Height;
	Rect.w = Width;
	Rect.x = XPos;
	Rect.y = YPos;
}

//Use like this:
//SDL_Rect myRect;
//Rectangle(myRect, 5, 5, 50, 20);

MainMenu::MainMenu( int ButtonX, int Surface, int SurfaceButtons )							
{
	surface = Surface;

	SurfaceButt = SurfaceButtons;

	int ArraySize = sizeof(ButtonClips) / sizeof(ButtonClips[0]);
	for( int i = 0; i < ArraySize; i++ )
	{
		ButtonClips[ i ].x = 0;
		ButtonClips[ i ].y = 0;
		ButtonClips[ i ].w = 0;
		ButtonClips[ i ].h = 0;
	}

	ArraySize = sizeof(DestClips) / sizeof(DestClips[0]);
	for( int i = 0; i < ArraySize; i++ )
	{
		DestClips[ i ].x = 0;
		DestClips[ i ].y = 0;
		DestClips[ i ].w = 0;
		DestClips[ i ].h = 0;
	}

	ButtonOptions = false;
	ButtonBack = false; 
	ButtonSound = false;
	ButtonCredits = false;
	ButtonHighScore = false;
	ButtonNewgame = false;

	ButtonClips[ BName::RESUME_GAME ]	= Rectangle( 401, 130, 350, 45 );
	ButtonClips[ BName::NEW_GAME ]		= Rectangle( 401, 186, 350, 45 );
	ButtonClips[ BName::LOAD_GAME ]		= Rectangle( 401, 242, 350, 45 );
	ButtonClips[ BName::SAVE_GAME ]		= Rectangle( 401, 298, 350, 45 );
	ButtonClips[ BName::OPTIONS ]		= Rectangle( 401, 355, 350, 45 );
	ButtonClips[ BName::UNKNOWN ]		= Rectangle( 401, 410, 350, 45 );
	ButtonClips[ BName::CREDITS ]		= Rectangle( 401, 465, 350, 45 );
	ButtonClips[ BName::QUIT_GAME ]		= Rectangle( 401, 519, 350, 45 );
	ButtonClips[ BName::UNKNOWN ]		= Rectangle( 0, 0, 0, 0 );
	ButtonClips[ BName::UNKNOWN ]		= Rectangle( 0, 0, 0, 0 );

	DestClips[ BName::RESUME_GAME ]		= Rectangle( 401, 0, 350, 45 );
	DestClips[ BName::NEW_GAME ]		= Rectangle( 401, 0, 350, 45 );
	DestClips[ BName::LOAD_GAME ]		= Rectangle( 401, 0, 350, 45 );
	DestClips[ BName::SAVE_GAME ]		= Rectangle( 401, 0, 0, 0 );
	DestClips[ BName::OPTIONS ]			= Rectangle( 401, 0, 350, 45 );
	DestClips[ BName::UNKNOWN ]			= Rectangle( 401, 0, 350, 45 );
	DestClips[ BName::CREDITS ]			= Rectangle( 401, 0, 350, 45 );
	DestClips[ BName::QUIT_GAME ]		= Rectangle( 401, 0, 350, 45 );
	DestClips[ BName::UNKNOWN ]			= Rectangle( 401, 0, 0, 0 );
	DestClips[ BName::UNKNOWN ]			= Rectangle( 0, 0, 0, 0 );
}


								