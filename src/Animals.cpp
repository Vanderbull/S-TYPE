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

void Animal::Setframe()
{	
	if( Frame >= 15 )
	{
		Frame = 0;
	}
}
void Animal::Update()
{
	this->xPos -= 0.0003f * gamestate.DeltaTime;//(500.0f * gamestate.DeltaTime);
	this->Destination.h = this->Height;
	this->Destination.w = this->Width;
	this->Destination.x = this->xPos;
	this->Destination.y = this->yPos; 

	this->PrevFrame = this->Frame++;
	this->Setframe();
	UpdateCollisionBox(Destination);
}

void Animal::Draw()
{
	SDL_FillRect(Gfx.BackBuffer, &CollisionBox,0xffffff );
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

void ControlAnimals::Draw_Animals()
{
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
		
		if( (*i)->xPos <= 0.0f - (*i)->Width )
		{
			i = My_Animals.erase(i);
		}
		else
		{
			++i;
		}

		
		//(*i)->xPos -= Speed;
		//
		//
		//SDL_Rect CrowDest = (*i)->GetDestination();
		//
		//SDL_BlitSurface(	gamestate.GetSurface( (*i)->Surface ),&(*i)->Clips[ (*i)->PrevFrame ], 
		//	gamestate.BackBuffer, &(*i)->GetDestination() );
		//
		//(*i)->Setframe();
		//(*i)->PrevFrame = (*i)->Frame;
		
		//++i;
	}

	// Draws the Crow and sets the frame
	
	//if( My_Animals.size() != 0 )
	//{
	//	//list< Animal* >::iterator i = My_Animals.begin();
	//	for( ; i != My_Animals.end(); ++i )
	//	{
	//		Animal * animal = (*i);
	//		
	//		animal->xPos -= Speed;

	//		SDL_Rect CrowDest = {	animal->xPos, animal->yPos, 	
	//								animal->Width, 
	//								animal->Height };  

	//													
	//		if( gamestate.OK_PaceEnemy() )
	//		{
	//			SDL_BlitSurface(	gamestate.GetSurface( animal->Surface ),&animal->Clips[ animal->Frame ], 
	//								gamestate.BackBuffer, &CrowDest );
	//			animal->Setframe();
	//			animal->PrevFrameCrow = animal->Frame;
	//		}
	//		else
	//		{
	//						
	//			SDL_BlitSurface(	gamestate.GetSurface( animal->Surface ),&animal->Clips[ animal->PrevFrameCrow ], 
	//								gamestate.BackBuffer, &CrowDest );
	//		}
	//	}
	//}
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
	if( My_Animals.size() < rand() % 5 )
	{
		//cout << "Creating animals..." << endl;
		My_Animals.push_back( CreateAnimal( SDL_GetVideoSurface()->w, 75 + ( rand() % Turf ) , gamestate.m_srfCrow ) );
	}
}

ControlAnimals::ControlAnimals()
{
	Turf = 200;
}

ControlAnimals::~ControlAnimals()
{
	cout << "Destroying the Animal Controller..." << endl;
}