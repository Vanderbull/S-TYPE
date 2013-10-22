#pragma once
#include "characters.h"
#include "Game.h"
#include "Objects.h"
#include "Enemies.h"
#include "ControlGfx.h"
#include "Bullets.h"
#include "Animals.h"
// holds all the info on the collisions
class ControlCollision
{
public:

	void ListByReference( std::list< Bullet > &BulletList, std::list< Animal > &AnimalList )
	{
		bool collision = false;
		std::list< Bullet >::iterator BulletCounter;
		BulletCounter = BulletList.begin();
		std::list< Animal >::iterator AnimalCounter;
		AnimalCounter = AnimalList.begin();

		for(std::list< Bullet >::iterator Iter = BulletList.begin(); Iter != BulletList.end(); Iter++ ) 
		{
			for(std::list< Animal >::iterator innerIter = AnimalList.begin(); innerIter != AnimalList.end(); innerIter++ ) 
			{
				if( BulletCounter->CollisionBox.x >= AnimalCounter->CollisionBox.x )
				{
					collision = true;
				}
			}
		}
	};

	int Box( std::list< Bullet* > My_Bullets, std::list< Animal* > iEnemy );
	// Old collision controlls
	bool CollisionBox( BaseCharacter *cPlayer, CEnemy *cEnemy, bool Show );

	bool CheckCollision( CEnemy *cEnemy, int WhichCollisionToUse, BaseCharacter *cPlayer );

};

extern ControlCollision CollisionController;
