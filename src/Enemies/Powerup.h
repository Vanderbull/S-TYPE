#pragma once
#include <iostream>
#include <list>
#include <vector>

using namespace std;
#include <SDL.h>
#include "../Objects.h"

class Powerup
{
protected:
	Powerup();
	~Powerup(){};

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

	int Powerup::SetClips(int _xStepping, int _yStepping, int _Width, int _Height);

	bool Active;
	int SurfaceID;
	int Frame;
	float xPos, yPos;
	SDL_Rect LocAndSize;
	SDL_Rect CollisionBox;

	SDL_Rect Clips[ 10 ];
	std::list<SDL_Rect> ImageClips;
};

class Red : public Powerup
{
public:

	Red( int _xPos, int _yPos, int _SurfaceID ) {};
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

class ControlPowerup
{
public:
	ControlPowerup();
	void DrawPowerup();
	void CreatePowerup();
	
	SDL_Rect destHealth;
	int FrameHealth;
	
	//vector of objects
	std::vector<Red> ActiveRed;
	Red SpawnPowerup( int _xPos, int _yPos, int _SurfaceID )
	{
		Red PowerupBuilder(_xPos,_yPos,_SurfaceID);
		return PowerupBuilder;
	};

	void Report(Object &rObject)
	{
		rObject.Active = false;
	}

	void ReportList()
	{
		cout << "Powerup is " << endl;
	}

	void RemoveActivePowerup()
	{
		for(std::vector<Red>::iterator it = ActiveRed.begin(); it != ActiveRed.end(); ++it) 
		{
			std::cout << (*it).isActive() << endl;
			if( !(*it).isActive() )
			{
				std::cout << "This should remove the Powerup from the vector" << endl;
			}
		}
	}


private:
};

extern ControlPowerup PowerupController;