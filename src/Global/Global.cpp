#include "Global.h"

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

flog logger;
// Paths for files
   const std::string path_assets = "assets/cfg/";

//Screen resolution
SDL_Rect ScreenSize = { 0, 0, 1920, 1080 };

// declaration of g_nValue 
int g_nValue = 5;
int DIFFICULTY = 0;
int SOUND = 3;
int MUSIC = 5;
int CURRENT_HIGHSCORE = 0;
string HIGHSCORE = "";

SDL_Rect ButtonClips[ 10 ];
int _SCORE = 0;
int FIRED = 0;
float SpaceScrollingSpeed = 0.0001f;
int LevelSize = 300000;
int LevelProgress = 0;
Sint16 SpriteWidth = 64;
Uint16 SpriteHeight = 64;
std::vector< int > PopupScore;

float MAX_VELOCITY = 5.0f;
float MIN_VELOCITY = -5.0f;
float NO_VELOCITY = 0.0f;

int PowerLevel = 100;
int PowerLevelSecond = 5;
int LaserRecharge = 1;

void SetGameOptionButtons()
{
    // easy option
    ButtonClips[ 0 ].h = 33;
    ButtonClips[ 0 ].w = 101;
    ButtonClips[ 0 ].x = 284;
    ButtonClips[ 0 ].y = 128;

    //medium option
    ButtonClips[ 1 ].h = 33;
    ButtonClips[ 1 ].w = 101;
    ButtonClips[ 1 ].x = 414;
    ButtonClips[ 1 ].y = 128;

    //hard option
    ButtonClips[ 2 ].h = 33;
    ButtonClips[ 2 ].w = 101;
    ButtonClips[ 2 ].x = 554;
    ButtonClips[ 2 ].y = 128;

    // sound on
    ButtonClips[ 3 ].h = 33;
    ButtonClips[ 3 ].w = 101;
    ButtonClips[ 3 ].x = 284;
    ButtonClips[ 3 ].y = 168;

    // sound off
    ButtonClips[ 4 ].h = 33;
    ButtonClips[ 4 ].w = 101;
    ButtonClips[ 4 ].x = 414;
    ButtonClips[ 4 ].y = 168;

    // music on
    ButtonClips[ 5 ].h = 33;
    ButtonClips[ 5 ].w = 101;
    ButtonClips[ 5 ].x = 284;
    ButtonClips[ 5 ].y = 218;

    // music off
    ButtonClips[ 6 ].h = 33;
    ButtonClips[ 6 ].w = 101;
    ButtonClips[ 6 ].x = 414;
    ButtonClips[ 6 ].y = 218;

    // back to main menu
    ButtonClips[ 7 ].h = 33;
    ButtonClips[ 7 ].w = 101;
    ButtonClips[ 7 ].x = 632;
    ButtonClips[ 7 ].y = 534;
}

//return by reference
void objRectangle(SDL_Rect &Rect, int XPos, int YPos, int Width, int Height)
{
	Rect.h = Height;
	Rect.w = Width;
	Rect.x = XPos;
	Rect.y = YPos;
};

int MouseInBox(SDL_Rect &Rect)
{
	std::cout << "Hey there is a mouse in this box!" << endl;
	return 0;
}

// Helper functions

int tickindex=0;
int ticksum=0;
int ticklist[MAXSAMPLES];

/* need to zero out the ticklist array before starting */
/* average will ramp up until the buffer is full */
/* returns average ticks per frame over the MAXSAMPPLES last frames */

double CalcAverageTick(int newtick)
{
    ticksum-=ticklist[tickindex];  /* subtract value falling off */
    ticksum+=newtick;              /* add new value */
    ticklist[tickindex]=newtick;   /* save new value so it can be subtracted later */
    if(++tickindex==MAXSAMPLES)    /* inc buffer index */
        tickindex=0;

    /* return average */
    return((double)ticksum/MAXSAMPLES);
}

//SDL_Joystick *GamePad;
OctoBoss OctoBossman;
