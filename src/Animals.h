#pragma once
#include <list>
#include <stack>
#include <SDL.h>

/// <summary>A basic ammo object</summary>
class AnimalObject
{
public:
	float xPos,yPos;
	int Height,Width;
	int SurfaceID;
	SDL_Rect CollisionBox;

private:
};

/// <summary>Keeps the state of any animal</summary>
class AnimalState
{
public:
	int Frame, State;
	int Radius;
	int Surface;
	SDL_Rect Destination;
};

/// <summary>Used to create a Animal entity</summary>
class Animal : public AnimalState, public AnimalObject
{

public:
	Animal();
	
	SDL_Rect UpdateCollisionBox(SDL_Rect Box);
	void Setframe();
	void Update();
	void Draw();
	
	SDL_Rect GetDestination();

private:
	SDL_Rect Clips[ 16 ];
	int PrevFrame;
};

/// <summary>A class the controls the animals</summary> 
class ControlAnimals
{
public:
	ControlAnimals();
	~ControlAnimals();
	void Draw_Animals();
	void Create_Animals();

	int Turf;

	Animal * CreateAnimal( int xPos, int yPos, int surface );

	
private:
	std::list< Animal* > My_Animals;
};

extern ControlAnimals AnimalController;