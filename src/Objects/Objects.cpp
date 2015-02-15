#include <cmath>
#include "Objects.h"
#include "../Game.h"
#include "../SpaceShip.h"
#include "../Collision.h"
#include "../ControlGfx.h"

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

SDL_Rect Object::GetRenderBox()
{
    logger.write(__LINE__, __FUNCTION__);

    SDL_Rect RenderBox;
    RenderBox.x = location.x;
    RenderBox.y = location.y;
    RenderBox.h = SpriteHeight;
    RenderBox.w = SpriteWidth;

    return RenderBox;
}

SDL_Rect Object::UpdateCollisionBox(SDL_Rect Box)
{
    logger.write(__LINE__, __FUNCTION__);

    CollisionBox = Box;

    return CollisionBox;
}

int Object::isColliding(SDL_Rect Box)
{
    logger.write(__LINE__, __FUNCTION__);

    int PlayerRight = Spaceship.GetPosition().x + Spaceship.GetPosition().w;
    int PlayerLeft = Spaceship.GetPosition().x;
    int PlayerTop = Spaceship.GetPosition().y;
    int PlayerBottom = Spaceship.GetPosition().x + Spaceship.GetPosition().h;

    int EnemyRight = Box.x + Box.w;
    int EnemyLeft = Box.x;
    int EnemyTop = Box.y;
    int EnemyBottom = Box.y + Box.h;

    if (EnemyBottom < PlayerTop) return(0);
    if (EnemyTop > PlayerBottom) return(0);

    if (EnemyRight < PlayerLeft) return(0);
    if (EnemyLeft > PlayerRight) return(0);
    return(1);
}

/////////////////////////////////////////////////////////////////////
// ControlObjects ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

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
	SDL_Rect srfHealth = {0,0,64*Spaceship._Lives,64};
	SDL_Rect Viewport_srfHealth = {0,0,64*Spaceship._Lives,64};

	SDL_BlitSurface( Gfx.GetSurface( gamestate.m_srfHealth ), &srfHealth,
					Gfx.BackBuffer, &Viewport_srfHealth );
}