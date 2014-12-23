#include <SDL.h>

//#include "Global\Global.h"
#include "BlueShip.h"
#include "../Game.h"
#include "../ControlGfx.h"

#define BLUESHIP_MAX_FRAMES 15
#define BLUESHIP_MAX_PROGRESS 10000
#define BLUESHIP_MIN_PROGRESS 0

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

ControlBlueShip BlueShipController;
const double BlueShipSpeed = -5.0;

BlueShip::BlueShip()
{
    acceleration = Vector3D(0, 0, 0);
    velocity = Vector3D(0, 0, 0);
    location = Vector3D(0, 0, 0);

    lifespan = 255.0f;
	Active = 1;
	CollisionBox.h = SpriteHeight - 16;
	CollisionBox.w = SpriteWidth - 16;
	CollisionBox.x = location.x;
	CollisionBox.y = location.y;

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

BlueShip::BlueShip(Vector3D v)
{
    acceleration = Vector3D(0, 0, 0);
    velocity = Vector3D(0, 0, 0);
    location = v;

    lifespan = 255.0f;

    Active = 1;
    CollisionBox.h = SpriteHeight - 16;
    CollisionBox.w = SpriteWidth - 16;
    CollisionBox.x = location.x;
    CollisionBox.y = location.y;

    LocAndSize.x = 0;
    LocAndSize.y = 0;
    LocAndSize.h = SpriteHeight;
    LocAndSize.w = SpriteWidth;

    PrevFrame = 0;
    Frame = 0;

    for (int i = 0; i < 16; i++)
    {
        Clips[i].x = (Sint16)i * SpriteWidth;
        Clips[i].y = 0;
        Clips[i].h = SpriteHeight;
        Clips[i].w = SpriteWidth;
    }
};

int BlueShip::isColliding(SDL_Rect Box)
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

SDL_Rect BlueShip::UpdateCollisionBox(SDL_Rect Box)
{
    SDL_Rect CollisionBox;
    CollisionBox = Box;

	CollisionBox = LocAndSize;
	return CollisionBox;
}

void BlueShip::Update()
{
    checkEdges(1920 - SpriteWidth, 1080 - SpriteHeight);
    velocity = velocity + acceleration;
    location = velocity + location;
    // add acceleration to velocity
    // add velocity to location
    lifespan -= 2.0f;

	//xPos = BlueShipSpeed * gamestate.DeltaTime;
    LocAndSize.x = GetX();//(Sint16)xPos;
    LocAndSize.y = GetY();//(Sint16)yPos;
	LocAndSize.h = SpriteHeight;
	LocAndSize.w = SpriteWidth;

    CollisionBox.x = GetX() + 16;//(Sint16)xPos;
    CollisionBox.y = GetY() + 16;//(Sint16)yPos;
    CollisionBox.h = 16;
    CollisionBox.w = 16;

	PrevFrame = Frame++;
	if( Frame >= BLUESHIP_MAX_FRAMES )
	{
		Frame = 0;
	}
	UpdateCollisionBox(LocAndSize);
}

void BlueShip::Draw()
{
	SDL_BlitSurface( 
		Gfx.GetSurface( SurfaceID ),
		&Clips[ 0 ], //PrevFrame replaced with 0 as there is no animation
		Gfx.BackBuffer, 
		&GetDestination() 
	);
    SDL_FillRect(Gfx.BackBuffer, &CollisionBox, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 255, 0, 0));
}

SDL_Rect BlueShip::GetDestination()
{
	return LocAndSize;
}

void ControlBlueShip::DrawBlueShip()
{
	std::vector< BlueShip >::iterator i;

	i = BlueShipArrayRef.begin();

	while(i != BlueShipArrayRef.end() )
	{
		i->Update();
        i->applyForce(Vector3D(0, 2 * (double)rand() / (double)RAND_MAX - 1, 0));
		i->Draw();
		
		if( i->LocAndSize.x <= 0.0f - SpriteWidth )
		{
			i = BlueShipArrayRef.erase(i);
		}
		else
		{
			++i;
		}
	}
}

void ControlBlueShip::CreateBlueShip(int iProgress )
{
	if( iProgress > BLUESHIP_MIN_PROGRESS && iProgress < BLUESHIP_MAX_PROGRESS )
	{
        if (std::rand() % 100 + 1 > 99)
        {
            BlueShipArrayRef.push_back(CreateBlueShipByReference(SDL_GetVideoSurface()->w, std::rand() % Gfx.BackBuffer->h, gamestate.m_srfBlueShip));
        }
	}
}

ControlBlueShip::ControlBlueShip()
{
}

ControlBlueShip::~ControlBlueShip()
{
}

BlueShip ControlBlueShip::CreateBlueShipByReference( Sint16 xPos, Sint16 yPos, int surface )
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
	BlueShip temp;
	temp.SurfaceID = surface;
	temp.LocAndSize.x = xPos;
	temp.LocAndSize.y = yPos;

    // Using Vector3D
    BlueShip temp2(Vector3D(xPos,yPos,0.0f));
    temp2.applyForce(Vector3D(BlueShipSpeed, 0, 0));
    temp2.SurfaceID = surface;
    temp2.LocAndSize.x = temp2.GetX();
    temp2.LocAndSize.y = temp2.GetY();

	return temp2;
}