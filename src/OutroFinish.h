#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//#include <SDL.h>

class Outro
{
public:
	Outro();
	int surface;

	Uint16 Height, Width;
	Uint16 xPos, yPos;

	SDL_Rect ClipsOutro[ 2 ];
};
