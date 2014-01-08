#include <cmath>
#include "Objects.h"
#include "Game.h"
#include "SpaceShip.h"
#include "Timers.h"
#include "Collision.h"
#include "ControlGfx.h"

// 1. this should go into every .cpp , after all header inclusions
#ifdef _WIN32
#ifdef _DEBUG
   #include <crtdbg.h>
   #undef THIS_FILE
   static char THIS_FILE[] = __FILE__;
   #define new       new( _NORMAL_BLOCK, __FILE__, __LINE__)
   #define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif

ControlObject ObjectController;

// Default Constructor for objects
Object::Object()
{
	Active = 0;
	SurfaceID = 0;
	Frame = 0;
	
	LocAndSize.h = 0;
	LocAndSize.w = 0;
	LocAndSize.x = 0;
	LocAndSize.y = 0;

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

bool Object::isActive()
{
	return Active;
}

int Object::Initialize( SDL_Rect iData,  int _Frame = 0 )
{
	LocAndSize = iData;
	CollisionBox = LocAndSize;
	Frame = _Frame;

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

ControlObject::ControlObject()
{
	destHealth.x = 50; 
	destHealth.y = 550;
	destHealth.w = 70;
	destHealth.h = 20;

	FrameHealth = 0;
}

void ControlObject::CreateObjects()
{
}

void ControlObject::DrawObjects()
{
	list< CEnemy* >vRemoveEnemy;
	list< CEnemy* >::iterator vRemoveIterEnemy; 

	// x,y,w,h
	SDL_Rect srfHealth = {0,0,64*BCSpaceShip._Lives,64};
	SDL_Rect Viewport_srfHealth = {0,0,64*BCSpaceShip._Lives,64};

	SDL_BlitSurface( Gfx.GetSurface( gamestate.m_srfHealth ), &srfHealth,
					Gfx.BackBuffer, &Viewport_srfHealth );
}