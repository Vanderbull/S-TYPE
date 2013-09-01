#pragma once
#include <list>
#include <stack>
#include <SDL.h>

/// <summary>A basic object</summary>
class AmmoObject
{
public:
	float xPos,yPos;
	int Height,Width;
	int SurfaceID;
	SDL_Rect Boundry;

	virtual int Collision(SDL_Rect Boundry);

private:
};

/// <summary>Keeps the state of any bullet</summary>
class BulletState
{
public:
	int Frame, State;
	int Radius;
	int Surface;
	SDL_Rect Destination;
};

/// <summary>Used to create a Bullet entity</summary>
class Bullet : public BulletState,public AmmoObject
{

public:
	Bullet();
	
	void Setframe();
	void Update();
	void Draw();
	int GetSurfaceID();
	int Collision();
	
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

	int Turf;

	Bullet * CreateBullet( int xPos, int yPos, int surface );

	
private:
	std::list< Bullet* > My_Bullets;
};

extern ControlBullets BulletController;