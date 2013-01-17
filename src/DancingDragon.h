#include "BaseController.h"
#include <SDL.h>

class DancingDragon : virtual public BaseController,public Renderable
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
	virtual void CreateAnimal(){};
};