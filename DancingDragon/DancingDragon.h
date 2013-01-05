#include <SDL.h>

class DancingDragon
{
public:
	DancingDragon( int Surface );
	int xPos, yPos;
	int Height, Width;
	int Frame, PrevFrame;
	int surface;
	int StateCounter;
	void SetFrame();
	void SetClips();
	SDL_Rect Clips[ 23 ];
	int AnimationTimestamp;
};