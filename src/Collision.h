#pragma once
#include "characters.h"
#include "Game.h"
#include "Objects.h"
#include "Enemies.h"
#include "ControlGfx.h"

// holds all the info on the collisions
class ControlCollision
{
public:

	int Box( BaseCharacter *Spaceship, CEnemy *Enemy );
	// Old collision controlls
	bool CollisionCircle( BaseCharacter *Mydemon, PowerUp *TransForm, bool Show );
	bool CollisionCircle( BaseCharacter *Mydemon, CEnemy *MyEnemy, bool Show );
	bool CollisionCircle( BaseCharacter *Mydemon, Boss *Myboss, bool Show );
	bool CollisionCircle( BaseCharacter *Mydemon, Heads *EnemyHead, bool Show );

	bool CollisionCircle( Fireball *MyFire, CEnemy *MyEnemy, bool Show );
	bool CollisionCircle( Fireball *MyFire, Heads *EnemyHead, bool Show );
	bool CollisionCircle( Fireball *MyFire, Boss *My_boss, bool Show );
	

	bool CollisionBox( BaseCharacter *Mydemon, CEnemy *MyEnemy, bool Show );
	bool CollisionPixel( BaseCharacter *Mydemon, CEnemy *MyEnemy );

	bool CheckCollisionWithdemon( CEnemy *MyEnemy, int WhichCollisionToUse, BaseCharacter *Mydemon );
	bool CheckCollisionWithdemon( PowerUp *TransForm, int WhichCollisionToUse );

	void Circle( long centerx, long centery, long radius );
	void SetPixelMine( int xPos, int yPos );
};

extern ControlCollision CollisionController;
