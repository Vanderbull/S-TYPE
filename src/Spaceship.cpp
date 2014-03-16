#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Spaceship.h"

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

BaseSpaceShip Spaceship(0, 0, 300, SPACESHIP_HEIGHT, SPACESHIP_WIDTH);

BaseSpaceShip::BaseSpaceShip()
{
	cout << "Creating Spaceship controller..." << endl;
}

BaseSpaceShip::BaseSpaceShip(int surface, int Xpos, int Ypos, int height, int width)
{
	_Lives = 3;
	BaseSpaceShip::SetAliveState(AliveState::ALIVE);

	isHit            = false; 

	_Position.x = Xpos;
	_Position.y = Ypos;
	_Position.h = 100;
	_Position.w = 130;

	//_SurfaceID = surface;

	xVelocity = 0.000015f; 
	yVelocity = 0.0f;
	_CollisionBox.x = 0;
	_CollisionBox.y = 0;
	_CollisionBox.w = width;
	_CollisionBox.h = height;
}

// checks if OK to move
bool BaseSpaceShip::CheckBoundaries()
{
	return true;
}

bool BaseSpaceShip::IsAttacking()
{
	return true;
}

// updates BCPlayer animations and moving, moved code to Update function

void BaseSpaceShip::Update()
{
	if( yVelocity != 0 )
	{
		if( (BaseSpaceShip::_Position.y + yVelocity > 0) && (BaseSpaceShip::_Position.y + yVelocity < Gfx.screen->h - 100) )
		{
			BaseSpaceShip::_Position.y += yVelocity;
		}
	}
	if( xVelocity != 0 )
	{
		if( (BaseSpaceShip::_Position.x + xVelocity > 0) && (BaseSpaceShip::_Position.x + xVelocity < Gfx.screen->w - 128) )
		{
			BaseSpaceShip::_Position.x += xVelocity;
		}
	}
}


void BaseSpaceShip::SetClips()
{
	int ArraySizeColumns = sizeof(AnimationArrays) / sizeof(AnimationArrays[0]);
	int ArraySizeRows = sizeof(AnimationArrays[0]) / sizeof(AnimationArrays[0][0]);
	for( int Column = 0; Column < ArraySizeColumns; Column++ )
	{
		for( int Row = 0; Row < ArraySizeRows; Row++ )
		{
            Spaceship.AnimationArrays[Column][Row].x = 0;//Row * _Position.w;
            Spaceship.AnimationArrays[Column][Row].y = 0;//Column * _Position.h;
            Spaceship.AnimationArrays[Column][Row].h = 130;//_Position.h;
            Spaceship.AnimationArrays[Column][Row].w = 100;//_Position.w;
		}
	}
}


void BaseSpaceShip::UpdatePosition(float xUnits, float yUnits)
{
	if( _Position.x < 0.0f )
	{
	}
	else
	{
	}
}

void BaseSpaceShip::Reset()
{
	BaseSpaceShip::SetAliveState(AliveState::ALIVE);

	isHit            = false; 

	_Position.x = Engine.SPAWN_POSITION_X;
	_Position.y = Engine.SPAWN_POSITION_Y;
	_Position.h = SPACESHIP_HEIGHT;
	_Position.w = SPACESHIP_WIDTH;

	xVelocity = 0.000015f; 
	yVelocity = 0.0f;
}

void BaseSpaceShip::Died()
{
	Gfx.srfText = TTF_RenderText_Shaded( Gfx.DefaultFont, " YOU DIED STOP PLAYING GOD DAMN YOU!!!!! ", Gfx.WhiteRGB, Gfx.BlackRGB );
	Gfx.apply_surface( 250, 500, Gfx.srfText, Gfx.BackBuffer );
	Gfx.FLIP();

	gamestate.GameState.push(GAME_PLAYER_DIED_STATE);
}

Uint32 BaseSpaceShip::TimeLeft(void)
{
	static Uint32 next_time = 0;
	Uint32 now;

	now = SDL_GetTicks();
	if ( next_time <= now ) {
		next_time = now+TICK_INTERVAL;
		return(0);
	}
	return(next_time-now);
}

int BaseSpaceShip::Animate()
{
	if( _AnimationFrame > 6 )
		_AnimationFrame = 0;
	if(TimeLeft() == 0 )
		++_AnimationFrame;
	return _AnimationFrame;
}