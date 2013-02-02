#pragma once
#include "characters.h"
#include "Game.h"
#include "Objects.h"
#include "Enemies.h"

// @date 2012-08-07

// holds all the info on the collisions
class ControlCollision
{
public:
	bool CollisionCircle( Demon *MyDemon, PowerUp *TransForm, bool Show );
	bool CollisionCircle( Demon *MyDemon, CEnemy *MyEnemy, bool Show );
	bool CollisionCircle( Demon *MyDemon, Boss *Myboss, bool Show );
	bool CollisionCircle( Demon *MyDemon, Heads *EnemyHead, bool Show );

	bool CollisionCircle( FireBall *MyFire, CEnemy *MyEnemy, bool Show );
	bool CollisionCircle( FireBall *MyFire, Heads *EnemyHead, bool Show );
	bool CollisionCircle( FireBall *MyFire, Boss *My_boss, bool Show );
	

	bool CollisionBox( Demon *MyDemon, CEnemy *MyEnemy, bool Show );
	bool CollisionPixel( Demon *MyDemon, CEnemy *MyEnemy );

	bool CheckCollisionWithPlayer( CEnemy *MyEnemy, int WhichCollisionToUse );
	bool CheckCollisionWithPlayer( PowerUp *TransForm, int WhichCollisionToUse );

	void Circle( long centerx, long centery, long radius );
	void SetPixelMine( int xPos, int yPos );
};

extern ControlCollision CollisionController;
