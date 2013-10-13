#pragma once
#include <list>
#include <stack>
#include <SDL.h>

#define TRIANGLE_MAX_FRAMES 15
#define TRIANGLE_MAX_PROGRESS 7500
#define TRIANGLE_MIN_PROGRESS 0

/// <summary>A basic ammo object</summary>
class TriangleObject
{
public:
	float xPos,yPos;
	int Height,Width;
	int SurfaceID;
	SDL_Rect CollisionBox;

private:
};

/// <summary>Keeps the state of any animal</summary>
class TriangleState
{
public:
	int Frame, State;
	int Radius;
	int Surface;
	SDL_Rect Destination;
};

/// <summary>Used to create a Animal entity</summary>
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

/// <summary>A class the controls the animals</summary> 
class ControlTriangles
{
public:
	ControlTriangles();
	~ControlTriangles();
	void DrawTriangles();
	void CreateTriangles( int iProgress );

	Triangle * CreateTriangle( int xPos, int yPos, int surface );
	std::list< Triangle* > GetTriangle(){ return TriangleList; };
	
private:
	std::list< Triangle* > TriangleList;
};

extern ControlTriangles TriangleController;