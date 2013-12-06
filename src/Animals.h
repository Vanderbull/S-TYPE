#pragma once
#include <list>
#include <stack>
#include <SDL.h>
#include "Bullets.h"
#include "Objects.h"

#define ANIMAL_MAX_FRAMES 15
#define ANIMAL_MIN_PROGRESS 0
#define ANIMAL_MAX_PROGRESS 2500

class Animal : public Object
{

public:
	Animal();
	
	int isColliding(SDL_Rect Box);
	SDL_Rect UpdateCollisionBox(SDL_Rect Box);
	void Update();
	void Draw();
	
	SDL_Rect GetDestination();

	bool isActive(){ return Active; };
	void DeActivate(){ Active = false; };
	void Activate(){ Active = true; };
	void onCollision(){ cout << "Im colliding with something" << endl; };
	void onDestruction(){ cout << "Im getting destroyed here" << endl; };
	void Spawn(){ cout << "Im getting spawned here" << endl; };

private:
	SDL_Rect Clips[ 16 ];
	int PrevFrame;
};

class ControlAnimals
{
public:
	ControlAnimals();
	~ControlAnimals();
	void DrawAnimals();
	void CreateAnimals( int iProgress );
	void Destroy(){ AnimalArrayRef.clear(); };
	std::vector< Animal > GetVectorWithAnimals(){ return AnimalArrayRef; };
	Animal CreateAnimalByReference( int xPos, int yPos, int surface );

	std::vector< Animal > AnimalArrayRef;
private:

};

extern ControlAnimals AnimalController;