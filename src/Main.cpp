#include <cmath>
#include <queue>
#include <iostream>
using namespace std;
//#include <vld.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Global\Global.h"
#include "Game.h"
#include "characters.h"
#include "time.h"
#include "Timers.h"
#include "ConfigFileConverter.h"
#include "resource.h"

int main( int argc, char * arg[] )
{
	srand( time( 0 ) );
	LARGE_INTEGER start  = { 0 }, end  = { 0 }, freq  = { 0 }, second = { 0 };
	SDL_Event event = {0};
	int timeOfEvent = 0;
	float PrevTick = 0, CurTick = 0, TotalTicks = 0, TickDelta = 0, OldestTickDelta = 0,DeltaTime = 0;
	UINT32 PreviousTick = 0, CurrentTick = 0;
	UINT32 MILLISECONDS = 1000;
	UINT32 UpdateStepping = 20; 
	Game GameEngine;
	Timer fps;
	int framecount = 0;
	int clock_ticks = 0;
	std::queue<float> DeltaHistory;
  
	QueryPerformanceFrequency(&freq);


	_putenv("SDL_VIDEO_WINDOW_POS=center");
	_putenv("SDL_VIDEO_CENTERED=1");
	ShellExecute(NULL, "open", "C:\\Users\\risk\\Documents\\GitHub\\LegendOfNimbus\\0000-0200.exe","", "", SW_SHOW );
	//Sleep(8000);

	//initialize all SDL subystems 

	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVERYTHING ) == -1)
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
	
	while( GameEngine.Quit == false )
	{
		second.QuadPart += ((end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart);
		gamestate.DeltaTime = ((end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart);
		if( second.QuadPart >= 2000000 )
		{	
			second.QuadPart = 0;
		}

		QueryPerformanceCounter(&start);

		SDL_PollEvent( &event );

		//while( SDL_PollEvent( &event ) )
		//{
			GameEngine.HandleEvents( event );
		//}		
		
		GameEngine.Update( event, gamestate.DeltaTime );
		Gfx.FLIP();

		QueryPerformanceCounter(&end);
	}

	GameEngine.Cleanup();
	gamestate.Cleanup();

	return 0;
}