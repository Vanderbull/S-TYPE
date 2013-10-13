#pragma once
#include <list>
#include <stack>
#include <SDL.h>
#include "Bullets.h"

#define ANIMAL_MAX_FRAMES 15
#define ANIMAL_MIN_PROGRESS 0
#define ANIMAL_MAX_PROGRESS 2500

typedef struct sPosition
{
	float x,y,z,h,w;
} AnimalPosition;

/// <summary>A basic ammo object</summary>
class AnimalObject
{
public:
	AnimalPosition mPosition;
	int SurfaceID;
	SDL_Rect CollisionBox;
	SDL_Rect Destination;
	int Frame;

private:
};

/// <summary>Used to create a Animal entity</summary>
class Animal : public AnimalObject
{

public:
	Animal();
	
	int isColliding(SDL_Rect Box);
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