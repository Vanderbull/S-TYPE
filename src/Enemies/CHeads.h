#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <list>
//#include "Objects.h"
#include "MovingThings.h"

class CHeads : public MovingThings
{
public:
	
	CHeads();
 	int GetFrame();
	void SetFrame( int WhichFrame );
	void UpdateFrame();

	SDL_Rect GetClips( int WhichClip );

	float length;
	float HowFarSpeed;
	float HowFar;
	int state;
	float HeadTimer;

	int HeadHeight, HeadWidth;


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

	SDL_Rect HeadClips[ 4 ][ 14 ];

private:
};