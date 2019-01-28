#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "OctoBoss.h"
#include "../Game.h"
#include "../GfxController/ControlGfx.h"

// 1. this should go into every .cpp , after all header inclusions
#ifdef _WIN32
#ifdef _DEBUG
#include <crtdbg.h>
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new       new( _NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif

OctoBoss OctoController;

const float OctoBossSpeed = 0.0001f;

OctoBoss::OctoBoss()
{
    acceleration = Vector3D(0, 0, 0);
    velocity = Vector3D(0, 0, 0);
    location = Vector3D(0, 0, 0);
    spawn_point = Vector3D(13000, 0, 0);

    lifespan = 2550.0f;
    Active = 0;

    LocAndSize.x = 0;
    LocAndSize.y = 0;
    LocAndSize.h = SpriteHeight;
    LocAndSize.w = SpriteWidth;

    _clip_height = 300;
    _clip_width = 300;
    _health = 1000;
}

OctoBoss::OctoBoss(Vector3D v, std::string inSurfaceImage)
{
    acceleration = Vector3D(0, 0, 0);
    velocity = Vector3D(0, 0, 0);
    location = v;
    spawn_point = Vector3D(13000, 0, 0);

    lifespan = 2550.0f;
    Active = 0;

    LocAndSize.x = GetX();
    LocAndSize.y = GetY();
    LocAndSize.h = _clip_height;
    LocAndSize.w = _clip_width;

    _clip_height = 300;
    _clip_width = 300;
    _health = 1000;
};

OctoBoss::~OctoBoss()
{
    SDL_FreeSurface(_Surface);
}

void OctoBoss::applyForce(Vector3D force)
{
    acceleration = force;
}

float OctoBoss::GetX()
{
    return location.x;
}

float OctoBoss::GetY()
{
    return location.y;
}

void OctoBoss::checkEdges(float width = 0, float height = 0)
{
    if (location.x +301 > width)
    {
        location.x = width - 301;
        velocity.x *= -1;
    }
    else if (location.x < 0)
    {
        velocity.x *= -1;
        location.x = 0;
    }

    if (location.y + 301 > height)
    {
        location.y = height - 301;
        velocity.y *= -1;
    }
    else if (location.y < 0)
    {
        velocity.y *= -1;
        location.y = 0;
    }
}

bool OctoBoss::onCollision(SDL_Rect* object)
{
    return !(
            object->x > ( _collisionbox.x + _collisionbox.w )
        ||  ( object->x + object->w ) < _collisionbox.x
        ||  object->y > ( _collisionbox.y + _collisionbox.h )
        ||  ( object->y + _collisionbox.h ) < _collisionbox.y );
}

void OctoBoss::Update()
{
    if (isActive())
    {
        velocity = velocity + acceleration;
        location = velocity + location;
        // add acceleration to velocity
        // add velocity to location
        lifespan -= 2.0f;

        checkEdges(1920, 1080);

        xPos = OctoBossSpeed * gamestate.DeltaTime;
        LocAndSize.x = GetX();
        LocAndSize.y = GetY();
        LocAndSize.h = _clip_height;
        LocAndSize.w = _clip_width;

        CollisionBox.x = GetX();
        CollisionBox.y = GetY();
        CollisionBox.h = _clip_height;
        CollisionBox.w = _clip_width;

        _collisionbox.x = GetX();
        _collisionbox.y = GetY();
        _collisionbox.h = _clip_height;
        _collisionbox.w = _clip_width;
    }
}

void OctoBoss::Draw()
{
    SDL_Rect m_location;
    m_location.x = location.x;
    m_location.y = location.y;
    m_location.h = _Surface->clip_rect.h;
    m_location.w = _Surface->clip_rect.w;
    SDL_BlitSurface(
        _Surface,
        0,
        Gfx.BackBuffer,
        &m_location
        );

    if (action_event.size() > 0)
    {
    for (int i = 0; i < 15; i++)
    {
        for (int i = 0; i < 15; i++)
        {
            SDL_BlitSurface(
                Gfx.GetSurface(gamestate.m_srfExplosion[i]),
                0,
                Gfx.BackBuffer,
                &_collisionbox
                );
        }
    }
    action_event.pop_back();
    }
}

SDL_Rect OctoBoss::GetDestination()
{
    return LocAndSize;
}

int OctoBoss::GetSurfaceID()
{
    return _SurfaceID;
}

SDL_Surface* OctoBoss::GetSurface()
{
    return _Surface;
}

void OctoBoss::SetSurface(SDL_Surface* inSurface)
{
    _Surface = inSurface;
}

// loads image with chosen value to not show
int OctoBoss::LoadImageAlpha(std::string filename, int r = 0, int g = 0, int b = 0)
{
    _Surface = IMG_Load(filename.c_str());
    if (_Surface != NULL)
    {
        //_Surface = SDL_DisplayFormatAlpha(_Surface);
        _Surface = SDL_ConvertSurface(_Surface, _Surface->format, NULL);
    }
    if (_Surface != NULL)
    {
        //SDL_SetColorKey(_Surface, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(_Surface->format, r, g, b));
        SDL_SetColorKey(_Surface, SDL_TRUE, SDL_MapRGB(_Surface->format, r, g, b));
    }
    return 0;
}

int OctoBoss::hasHealth()
{
    return _health;
}

void OctoBoss::isWounded(int idamage)
{
    action_event.push_back("explosion");

    static int frame_explosion;

    //if (frame_explosion > 15)
    //    frame_explosion = 0;

    //for (int i = 0; i < 15; i++)
    //{
    //SDL_BlitSurface(
    //    Gfx.GetSurface(gamestate.m_srfExplosion[i]),
    //    0,
    //    Gfx.BackBuffer,
    //    &_collisionbox
    //    );
    //}
    //frame_explosion++;

    _health -= idamage;
    FireInk();
}

Vector3D OctoBoss::GetSpawnPoint()
{
    return spawn_point;
}

void OctoBoss::Spawn(){}

int OctoBoss::Spawn(int checkpoint)
{
    if (!isActive())
    {
        if (checkpoint > spawn_point.x )
        {
            velocity = Vector3D(0, 0, 0);
            location = Vector3D(Gfx.BackBuffer->w - _Surface->w, 0, 0);
            Activate();
            return 0;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}

void OctoBoss::onDestruction()
{
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
    _health = 1000;
    DeActivate();
};

void OctoBoss::FireInk()
{
    OctoBulletController.CreateOctoBullets();
}
