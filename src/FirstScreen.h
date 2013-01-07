#pragma once
#include <SDL.h>

// @date 2012-08-07

class FirstScreen
{
public:
	FirstScreen( int ButtonX, int Surface, int SurfaceButtons );

	//int xPos, yPos;
	//int Width, Height;
	int surface;
	int SurfaceButt;
	SDL_Rect ButtonClips[ 10 ];
	SDL_Rect DestClips[ 10 ];

	bool ButtonOptions;
	bool ButtonNewgame;
	bool ButtonQuit;
	bool ButtonBack;
	bool ButtonSound; 
	bool ButtonCredits;
	bool ButtonHighScore;

	//int ButtonXpos;
	//int Button_Width, Button_Height;
	//int Button_Small_Width,	Button_Small_Height;
};