#include "OutroFinish.h"
#include "Game.h"

// @date 2012-08-07

Outro::Outro()
{
	surface = gamestate.m_srfReaper;

	Height = 600;
	Width = 300;
	
	xPos = 0;
	yPos = 0;
	for( int i = 0; i < 2; i++ )
	{
		ClipsOutro[ i ].x = xPos;
		ClipsOutro[ i ].y = yPos;
		ClipsOutro[ i ].w = Width;
		ClipsOutro[ i ].h = Height;
	}
}