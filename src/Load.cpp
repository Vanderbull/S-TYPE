#include "Global\Global.h"
#include "Load.h" 
#include <SDL.h>

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

enum BName {
	RESUME_GAME,
	NEW_GAME,
	LOAD_GAME,
	SAVE_GAME,
	OPTIONS,
	UNKNOWN,
	CREDITS,
	QUIT_GAME
};

Load::Load( int ButtonX, int Surface, int SurfaceButtons )							
{
	std::cout << "Load rendering like a god!!!!!" << endl;
	surface = Surface;

	SurfaceButt = SurfaceButtons;

	int ArraySize = sizeof(ButtonClips) / sizeof(ButtonClips[0]);
	for( int i = 0; i < ArraySize; i++ )
	{
		ButtonClips[ i ].x = 0;
		ButtonClips[ i ].y = 0;
		ButtonClips[ i ].w = 0;
		ButtonClips[ i ].h = 0;
	}

	ArraySize = sizeof(DestClips) / sizeof(DestClips[0]);
	for( int i = 0; i < ArraySize; i++ )
	{
		DestClips[ i ].x = 0;
		DestClips[ i ].y = 0;
		DestClips[ i ].w = 0;
		DestClips[ i ].h = 0;
	}

	ButtonOptions = false;
	ButtonBack = false; 
	ButtonSound = false;
	ButtonCredits = false;
	ButtonHighScore = false;
	ButtonNewgame = false;

	objRectangle(ButtonClips[ BName::RESUME_GAME ], 401, 130, 350, 45 );
	objRectangle(ButtonClips[ BName::NEW_GAME ], 401, 186, 350, 45 );
	objRectangle(ButtonClips[ BName::LOAD_GAME ], 401, 242, 350, 45 );
	objRectangle(ButtonClips[ BName::SAVE_GAME ], 401, 298, 350, 45 );
	objRectangle(ButtonClips[ BName::OPTIONS ], 401, 355, 350, 45 );
	objRectangle(ButtonClips[ BName::UNKNOWN ], 401, 410, 350, 45 );
	objRectangle(ButtonClips[ BName::CREDITS ], 401, 465, 350, 45 );
	objRectangle(ButtonClips[ BName::QUIT_GAME ], 401, 519, 350, 45 );
	objRectangle(ButtonClips[ BName::UNKNOWN ], 0, 0, 0, 0 );
	objRectangle(ButtonClips[ BName::UNKNOWN ], 0, 0, 0, 0 );

	objRectangle(DestClips[ BName::RESUME_GAME ], 401, 0, 350, 45 );
	objRectangle(DestClips[ BName::NEW_GAME ], 401, 0, 350, 45 );
	objRectangle(DestClips[ BName::LOAD_GAME ], 401, 0, 350, 45 );
	objRectangle(DestClips[ BName::SAVE_GAME ], 401, 0, 0, 0 );
	objRectangle(DestClips[ BName::OPTIONS ], 401, 0, 350, 45 );
	objRectangle(DestClips[ BName::UNKNOWN ], 401, 0, 350, 45 );
	objRectangle(DestClips[ BName::CREDITS ], 401, 0, 350, 45 );
	objRectangle(DestClips[ BName::QUIT_GAME ], 401, 0, 350, 45 );
	objRectangle(DestClips[ BName::UNKNOWN ], 401, 0, 0, 0 );
	objRectangle(DestClips[ BName::UNKNOWN ], 0, 0, 0, 0 );

    SetGameOptionButtons();
}

void Load::SetGameOptionButtons()
{
    // easy option
    ButtonClips[0].h = 33;
    ButtonClips[0].w = 101;
    ButtonClips[0].x = 284;
    ButtonClips[0].y = 128;

    //medium option
    ButtonClips[1].h = 33;
    ButtonClips[1].w = 101;
    ButtonClips[1].x = 414;
    ButtonClips[1].y = 128;

    //hard option
    ButtonClips[2].h = 33;
    ButtonClips[2].w = 101;
    ButtonClips[2].x = 554;
    ButtonClips[2].y = 128;

    // sound on
    ButtonClips[3].h = 33;
    ButtonClips[3].w = 101;
    ButtonClips[3].x = 284;
    ButtonClips[3].y = 168;

    // sound off
    ButtonClips[4].h = 33;
    ButtonClips[4].w = 101;
    ButtonClips[4].x = 414;
    ButtonClips[4].y = 168;

    // music on
    ButtonClips[5].h = 33;
    ButtonClips[5].w = 101;
    ButtonClips[5].x = 284;
    ButtonClips[5].y = 218;

    // music off
    ButtonClips[6].h = 33;
    ButtonClips[6].w = 101;
    ButtonClips[6].x = 414;
    ButtonClips[6].y = 218;

    // back to main menu
    ButtonClips[7].h = 33;
    ButtonClips[7].w = 101;
    ButtonClips[7].x = 632;
    ButtonClips[7].y = 534;
}


								