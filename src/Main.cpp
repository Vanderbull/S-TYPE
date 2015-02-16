#include <cmath>
#include <queue>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <chrono>
using namespace std;
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Global\Global.h"
#include "Game.h"
#include "Objects/SpaceShip.h"
#include "time.h"
#include "ConfigFileConverter.h"
#include "resource.h"

#ifdef _DEBUG
// THE CODE IS COMPILING IN DEBUG MODE.
#endif
//#pragma comment(linker,"/SUBSYSTEM:windows")

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

//deltatime variables
double t = 0.0;
double dt = 1 / 60.0;



// How many frames time values to keep
// The higher the value the smoother the result is...
// Don't make it 0 or less :)
#define FRAME_VALUES 10

// An array to store frame times:
Uint32 frametimes[FRAME_VALUES];

// Last calculated SDL_GetTicks
Uint32 frametimelast;

// total frames rendered
Uint32 framecount;

// the value you want
float framespersecond;

// This function gets called once on startup.
void fpsinit() {

    // Set all frame times to 0ms.
    memset(frametimes, 0, sizeof(frametimes));
    framecount = 0;
    framespersecond = 0;
    frametimelast = SDL_GetTicks();

}

void fpsthink() {

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
    if (framecount < FRAME_VALUES) {

        count = framecount;

    }
    else {

        count = FRAME_VALUES;

    }

    // add up all the values and divide to get the average frame time.
    framespersecond = 0;
    for (i = 0; i < count; i++) {

        framespersecond += frametimes[i];

    }

    framespersecond /= count;

    // now to make it an actual frames per second value...
    framespersecond = 1000.f / framespersecond;

}




int main( int argc, char * arg[] )
{
    // At the beginning of our application we need this
    int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    tmpFlag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(tmpFlag);

    LARGE_INTEGER start = { 0 }, end = { 0 }, freq = { 0 };
    SDL_Event event = { 0 };

    std::srand(std::time(0)); // use current time as seed for random generator
    QueryPerformanceFrequency(&freq);

    OSVERSIONINFO osvi;
    BOOL bIsWindowsXPorLater;

    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    GetVersionEx(&osvi);

    bIsWindowsXPorLater =
        ((osvi.dwMajorVersion > 5) ||
        ((osvi.dwMajorVersion == 5) && (osvi.dwMinorVersion >= 1)));

    if (bIsWindowsXPorLater)
    {   
        logger.write(__LINE__, "The system meets the requirements.");
    }
    else
    {
        logger.write(__LINE__, "The system does not meets the requirements.");
    }

    std::cout << "Have " << argc << " arguments:" << std::endl;
    for (int i = 0; i < argc; ++i) 
    {
        std::cout << arg[i] << std::endl;
    }
    
    //int random_variable = std::rand();
    //std::cout    << random_variable << '\n';
    //std::cout << "Random value on [0 " << RAND_MAX << "]: ";

	_putenv("SDL_VIDEO_WINDOW_POS=center");
	_putenv("SDL_VIDEO_CENTERED=1");

    // Playing Bink videos intro
    std::string video_path;
    video_path = PROJECT_ROOT_FOLDER;
    video_path.append("assets\\video\\0000-0200.exe");
	//ShellExecute(NULL, "open", video_path.c_str(),"", "", SW_HIDE );
    video_path = PROJECT_ROOT_FOLDER;
    video_path.append("assets\\video\\0001-0130.exe");
    //ShellExecute(NULL, "open", video_path.c_str(), "", "", SW_HIDE);

    logger.write(__LINE__, "Intro video playback finished...");


	SDL_WM_SetCaption("S-TYPE DEBUG", "src/res/power.ico");

    //cout << Engine.GamePad->CountDevices() << endl;
    //Engine.GamePad->init();
    Engine.GamePad.init();

    logger.write(__LINE__, "Engine GamePad initialized...");
    
    LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds = { 0 };
    LARGE_INTEGER Frequency = { 0 };

    // put this as close as possible to the start of the loop (before it starts!)
    fpsinit();

	while( Engine.Quit == false )
	{
        QueryPerformanceFrequency(&Frequency);
        QueryPerformanceCounter(&StartingTime);

		gamestate.DeltaTime = ((end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart);
        //logger.write(__LINE__, "DT = " + std::to_string(gamestate.DeltaTime));
		
		QueryPerformanceCounter(&start);

		while( SDL_PollEvent( &event ) )
        {
            Engine.HandleEvents( event );
        }
        
        //Engine.Update(event, (double)ElapsedMicroseconds.QuadPart);
        Engine.Update(event, (double)framespersecond);
        //Engine.GamePad->Update();
        //Engine.GamePad->HandleInput(event);
        Engine.GamePad.Update();
        //Engine.GamePad.HandleInput(event);
        //Audio.Render();
		Gfx.FLIP();  

        fpsthink();
        printf("%f\n", framespersecond);

		QueryPerformanceCounter(&end);
        QueryPerformanceCounter(&EndingTime);
        
        ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

        //
        // We now have the elapsed number of ticks, along with the
        // number of ticks-per-second. We use these values
        // to convert to the number of elapsed microseconds.
        // To guard against loss-of-precision, we convert
        // to microseconds *before* dividing by ticks-per-second.
        //
        
        ElapsedMicroseconds.QuadPart *= 1000000;
        ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	}

    gamestate.Cleanup();
	Engine.Cleanup();
	return 0;
}