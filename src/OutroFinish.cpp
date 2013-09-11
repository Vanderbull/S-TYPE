#include "OutroFinish.h"
#include "Game.h"

Outro::Outro()
{
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