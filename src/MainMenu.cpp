#include "MainMenu.h" 
#include <SDL.h>

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

	ButtonClips[ 0 ] = Rectangle( 50, 140, 250, 60 );
	ButtonClips[ 1 ] = Rectangle( 50, 267, 475, 60 );
	ButtonClips[ 2 ] = Rectangle( 50, 400, 450, 70 );
	ButtonClips[ 3 ] = Rectangle( 0, 0, 0, 0 );
	ButtonClips[ 4 ] = Rectangle( 325, 0, 325, 70 );
	ButtonClips[ 5 ] = Rectangle( 325, 70, 325, 70 );
	ButtonClips[ 6 ] = Rectangle( 325, 70, 325, 70 );
	ButtonClips[ 7 ] = Rectangle( 325, 140, 325, 70 );
	ButtonClips[ 8 ] = Rectangle( 0, 0, 0, 0 );
	ButtonClips[ 9 ] = Rectangle( 0, 0, 0, 0 );

	DestClips[ 0 ] = Rectangle( 50, 140, 250, 60 );
	DestClips[ 1 ] = Rectangle( 50, 267, 475, 60 );
	DestClips[ 2 ] = Rectangle( 50, 400, 450, 70 );
	DestClips[ 3 ] = Rectangle( 0, 0, 0, 0 );
	DestClips[ 4 ] = Rectangle( 325, 200, 325, 70 );
	DestClips[ 5 ] = Rectangle( 325, 270, 325, 70 );
	DestClips[ 6 ] = Rectangle( 325, 270, 325, 70 );
	DestClips[ 7 ] = Rectangle( 475, 460, 325, 70 );
	DestClips[ 8 ] = Rectangle( 0, 0, 0, 0 );
	DestClips[ 9 ] = Rectangle( 0, 0, 0, 0 );
}


								