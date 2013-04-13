#include "Animals.h"
#include <SDL.h>
#include "game.h"
#include "ControlGfx.h"

ControlAnimals AnimalController;

void Animal::Setframe()
{	
	if( Frame == 15 )
	{
		Frame = 0;
	}
	else
	{
		Frame++;
	}
}
void Animal::Update()
{
	this->xPos -= (500.0f * gamestate.dt);
	this->Destination.h = this->Height;
	this->Destination.w = this->Width;
	this->Destination.x = this->xPos;
	this->Destination.y = this->yPos; 

	this->PrevFrame = this->Frame;
	this->Setframe();
}

void Animal::Draw()
{
	SDL_BlitSurface( 
		Gfx.GetSurface( this->Surface ),
		&this->Clips[ this->PrevFrame ], 
		gamestate.BackBuffer, 
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

void ControlAnimals::Draw_Animals()
{
	float Speed = 2.5f;//2000.0f * ( gamestate.dt / 1000.0f );

 	list< Animal* >::iterator i;
	/*
	i = My_Animals.begin();
	while(i != My_Animals.end() )
	{
		if( (*i)->xPos <= -200.0f )
		{
        		// cout << "The Bird is no longer..." << endl;
      			i = My_Animals.erase(i);
		}
  		else
		{
			++i;
		}
	}
	*/
	i = My_Animals.begin();
	while(i != My_Animals.end() )
	{
		(*i)->Update();
		(*i)->Draw();
		if( (*i)->xPos <= 200.0f )
			i = My_Animals.erase(i);
		else
			++i;
		/*
		(*i)->xPos -= Speed;
		
		
		SDL_Rect CrowDest = (*i)->GetDestination();
		
		SDL_BlitSurface(	gamestate.GetSurface( (*i)->Surface ),&(*i)->Clips[ (*i)->PrevFrame ], 
			gamestate.BackBuffer, &(*i)->GetDestination() );
			*/
		/*
		(*i)->Setframe();
		(*i)->PrevFrame = (*i)->Frame;
		*/
		//++i;
	}

	// Draws the Crow and sets the frame
	/*
	if( My_Animals.size() != 0 )
	{
		//list< Animal* >::iterator i = My_Animals.begin();
		for( ; i != My_Animals.end(); ++i )
		{
			Animal * animal = (*i);
			
			animal->xPos -= Speed;

			SDL_Rect CrowDest = {	animal->xPos, animal->yPos, 	
									animal->Width, 
									animal->Height };  

														
			if( gamestate.OK_PaceEnemy() )
			{
				SDL_BlitSurface(	gamestate.GetSurface( animal->Surface ),&animal->Clips[ animal->Frame ], 
									gamestate.BackBuffer, &CrowDest );
				animal->Setframe();
				animal->PrevFrameCrow = animal->Frame;
			}
			else
			{
							
				SDL_BlitSurface(	gamestate.GetSurface( animal->Surface ),&animal->Clips[ animal->PrevFrameCrow ], 
									gamestate.BackBuffer, &CrowDest );
			}
		}
	}*/
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
  
void ControlAnimals::Create_Animals()
{
	if( My_Animals.size() < rand() % 25 )
	My_Animals.push_back( CreateAnimal( SDL_GetVideoSurface()->w, 75 + ( rand() % Turf ) , gamestate.m_srfCrow ) );
}

ControlAnimals::ControlAnimals()
{
	Turf = 200;
}

ControlAnimals::~ControlAnimals()
{
}