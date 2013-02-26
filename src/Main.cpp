#include <SDL.h>
#include "Game.h"
#include "characters.h"
#include <cmath>
#include "time.h"
#include "Timers.h"
#include "ConfigFileConverter.h"

// @date 2012-08-07

const int FRAMES_PER_SECOND = 20;
using namespace std;


bool Quit = false;

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
	SDL_Event event = {0};
	ConfigFile cfg("config.cfg");

	bool exists = false;
		
	exists = cfg.keyExists("width");
	std::cout << "width key: " << std::boolalpha << exists << endl;
	
	exists = cfg.keyExists("height");
	std::cout << "height key: " << exists << endl;

	//std::string someValue = cfg.getValueOfKey<std::string>("mykey", "Unknown");
	//std::cout << "value of key mykey: " << someValue << "\n";
	int widthValue = cfg.getValueOfKey<int>("width");
	std::cout << "value of width key: " << widthValue << "\n";
	int heightValue = cfg.getValueOfKey<int>("height");
	std::cout << "value of key height: " << heightValue << "\n\n";

	std::cin.get();

	srand( time( 0 ) );
	DWORD	PrevTick = 0, CurTick = 0;
	UINT32 PreviousTick = 0, CurrentTick = 0,DeltaTime = 0;
	UINT32 MILLISECONDS = 1000;
	UINT32 UpdayeStepping = 20; 
	Game New_Game;

	PrevTick = SDL_GetTicks();

	Timer fps;

	int framecount = 0;
	int clock_ticks = 0;
	
	while( !Quit )
	{		
		 clock_t t;
		 t = clock();
 		//fps.start();

		if( gamestate.GameOK == false )
		{
			Quit = true;
		}		
		
		while( SDL_PollEvent( &event ) )
		{
			New_Game.Handle_events( event );
			if( event.type == SDL_QUIT  )
			{
				Quit = true;
			}
		}		
		
		New_Game.upDate( event );
		//CurTick = SDL_GetTicks();
		//gamestate.dt = float(CurTick - PrevTick);
		//PrevTick = CurTick;

	    //Cap the frame rate
		/*
        while( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            //wait    
        } */
				
		gamestate.AddTick()	;
		//Sleep(100);
		t = clock() - t;
		gamestate.dt = (float)t/CLOCKS_PER_SEC;
		clock_ticks += t;
		if( clock_ticks > CLOCKS_PER_SEC )
		{
			printf ("FPS: %d .\n",framecount);
			clock_ticks = 0;
			framecount = 0;
		}
		else
		{
			framecount++;
		}
		//printf ("average ticks per frame: %f .\n",CalcAverageTick((int)t));


		//t = clock() - t;
		//printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
	}

	New_Game.cleanUp();
	gamestate.EndAll();

	return 0;
}