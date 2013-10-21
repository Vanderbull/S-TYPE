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
	xPos -= 0.0003f * gamestate.DeltaTime;//(500.0f * gamestate.DeltaTime);
	Destination.h = Height;
	Destination.w = Width;
	Destination.x = xPos;
	Destination.y = yPos; 

	PrevFrame = Frame++;
	if( Frame >= CUBE_MAX_FRAMES )
	{
		Frame = 0;
	}
	UpdateCollisionBox(Destination);
}

void Cube::Draw()
{
	#ifdef _DEBUG 
	//SDL_FillRect(Gfx.BackBuffer, &CollisionBox,0xffffff );
	#endif
	
	SDL_BlitSurface( 
		Gfx.GetSurface( Surface ),
		&Clips[ PrevFrame ], 
		Gfx.BackBuffer, 
		&GetDestination() 
	);
}

SDL_Rect Cube::GetDestination()
{
	return Destination;
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