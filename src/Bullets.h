#pragma once
#include <list>
#include <vector>
#include <stack>
#include <SDL.h>
#include "Objects.h"

#define BULLET_MAX_FRAMES 15

/// <summary>Used to create a Bullet entity</summary>
class Bullet : public Object
{

public:
	Bullet();
	
	SDL_Rect UpdateCollisionBox(SDL_Rect Box);
	void Update();
	void Draw();
	int GetSurfaceID();
	void onCollision(){};
	int isActive(){ return 0; };
	void DeActivate(){};
	void onDestruction(){};
	
	SDL_Rect GetLocAndSize();

private:
	SDL_Rect Clips[ 16 ];
	int PrevFrame;
};

/// <summary>A class the controls the animals</summary> 
class ControlBullets
{
public:
	ControlBullets();
	~ControlBullets();
	void Draw_Bullets();
	void Create_Bullets();

	void LoadBullet( int xPos, int yPos, int iSurfaceID );
	std::vector< Bullet > GetVBulletsByReference(){ return BulletArrayRef; };

	std::list< Bullet > GetBulletsByReference(){ return Bullets;};

	Bullet CreateBulletByReference( int xPos, int yPos, int surface );

	
private:
	std::vector< Bullet > BulletArrayRef;

	std::list< Bullet > Bullets;
};

extern ControlBullets BulletController;