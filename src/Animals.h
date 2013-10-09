#pragma once
#include <list>
#include <stack>
#include <SDL.h>

#define ANIMAL_MAX_FRAMES 15
#define ANIMAL_MIN_PROGRESS 0
#define ANIMAL_MAX_PROGRESS 2500

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
	void DrawAnimals();
	void CreateAnimals( int iProgress );

	Animal * CreateAnimal( int xPos, int yPos, int surface );
	std::list< Animal* > GetAnimal(){ return AnimalList; };
	
private:
	std::list< Animal* > AnimalList;
};

extern ControlAnimals AnimalController;