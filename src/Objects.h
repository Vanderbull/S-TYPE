#pragma once
#include <iostream>
#include <list>
#include <vector>

using namespace std;
#include <SDL.h>

class Object
{
protected:
	Object();
	~Object(){ std::cout << "Destroying a object" << endl; };

public:

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual int isActive() = 0;
	virtual void DeActivate() = 0;
	virtual void onCollision() = 0;
	virtual void onDestruction() = 0;

	int Initialize(float _xPos, float _yPos, int _Width, int _Height,int Frame, int _Radius);
	int Object::SetClips(int _xStepping, int _yStepping, int _Width, int _Height);

	int Active;
	int xPos, yPos;
	int Width, Height;
	int Surface;
	int Frame;
	int Radius; // fireball crap
	SDL_Rect CollisionBox;

	SDL_Rect Clips[ 10 ];
	SDL_Rect SingleClip; // Tree
	std::list<SDL_Rect> ImageClips;
};

// Types of asteroids carbonaceous (stony and darker than coal);  silicaceous (bright, stony bodies which contain metal), and metallic (exposed metallic cores of much larger bodies)
class Asteroid : public Object
{
public:

	Asteroid( int _xPos, int _yPos, int _SurfaceID ) {};
	void Update() {};
	void Draw() {};
	int isActive() { return true; };
	void DeActivate() {};
	void onCollision(){};
	void onDestruction(){};
};

class PowerUp : public Object
{
public:
	PowerUp( int _xPos, int _yPos, int Surface );
	void Update() {};
	void Draw() {};
	int isActive() { return true; };
	void DeActivate() {};
	void onCollision(){};
	void onDestruction(){};

	void SetFrame();
	bool Left, Right;
};

class Tree : public Object
{
public:
	Tree();
	void Update() {};
	void Draw() {};
	int isActive() { return true; };
	void DeActivate() {};
	void onCollision(){};
	void onDestruction(){};
};

class Fireball : public Object
{
public:
	Fireball();
	void Update() {};
	void Draw() {};
	int isActive() { return true; };
	void DeActivate() {};
	void onCollision(){};
	void onDestruction(){};

	int FrameRight, FrameLeft;
	bool FireRight, FireLeft;

	int FireWidth, FireHeight;
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

	bool PowerUpMan;
	
	//vector of objects
	std::vector<Asteroid> ActiveAsteroids;
	Asteroid SpawnAsteroid( int _xPos, int _yPos, int _SurfaceID )
	{
		Asteroid AsteroidBuilder(_xPos,_yPos,_SurfaceID);
		return AsteroidBuilder;
	};

	void Report(Object &rObject)
	{
		rObject.Active = false;
		cout << "Object is " << rObject.isActive() << endl;
	}

	void ReportList()
	{
		cout << "Object is " << endl;
	}

	void RemoveActiveObjects()
	{
		for(std::vector<Asteroid>::iterator it = ActiveAsteroids.begin(); it != ActiveAsteroids.end(); ++it) 
		{
			std::cout << (*it).isActive() << endl;
			if( !(*it).isActive() )
			{
				std::cout << "This should remove the asteroid from the vector" << endl;
			}
		}
	}


private:
};

extern ControlObject ObjectController;