#include "Bullets.h"
#include <SDL.h>
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

ControlBullets BulletController;
ControlBullets OctoBulletController;

SDL_Rect Bullet::UpdateCollisionBox(SDL_Rect Box)
{
	CollisionBox = Box;
	return CollisionBox;
}

void Bullet::Update()
{
	SetCollisionBox(this->GetLocAndSize().x, this->GetLocAndSize().y + 30, 5, 80);
	LocAndSize.x += (Sint16)(0.0010 * gamestate.DeltaTime);
	
	PrevFrame = Frame++;
	
	if( Frame >= BULLET_MAX_FRAMES )
	{
		Frame = 0;
	}
	
	//UpdateCollisionBox( LocAndSize );
}

void Bullet::OctoUpdate()
{
    SetCollisionBox(this->GetLocAndSize().x, this->GetLocAndSize().y + 30, 5, 80);
    LocAndSize.x -= Sint16(0.0010 * gamestate.DeltaTime);

    PrevFrame = Frame++;

    if (Frame >= BULLET_MAX_FRAMES)
    {
        Frame = 0;
    }
}

void Bullet::Draw()
{
	#ifdef _DEBUG 
	 //SDL_FillRect(Gfx.BackBuffer, &CollisionBox,0xffffff );
	#endif

    //LocAndSize.y = LocAndSize.y - 10;
	SDL_BlitSurface( 
		Gfx.GetSurface( SurfaceID ),
		&Clips[ PrevFrame ], 
		Gfx.BackBuffer, 
        &LocAndSize
	);
}

int Bullet::GetSurfaceID()
{
	return SurfaceID;
}

SDL_Rect Bullet::GetLocAndSize()
{
	return LocAndSize;
}

Bullet::Bullet()
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

    for (Sint16 i = 0; i < 16; i++)
	{
		Clips[ i ].x = i * LocAndSize.w;
		Clips[ i ].y = 0;
		Clips[ i ].h = LocAndSize.h;
		Clips[ i ].w = LocAndSize.w;
	}
}

void ControlBullets::Draw_Bullets()
{
	std::vector< Bullet >::iterator BulletCounter;

	BulletCounter = BulletArrayRef.begin();

	while( BulletCounter != BulletArrayRef.end() )
	{
		BulletCounter->Update();
		BulletCounter->Draw();
		if( BulletCounter->LocAndSize.x >= Gfx.screen->w - BulletCounter->LocAndSize.w )
		{
			BulletCounter = BulletArrayRef.erase(BulletCounter);
		}
		else
		{
			++BulletCounter;
		}
	}
}

void ControlBullets::DrawOctoBullets()
{
    std::vector< Bullet >::iterator BulletCounter;

    BulletCounter = BulletArrayRef.begin();

    while (BulletCounter != BulletArrayRef.end())
    {
        BulletCounter->OctoUpdate();
        BulletCounter->Draw();
        if (BulletCounter->LocAndSize.x <= 0)
        {
            BulletCounter = BulletArrayRef.erase(BulletCounter);
        }
        else
        {
            ++BulletCounter;
        }
    }
}

void ControlBullets::LoadBullet(Sint16 xPos, Sint16 yPos, Sint16 surface)
{
	Bullet tempBullet;

	tempBullet.LocAndSize.x = xPos;
	tempBullet.LocAndSize.y = yPos-15;
	tempBullet.SurfaceID = surface;

	BulletArrayRef.push_back( tempBullet );
 }

Bullet ControlBullets::CreateBulletByReference(Sint16 xPos, Sint16 yPos, Sint16 surface)
{
	Bullet temp;
	temp.SurfaceID = surface;
	temp.LocAndSize.x = xPos;
	temp.LocAndSize.y = yPos;

	return temp;
}

void ControlBullets::Create_Bullets()
{
    LoadBullet(Spaceship.GetPosition().x + Spaceship._CollisionBox.w / 2, Spaceship.GetPosition().y + Spaceship._CollisionBox.h / 2, gamestate.m_srfLaser);
}

void ControlBullets::CreateOctoBullets()
{
    Sint16 ScreenWidth;
    Sint16 ScreenHeight;
    ScreenWidth = rand() % 1920;
    ScreenHeight = rand() % 1080;
    LoadBullet(ScreenWidth, ScreenHeight, gamestate.m_srfInk);
}

ControlBullets::ControlBullets()
{
	cout << "Creating the Bullet Controller..." << endl;
}

ControlBullets::~ControlBullets()
{
	cout << "Destroying the Bullet Controller..." << endl;
}