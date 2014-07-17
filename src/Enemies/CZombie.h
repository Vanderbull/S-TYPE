#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <list>
#include "Objects.h"
#include "MovingThings.h"

class CZombie : public MovingThings
{
public:
	
	CZombie();
	void Set_Clips( int WhichTypeOfEnemy ); // Should be replaced by objects SetClips
	void SetFrame();

	int xPos, yPos;
	int Width, Height;
	int Surface;
	int PrevFrame, Frame, Radius, 
		WalkFrameLeft, WalkFrameRight, 
		AttackFrameRight, AttackFrameLeft, 
		DieFrameLeft, DieFrameRight, 
		AnimCounter;

	bool Walk, Attack, Die, LeftOf_demon, RightOf_demon;

	SDL_Rect ZombieClips[ 10 ];

private:
};