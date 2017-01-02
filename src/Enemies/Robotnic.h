#pragma once

#include <SDL2/SDL.h>
//#include <SDL.h>

#include <list>
#include <stack>

#include "../Objects/Bullets.h"
#include "../Objects/Objects.h"
#include "../ParticleController/Vector3D.h"

#define ROBOTNIC_MAX_FRAMES 15
#define ROBOTNIC_MAX_PROGRESS 10000
#define ROBOTNIC_MIN_PROGRESS 1000

class Robotnic : public Object
{

public:
    Robotnic();
    Robotnic(Vector3D v);

	void Update();
	void Draw();

	bool isActive(){ return Active; };
	void DeActivate(){ Active = false; };
	void Activate(){ Active = true; };

	void onCollision(){ };
	void onDestruction(){ };
	void Spawn(){ };

    std::vector<SDL_Rect> bullet_object;

private:
	SDL_Rect Clips[ 16 ];
	int PrevFrame;
    float lifespan;
};

class ControlRobotnic
{
public:
    ControlRobotnic();
    ~ControlRobotnic();
    void DrawRobotnic();
    void CreateRobotnic(int iProgress);
    void Destroy(){ RobotnicArrayRef.clear(); };
    std::vector< Robotnic > GetVectorWithRobotnic(){ return RobotnicArrayRef; };
    Robotnic CreateRobotnicByReference(Sint16 xPos, Sint16 yPos, int surface);

    std::vector< Robotnic > RobotnicArrayRef;
private:

};

extern ControlRobotnic RobotnicController;
