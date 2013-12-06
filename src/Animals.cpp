#include "Animals.h"
#include <SDL.h>
#include "game.h"
#include "ControlGfx.h"

ControlAnimals AnimalController;
const float AnimalSpeed = 0.0001f;
const int SpriteHeight = 64;
const int SpriteWidth = 64;

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
		Clips[ i ].x = i * SpriteWidth;
		Clips[ i ].y = 0;
		Clips[ i ].h = SpriteHeight;
		Clips[ i ].w = SpriteWidth;
	}
}

int Animal::isColliding(SDL_Rect Box)
{
	int PlayerRight = BCPlayer.GetPosition().x + BCPlayer.GetPosition().w;
	int PlayerLeft = BCPlayer.GetPosition().x;
	int PlayerTop = BCPlayer.GetPosition().y;
	int PlayerBottom = BCPlayer.GetPosition().x + BCPlayer.GetPosition().h;

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
	LocAndSize.x -= AnimalSpeed * gamestate.DeltaTime;

	LocAndSize.h = SpriteHeight;
	LocAndSize.w = SpriteWidth;
	LocAndSize.x = LocAndSize.x;
	LocAndSize.y = LocAndSize.y; 

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
	SDL_FillRect(Gfx.BackBuffer, &CollisionBox,0xffffff );
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
	if( iProgress > ANIMAL_MIN_PROGRESS && iProgress < ANIMAL_MAX_PROGRESS )
	{
		if( AnimalArrayRef.size() < rand() % 5 )
		{
			AnimalArrayRef.push_back( CreateAnimalByReference( SDL_GetVideoSurface()->w, rand() % Gfx.BackBuffer->h , gamestate.m_srfCrow ) );
		}
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

Animal ControlAnimals::CreateAnimalByReference( int xPos, int yPos, int surface )
{
	Animal temp;
	temp.SurfaceID = surface;
	temp.LocAndSize.x = xPos;
	temp.LocAndSize.y = yPos;

	return temp;
}