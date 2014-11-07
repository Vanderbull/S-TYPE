#pragma once
#include <list>
#include <stack>
#include <SDL.h>
#include "../Bullets.h"
#include "../Objects.h"
#include "../ParticleController/Vector3D.h"

#define OCTOBOSS_MAX_FRAMES 15
#define OCTOBOSS_MAX_PROGRESS 10000
#define OCTOBOSS_MIN_PROGRESS 1000


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
    bool onCollision(SDL_Rect object);
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

    void onDestruction(){
        location.x = 0;
        location.y = 0;
        location.z = 0;
        velocity.x = 0;
        velocity.y = 0;
        velocity.z = 0;
        _collisionbox.x = 0;
        _collisionbox.y = 0;
        _collisionbox.h = 0;
        _collisionbox.w = 0;

    };
    void Spawn(){ };
    int LoadImageAlpha(std::string filename, int r, int g, int b);
    void FireLaser();

private:
    SDL_Rect Clips[16];
    int _SurfaceID;
    SDL_Surface* _Surface;

    int PrevFrame;

    Vector3D acceleration;
    Vector3D velocity;
    Vector3D location;

    float lifespan;
    std::vector<Bullet> mBullet;
    int _clip_height;
    int _clip_width;
    SDL_Rect _collisionbox;
};

extern OctoBoss OctoController;