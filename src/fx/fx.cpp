#include "fx.h"
#include <SDL2/SDL.h>
//#include <SDL.h>
#include "../Game.h"
#include "../GfxController/ControlGfx.h"

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

ControlFX FXController;

SDL_Rect FX::UpdateCollisionBox(SDL_Rect Box)
{
	CollisionBox = Box;
	return CollisionBox;
}

void FX::Update()
{
	SetCollisionBox(this->GetLocAndSize()->x, this->GetLocAndSize()->y + 30, 5, 80);
	LocAndSize.x += 0.0010f * gamestate.DeltaTime;

	PrevFrame = Frame++;

	if( Frame >= FX_MAX_FRAMES )
	{
		Frame = 0;
	}

	//UpdateCollisionBox( LocAndSize );
}

void FX::Draw()
{
	#ifdef _DEBUG
	 //SDL_FillRect(Gfx.BackBuffer, &CollisionBox,0xffffff );
	#endif

    //LocAndSize.y = LocAndSize.y - 10;
	SDL_BlitSurface(
		Gfx.GetSurface( SurfaceID ),
		&Clips[ PrevFrame ],
		Gfx.BackBuffer,
		GetLocAndSize()
	);
}

int FX::GetSurfaceID()
{
	return SurfaceID;
}

SDL_Rect* FX::GetLocAndSize()
{
	return &LocAndSize;
}

FX::FX()
{
	LocAndSize.h = 64;
	LocAndSize.w = 64;
	LocAndSize.x = 0;
	LocAndSize.y = 0;

	// Setup collision box boundries
	CollisionBox.x = 0;
	CollisionBox.y = 0;
	CollisionBox.w = 64;
	CollisionBox.h = 64;

	PrevFrame = 0;
	Frame = 0;
	Active = 1;

	for( int i = 0; i < 16; i++ )
	{
		Clips[ i ].x = i * LocAndSize.w;
		Clips[ i ].y = 0;
		Clips[ i ].h = LocAndSize.h;
		Clips[ i ].w = LocAndSize.w;
	}
}

void ControlFX::DrawFX()
{
	std::vector< FX >::iterator FXCounter;

	FXCounter = FXArrayRef.begin();

	while( FXCounter != FXArrayRef.end() )
	{
		FXCounter->Update();
		FXCounter->Draw();
		if( FXCounter->LocAndSize.x >= Gfx.screen->w - FXCounter->LocAndSize.w )
		{
			FXCounter = FXArrayRef.erase(FXCounter);
		}
		else
		{
			++FXCounter;
		}
	}
}

void ControlFX::LoadFX( int xPos, int yPos, int surface )
{
	FX tempFX;

	tempFX.LocAndSize.x = xPos;
	tempFX.LocAndSize.y = yPos-15;
	tempFX.SurfaceID = surface;

	FXArrayRef.push_back( tempFX );
 }

FX ControlFX::CreateFXByReference( int xPos, int yPos, int surface )
{
	FX temp;
	temp.SurfaceID = surface;
	temp.LocAndSize.x = xPos;
	temp.LocAndSize.y = yPos;

	return temp;
}

void ControlFX::CreateFX()
{
    //LoadFX(Spaceship.GetPosition().x + Spaceship._CollisionBox.w / 2, Spaceship.GetPosition().y + Spaceship._CollisionBox.h / 2, gamestate.m_srfLaser);
}

ControlFX::ControlFX()
{
}

ControlFX::~ControlFX()
{
}
