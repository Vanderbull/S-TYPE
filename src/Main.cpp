#include <SDL.h>
#include "Game.h"
#include "characters.h"
#include <cmath>
#include "time.h"
#include "Timers.h"
#include "ConfigFileConverter.h"

// @date 2012-08-07

const int FRAMES_PER_SECOND = 30;
using namespace std;


bool Quit = false;


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
	
	while( Quit == false )
	{				
 		fps.start();

		if( gamestate.GameOK == false )
		{
			Quit = true;
		}		
		
		while( SDL_PollEvent( &event ) )
		{
			            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                //Set the proper message surface
                switch( event.key.keysym.sym )
                {
                    case SDLK_UP: cout << "UP UP AND AWAY" << endl; break;
                    case SDLK_DOWN: cout << "UP UP AND AWAY" << endl; break;
                    case SDLK_LEFT: cout << "UP UP AND AWAY" << endl; break;
                    case SDLK_RIGHT: cout << "UP UP AND AWAY" << endl; break;
                }
            }
            
			//If the user has Xed out the window
		else if( event.type == SDL_QUIT  )
			{
				Quit = true;
			}
		}		
		
		
		CurTick = SDL_GetTicks();
		gamestate.dt = float(CurTick - PrevTick);
		PrevTick = CurTick;
		
		New_Game.upDate( event );

	    //Cap the frame rate
        while( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            //wait    
        }
				
		gamestate.AddTick();		
	}

	New_Game.cleanUp();
	gamestate.EndAll();

	return 0;
}