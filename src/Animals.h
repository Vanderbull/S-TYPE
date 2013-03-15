#pragma once
#include <list>
#include <stack>
#include <SDL.h>

/// <summary>Keeps the state of any animal</summary>
class AnimalState
{
public:
	float xPos, yPos;
	int Frame, State;
	int Height, Width;
	int Radius;
	int Surface;
	SDL_Rect Destination;
};

/// <summary>Used to create a Animal entity</summary>
class Animal : public AnimalState
{

public:
	Animal();
	
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