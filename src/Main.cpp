#include <cmath>
#include <queue>
#include <iostream>
using namespace std;
//#include <vld.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Game.h"
#include "characters.h"
#include "time.h"
#include "Timers.h"
#include "ConfigFileConverter.h"
#include "resource.h"
const int FRAMES_PER_SECOND = 20;

#define MAXSAMPLES 100
int tickindex=0;
int ticksum=0;
int ticklist[MAXSAMPLES];

/* need to zero out the ticklist array before starting */
/* average will ramp up until the buffer is full */
/* returns average ticks per frame over the MAXSAMPPLES last frames */

double CalcAverageTick(int newtick)
{
    ticksum-=ticklist[tickindex];  /* subtract value falling off */
    ticksum+=newtick;              /* add new value */
    ticklist[tickindex]=newtick;   /* save new value so it can be subtracted later */
    if(++tickindex==MAXSAMPLES)    /* inc buffer index */
        tickindex=0;

    /* return average */
    return((double)ticksum/MAXSAMPLES);
}

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


	putenv("SDL_VIDEO_WINDOW_POS=center");
	putenv("SDL_VIDEO_CENTERED=1");
	//ShellExecute(NULL, "open", "C:\\Users\\risk\\Documents\\GitHub\\LegendOfNimbus\\0000-0200.exe","", "", SW_SHOW );
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
	SDL_WM_SetCaption("", "src/res/big.ico");
	SDL_WM_SetIcon(SDL_LoadBMP("src/res/small.bmp"), NULL);
	
 	//gamestate.font = TTF_OpenFont("cour.ttf", 14);
  //  if (gamestate.font == NULL){
  //    printf("Unable to load font: %s %s \n", "HERE FUCKER!", TTF_GetError());
  //    // Handle the error here.
  //  }


	while( GameEngine.Quit == false )
	{
		second.QuadPart += ((end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart);
		gamestate.DeltaTime = ((end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart);
		if( second.QuadPart >= 2000000 )
		{	
			//cout << "The resolution of this timer is: " << freq.QuadPart << " Hz." << endl;
			//cout << "Time to calculate run one gameloop: " << (end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart << " microSeconds" << endl;
			second.QuadPart = 0;
		}

		QueryPerformanceCounter(&start);

		//DeltaTime = CurTick - PrevTick;
		//PrevTick = CurTick;
		//CurTick = clock();
		//TotalTicks += DeltaTime;
		//DeltaHistory.push(DeltaTime);
		//cout << PrevTick << "->" << CurTick << endl;
		//cout << "Framerate:" << CLOCKS_PER_SEC / (TotalTicks / DeltaHistory.size() ) << endl;

		//if( DeltaHistory.size() > 10 )
		//{
		//	OldestTickDelta = DeltaHistory.front();
		//	DeltaHistory.pop();
		//	TotalTicks -= OldestTickDelta;
		//}
		

		// Delta = CurrentTick - PreviusTick
		// Delta / CLOCKS_PER_SEC for delta per second
		//t = clock();		
		
		SDL_PollEvent( &event );

		//while( SDL_PollEvent( &event ) )
		//{
			GameEngine.HandleEvents( event );
		//}		
		
		GameEngine.Update( event, gamestate.DeltaTime );
		Gfx.FLIP();

		//gamestate.AddTick()	;
		//t = clock() - t;
		//gamestate.DeltaTime = (float)t/CLOCKS_PER_SEC;
		//clock_ticks += t;
		//if( clock_ticks > CLOCKS_PER_SEC )
		//{
		//	printf ("FPS: %d .\n",framecount);
		//	clock_ticks = 0;
		//	framecount = 0;
		//}
		//else
		//{
		//	framecount++;
		//}
		//printf ("average ticks per frame: %f .\n",CalcAverageTick((int)t));


		//t = clock() - t;
		//printf ("It took me %d ticks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
		QueryPerformanceCounter(&end);
	}

	GameEngine.Cleanup();
	gamestate.EndAll();

	return 0;
}