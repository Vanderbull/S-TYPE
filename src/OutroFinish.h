#pragma once
#include <SDL.h>

// @date 2012-08-07

class Outro
{
public:
	Outro();
	int surface;

	int Height, Width;
	int xPos, yPos;
	
	SDL_Rect ClipsOutro[ 2 ];
};