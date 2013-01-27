#pragma once
#include <list>
#include <stack>
#include <SDL.h>

/*
   Class: AnimalState
   A class
*/
class AnimalState
{
public:
	int xPos, yPos;
	int Frame, State;
	int Height, Width;
	int Radius;
	int Surface;
	SDL_Rect Destination;
};

/*
   Class: Animal
   A class
*/
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

/*
   Class: ControlAnimals
   A class that controls the animals
*/ 
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