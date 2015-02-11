#include <cmath>
#include <random>
#include "Powerup.h"
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

ControlPowerup PowerupController;

Powerup::Powerup()
{
    Activate();
	
    CollisionBox.x = 0;
	CollisionBox.y = 0;
	CollisionBox.h = SpriteHeight;
	CollisionBox.w = SpriteWidth;

	LocAndSize.x = 0;
	LocAndSize.y = 0;
	LocAndSize.h = SpriteHeight;
	LocAndSize.w = SpriteWidth;

	PrevFrame = 0;
	Frame = 0;

	for( int i = 0; i < 16; i++ )
	{
		Clips[ i ].x = i * SpriteWidth;
		Clips[ i ].y = 0;
		Clips[ i ].h = SpriteHeight;
		Clips[ i ].w = SpriteWidth;
	}
    Timer = 500;
}

SDL_Rect Powerup::UpdateCollisionBox(SDL_Rect Box)
{
	CollisionBox = LocAndSize;
	return CollisionBox;
}

void Powerup::Update()
{
    Timer = Timer - gamestate.DeltaTime;
    xPos = 0.0001f * gamestate.DeltaTime;
    LocAndSize.x -= (Sint16)xPos;
    LocAndSize.h = SpriteHeight;
    LocAndSize.w = SpriteWidth;
    static int delay = 0;
    delay++;
    if ( delay > 1)
    {
	    PrevFrame = Frame++;
        delay = 0;
    }
	if( Frame >= MAX_FRAMES )
	{
		Frame = 0;
	}
}

void Powerup::Draw()
{
	SDL_BlitSurface( 
		Gfx.GetSurface( SurfaceID ),
		&Clips[ 0 ], 
		Gfx.BackBuffer, 
		&GetDestination() 
	);
}

SDL_Rect Powerup::GetDestination()
{
	return LocAndSize;
}

void ControlPowerup::DrawPowerup()
{
	std::vector< Powerup >::iterator i;

	i = PowerupArrayRef.begin();

	while(i != PowerupArrayRef.end() )
	{
		i->Update();
		i->Draw();

        Gfx.RenderText("POWERUP!", i->LocAndSize.x, i->LocAndSize.y + i->GetTimer());

        if (i->GetTimer() <= 0)
		{
			i = PowerupArrayRef.erase(i);
		}
		else
		{
			++i;
		}
	}
}

void ControlPowerup::CreatePowerup( SDL_Rect Pobject )
{
    // Seed with a real random value, if available
    std::random_device rd;

    // Choose a random mean between 1 and 100
    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(1, 100);
    int Color = uniform_dist(e1);

    if ( Color <= 33 )
        PowerupArrayRef.push_back(CreatePowerupByReference(Pobject.x, Pobject.y, gamestate.m_srfRedPowerup ));
    else if ( Color <= 66 )
        PowerupArrayRef.push_back(CreatePowerupByReference(Pobject.x, Pobject.y, gamestate.m_srfGreenPowerup));
    else
        PowerupArrayRef.push_back(CreatePowerupByReference(Pobject.x, Pobject.y, gamestate.m_srfBluePowerup));
}

ControlPowerup::ControlPowerup()
{
	cout << "Creating the Powerup Controller..." << endl;
}

ControlPowerup::~ControlPowerup()
{
	cout << "Destroying the Powerup Controller..." << endl;
}

Powerup ControlPowerup::CreatePowerupByReference( int xPos, int yPos, int surface )
{
	Powerup temp;
	temp.SurfaceID = surface;
	temp.LocAndSize.x = xPos;
	temp.LocAndSize.y = yPos;

	return temp;
}