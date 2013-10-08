#ifndef GLOBAL_H // header guards 
#define GLOBAL_H   // extern tells the compiler this variable is declared elsewhere 
#include <iostream>
#include <windows.h>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;
extern int g_nValue;
extern SDL_Rect ScreenSize;
#define MAXSAMPLES 100
const int FRAMES_PER_SECOND = 20;

void objRectangle(SDL_Rect &Rect, int XPos, int YPos, int Width, int Height);
int MouseInBox(SDL_Rect &Rect);
//Use like this:
//SDL_Rect myRect;
//Rectangle(myRect, 5, 5, 50, 20);

// Used in Game.h file
typedef enum
{
	GAME_RESUME_STATE,
	GAME_NEW_STATE,
	GAME_LOAD_STATE,
	GAME_SAVE_STATE,
	GAME_QUIT_STATE,
	GAME_CREDITS_STATE,
	GAME_OPTIONS_STATE,
	MENU_MAIN_STATE,
	MENU_SUB_STATE,
	GAME_RUNNING_STATE,
	GAME_INTRO_STATE,
	GAME_OUTRO_STATE,
	GAME_PAUSED_STATE,
	GAME_STORY_STATE,
	GAME_LOADING_STATE,
	GAME_SAVING_STATE,
	GAME_BOSS_STATE,
	GAME_PLAYER_DIED_STATE
} InGameStates;

enum{ BOSS_IDLE, BOSS_ATTACK, BOSS_DIE };
enum{ HEAD_GO, HEAD_DOWN, HEAD_CRASH };
enum{ BUTTON_NEW_GAME, BUTTON_OPTIONS, BUTTON_QUIT };
enum{ MAIN_MENU, OPTIONS_MENU, CREDITS_MENU };

const int MAX_SURFACE = 128;
const int ANIMPACE = 150;
const int ANIMPACESLOWER = 300;
const int ANIMPACEENEMY = 50;
const int ANIMPACEBOSSHEAD = 5;

const int demonHEIGHT = 100;
const int demonWIDTH = 130;
const int demonWIDTHREAL = 25;
const int demonHEIGHTREAL = 25;

const int GROUND_Y = 500;
const int GROUND_X = 400;
const int STARTSCROLLING = 400;
const int BOSS_ATTACK_START = 150;


#endif