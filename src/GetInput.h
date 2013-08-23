#pragma once
#include <SDL.h>
#include <SDL_events.h>
#include <string>


//The key press interpreter
class StringInput
{  
    public:
	
    //Initializes variables
    StringInput();
    
    //Does clean up
    ~StringInput();
    
    //Handles input
    bool handle_input( );

    
    //Shows the message on screen
    void show_centered();    

	//The storage string
    std::string str;

    private:

    //The text surface
    SDL_Surface *text;
	SDL_Event StringEvent;
};