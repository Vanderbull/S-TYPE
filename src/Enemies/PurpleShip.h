#pragma once
#include <list>
#include <stack>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//#include <SDL.h>
#include "../Objects/Bullets.h"
#include "../Objects/Objects.h"
#include "../ParticleController/Vector3D.h"

#define PURPLESHIP_MAX_FRAMES 15
#define PURPLESHIP_MAX_PROGRESS 10000
#define PURPLESHIP_MIN_PROGRESS 1000

class PurpleShip : public Object
{

public:
    PurpleShip();
    PurpleShip(Vector3D v);

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

class ControlPurpleShip
{
public:
    ControlPurpleShip();
    ~ControlPurpleShip();
    void DrawPurpleShip();
    void CreatePurpleShip(int iProgress);
    void Destroy(){ PurpleShipArrayRef.clear(); };
    std::vector< PurpleShip > GetVectorWithPurpleShip(){ return PurpleShipArrayRef; };
    PurpleShip CreatePurpleShipByReference(Sint16 xPos, Sint16 yPos, int surface);

    std::vector< PurpleShip > PurpleShipArrayRef;
private:

};

extern ControlPurpleShip PurpleShipController;
