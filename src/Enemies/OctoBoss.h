#pragma once

#include <SDL2/SDL.h>
//#include <SDL.h>

#include <list>
#include <stack>

#include "../Objects/Bullets.h"
#include "../Objects/Objects.h"
#include "../ParticleController/Vector3D.h"

#define OCTOBOSS_MAX_FRAMES 15

class OctoBoss : public Object
{

public:
    OctoBoss();
    OctoBoss(Vector3D v,std::string inSurfaceImage);
    ~OctoBoss();
    void applyForce(Vector3D force);
    float GetX();
    float GetY();
    void checkEdges(float width, float height);
    bool onCollision(SDL_Rect* object);
    void onCollision(){ };
    void Update();
    void Draw();

    SDL_Rect GetDestination();
    int GetSurfaceID();
    SDL_Surface* GetSurface();
    void SetSurface(SDL_Surface* inSurface);

    bool isActive(){ return Active; };
    void DeActivate(){ Active = false; };
    void Activate(){ Active = true; };
    void onDestruction();
    int LoadImageAlpha(std::string filename, int r, int g, int b);
    int hasHealth();
    void isWounded(int idamage);
    Vector3D GetSpawnPoint();
    void Spawn();
    int Spawn(int checkpoint);
    void FireInk();

private:
    SDL_Rect Clips[16];
    int _SurfaceID;
    SDL_Surface* _Surface;

    int PrevFrame;

    Vector3D acceleration;
    Vector3D velocity;
    Vector3D location;
    Vector3D spawn_point;

    float lifespan;
    std::vector<Bullet> mBullet;
    int _clip_height;
    int _clip_width;
    SDL_Rect _collisionbox;
    int _health;
    std::vector<std::string> action_event;
};

extern OctoBoss OctoController;
