#include <SDL.h>

//#include "Global\Global.h"
#include "BlueShip.h"
#include "game.h"
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

ControlBlueShip BlueShipController;
const float BlueShipSpeed = 0.0001f;

BlueShip::BlueShip()
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
	xPos = BlueShipSpeed * gamestate.DeltaTime;
    LocAndSize.x -= (Sint16)xPos;
	LocAndSize.h = SpriteHeight;
	LocAndSize.w = SpriteWidth;

	PrevFrame = Frame++;
	if( Frame >= BLUESHIP_MAX_FRAMES )
	{
		Frame = 0;
	}
	UpdateCollisionBox(LocAndSize);
}

void BlueShip::Draw()
{
	#ifdef _DEBUG 
	//SDL_FillRect(Gfx.BackBuffer, &CollisionBox,0xffffff );
	#endif
	
	SDL_BlitSurface( 
		Gfx.GetSurface( SurfaceID ),
		&Clips[ 0 ], //PrevFrame replaced with 0 as there is no animation
		Gfx.BackBuffer, 
		&GetDestination() 
	);

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
	if( iProgress > BLUESHIP_MIN_PROGRESS && iProgress < TRIANGLE_MAX_PROGRESS )
	{
        if (std::rand() % 100 + 1 > 99)
        {
            BlueShipArrayRef.push_back(CreateBlueShipByReference(SDL_GetVideoSurface()->w, std::rand() % Gfx.BackBuffer->h, gamestate.m_srfBlueShip));
        }
	}
	else
	{
		cout << "Progress passed the target range..." << endl;
	}
}

ControlBlueShip::ControlBlueShip()
{
	cout << "Creating the Animal Controller..." << endl;
}

ControlBlueShip::~ControlBlueShip()
{
	cout << "Destroying the Animal Controller..." << endl;
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

	return temp;
}