#include "Cubes.h"
#include <SDL.h>
#include "../Game.h"
#include "../ControlGfx.h"

ControlCubes CubeController;

SDL_Rect Cube::UpdateCollisionBox(SDL_Rect Box)
{
	CollisionBox = Box;
	return CollisionBox;
}

void Cube::Update()
{
	this->xPos -= 0.0003f * gamestate.DeltaTime;//(500.0f * gamestate.DeltaTime);
	this->Destination.h = this->Height;
	this->Destination.w = this->Width;
	this->Destination.x = this->xPos;
	this->Destination.y = this->yPos; 

	this->PrevFrame = this->Frame++;
	if( this->Frame >= CUBE_MAX_FRAMES )
	{
		this->Frame = 0;
	}
	UpdateCollisionBox(Destination);
}

void Cube::Draw()
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

SDL_Rect Cube::GetDestination()
{
	return this->Destination;
}

Cube::Cube()
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

void ControlCubes::DrawCubes()
{
 	list< Cube* >::iterator i;

	i = CubeList.begin();
	while(i != CubeList.end() )
	{
		(*i)->Update();
		(*i)->Draw();
		
		if( (*i)->xPos <= 0.0f - (*i)->Width )
		{
			i = CubeList.erase(i);
		}
		else
		{
			++i;
		}
	}
}

Cube * ControlCubes::CreateCube( int xPos, int yPos, int surface )
{
		Cube * temp = new Cube;
		temp->Surface = surface;
		temp->xPos = xPos;
		temp->yPos = yPos;

		temp->Radius = ( temp->Width > temp->Height ) ? temp->Width / 2 : temp->Height / 2;

		return temp;
}
  
void ControlCubes::CreateCubes(int iProgress )
{
	if( iProgress > CUBE_MIN_PROGRESS && iProgress < CUBE_MAX_PROGRESS )
	{
		if( CubeList.size() < rand() % 5 )
		{
			cout << "Creating a cube..." << endl;
			CubeList.push_back( CreateCube( SDL_GetVideoSurface()->w, rand() % Gfx.BackBuffer->h , gamestate.m_srfCube ) );
		}
	}
	else
	{
		cout << "Progress passed the target range... " << endl;
	}
}

ControlCubes::ControlCubes()
{
}

ControlCubes::~ControlCubes()
{
	cout << "Destroying the Cube Controller..." << endl;
}