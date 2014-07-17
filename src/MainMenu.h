#pragma once
#include <SDL.h>

// MainMenu for the game
// input: int button,int surface,int surfacebutton
class MainMenu
{
public:
	MainMenu( int ButtonX, int Surface, int SurfaceButtons );

	int surface;
	int SurfaceButt;
	SDL_Rect ButtonClips[ 10 ];
	SDL_Rect DestClips[ 10 ];

	bool ButtonOptions;
	bool ButtonNewgame;
	bool ButtonBack;
	bool ButtonSound; 
	bool ButtonCredits;

	//bool ButtonHighScore;
};