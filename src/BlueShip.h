#pragma once
#include <list>
#include <stack>
#include <SDL.h>
#include "Bullets.h"
#include "Objects.h"

#define BLUESHIP_MAX_FRAMES 15
#define BLUESHIP_MIN_PROGRESS 0
#define BLUESHIP_MAX_PROGRESS 2500

class BlueShip : public Object
{

public:
	BlueShip();
	
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

class ControlBlueShip
{
public:
	ControlBlueShip();
	~ControlBlueShip();
	void DrawBlueShip();
	void CreateBlueShip( int iProgress );
	void Destroy(){ BlueShipArrayRef.clear(); };
	std::vector< BlueShip > GetVectorWithBlueShip(){ return BlueShipArrayRef; };
	BlueShip CreateBlueShipByReference( Sint16 xPos, Sint16 yPos, int surface );

	std::vector< BlueShip > BlueShipArrayRef;
private:

};

extern ControlBlueShip BlueShipController;