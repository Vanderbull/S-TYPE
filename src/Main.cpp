#include <cmath>
#include <queue>
#include <iostream>
using namespace std;
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Global\Global.h"
#include "Game.h"
#include "SpaceShip.h"
#include "time.h"
#include "Timers.h"
#include "ConfigFileConverter.h"
#include "resource.h"

#pragma comment(linker,"/SUBSYSTEM:windows")

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

int main( int argc, char * arg[] )
{
    // At the beginning of our app we need this
    int tmpFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
        tmpFlag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag( tmpFlag );

    srand(time_t(0));
	LARGE_INTEGER start  = { 0 }, end  = { 0 }, freq  = { 0 }, second = { 0 };
	SDL_Event event = {0};
	int timeOfEvent = 0;
 
	//Game GameEngine;
	Timer fps;

	std::queue<float> DeltaHistory;
	QueryPerformanceFrequency(&freq);


	_putenv("SDL_VIDEO_WINDOW_POS=center");
	_putenv("SDL_VIDEO_CENTERED=1");
	//ShellExecute(NULL, "open", "C:\\Users\\risk\\Documents\\GitHub\\S-TYPE\\0000-0200.exe","", "", SW_SHOW );
	//Sleep(10000);
	//ShellExecute(NULL, "open", "C:\\Users\\risk\\Documents\\GitHub\\S-TYPE\\0001-0130.exe","", "", SW_SHOW );
	//Sleep(8000);

	//initialize all SDL subystems 

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		cout << "SDL INIT FAILED..." << endl;
		SDL_Quit();
	}
	else
	{
		cout << "SDL_INIT_EVERYTHING..." << endl;
		timeOfEvent = SDL_GetTicks();
	}
	SDL_WM_SetCaption("S-TYPE DEBUG", "src/res/app.ico");
	SDL_Surface* icon = SDL_LoadBMP("src/res/small.bmp");
	SDL_SetColorKey(icon, SDL_SRCCOLORKEY, SDL_MapRGB(icon->format, 255, 255, 255));
	SDL_WM_SetIcon(icon, 0);


	//SDL_WM_SetIcon(SDL_LoadBMP("src/res/small.bmp"), NULL);

    cout << Engine.GamePad->CountDevices() << endl;
    Engine.GamePad->init();
	
	while( Engine.Quit == false )
	{
		second.QuadPart += ((end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart);
		gamestate.DeltaTime = ((end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart);
		if( second.QuadPart >= 2000000 )
		{	
			second.QuadPart = 0;
		}

		QueryPerformanceCounter(&start);

		while( SDL_PollEvent( &event ) )
        {
            Engine.HandleEvents( event );
        }

        Engine.GamePad->Update();
		Engine.Update( event, gamestate.DeltaTime );
		Gfx.FLIP();

		QueryPerformanceCounter(&end);
	}

	Engine.Cleanup();
	gamestate.Cleanup();
	return 0;
}