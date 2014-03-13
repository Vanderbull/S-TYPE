#include "Triangles.h"
#include <SDL.h>
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

ControlTriangles TriangleController;

const float CubeSpeed = 0.0001f;

SDL_Rect Triangle::UpdateCollisionBox(SDL_Rect Box)
{
	CollisionBox = Box;
	return CollisionBox;
}

void Triangle::Update()
{
	xPos -= 0.0003f * gamestate.DeltaTime;
	Destination.w = Width;
	Destination.x = xPos;
	Destination.y = yPos+rand()% 12; 

	PrevFrame = Frame++;
	if( Frame >= TRIANGLE_MAX_FRAMES )
	{
		Frame = 0;
	}
	UpdateCollisionBox(Destination);
}

void Triangle::Draw()
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

SDL_Rect Triangle::GetDestination()
{
	return Destination;
}

Triangle::Triangle()
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

void ControlTriangles::DrawTriangles()
{
	if( TriangleArrayRef.size() < 1 )
		return;
	vector< Triangle >::iterator i;

	i = TriangleArrayRef.begin();

	while(i != TriangleArrayRef.end() )
	{
		i->Update();
		i->Draw();
		
		if( i->xPos <= 0.0f - SpriteWidth )
		{
			i = TriangleArrayRef.erase(i);
		}
		else
		{
			++i;
		}
	}
}

void ControlTriangles::CreateTriangles(int iProgress )
{
	if( iProgress > TRIANGLE_MIN_PROGRESS && iProgress < TRIANGLE_MAX_PROGRESS )
	{
		if( TriangleArrayRef.size() < rand() % 5 )
		{
			TriangleArrayRef.push_back( CreateTriangleByReference( SDL_GetVideoSurface()->w, rand() % Gfx.BackBuffer->h , gamestate.m_srfTriangle ) );
		}
	}
	else
	{
		cout << "Progress passed the target range... " << endl;
	}
}

Triangle ControlTriangles::CreateTriangleByReference( int xPos, int yPos, int surface )
{
	static int old_y_pos = 0;
	
	while( yPos > old_y_pos && yPos < old_y_pos + 64 )
	{
		yPos = rand() % Gfx.BackBuffer->h - 64;
	}
	if( yPos < 64 )
		yPos = 64;

	Triangle temp;
	temp.SurfaceID = surface;
	temp.xPos = xPos;
	temp.yPos = yPos;

	return temp;
}

ControlTriangles::ControlTriangles()
{
	cout << "Creating the Triangle Controller..." << endl;
}

ControlTriangles::~ControlTriangles()
{
	cout << "Destroying the Triangle Controller..." << endl;
}