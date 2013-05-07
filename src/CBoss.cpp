#include "CBoss.h"
#include <iostream>
#include <list>
using namespace std;
#include "Enemies.h"
#include "Game.h"
#include "Timers.h"
#include "Objects.h"
#include "Collision.h"
#include "ControlGfx.h"

CBoss gBoss;

// Collision code from old boss code
//Heads * head = ( *h );
//if( CollisionController.CollisionCircle( temp, head, false ) )
//{
//	gamestate.AddScore(5);
//	vRemoveHead.push_back( ( *h ) );
//	vRemoveFireBall.push_back( ( *i ) );
//}

// Part for damaging the boss also removed from gamestate code
//if( CollisionController.CollisionCircle( temp, gamestate.pBoss, true ) )
//{
//	vRemoveFireBall.push_back( ( *i ) ); 
//	gamestate.AddScore(5);
//	gamestate.pBoss->BossLife -= 50;
//	if( gamestate.pBoss->BossLife < 0 )
//	{
//		gamestate.pBoss->BossDead = true;
//	}
//}

CBoss::CBoss()
{
	CollisionBox.h = 300;
	CollisionBox.w = 150;
	CollisionBox.x = 630;
	CollisionBox.y = 290;

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
		Clips[ i ].x = i * CollisionBox.w;
		Clips[ i ].y = 0;
		Clips[ i ].h = CollisionBox.h;
		Clips[ i ].w = CollisionBox.w;
	}
	Timer = 0;
}

CHeads * CBoss::CreateBossHeads( int xPos, int yPos, int surface, int lengthOfTravel )
{
	CHeads * temp = new CHeads;
	temp->xPos = xPos;
	temp->yPos = yPos;
	temp->Surface = surface;
	temp->length = lengthOfTravel;

	temp->Radius = ( temp->HeadWidth > temp->HeadHeight ) ? temp->HeadWidth / 2 : temp->HeadHeight;

	return temp;
}

void CBoss::Update()
{
	SDL_Rect destRect = {	630, 290, CollisionBox.w, CollisionBox.h };
	SDL_BlitSurface( Gfx.GetSurface( 10 ), &Clips[0], Gfx.BackBuffer, &destRect );

	list< CHeads* >::iterator i = _BossHeads.begin();

	float HeadSpeed = 3.0f;
	
	int Length = rand() % ( SDL_GetVideoSurface()->w - 100 ) + 30;

	if( Timer > 50 )
	{
		Timer = 0;
	}

	if( Timer == 0 )
	{
		UpdateFrame();
		if( GetFrame() == 5)
			_BossHeads.push_back( CreateBossHeads( 640, 300, Surface, Length ) );
	}

	Timer++;
	
	list< CHeads* >::iterator iterator = _BossHeads.begin();
	while( iterator != _BossHeads.end() )
	{
		SDL_Rect HeadDest = { (*iterator)->xPos, (*iterator)->yPos, (*iterator)->Width, (*iterator)->Height };
			
		SDL_BlitSurface(	Gfx.GetSurface( 10 ), &(*iterator)->GetClips((*iterator)->GetFrame()), Gfx.BackBuffer, &HeadDest );
		(*iterator)->length -= 3.0f;
		if(  (*iterator)->length > 0 ) 
		{
			(*iterator)->xPos -= 3.0f; 
			++iterator;
		}
		else if( (*iterator)->length <= 0 )
		{
			(*iterator)->yPos += 3.0f;
			++iterator;
		}
		else if( (*iterator)->yPos > SDL_GetVideoSurface()->h )
		{
			iterator = _BossHeads.erase(iterator);
		}
	}
}

void CBoss::UpdateFrame()
{
	if( Frame >= 6 )
	{
		Frame = 0;
	}
	else
		Frame++;
};
int CBoss::GetFrame()
{
	return Frame;
};

void CBoss::SetClips()
{
}
void CBoss::SetSurface(int iSurface)
{
	Surface_ = iSurface;
}