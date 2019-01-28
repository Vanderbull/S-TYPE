#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class MovingThings
{
public:
	int Frame;
	int Radius;
	Sint16 Width, Height;
	float Speed;

	int Surface;
	SDL_Rect Clips[ 16 ];
	SDL_Rect _Position;
};
