#pragma once
#include <iostream>
#include <list>
#include <vector>

using namespace std;
#include <SDL.h>
#include "../Objects.h"

#define ANIMAL_MAX_FRAMES 15
#define ANIMAL_MIN_PROGRESS 0
#define ANIMAL_MAX_PROGRESS 2500

class Powerup : public Object
{

public:
	Powerup();
	
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

class ControlPowerup
{
public:
	ControlPowerup();
	~ControlPowerup();
	void DrawPowerup();
	void CreatePowerup( int iProgress );
	void Destroy(){ PowerupArrayRef.clear(); };
	std::vector< Powerup > GetVectorWithPowerups(){ return PowerupArrayRef; };
	Powerup CreatePowerupByReference( int xPos, int yPos, int surface );

	std::vector< Powerup > PowerupArrayRef;
private:

};

extern ControlPowerup PowerupController;