#include "Triangles.h"
#include <SDL.h>
#include "Game.h"
#include "ControlGfx.h"

ControlTriangles TriangleController;

SDL_Rect Triangle::UpdateCollisionBox(SDL_Rect Box)
{
	CollisionBox = Box;
	return CollisionBox;
}

void Triangle::Update()
{
	this->xPos -= 0.0003f * gamestate.DeltaTime;//(500.0f * gamestate.DeltaTime);
	this->Destination.h = this->Height;
	this->Destination.w = this->Width;
	this->Destination.x = this->xPos;
	this->Destination.y = this->yPos; 

	this->PrevFrame = this->Frame++;
	if( this->Frame >= TRIANGLE_MAX_FRAMES )
	{
		this->Frame = 0;
	}
	UpdateCollisionBox(Destination);
}

void Triangle::Draw()
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

SDL_Rect Triangle::GetDestination()
{
	return this->Destination;
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
 	list< Triangle* >::iterator i;

	i = TriangleList.begin();
	while(i != TriangleList.end() )
	{
		(*i)->Update();
		(*i)->Draw();
		
		if( (*i)->xPos <= 0.0f - (*i)->Width )
		{
			i = TriangleList.erase(i);
		}
		else
		{
			++i;
		}
	}
}

Triangle * ControlTriangles::CreateTriangle( int xPos, int yPos, int surface )
{
		Triangle * temp = new Triangle;
		temp->Surface = surface;
		temp->xPos = xPos;
		temp->yPos = yPos;

		temp->Radius = ( temp->Width > temp->Height ) ? temp->Width / 2 : temp->Height / 2;

		return temp;
}
  
void ControlTriangles::CreateTriangles(int iProgress )
{
	if( iProgress > TRIANGLE_MIN_PROGRESS && iProgress < TRIANGLE_MAX_PROGRESS )
	{
		if( TriangleList.size() < rand() % 5 )
		{
			cout << "Creating a triangle..." << endl;
			TriangleList.push_back( CreateTriangle( SDL_GetVideoSurface()->w, rand() % Gfx.BackBuffer->h , gamestate.m_srfTriangle ) );
		}
	}
	else
	{
		cout << "Progress passed the target range... " << endl;
	}
}

ControlTriangles::ControlTriangles()
{
}

ControlTriangles::~ControlTriangles()
{
	cout << "Destroying the Triangle Controller..." << endl;
}