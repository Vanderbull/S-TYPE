#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Paralaxlayers.h"

const int MAX_SURFACES = 128;

class ControlGfx
{
public:
	ControlGfx();
	int Load_imageAlpha( std::string filename, int r, int g, int b );
	void stretchPicToBackBuffer( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect );
	void blit( int index, int xpos, int ypos, bool transparent );
	int findAvailableIndex();
	SDL_Surface* GetSurface(int index);
	void PasteScreenToAnother( SDL_Rect srcRect, SDL_Rect destRect );
	void FLIP();
	void stretchBlit( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect );
	void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
	SDL_Color WhiteRGB,BlackRGB;

private:
	SDL_Surface * m_surfaceList[ MAX_SURFACES ];
};

extern ControlGfx Gfx;