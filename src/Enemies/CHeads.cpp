#include "CHeads.h"

CHeads::CHeads()
{
	Width = 54;
	Height = 54;

	HeadHeight = 30;
	HeadWidth = 30;

	Frame = 0;
	HowFar = 0.0f;
	HeadTimer = 0.0f;
	HowFarSpeed = 0.0f;

	state = 0;
	
	Clips[0].x = 1050;
	Clips[0].y = 0;
	Clips[0].h = 77;
	Clips[0].w = 55;

	Clips[1].x = 1125;
	Clips[1].y = 0;
	Clips[1].h = 74;
	Clips[1].w = 65;

	Clips[2].x = 1190;
	Clips[2].y = 0;
	Clips[2].h = 74;
	Clips[2].w = 75;

	Clips[3].x = 1060;
	Clips[3].y = 87;
	Clips[3].h = 50;
	Clips[3].w = 55;

	Clips[4].x = 1125;
	Clips[4].y = 85;
	Clips[4].h = 55;
	Clips[4].w = 60;

	Clips[5].x = 1195;
	Clips[5].y = 80;
	Clips[5].h = 54;
	Clips[5].w = 70;
}

int CHeads::GetFrame()
{
	return 0;
}

void CHeads::SetFrame( int WhichFrame )
{
}

void CHeads::UpdateFrame()
{
}

void CHeads::Set_Clips( int WhichTypeOfEnemy )
{
}

void CHeads::SetFrame()
{
}
SDL_Rect CHeads::GetClips( int WhichClip )
{
	return Clips[ WhichClip ];
}
