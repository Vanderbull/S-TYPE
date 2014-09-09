#pragma once
#include <list>
#include <vector>
#include <stack>
#include <SDL.h>

#define TRIANGLE_MAX_FRAMES 15
#define TRIANGLE_MAX_PROGRESS 7500
#define TRIANGLE_MIN_PROGRESS 5000

class TriangleObject
{
public:
	Uint16 xPos,yPos;
	Uint16 Height,Width;
	Uint16 SurfaceID;
	SDL_Rect CollisionBox;

private:
};

class TriangleState
{
public:
	Uint16 Frame, State;
	Uint16 Radius;
	Uint16 Surface;
	SDL_Rect Destination;
};


class Triangle : public TriangleState, public TriangleObject
{

public:
	Triangle();
	
	SDL_Rect UpdateCollisionBox(SDL_Rect Box);
	void Update();
	void Draw();
	
	SDL_Rect GetDestination();

private:
	SDL_Rect Clips[ 16 ];
	int PrevFrame;
};


class ControlTriangles
{
public:
	ControlTriangles();
	~ControlTriangles();
	void DrawTriangles();
	void CreateTriangles( int iProgress );

	Triangle CreateTriangleByReference( int xPos, int yPos, int surface );
	std::vector< Triangle > GetVectorWithTriangles(){ return TriangleArrayRef; };
	std::vector< Triangle > TriangleArrayRef;

private:

};

extern ControlTriangles TriangleController;