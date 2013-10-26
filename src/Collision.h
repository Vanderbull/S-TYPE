#pragma once
#include "characters.h"
#include "Game.h"
#include "Objects.h"
#include "Enemies.h"
#include "ControlGfx.h"
#include "Bullets.h"
#include "Animals.h"


class ControlCollision
{
public:

	void ObjectCollider( std::vector<Bullet> &VBullets, std::vector<Animal> &VAnimals )
	{
		for(vector< Bullet >::iterator ite = VBullets.begin(); ite != VBullets.end(); )
		{
			for(vector< Animal >::iterator ute = VAnimals.begin(); ute != VAnimals.end(); )
			{
				if( ite->LocAndSize.x > ute->LocAndSize.x && ite->LocAndSize.x < ute->LocAndSize.x + 64 && ite->LocAndSize.y > ute->LocAndSize.y && ite->LocAndSize.y < ute->LocAndSize.y + 64)
				{
						ute = VAnimals.erase(ute);
						ite->DeActivate();
				}
				else
				{
					++ute;
				}
			}
			if( !ite->isActive() )
				ite = VBullets.erase(ite);
			else
				++ite;
		}
	};

	// Old collision controlls
	bool CollisionBox( BaseCharacter *cPlayer, CEnemy *cEnemy, bool Show );

	bool CheckCollision( CEnemy *cEnemy, int WhichCollisionToUse, BaseCharacter *cPlayer );

};

extern ControlCollision CollisionController;
