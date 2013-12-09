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
	~Object(){};

public:

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual bool isActive() = 0;
	virtual void DeActivate() = 0;
	virtual void Activate() = 0;
	virtual void onCollision() = 0;
	virtual void onDestruction() = 0;
	virtual void Spawn() = 0;


	int Initialize(SDL_Rect iData,int Frame);

	int Object::SetClips(int _xStepping, int _yStepping, int _Width, int _Height);

	bool Active;
	int SurfaceID;
	int Frame;
	float xPos, yPos;
	SDL_Rect LocAndSize;
	SDL_Rect CollisionBox;

	SDL_Rect Clips[ 10 ];
	std::list<SDL_Rect> ImageClips;
};

// Types of asteroids carbonaceous (stony and darker than coal);  silicaceous (bright, stony bodies which contain metal), and metallic (exposed metallic cores of much larger bodies)
class Asteroid : public Object
{
public:

	Asteroid( int _xPos, int _yPos, int _SurfaceID ) {};
	void Update() {};
	void Draw() {};
	bool isActive(){ return true; };
	void DeActivate(){ Active = false; };
	void Activate(){ Active = true; };
	void onCollision(){};
	void onDestruction(){};
	void Spawn() {};

private:
};

class ControlObject
{
public:
	ControlObject();
	void DrawObjects();
	void CreateObjects();
	
	SDL_Rect destHealth;
	int FrameHealth;
	
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
		//cout << "Object is " << rObject.isActive() << endl;
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