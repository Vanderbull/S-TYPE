#pragma once

#include <SDL2/SDL.h>

#include <iostream>
#include <list>
#include <vector>

using namespace std;

#include "../ParticleController/Vector3D.h"

class Object
{
protected:
	Object();
	~Object(){ std::cout << "Destroying a object..." << std::endl; };

public:

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual bool isActive() = 0;
	virtual void DeActivate() = 0;
	virtual void Activate() = 0;
	virtual void onCollision() = 0;
	virtual void onDestruction() = 0;
	virtual void Spawn() = 0;

    SDL_Rect* GetRenderBox();
    SDL_Rect UpdateCollisionBox(SDL_Rect Box);
    int isColliding(SDL_Rect Box);

    void applyForce(Vector3D force)
    {
        acceleration = force;
    }
    float GetX()
    {
        return location.x;
    }
    float GetY()
    {
        return location.y;
    }

    void checkEdges(float width = 0, float height = 0)
    {
        if (location.x > width)
        {
            location.x = width;
            velocity.x *= -1;
        }
        else if (location.x < 0)
        {
            velocity.x *= -1;
            location.x = 0;
        }

        if (location.y > height)
        {
            velocity.y *= -1;
            location.y = height;
        }
        else if (location.y < 0)
        {
            velocity.y *= -1;
            location.y = 0;
        }
    }

	int Initialize(SDL_Rect iData,int Frame);

	int SetClips(int _xStepping, int _yStepping, int _Width, int _Height);

	bool Active;
	int SurfaceID;
	int Frame;
	float xPos, yPos;
	SDL_Rect LocAndSize;
	SDL_Rect CollisionBox;

	SDL_Rect Clips[ 10 ];
	std::list<SDL_Rect> ImageClips;

    Vector3D acceleration;
    Vector3D velocity;
    Vector3D location;
};

// Types of asteroids carbonaceous (stony and darker than coal);  silicaceous (bright, stony bodies which contain metal), and metallic (exposed metallic cores of much larger bodies)
class Asteroid : public Object
{
public:

	Asteroid( int _x = 0, int _y = 0, int _SurfaceID = 0 ) { x = _x; y = _y; SurfaceID = _SurfaceID; };
	void Update() {};
	void Draw() {};
	bool isActive(){ return true; };
	void DeActivate(){ Active = false; };
	void Activate(){ Active = true; };
	void onCollision(){};
	void onDestruction(){};
	void Spawn() {};

private:
    int x;
    int y;
    int SurfaceID;
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
