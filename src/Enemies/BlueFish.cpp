#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//#include <SDL.h>

//#include "Global\Global.h"
#include "BlueFish.h"
#include "../Game.h"
#include "../GfxController/ControlGfx.h"

#define BLUEFISH_MAX_FRAMES 15
#define BLUEFISH_MAX_PROGRESS 12000
#define BLUEFISH_MIN_PROGRESS 10000

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

ControlBlueFish BlueFishController;
const double BlueFishSpeed = -15.0;

BlueFish::BlueFish()
{
    logger.write(__LINE__, __FUNCTION__);

    // Activate object
    Active = 1;

    // Setup speed and placement
    acceleration = Vector3D(0, 0, 0);
    velocity = Vector3D(0, 0, 0);
    location = Vector3D(0, 0, 0);

    // Set for how long the object should be activate
    lifespan = 255.0f;

    // Set size for collision box
    CollisionBox.h = SpriteHeight - 16;
    CollisionBox.w = SpriteWidth - 16;
    CollisionBox.x = location.x;
    CollisionBox.y = location.y;

    // Setup framerelated information
    PrevFrame = 0;
    Frame = 0;

    // Setup size of image clips for animation
    for (int i = 0; i < 16; i++)
    {
        Clips[i].x = (Sint16)i * SpriteWidth;
        Clips[i].y = 0;
        Clips[i].h = SpriteHeight;
        Clips[i].w = SpriteWidth;
    }

    // Setup the red noise box
    SDL_Rect tmp;

    for (int i = 0; i < 250; i++)
    {
        tmp.h = rand() % 5;
        tmp.w = tmp.h;
        tmp.x = location.x - rand() % 100;
        tmp.y = location.y;
        bullet_object.push_back(tmp);
    };
}

BlueFish::BlueFish(Vector3D v)
{
    logger.write(__LINE__, __FUNCTION__);

    Active = 1;

    acceleration = Vector3D(0, 0, 0);
    velocity = Vector3D(0, 0, 0);
    location = v;

    lifespan = 255.0f;

    CollisionBox.h = SpriteHeight - 16;
    CollisionBox.w = SpriteWidth - 16;
    CollisionBox.x = location.x;
    CollisionBox.y = location.y;

    PrevFrame = 0;
    Frame = 0;

    for (int i = 0; i < 16; i++)
    {
        Clips[i].x = (Sint16)i * SpriteWidth;
        Clips[i].y = 0;
        Clips[i].h = SpriteHeight;
        Clips[i].w = SpriteWidth;
    }

    SDL_Rect tmp;

    for (int i = 0; i < 250; i++)
    {
        tmp.h = rand() % 5;
        tmp.w = tmp.h;
        tmp.x = location.x - rand() % 100;
        tmp.y = location.y;
        bullet_object.push_back(tmp);
    };
};

void BlueFish::Update()
{
    logger.write(__LINE__, __FUNCTION__);

    SDL_Rect tmp;
    bullet_object.clear();


    //checkEdges(1920 - SpriteWidth, 1080 - SpriteHeight);
    velocity = velocity + acceleration;
    location = velocity + location;

    CollisionBox.x = GetX() + (SpriteHeight / 2);
    CollisionBox.y = GetY() + (SpriteWidth / 2);
    CollisionBox.h = SpriteHeight / 2;
    CollisionBox.w = SpriteWidth / 2;

    for (int i = 0; i < 1000; i++)
    {
        tmp.h = rand() % 5;
        tmp.w = tmp.h;
        tmp.x = GetX() - rand() % 100;
        tmp.y = GetY() - rand() % 100;
        bullet_object.push_back(tmp);
    };

    PrevFrame = Frame++;
    if (Frame >= BLUEFISH_MAX_FRAMES)
    {
        Frame = 0;
    }

    lifespan -= 2.0f;

    //UpdateCollisionBox(LocAndSize);
}

void BlueFish::Draw()
{
    logger.write(__LINE__, __FUNCTION__);
/*
    SDL_BlitSurface(
        Gfx.GetSurface(SurfaceID),
        &Clips[0], //PrevFrame replaced with 0 as there is no animation
        Gfx.BackBuffer,
        &GetRenderBox()
        );
*/
    SDL_FillRect(Gfx.BackBuffer, &CollisionBox, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 255, 0, 0));
}

void ControlBlueFish::DrawBlueFish()
{
    logger.write(__LINE__, __FUNCTION__);

    std::vector< BlueFish >::iterator i;

    i = BlueFishArrayRef.begin();

    while (i != BlueFishArrayRef.end())
    {
        i->Update();
        i->applyForce(Vector3D(0, 2 * (double)rand() / (double)RAND_MAX - 1, 0));
        i->Draw();

        if (i->location.x <= 0.0f - SpriteWidth)
        {
            i = BlueFishArrayRef.erase(i);
        }
        else
        {
            ++i;
        }
    }
}

void ControlBlueFish::CreateBlueFish(int iProgress)
{
    logger.write(__LINE__, __FUNCTION__);

    if (iProgress > BLUEFISH_MIN_PROGRESS && iProgress < BLUEFISH_MAX_PROGRESS)
    {
        if (std::rand() % 100 + 1 > 99)
        {
            //BlueFishArrayRef.push_back(CreateBlueFishByReference(SDL_GetVideoSurface()->w, std::rand() % Gfx.BackBuffer->h, gamestate.m_srfBlueFish));

            BlueFishArrayRef.push_back(CreateBlueFishByReference(800, std::rand() % Gfx.BackBuffer->h, gamestate.m_srfBlueFish));
        }
    }
}

ControlBlueFish::ControlBlueFish()
{
    logger.write(__LINE__, __FUNCTION__);
}

ControlBlueFish::~ControlBlueFish()
{
    logger.write(__LINE__, __FUNCTION__);
}

BlueFish ControlBlueFish::CreateBlueFishByReference(Sint16 xPos, Sint16 yPos, int surface)
{
    logger.write(__LINE__, __FUNCTION__);

    static int old_y_pos = 0;

    while (yPos > old_y_pos && yPos < old_y_pos + 128)
    {
        yPos = (Sint16)(std::rand() % Gfx.BackBuffer->h - 128);
    }

    if (yPos < 64)
    {
        yPos = 64;
    }

    if (yPos > Gfx.BackBuffer->h - 128)
    {
        yPos = (Sint16)(Gfx.BackBuffer->h - 128);
    }

    BlueFish temp;
    temp.SurfaceID = surface;

    temp.location = Vector3D(xPos, yPos, 0);

    BlueFish temp2(Vector3D(xPos, yPos, 0.0f));
    temp2.applyForce(Vector3D(BlueFishSpeed, 0, 0));
    temp2.SurfaceID = surface;
    temp2.LocAndSize.x = temp2.GetX();
    temp2.LocAndSize.y = temp2.GetY();

    return temp2;
}
