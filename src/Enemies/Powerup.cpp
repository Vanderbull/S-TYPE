#include <cmath>
#include "Powerup.h"
#include "../Game.h"
#include "../SpaceShip.h"
#include "../Timers.h"
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
		Clips[ i ].x = i * SpriteWidth;
		Clips[ i ].y = 0;
		Clips[ i ].h = SpriteHeight;
		Clips[ i ].w = SpriteWidth;
	}
    Timer = 500;
}

int Powerup::isColliding(SDL_Rect Box)
{
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

SDL_Rect Powerup::UpdateCollisionBox(SDL_Rect Box)
{
	CollisionBox = LocAndSize;
	return CollisionBox;
}

void Powerup::Update()
{
    Timer--;
    xPos = 0.0003f * gamestate.DeltaTime;
    LocAndSize.x -= (Sint16)xPos;
    LocAndSize.h = SpriteHeight;
    LocAndSize.w = SpriteWidth;
	//xPos = 0.0003f * gamestate.DeltaTime;
	//LocAndSize.x = 150;
	//LocAndSize.y = 150;
	//LocAndSize.h = SpriteHeight;
	//LocAndSize.w = SpriteWidth;

	PrevFrame = Frame++;
	if( Frame >= MAX_FRAMES )
	{
		Frame = 0;
	}
	//UpdateCollisionBox(LocAndSize);
}

void Powerup::Draw()
{
	#ifdef _DEBUG 
	//SDL_FillRect(Gfx.BackBuffer, &CollisionBox,0xffffff );
	#endif
	
	SDL_BlitSurface( 
		Gfx.GetSurface( SurfaceID ),
		&Clips[ PrevFrame ], 
		Gfx.BackBuffer, 
		&GetDestination() 
	);

    //PopupScore.push_back(50);
    //_SCORE += 100;
    SDL_Surface * SrfProgress;
    SrfProgress = TTF_RenderText_Solid(Gfx.DefaultFont, "POWER UP COOL *YEA GRIIM!!!!!", Gfx.WhiteRGB);
    Gfx.apply_surface(GetDestination().x, GetDestination().y, SrfProgress, Gfx.BackBuffer);


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
		
        if (i->GetTimer() <= 0)//if(PowerupArrayRef.size() > 50 )//if( i->LocAndSize.x <= 0.0f - SpriteWidth )
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
    if (rand()%100 >= 50 )
	PowerupArrayRef.push_back( CreatePowerupByReference( Pobject.x, Pobject.y , gamestate.m_srfCube ) );
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
	//static int old_y_pos = 0;
	//
	//while( yPos > old_y_pos && yPos < old_y_pos + 128 )
	//{
	//	yPos = rand() % Gfx.BackBuffer->h - 128;
	//}
	//if( yPos < 64 )
	//	yPos = 64;
	//if( yPos > Gfx.BackBuffer->h - 128 )
	//	yPos = Gfx.BackBuffer->h - 128;
	Powerup temp;
	temp.SurfaceID = surface;
	temp.LocAndSize.x = xPos;
	temp.LocAndSize.y = yPos;

	return temp;
}