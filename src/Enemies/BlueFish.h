#pragma once
#include <list>
#include <stack>
#include <SDL.h>
#include "../Bullets.h"
#include "../Objects/Objects.h"
#include "../ParticleController/Vector3D.h"

#define BLUEFISH_MAX_FRAMES 15
#define BLUEFISH_MAX_PROGRESS 10000
#define BLUEFISH_MIN_PROGRESS 1000

class BlueFish : public Object
{

public:
    BlueFish();
    BlueFish(Vector3D v);

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
    SDL_Rect Clips[16];
    int PrevFrame;
    float lifespan;
};

class ControlBlueFish
{
public:
    ControlBlueFish();
    ~ControlBlueFish();
    void DrawBlueFish();
    void CreateBlueFish(int iProgress);
    void Destroy(){ BlueFishArrayRef.clear(); };
    std::vector< BlueFish > GetVectorWithBlueFish(){ return BlueFishArrayRef; };
    BlueFish CreateBlueFishByReference(Sint16 xPos, Sint16 yPos, int surface);

    std::vector< BlueFish > BlueFishArrayRef;
private:

};

extern ControlBlueFish BlueFishController;