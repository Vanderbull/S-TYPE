#pragma once
#include <list>
#include <SDL.h>

class Object
{
public:

	Object(){};
	~Object(){};
	int Initialize(float _xPos, float _yPos, int _Width, int _Height,int Frame, int _Radius);
	int Object::SetClips(int _xStepping, int _yStepping, int _Width, int _Height);
	int xPos, yPos;
	int Width, Height;
	int Surface;
	int Frame;
	int Radius;

	SDL_Rect Clips[ 10 ];
	SDL_Rect SingleClip; // Tree
	std::list<SDL_Rect> ImageClips;
};

//class ThingsTodemon : public Object
//{
//public:
//	ThingsTodemon();
//	void SetClips();
//	SDL_Rect HealthClips[ 6 ];
//	int SurfaceHealth;
//};

class PowerUp : public Object
{
public:
	PowerUp( int _xPos, int _yPos, int Surface );
	//void SetClips();
	void SetFrame();
	bool Left, Right;
};

class Tree : public Object
{
public:
	Tree();
};

class Fireball : public Object
{
public:
	Fireball();
	//void SetClips();
	int FrameRight, FrameLeft;
	bool FireRight, FireLeft;

	int FireWidth, FireHeight;
};

class Coffin : public Object
{
public:
	Coffin();
	//void SetClips();
	void SetFrames();
};

class ControlObject
{
public:
	ControlObject();
	void DrawObjects();
	void CreateObjects();

	
	int WhichLifeToShow;
	SDL_Rect destHealth;
	int FrameHealth;

	int Zombie, Skeleton, Skull;

	bool PowerUpMan;
	
	Fireball * CreateFireBall( int xPos, int yPos, int Surface, bool Right, bool Left );
	Coffin * CreateCoffin( int xPos, int yPos, int Surface );

	PowerUp * WereWolf;
	
	std::list< PowerUp * > List_PowerUps;
	std::list< Tree * > List_Trees;
	std::list< Fireball * > List_FireBalls;
	std::list< Coffin * > List_Coffins;

	//ThingsTodemon * demonLife;

private:
};

extern ControlObject ObjectController;