#include "Animals.h"
#include <SDL.h>
#include "game.h"
#include "ControlGfx.h"

ControlAnimals AnimalController;
const float AnimalSpeed = 0.0003f;
const int SpriteHeight = 64;
const int SpriteWidth = 64;

Animal::Animal()
{
	mPosition.x = 0;
	mPosition.y = 0;
	mPosition.z = 0;
	mPosition.h = SpriteHeight;
	mPosition.w = SpriteWidth;

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
	if( mPosition.x <= 200.0f )
	{
		cout << "destroying object..." << endl;
		return 1;
	}
	else
		return 0;
}

SDL_Rect Animal::UpdateCollisionBox(SDL_Rect Box)
{
	CollisionBox = Box;
	return CollisionBox;
}

void Animal::Update()
{
	mPosition.x -= AnimalSpeed * gamestate.DeltaTime;

	Destination.h = SpriteHeight;
	Destination.w = SpriteWidth;
	Destination.x = mPosition.x;
	Destination.y = mPosition.y; 

	PrevFrame = Frame++;
	if( Frame >= ANIMAL_MAX_FRAMES )
	{
		Frame = 0;
	}
	UpdateCollisionBox(Destination);
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
	return Destination;
}

void ControlAnimals::DrawAnimals()
{
 	list< Animal* >::iterator i;

	i = AnimalList.begin();
	while(i != AnimalList.end() )
	{
		(*i)->Update();
		(*i)->Draw();
		
		if( (*i)->mPosition.x <= 0.0f - SpriteWidth )
		{
			i = AnimalList.erase(i);
		}
		else if( (*i)->isColliding((*i)->CollisionBox) != 0 )
		{
			i = AnimalList.erase(i);
		}
		else
		{
			++i;
		}
	}
}

Animal * ControlAnimals::CreateAnimal( int xPos, int yPos, int surface )
{
	Animal * temp = new Animal;
	temp->SurfaceID = surface;
	temp->mPosition.x = xPos;
	temp->mPosition.y = yPos;

	return temp;
}
  
void ControlAnimals::CreateAnimals(int iProgress )
{
	if( iProgress > ANIMAL_MIN_PROGRESS && iProgress < ANIMAL_MAX_PROGRESS )
	{
		if( AnimalList.size() < rand() % 5 )
		{
			cout << "Creating a animal..." << endl;
			AnimalList.push_back( CreateAnimal( SDL_GetVideoSurface()->w, rand() % Gfx.BackBuffer->h , gamestate.m_srfCrow ) );
		}
	}
	else
	{
		cout << "Progress passed the target range..." << endl;
	}
}

ControlAnimals::ControlAnimals()
{
}

ControlAnimals::~ControlAnimals()
{
	cout << "Destroying the Animal Controller..." << endl;
}