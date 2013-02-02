#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <list>
#include "Objects.h"
#include "MovingThings.h"

class CSkeleton : public MovingThings
{
public:
	
	CSkeleton();
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

	bool Walk, Attack, Die, LeftOf_Demon, RightOf_Demon;

	SDL_Rect SkeletonClips[ 4 ][ 14 ];

private:
};