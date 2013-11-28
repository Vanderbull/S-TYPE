#pragma once
#include <list>
#include <vector>
#include <stack>
#include <SDL.h>

#define CUBE_MAX_FRAMES 15
#define CUBE_MAX_PROGRESS 5000
#define CUBE_MIN_PROGRESS 2500

class CubeObject
{
public:
	float xPos,yPos;
	int Height,Width;
	int SurfaceID;
	SDL_Rect CollisionBox;

private:
};

class CubeState
{
public:
	int Frame, State;
	int Radius;
	int Surface;
	SDL_Rect Destination;
};

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

class ControlCubes
{
public:
	ControlCubes();
	~ControlCubes();
	void DrawCubes();
	void CreateCubes( int iProgress );

	Cube CreateCubeByReference( int xPos, int yPos, int surface );
	std::vector< Cube > GetVectorWithCubes(){ return CubeArrayRef; };
	std::vector< Cube > CubeArrayRef;
	
private:
};

extern ControlCubes CubeController;