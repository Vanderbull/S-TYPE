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
		for(vector< Bullet >::iterator iBullet = VBullets.begin(); iBullet != VBullets.end(); )
		{
			for(vector< Animal >::iterator iAnimal = VAnimals.begin(); iAnimal != VAnimals.end(); )
			{
				if( !( 
					iBullet->LocAndSize.x > iAnimal->LocAndSize.x + iAnimal->LocAndSize.w || 
					iBullet->LocAndSize.x + iBullet->LocAndSize.w < iAnimal->LocAndSize.x || 
					iBullet->LocAndSize.y > iAnimal->LocAndSize.y + iAnimal->LocAndSize.h || 
					iBullet->LocAndSize.y + iBullet->LocAndSize.h < iAnimal->LocAndSize.y
					) )
				{
					iAnimal = VAnimals.erase(iAnimal);
					iBullet->DeActivate();
				}
				else
				{
					++iAnimal;
				}
			}
			if( !iBullet->isActive() )
				iBullet = VBullets.erase(iBullet);
			else
				++iBullet;
		}
	};
	void SpaceshipCollider( BaseCharacter Spaceship, std::vector<Animal> &VAnimals )
	{
			for(vector< Animal >::iterator iAnimal = VAnimals.begin(); iAnimal != VAnimals.end(); )
			{
				if( !( 
					Spaceship.GetPosition().x > iAnimal->LocAndSize.x + iAnimal->LocAndSize.w || 
					Spaceship.GetPosition().x + Spaceship.GetPosition().w < iAnimal->LocAndSize.x || 
					Spaceship.GetPosition().y > iAnimal->LocAndSize.y + iAnimal->LocAndSize.h || 
					Spaceship.GetPosition().y + Spaceship.GetPosition().h < iAnimal->LocAndSize.y
					) )
				{
					iAnimal = VAnimals.erase(iAnimal);
					Spaceship.Died();
				}
				else
				{
					++iAnimal;
				}
			}
	};
	// Old collision controlls
	bool CollisionBox( BaseCharacter *cPlayer, CEnemy *cEnemy, bool Show );

	bool CheckCollision( CEnemy *cEnemy, int WhichCollisionToUse, BaseCharacter *cPlayer );

};

extern ControlCollision CollisionController;
