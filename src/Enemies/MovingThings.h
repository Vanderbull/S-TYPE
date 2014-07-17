#pragma once
#include <SDL.h>
#include <SDL_image.h>

class MovingThings
{
public:
	//float xPos, yPos;
	int Frame;
	int Radius;
	Sint16 Width, Height;
	float Speed;
	
	int Surface;
	SDL_Rect Clips[ 16 ];
	SDL_Rect _Position;
};