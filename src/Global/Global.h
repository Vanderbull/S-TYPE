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


void objRectangle(SDL_Rect &Rect, int XPos, int YPos, int Width, int Height);
int MouseInBox(SDL_Rect &Rect);

//Use like this:
//SDL_Rect myRect;
//Rectangle(myRect, 5, 5, 50, 20);
#endif