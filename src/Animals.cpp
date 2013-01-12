#include "Animals.h"
#include <SDL.h>
#include "game.h"

// @date 2012-08-07

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
		float Speed = 2.5f;//2000.0f * ( gamestate.dt / 1000.0f );
		this->xPos -= Speed;
		this->CrowDest.h = this->Height;
		this->CrowDest.w = this->Width;
		this->CrowDest.x = this->xPos;
		this->CrowDest.y = this->yPos; 

		this->Setframe();
		this->PrevFrameCrow = this->Frame;
}

void Animal::Draw()
{
		SDL_BlitSurface(	gamestate.GetSurface( this->Surface ),&this->Clips[ this->PrevFrameCrow ], 
			gamestate.BackBuffer, &this->GetDestination() );
}

SDL_Rect Animal::GetDestination()
{
	return this->CrowDest;
}

Animal::Animal()
{
	Frame = 0;
	PrevFrameCrow = 0;
	Height =	64;
	Width =		64;

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

	i = My_Animals.begin();
	while(i != My_Animals.end() )
	{
		(*i)->Update();
		(*i)->Draw();
		/*
		(*i)->xPos -= Speed;
		
		
		SDL_Rect CrowDest = (*i)->GetDestination();
		
		SDL_BlitSurface(	gamestate.GetSurface( (*i)->Surface ),&(*i)->Clips[ (*i)->PrevFrameCrow ], 
			gamestate.BackBuffer, &(*i)->GetDestination() );
			*/
		/*
		(*i)->Setframe();
		(*i)->PrevFrameCrow = (*i)->Frame;
		*/
		++i;
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
	if( My_Animals.size() < rand()%25 )
	My_Animals.push_back( CreateAnimal( gamestate.SCREEN_WIDTH, 75 + ( rand() % CrowTurf ) , gamestate.m_srfCrow ) );
}

ControlAnimals::ControlAnimals()
{
	CrowTurf = 200;
}