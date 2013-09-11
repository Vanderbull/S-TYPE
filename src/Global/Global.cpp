#include "Global.h"
// declaration of g_nValue 
int g_nValue = 5;

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