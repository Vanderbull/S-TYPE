#include <cmath>
#include <queue>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>

using namespace std;
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Global\Global.h"
#include "Game.h"
#include "SpaceShip.h"
#include "time.h"
#include "ConfigFileConverter.h"
#include "resource.h"

#ifdef _DEBUG
// THE CODE IS COMPILING IN DEBUG MODE.
#endif
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
    logger.write(__LINE__,__FILE__);
    std::srand(std::time(0)); // use current time as seed for random generator

    int random_variable = std::rand();
    std::cout << "Random value on [0 " << RAND_MAX << "]: "
        << random_variable << '\n';

    // At the beginning of our app we need this
    int tmpFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
        tmpFlag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag( tmpFlag );

	LARGE_INTEGER start  = { 0 }, end  = { 0 }, freq  = { 0 }, second = { 0 };
	SDL_Event event = {0};
	int timeOfEvent = 0;

	QueryPerformanceFrequency(&freq);

	_putenv("SDL_VIDEO_WINDOW_POS=center");
	_putenv("SDL_VIDEO_CENTERED=1");
	//ShellExecute(NULL, "open", "C:\\Users\\risk\\Documents\\GitHub\\S-TYPE\\0000-0200.exe","", "", SW_SHOW );
	//Sleep(10000);
	//ShellExecute(NULL, "open", "C:\\Users\\risk\\Documents\\GitHub\\S-TYPE\\0001-0130.exe","", "", SW_SHOW );
	//Sleep(8000);

	SDL_WM_SetCaption("S-TYPE DEBUG", "src/res/app.ico");

    //cout << Engine.GamePad->CountDevices() << endl;
    //Engine.GamePad->init();
    Engine.GamePad.init();
	
	while( Engine.Quit == false )
	{
        logger.write_score(_SCORE);
		gamestate.DeltaTime = ((end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart);

        logger.write_deltatime(gamestate.DeltaTime);
		
		QueryPerformanceCounter(&start);

		while( SDL_PollEvent( &event ) )
        {
            Engine.HandleEvents( event );
        }


		Engine.Update( event, gamestate.DeltaTime );
        //Engine.GamePad->Update();
        //Engine.GamePad->HandleInput(event);
        Engine.GamePad.Update();
        Engine.GamePad.HandleInput(event);
        Audio.Render();
		Gfx.FLIP();

		QueryPerformanceCounter(&end);
	}

    gamestate.Cleanup();
	Engine.Cleanup();
	return 0;
}