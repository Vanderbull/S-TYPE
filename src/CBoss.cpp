#include "CBoss.h"
 
CBoss gBoss;

CBoss::CBoss()
{
	Height = 300;
	Width = 150;

	BossLife = 400;
	BossDead = false;

	BossWidth = 0; 
	BossHeight = 120;

	HeadsComing = false;
	HeadAnimation = false;
	HeadTimer = 0;
	SizeHeads = 1;
	
	AnimPaceBoss = 0;
	State = 0;
	Frame = 0;

	for( int i = 0; i < 8; i++ )
	{
		Clips[ i ].x = i * Width;
		Clips[ i ].y = 0;
		Clips[ i ].h = Height;
		Clips[ i ].w = Width;
	}
}
void CBoss::Update()
{
}
void CBoss::SetClips()
{
}
void CBoss::SetSurface(int iSurface)
{
	Surface_ = iSurface;
}