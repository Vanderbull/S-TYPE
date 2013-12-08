#include "OutroFinish.h"
#include "Game.h"

// 1. this should go into every .cpp , after all header inclusions
#ifdef _WIN32
#ifdef _DEBUG
   #include <crtdbg.h>
   #undef THIS_FILE
   static char THIS_FILE[] = __FILE__;
   #define new       new( _NORMAL_BLOCK, __FILE__, __LINE__)
   #define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif

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