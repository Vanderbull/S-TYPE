#pragma once
#include <list>
#include <vector>
#include <stack>
#include <SDL.h>

#define BULLET_MAX_FRAMES 15

/// <summary>A basic ammo object</summary>
class AmmoObject
{
public:
	float xPos,yPos;
	int Height,Width;
	int Radius;
	int SurfaceID;
	int Frame;
	int State;
	SDL_Rect CollisionBox;
	SDL_Rect Destination;
	virtual void onCollision() = 0;

private:
};

/// <summary>Used to create a Bullet entity</summary>
class Bullet : public AmmoObject
{

public:
	Bullet();
	
	SDL_Rect UpdateCollisionBox(SDL_Rect Box);
	void Update();
	void Draw();
	int GetSurfaceID();
	void onCollision(){};
	
	SDL_Rect GetDestination();

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

	void LoadBullet( int xPos, int yPos, int surface );
	std::vector< Bullet > GetVBulletsByReference(){ return BulletArrayRef; };

	std::list< Bullet* > GetBullets(){ return My_Bullets;};
	std::list< Bullet > GetBulletsByReference(){ return Bullets;};

	Bullet * CreateBullet( int xPos, int yPos, int surface );
	Bullet CreateBulletByReference( int xPos, int yPos, int surface );

	
private:
	std::vector< Bullet > BulletArrayRef;

	std::list< Bullet* > My_Bullets;
	std::list< Bullet > Bullets;
};

extern ControlBullets BulletController;