#include <cmath>
#include "Objects.h"
#include "Game.h"
#include "characters.h"
#include "Timers.h"
#include "Collision.h"
#include "ControlGfx.h"

ControlObject ObjectController;

// Default Constructor for objects
Object::Object()
{
	Active = 0;
	xPos = yPos = 0;
	Width = Height = 0;
	Surface = 0;
	Frame = 0;
	Radius = 0; // fireball crap
	CollisionBox.h = 0;
	CollisionBox.w = 0;
	CollisionBox.x = 0;
	CollisionBox.y = 0;

	int ArraySize = sizeof(Clips) / sizeof(Clips[0]);
	// Zeroing the Clips array
	for( int i = 0; i < ArraySize; i++ )
	{
		Clips[ i ].x = 0;
		Clips[ i ].y = 0;
		Clips[ i ].w = 0;
		Clips[ i ].h = 0;
	}
}

int Object::isActive()
{
	return true;
}

int Object::Initialize(float _xPos = 0.0f, float _yPos = 0.0f, int _Width = 0, int _Height = 0, int _Frame = 0, int _Radius = 0 )
{
	xPos = _xPos;
	yPos = _yPos;
	Width = _Width;
	Height = _Height;
	Frame = _Frame;
	Radius = _Radius;

	int ArraySize = sizeof(Clips) / sizeof(Clips[0]);
	// Zeroing the Clips array
	for( int i = 0; i < ArraySize; i++ )
	{
		Clips[ i ].x = 0;
		Clips[ i ].y = 0;
		Clips[ i ].w = 0;
		Clips[ i ].h = 0;
	}
	return 0;
}

int Object::SetClips(int _xStepping = 0, int _yStepping = 0, int _Width = 0, int _Height = 0)
{
	int ArraySize = sizeof(Clips) / sizeof(Clips[0]);
	for( int i = 0; i < ArraySize; i++ )
	{
		Clips[ i ].x = _xStepping * i;
		Clips[ i ].y = _yStepping;
		Clips[ i ].w = _Width;
		Clips[ i ].h = _Height;
	}
	return 0;
}

Tree::Tree()
{
	SingleClip.h = 180;
	SingleClip.w = 158;
	SingleClip.x = 0;
	SingleClip.y = 0;
}

ControlObject::ControlObject()
{
	//demonLife = new ThingsTodemon;
	//demonLife->Initialize(0,0,50,50,0,0);
	//demonLife->SetClips();
	// Replaced by Initialize function
	//demonLife->Frame = 0;
	//demonLife->Height = 43;
	//demonLife->Width = 49;
	//demonLife->xPos = 0;
	//demonLife->yPos = 0;

	WhichLifeToShow = 0;
	
	destHealth.x = 50; 
	destHealth.y = 550;
	destHealth.w = 70;
	destHealth.h = 20;

	FrameHealth = 0;

	PowerUpMan = false;
}

void ControlObject::CreateObjects()
{
}

void PowerUp::SetFrame()
{
	if( Frame < 3 )
	{
		Frame++;
	}
	else
	{
		Frame = 0;
	}

}

// draws the objects coffins, fireballs etc, that exist and checks for collision 
// fireballs against the enemies and the boss, also the powerup
// shows life and lifeicon
void ControlObject::DrawObjects()
{
	float speed = 500.0f * ( gamestate.DeltaTime / 1000.0f );
    float CoffinTim = 50.0f * ( gamestate.DeltaTime / 1000.0f );

	list< Fireball* > vRemoveFireBall;
	list< Fireball* >::iterator vRemoveIterFireBall;

	list< CEnemy* >vRemoveEnemy;
	list< CEnemy* >::iterator vRemoveIterEnemy; 

	list< Heads* > vRemoveHead;
	list< Heads* >::iterator vRemoveIterHead;

	//SDL_Rect dstRect = { demonLife->xPos, demonLife->yPos, demonLife->Width, demonLife->Height };

	//if( demon.LifeFull_Small )
	//{
	//	demonLife->Frame = 2;

	//	SDL_BlitSurface(	Gfx.GetSurface( gamestate.m_srfdemonLife ), &demonLife->Clips[ demonLife->Frame ],
	//						Gfx.BackBuffer, &dstRect );
	//}
	//else if( demon.LifeMedium_Small )
	//{
	//	demonLife->Frame = 1;

	//	SDL_BlitSurface(	Gfx.GetSurface( gamestate.m_srfdemonLife ), &demonLife->Clips[ demonLife->Frame ],
	//						Gfx.BackBuffer, &dstRect );
	//}
	//else if( demon.LifeLittle_Small )
	//{
	//	demonLife->Frame = 0;

	//	SDL_BlitSurface(	Gfx.GetSurface( gamestate.m_srfdemonLife ), &demonLife->Clips[ demonLife->Frame ],
	//						Gfx.BackBuffer, &dstRect );
	//}

	// x,y,w,h
	BCPlayer._Lives = 3;
	SDL_Rect srfHealth = {0,0,64*BCPlayer._Lives,64};
	SDL_Rect Viewport_srfHealth = {0,0,64*BCPlayer._Lives,64};

	SDL_BlitSurface( Gfx.GetSurface( gamestate.m_srfHealth ), &srfHealth,
					Gfx.BackBuffer, &Viewport_srfHealth );

	//SDL_BlitSurface(	Gfx.GetSurface( gamestate.m_srfdemonHealthAndFire ), &demonLife->HealthClips[ WhichLifeToShow  ],
	//				Gfx.BackBuffer, &ObjectController.destHealth );
}

Fireball::Fireball()
{
	xPos = 0;
	yPos = 0;

	FrameRight = 0;
	FrameLeft = 3;
	FireRight = false;
	FireLeft = false;

	FireWidth = 35;
	FireHeight = 35;
	SetClips(35,35,35,35);
}

/*
void FireBall::SetClips()
{
	for( int i = 0; i < 6; i++ )
	{
		Clips[ i ].x = Width * i;
		Clips[ i ].y = 70;
		Clips[ i ].w = Width;
		Clips[ i ].h = Height;
	}

	Clips[ 6 ].x = 420;
	Clips[ 6 ].y = 60;
	Clips[ 6 ].w = 40;
	Clips[ 6 ].h = 40;

	Clips[ 7 ].x = 480;
	Clips[ 7 ].y = 45;
	Clips[ 7 ].w = 80;
	Clips[ 7 ].h = 70;
}
*/
