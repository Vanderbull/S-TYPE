#include <SDL.h>

#include "PurpleShip.h"
#include "../Game.h"
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

ControlPurpleShip PurpleShipController;
const float PurpleShipSpeed = 0.0001f;

PurpleShip::PurpleShip()
{
	Active = 1;
	CollisionBox.h = 0;
	CollisionBox.w = 0;
	CollisionBox.x = SpriteHeight;
	CollisionBox.y = SpriteWidth;

	LocAndSize.x = 0;
	LocAndSize.y = 0;
	LocAndSize.h = SpriteHeight;
	LocAndSize.w = SpriteWidth;

	PrevFrame = 0;
	Frame = 0;

	for( int i = 0; i < 16; i++ )
	{
        Clips[i].x = (Sint16)i * SpriteWidth;
		Clips[ i ].y = 0;
		Clips[ i ].h = SpriteHeight;
		Clips[ i ].w = SpriteWidth;
	}
}

int PurpleShip::isColliding(SDL_Rect Box)
{
    SDL_Rect CollisionBox;
    CollisionBox = Box;
	int PlayerRight = Spaceship.GetPosition().x + Spaceship.GetPosition().w;
	int PlayerLeft = Spaceship.GetPosition().x;
	int PlayerTop = Spaceship.GetPosition().y;
	int PlayerBottom = Spaceship.GetPosition().x + Spaceship.GetPosition().h;

	int EnemyRight = LocAndSize.x + LocAndSize.w;
	int EnemyLeft = LocAndSize.x;
	int EnemyTop = LocAndSize.y;
	int EnemyBottom = LocAndSize.y + LocAndSize.h;

	if (EnemyBottom < PlayerTop) return(0);
	if (EnemyTop > PlayerBottom) return(0);
  
	if (EnemyRight < PlayerLeft) return(0);
	if (EnemyLeft > PlayerRight) return(0);
	return(1);
}

SDL_Rect PurpleShip::UpdateCollisionBox(SDL_Rect Box)
{
    SDL_Rect CollisionBox;
    CollisionBox = Box;

	CollisionBox = LocAndSize;
	return CollisionBox;
}

void PurpleShip::Update()
{
    //if (rand()%100 > 50)
        FireMissile();
	xPos = PurpleShipSpeed * gamestate.DeltaTime;
    LocAndSize.x -= (Sint16)xPos;
	LocAndSize.h = SpriteHeight;
	LocAndSize.w = SpriteWidth;

	PrevFrame = Frame++;
	if( Frame >= PURPLESHIP_MAX_FRAMES )
	{
		Frame = 0;
	}
	UpdateCollisionBox(LocAndSize);
}

void PurpleShip::Draw()
{
	SDL_BlitSurface( 
		Gfx.GetSurface( SurfaceID ),
		&Clips[ 0 ], //PrevFrame replaced with 0 as there is no animation
		Gfx.BackBuffer, 
		&GetDestination() 
	);
}

SDL_Rect PurpleShip::GetDestination()
{
	return LocAndSize;
}

void PurpleShip::FireMissile()
{
return;
static int Flyby;
SDL_Rect Position;
if (Flyby > 100)
    Flyby = 0;
Position.x = GetDestination().x - Flyby;
Position.y = GetDestination().y;
Position.h = GetDestination().h;
Position.w = GetDestination().w;
Flyby++;
    SDL_BlitSurface(
        Gfx.GetSurface(SurfaceID),
        &Clips[0],
        Gfx.BackBuffer,
        &Position
        );
}

void ControlPurpleShip::DrawPurpleShip()
{
	std::vector< PurpleShip >::iterator i;

	i = PurpleShipArrayRef.begin();

	while(i != PurpleShipArrayRef.end() )
	{
		i->Update();
		i->Draw();
		
		if( i->LocAndSize.x <= 0.0f - SpriteWidth )
		{
			i = PurpleShipArrayRef.erase(i);
		}
		else
		{
			++i;
		}
	}
}

void ControlPurpleShip::CreatePurpleShip(int iProgress )
{
	if( iProgress > PURPLESHIP_MIN_PROGRESS && iProgress < PURPLESHIP_MAX_PROGRESS )
	{
        if (std::rand() % 1000 + 1 > 999)
        {
            PurpleShipArrayRef.push_back(CreatePurpleShipByReference(SDL_GetVideoSurface()->w, std::rand() % Gfx.BackBuffer->h, gamestate.m_srfPurpleShip));
        }
	}
}

ControlPurpleShip::ControlPurpleShip()
{
}

ControlPurpleShip::~ControlPurpleShip()
{
}

PurpleShip ControlPurpleShip::CreatePurpleShipByReference( Sint16 xPos, Sint16 yPos, int surface )
{
	static int old_y_pos = 0;
	
	while( yPos > old_y_pos && yPos < old_y_pos + 128 )
	{
        yPos = (Sint16)(std::rand() % Gfx.BackBuffer->h - 128);
	}
	if( yPos < 64 )
		yPos = 64;
	if( yPos > Gfx.BackBuffer->h - 128 )
        yPos = (Sint16)(Gfx.BackBuffer->h - 128);
	PurpleShip temp;
	temp.SurfaceID = surface;
	temp.LocAndSize.x = xPos;
	temp.LocAndSize.y = yPos;

	return temp;
}