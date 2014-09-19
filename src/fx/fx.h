#pragma once
#include <list>
#include <vector>
#include <stack>
#include <SDL.h>
#include "../Objects.h"

#define FX_MAX_FRAMES 15

class FX : public Object
{

public:
	FX();
	
	SDL_Rect UpdateCollisionBox(SDL_Rect Box);
	void Update();
	void Draw();
	int GetSurfaceID();
	void onCollision(){ DeActivate(); };
	bool isActive(){ return Active; };
	void DeActivate(){ Active = false; };
	void Activate(){ Active = true; };
	void onDestruction(){ DeActivate(); };
	
	SDL_Rect GetLocAndSize();
	void SetCollisionBox(Sint16 x, Sint16 y, Sint16 h, Sint16 w)
	{
		CollisionBox.x = x;
		CollisionBox.y = y;
		CollisionBox.h = h;
		CollisionBox.w = w;
	}
	SDL_Rect GetCollisionBox(){ return CollisionBox; };
	void Spawn() {};

private:
	SDL_Rect Clips[ 16 ];
	int PrevFrame;
};

/// <summary>A class the controls the animals</summary> 
class ControlFX
{
public:
	ControlFX();
	~ControlFX();
	void DrawFX();
	void CreateFX();

	void LoadFX( int xPos, int yPos, int iSurfaceID );
	std::vector< FX > GetVFXByReference(){ return FXArrayRef; };

	FX CreateFXByReference( int xPos, int yPos, int surface );

	std::vector< FX > FXArrayRef;	
private:

};

extern ControlFX FXController;