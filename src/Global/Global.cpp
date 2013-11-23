#include "Global.h"
// declaration of g_nValue 
int g_nValue = 5;
int DIFFICULTY = 0;
int SOUND = 3;
int MUSIC = 5;
string HIGHSCORE = "";
SDL_Rect ScreenSize = {0,0,800,600};
SDL_Rect ButtonClips[ 10 ];
#define _DEBUG 0

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