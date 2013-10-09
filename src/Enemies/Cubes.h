#pragma once
#include <list>
#include <stack>
#include <SDL.h>

#define CUBE_MAX_FRAMES 15
#define CUBE_MAX_PROGRESS 5000
#define CUBE_MIN_PROGRESS 2500

/// <summary>A basic ammo object</summary>
class CubeObject
{
public:
	float xPos,yPos;
	int Height,Width;
	int SurfaceID;
	SDL_Rect CollisionBox;

private:
};

/// <summary>Keeps the state of any animal</summary>
class CubeState
{
public:
	int Frame, State;
	int Radius;
	int Surface;
	SDL_Rect Destination;
};

/// <summary>Used to create a Animal entity</summary>
class Cube : public CubeState, public CubeObject
{

public:
	Cube();
	
	SDL_Rect UpdateCollisionBox(SDL_Rect Box);
	void Update();
	void Draw();
	
	SDL_Rect GetDestination();

private:
	SDL_Rect Clips[ 16 ];
	int PrevFrame;
};

/// <summary>A class the controls the animals</summary> 
class ControlCubes
{
public:
	ControlCubes();
	~ControlCubes();
	void DrawCubes();
	void CreateCubes( int iProgress );

	Cube * CreateCube( int xPos, int yPos, int surface );
	std::list< Cube* > GetCube(){ return CubeList; };
	
private:
	std::list< Cube* > CubeList;
};

extern ControlCubes CubeController;