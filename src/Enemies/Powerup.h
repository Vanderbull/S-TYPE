#pragma once
#include <iostream>
#include <list>
#include <vector>

using namespace std;
#include <SDL.h>
#include "../Objects/Objects.h"

#define MAX_FRAMES 15
#define MIN_PROGRESS 0
#define MAX_PROGRESS 2500
#define CLIP_COUNT 16

class Powerup : public Object
{

public:
	Powerup();

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
    int GetTimer(){ return Timer--; };

private:
	SDL_Rect Clips[ CLIP_COUNT ];
	int PrevFrame;
    int Timer;
};

class ControlPowerup
{
public:
	ControlPowerup();
	~ControlPowerup();
	void DrawPowerup();
    void CreatePowerup( SDL_Rect Pobject );
	void Destroy(){ PowerupArrayRef.clear(); };
	std::vector< Powerup > GetVectorWithPowerups(){ return PowerupArrayRef; };
	Powerup CreatePowerupByReference( int xPos, int yPos, int surface );

	std::vector< Powerup > PowerupArrayRef;
private:

};

extern ControlPowerup PowerupController;