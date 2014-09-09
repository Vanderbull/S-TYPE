#pragma once
#include <SDL.h>

class Outro
{
public:
	Outro();
	int surface;

	Uint16 Height, Width;
	Uint16 xPos, yPos;
	
	SDL_Rect ClipsOutro[ 2 ];
};