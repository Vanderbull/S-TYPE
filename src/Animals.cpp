#include "Animals.h"
#include <SDL.h>
#include "game.h"
#include "ControlGfx.h"

ControlAnimals AnimalController;

SDL_Rect Animal::UpdateCollisionBox(SDL_Rect Box)
{
	CollisionBox = Box;
	return CollisionBox;
}

void Animal::Update()
{
	this->xPos -= 0.0003f * gamestate.DeltaTime;//(500.0f * gamestate.DeltaTime);
	this->Destination.h = this->Height;
	this->Destination.w = this->Width;
	this->Destination.x = this->xPos;
	this->Destination.y = this->yPos; 

	this->PrevFrame = this->Frame++;
	if( this->Frame >= ANIMAL_MAX_FRAMES )
	{
		this->Frame = 0;
	}
	UpdateCollisionBox(Destination);
}

void Animal::Draw()
{
	#ifdef _DEBUG 
	//SDL_FillRect(Gfx.BackBuffer, &CollisionBox,0xffffff );
	#endif
	
	SDL_BlitSurface( 
		Gfx.GetSurface( this->Surface ),
		&this->Clips[ this->PrevFrame ], 
		Gfx.BackBuffer, 
		&this->GetDestination() 
	);
}

SDL_Rect Animal::GetDestination()
{
	return this->Destination;
}

Animal::Animal()
{
	PrevFrame = 0;
	Frame = 0;
	Height = 64;
	Width =	64;

	for( int i = 0; i < 16; i++ )
	{
		Clips[ i ].x = i * Width;
		Clips[ i ].y = 0;
		Clips[ i ].h = Height;
		Clips[ i ].w = Width;
	}
}

void ControlAnimals::DrawAnimals()
{
 	list< Animal* >::iterator i;

	i = AnimalList.begin();
	while(i != AnimalList.end() )
	{
		(*i)->Update();
		(*i)->Draw();
		
		if( (*i)->xPos <= 0.0f - (*i)->Width )
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
		temp->Surface = surface;
		temp->xPos = xPos;
		temp->yPos = yPos;

		temp->Radius = ( temp->Width > temp->Height ) ? temp->Width / 2 : temp->Height / 2;

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
		cout << "Progress passed the target range... " << endl;
	}
}

ControlAnimals::ControlAnimals()
{
}

ControlAnimals::~ControlAnimals()
{
	cout << "Destroying the Animal Controller..." << endl;
}