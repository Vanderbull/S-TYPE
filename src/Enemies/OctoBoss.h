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
    OctoBoss(Vector3D v);

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

    int isColliding(SDL_Rect Box);
    SDL_Rect UpdateCollisionBox(SDL_Rect Box);
    void Update();
    void Draw();

    SDL_Rect GetDestination();
    int GetSurface();

    bool isActive(){ return Active; };
    void DeActivate(){ Active = false; };
    void Activate(){ Active = true; };
    void onCollision(){ };
    void onDestruction(){ };
    //void Spawn(Sint16 xPos, Sint16 yPos, int surface){ location.x = xPos; location.y = yPos; _Surface = surface; };
    void Spawn(){ };

private:
    SDL_Rect Clips[16];
    int _Surface;

    int PrevFrame;

    Vector3D acceleration;
    Vector3D velocity;
    Vector3D location;

    float lifespan;
};

class ControlOctoBoss
{
public:
    ControlOctoBoss();
    ~ControlOctoBoss();
    void DrawOctoBoss();
    void CreateOctoBoss(int iProgress);
    void Destroy(){ OctoBossArrayRef.clear(); };
    std::vector< OctoBoss > GetVectorWithOctoBoss(){ return OctoBossArrayRef; };
    OctoBoss CreateOctoBossByReference(Sint16 xPos, Sint16 yPos, int surface);

    std::vector< OctoBoss > OctoBossArrayRef;
private:

};

extern ControlOctoBoss OctoBossController;