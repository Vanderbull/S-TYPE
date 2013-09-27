#pragma once
#include <SDL.h>

class Outro
{
public:
	Outro();
	int surface;

	int Height, Width;
	int xPos, yPos;
	
	SDL_Rect ClipsOutro[ 2 ];
};