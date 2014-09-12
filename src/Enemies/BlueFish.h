#pragma once
#include <list>
#include <stack>
#include <SDL.h>
#include "../Bullets.h"
#include "../Objects.h"

#define BLUEFISH_MAX_FRAMES 15
#define BLUEFISH_MAX_PROGRESS 10000
#define BLUEFISH_MIN_PROGRESS 0

class BlueFish : public Object
{

public:
    BlueFish();

    int isColliding(SDL_Rect Box);
    SDL_Rect UpdateCollisionBox(SDL_Rect Box);
    void Update();
    void Draw();

    SDL_Rect GetDestination();

    bool isActive(){ return Active; };
    void DeActivate(){ Active = false; };
    void Activate(){ Active = true; };
    void onCollision(){ cout << "Im colliding with something" << endl; };
    void onDestruction(){ cout << "Im getting destroyed here" << endl; };
    void Spawn(){ cout << "Im getting spawned here" << endl; };

private:
    SDL_Rect Clips[16];
    int PrevFrame;
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