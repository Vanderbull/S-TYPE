#pragma once
#include <list>
#include <stack>
#include <SDL.h>

// @date 2012-08-07


class AnimalState
{
public:
	float xPos, yPos;
	int Frame, State;
	int Height, Width;
	int Radius;
	int Surface;
	SDL_Rect CrowDest;
};

class Animal : public AnimalState
{

public:
	Animal();

	SDL_Rect Clips[ 16 ];
	void Setframe();
	void Update();
	void Draw();
	SDL_Rect GetDestination();
	int PrevFrameCrow;
	

private:
};

// the class that controls the animals
class ControlAnimals
{
public:
	ControlAnimals();
	~ControlAnimals();
	void Draw_Animals();
	void Create_Animals();

	int CrowTurf;

	Animal * CreateAnimal( int xPos, int yPos, int surface );

	
private:
	std::list< Animal* > My_Animals;
};

extern ControlAnimals AnimalController;