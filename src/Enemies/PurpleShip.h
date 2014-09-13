#pragma once
#include <list>
#include <stack>
#include <SDL.h>
#include "../Bullets.h"
#include "../Objects.h"

#define PURPLESHIP_MAX_FRAMES 15
#define PURPLESHIP_MAX_PROGRESS 30000
#define PURPLESHIP_MIN_PROGRESS 20000


class PurpleShip : public Object
{

public:
	PurpleShip();
	
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

class ControlPurpleShip
{
public:
	ControlPurpleShip();
	~ControlPurpleShip();
	void DrawPurpleShip();
	void CreatePurpleShip( int iProgress );
	void Destroy(){ PurpleShipArrayRef.clear(); };
	std::vector< PurpleShip > GetVectorWithPurpleShip(){ return PurpleShipArrayRef; };
	PurpleShip CreatePurpleShipByReference( Sint16 xPos, Sint16 yPos, int surface );

	std::vector< PurpleShip > PurpleShipArrayRef;
private:

};

extern ControlPurpleShip PurpleShipController;