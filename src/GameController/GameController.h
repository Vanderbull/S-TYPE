#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
//#include <SDL.h>
//#include <SDL_events.h>


class GameController
{
public:

    //const int JOYSTICK_DEAD_ZONE = 8000;
    //Initializing variables
    GameController();
    //Cleanup the game controller
    ~GameController();

    void init(void);

    //Handles input
    void HandleInput(SDL_Event _event);
    int CountDevices();
    void Open(int index);
    void Update();
    void KeyMapping(SDL_Event _event);
    void RenderText();

private:
    SDL_Event Events;
    std::vector<int> counters;
    SDL_Joystick *joysticks[4];
    SDL_Joystick *GamePad;
    std::map<string, int> ButtonMap;
    std::string ControllerInfo;
    std::vector<string> CtrlData;
    int magnitude;
};
