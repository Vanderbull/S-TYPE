#include "fps.h"
#include <SDL.h>
#include "../game.h"
//#include "../GfxController/ControlGfx.h"

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

fps fpsController;

fps::fps()
{}

// This function gets called once on startup.
void fps::fpsinit()
{
    // Set all frame times to 0ms.
    memset(frametimes, 0, sizeof(frametimes));
    framecount = 0;
    framespersecond = 0;
    frametimelast = SDL_GetTicks();
}

void fps::fpsthink()
{
    Uint32 frametimesindex;
    Uint32 getticks;
    Uint32 count;
    Uint32 i;

    // frametimesindex is the position in the array. It ranges from 0 to FRAME_VALUES.
    // This value rotates back to 0 after it hits FRAME_VALUES.
    frametimesindex = framecount % FRAME_VALUES;

    // store the current time
    getticks = SDL_GetTicks();

    // save the frame time value
    frametimes[frametimesindex] = getticks - frametimelast;

    // save the last frame time for the next fpsthink
    frametimelast = getticks;

    // increment the frame count
    framecount++;

    // Work out the current framerate

    // The code below could be moved into another function if you don't need the value every frame.

    // I've included a test to see if the whole array has been written to or not. This will stop
    // strange values on the first few (FRAME_VALUES) frames.
    if (framecount < FRAME_VALUES)
    {
        count = framecount;
    }
    else
    {
        count = FRAME_VALUES;
    }

    // add up all the values and divide to get the average frame time.
    framespersecond = 0;
    for (i = 0; i < count; i++)
    {
        framespersecond += frametimes[i];
    }

    framespersecond /= count;

    // now to make it an actual frames per second value...
    framespersecond = 1000.f / framespersecond;
}