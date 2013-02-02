#pragma once
#include <SDL.h>
#include <SDL_image.h>

class MovingThings
{
public:
	float xPos, yPos;
	int Frame;
	int Radius;
	int Width, Height;
	int Speed;
	
	int Surface;
	SDL_Rect Clips[ 16 ];
};