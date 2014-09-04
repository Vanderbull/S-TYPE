#include <SDL.h>

//#include "Global\Global.h"
#include "Animals.h"
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

ControlAnimals AnimalController;
const float AnimalSpeed = 0.0003f;

Animal::Animal()
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

int Animal::isColliding(SDL_Rect Box)
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

SDL_Rect Animal::UpdateCollisionBox(SDL_Rect Box)
{
	CollisionBox = LocAndSize;
	return CollisionBox;
}

void Animal::Update()
{
	xPos = AnimalSpeed * gamestate.DeltaTime;
    LocAndSize.x -= (Sint16)xPos;
	LocAndSize.h = SpriteHeight;
	LocAndSize.w = SpriteWidth;

	PrevFrame = Frame++;
	if( Frame >= ANIMAL_MAX_FRAMES )
	{
		Frame = 0;
	}
	UpdateCollisionBox(LocAndSize);
}

void Animal::Draw()
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

}

SDL_Rect Animal::GetDestination()
{
	return LocAndSize;
}

void ControlAnimals::DrawAnimals()
{
	std::vector< Animal >::iterator i;

	i = AnimalArrayRef.begin();

	while(i != AnimalArrayRef.end() )
	{
		i->Update();
		i->Draw();
		
		if( i->LocAndSize.x <= 0.0f - SpriteWidth )
		{
			i = AnimalArrayRef.erase(i);
		}
		else
		{
			++i;
		}
	}
}

void ControlAnimals::CreateAnimals(int iProgress )
{
	if( iProgress > ANIMAL_MIN_PROGRESS && iProgress < TRIANGLE_MAX_PROGRESS )
	{
        if (std::rand() % 100 + 1 > 99)
        {
            AnimalArrayRef.push_back(CreateAnimalByReference(SDL_GetVideoSurface()->w, std::rand() % Gfx.BackBuffer->h, gamestate.m_srfAsteroid));
        }
		//if( rand() % 100 + 1 > 99 )
		//{
  //          AnimalArrayRef.push_back(CreateAnimalByReference(SDL_GetVideoSurface()->w, rand() % Gfx.BackBuffer->h, gamestate.m_srfAsteroid));
		//}
	}
	else
	{
		cout << "Progress passed the target range..." << endl;
	}
}

ControlAnimals::ControlAnimals()
{
	cout << "Creating the Animal Controller..." << endl;
}

ControlAnimals::~ControlAnimals()
{
	cout << "Destroying the Animal Controller..." << endl;
}

Animal ControlAnimals::CreateAnimalByReference( Sint16 xPos, Sint16 yPos, int surface )
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
	Animal temp;
	temp.SurfaceID = surface;
	temp.LocAndSize.x = xPos;
	temp.LocAndSize.y = yPos;

	return temp;
}