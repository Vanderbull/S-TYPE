#pragma once
#include <iostream>
#include <list>
#include <vector>
using namespace std;

#include <SDL.h>
#include "Vector3D.h"

class Particle
{
public:

    Particle()
    {
        acceleration = Vector3D(0.0f, 0.0f, 0.0f);
        velocity = Vector3D(0.0f, 0.0f, 0.0f);
        location = Vector3D(0.0f, 0.0f, 0.0f);

        lifespan = 255.0f;
    }

    Particle(Vector3D v)
    {
        acceleration = Vector3D(0, 0, 0);
        velocity = Vector3D(0, 0, 0);
        location = v;

        lifespan = 255.0f;
    };


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

    void applyForce(Vector3D force) 
    {
        acceleration = force;
    }

    void Update()
    {
        velocity = velocity + acceleration;
        location = velocity + location;
        // add acceleration to velocity
        // add velocity to location
        lifespan -= 2.0f;
    };
    void Display()
    {
        // render at location
    };

    bool isDead()
    {
        if (lifespan < 0.0f)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    float GetX()
    {
        return location.x;
    }
    float GetY()
    {
        return location.y;
    }


private:
    Vector3D location;
    Vector3D velocity;
    Vector3D acceleration;
    float lifespan;

};

class ControlParticle
{
public:
private:
};

extern ControlParticle ParticleController;