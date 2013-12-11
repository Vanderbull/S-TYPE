#include "Cubes.h"
#include <SDL.h>
#include "../Game.h"
#include "../ControlGfx.h"

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

ControlCubes CubeController;

const float CubeSpeed = 0.0001f;
const int SpriteHeight = 64;
const int SpriteWidth = 64;

SDL_Rect Cube::UpdateCollisionBox(SDL_Rect Box)
{
	CollisionBox = Box;
	return CollisionBox;
}

void Cube::Update()
{
	double wavelength = 50;
	int _sTime = 10, waveheight = 25;

	xPos -= CubeSpeed * gamestate.DeltaTime;
	Destination.h = Height;
	Destination.w = Width;
	Destination.x = xPos;
	Destination.y = yPos; //(sin(xPos / wavelength )*waveheight) + 300;

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
	SDL_FillRect(Gfx.BackBuffer, &CollisionBox,0xffffff );
	#endif
	
	SDL_BlitSurface( 
		Gfx.GetSurface( SurfaceID ),
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
	if( CubeArrayRef.size() < 1 )
		return;
	vector< Cube >::iterator i;

	i = CubeArrayRef.begin();

	while(i != CubeArrayRef.end() )
	{
		i->Update();
		i->Draw();
		
		if( i->xPos <= 0.0f - SpriteWidth )
		{
			i = CubeArrayRef.erase(i);
		}
		else
		{
			++i;
		}
	}
}

void ControlCubes::CreateCubes(int iProgress )
{
	if( iProgress > ANIMAL_MIN_PROGRESS && iProgress < TRIANGLE_MAX_PROGRESS )
	{
		//if( CubeArrayRef.size() < rand() % 5 )
		if( rand() % 100 + 1 >= 100 )
		{
			CubeArrayRef.push_back( CreateCubeByReference( SDL_GetVideoSurface()->w, rand() % Gfx.BackBuffer->h - 64, gamestate.m_srfCube ) );
		}
	}
	else
	{
		cout << "Progress passed the target range... " << endl;
	}
}

Cube ControlCubes::CreateCubeByReference( int xPos, int yPos, int surface )
{
	static int old_y_pos = 0;
	static int old_x_pos = 0;

	while( xPos > old_x_pos && xPos < old_x_pos + 64 )
	{
		xPos = rand() % Gfx.BackBuffer->w - 64;
	}
	if( xPos < 64 )
		xPos = 64;
	
	while( yPos > old_y_pos && yPos < old_y_pos + 64 )
	{
		yPos = rand() % Gfx.BackBuffer->h - 64;
	}
	if( yPos < 64 )
		yPos = 64;

	Cube temp;
	temp.SurfaceID = surface;
	temp.xPos = xPos;
	temp.yPos = yPos;

	old_y_pos = yPos;

	return temp;
}
ControlCubes::ControlCubes()
{
}

ControlCubes::~ControlCubes()
{
	cout << "Destroying the Cube Controller..." << endl;
}