#pragma once
#include <list>
#include <vector>
#include <stack>
#include <SDL.h>
#include "Objects/Objects.h"
#include "Enemies\Robotnic.h"

#define BULLET_MAX_FRAMES 15

/// <summary>Used to create a Bullet entity</summary>
class Bullet : public Object
{

public:
	Bullet();
	
	SDL_Rect UpdateCollisionBox(SDL_Rect Box);
	void Update();
    // Octobullet Update
    void OctoUpdate();
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

class ControlBullets
{
public:
	ControlBullets();
	~ControlBullets();
	void Draw_Bullets();
	void Create_Bullets();
    // OctoBullet creators
    void CreateOctoBullets();
    void DrawOctoBullets();
    void LoadBullet(Sint16 xPos, Sint16 yPos, Sint16 iSurfaceID);
	std::vector< Bullet > GetVBulletsByReference(){ return BulletArrayRef; };

    Bullet CreateBulletByReference(Sint16 xPos, Sint16 yPos, Sint16 surface);

	std::vector< Bullet > BulletArrayRef;	
private:

};

extern ControlBullets BulletController;
extern ControlBullets OctoBulletController;