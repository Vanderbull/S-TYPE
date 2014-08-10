#pragma once
#include <SDL.h>
#include <SDL_events.h>


//Name
//SDL_NumJoysticks -- Count available joysticks.
//Synopsis
//Description
//Counts the number of joysticks attached to the system.
//Return Value
//Returns the number of attached joysticks
class GameController
{
public:

    //Initializing variables
    GameController();
    //Cleanup the game controller
    ~GameController();

    void init(void);
    
    //Handles input
    void HandleInput(SDL_Event _event);
    void Act();
    int CountDevices();
    void Open(int index);
    void Update();

private:
    SDL_Event Events;

};