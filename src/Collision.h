#pragma once
#include "characters.h"
#include "Game.h"
#include "Objects.h"
#include "Enemies.h"
#include "ControlGfx.h"
#include "Bullets.h"
#include "Animals.h"
#include "Enemies\Cubes.h"
#include "Triangles.h"


class ControlCollision
{
public:

	void ObjectCollider( std::vector<Bullet> &VBullets, std::vector<Animal> &VAnimals )
	{
		std::cout << "Object Collider Animals" << endl;
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
	void ObjectCollider( std::vector<Bullet> &VBullets, std::vector<Cube> &VCubes )
	{
		std::cout << "Object Collider Cubes" << endl;
		for(vector< Bullet >::iterator iBullet = VBullets.begin(); iBullet != VBullets.end(); )
		{
			for(vector< Cube >::iterator iCube = VCubes.begin(); iCube != VCubes.end(); )
			{
				if( !( 
					iBullet->LocAndSize.x > iCube->xPos + iCube->Width || 
					iBullet->LocAndSize.x + iBullet->LocAndSize.w < iCube->xPos || 
					iBullet->LocAndSize.y > iCube->yPos + iCube->Height || 
					iBullet->LocAndSize.y + iBullet->LocAndSize.h < iCube->yPos
					) )
				{
					iCube = VCubes.erase(iCube);
					iBullet->DeActivate();
				}
				else
				{
					++iCube;
				}
			}
			if( !iBullet->isActive() )
				iBullet = VBullets.erase(iBullet);
			else
				++iBullet;
		}
	};
	void ObjectCollider( std::vector<Bullet> &VBullets, std::vector<Triangle> &VTriangles )
	{
		std::cout << "Object Collider Triangles" << endl;
		for(vector< Bullet >::iterator iBullet = VBullets.begin(); iBullet != VBullets.end(); )
		{
			for(vector< Triangle >::iterator iTriangle = VTriangles.begin(); iTriangle != VTriangles.end(); )
			{
				if( !( 
					iBullet->LocAndSize.x > iTriangle->xPos + iTriangle->Width || 
					iBullet->LocAndSize.x + iBullet->LocAndSize.w < iTriangle->xPos || 
					iBullet->LocAndSize.y > iTriangle->yPos + iTriangle->Height || 
					iBullet->LocAndSize.y + iBullet->LocAndSize.h < iTriangle->yPos
					) )
				{
					iTriangle = VTriangles.erase(iTriangle);
					iBullet->DeActivate();
				}
				else
				{
					++iTriangle;
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
		if(VAnimals.empty() || VAnimals.size() < 1)
		{
			std::cout << "NO animals in the zoo" << endl;
			return;
		}
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
					std::cout << "Just died Animal" << endl;
				}
				else
				{
					++iAnimal;
				}
			}
			std::cout << "Exitting SPaceshipCollider" << endl;
	};
	void SpaceshipCollider( BaseCharacter Spaceship, std::vector<Cube> &VCubes )
	{
			for(vector< Cube >::iterator iCube = VCubes.begin(); iCube != VCubes.end(); )
			{
				if( !( 
					Spaceship.GetPosition().x > iCube->xPos + iCube->Width || 
					Spaceship.GetPosition().x + Spaceship.GetPosition().w < iCube->xPos || 
					Spaceship.GetPosition().y > iCube->yPos + iCube->Height || 
					Spaceship.GetPosition().y + Spaceship.GetPosition().h < iCube->yPos
					) )
				{
					iCube = VCubes.erase(iCube);
					Spaceship.Died();
					std::cout << "Just died CUBES" << endl;
				}
				else
				{
					++iCube;
				}
			}
			std::cout << "Exitting SPaceshipCollider" << endl;
	};
	void SpaceshipCollider( BaseCharacter Spaceship, std::vector<Triangle> &VTriangles )
	{
			for(vector< Triangle >::iterator iTriangle = VTriangles.begin(); iTriangle != VTriangles.end(); )
			{
				if( !( 
					Spaceship.GetPosition().x > iTriangle->xPos + iTriangle->Width || 
					Spaceship.GetPosition().x + Spaceship.GetPosition().w < iTriangle->xPos || 
					Spaceship.GetPosition().y > iTriangle->yPos + iTriangle->Height || 
					Spaceship.GetPosition().y + Spaceship.GetPosition().h < iTriangle->yPos
					) )
				{
					iTriangle = VTriangles.erase(iTriangle);
					Spaceship.Died();
					std::cout << "Just died triangles" << endl;
				}
				else
				{
					++iTriangle;
				}
			}
			std::cout << "Exitting SPaceshipCollider" << endl;
	};
	// Old collision controlls
	bool CollisionBox( BaseCharacter *cPlayer, CEnemy *cEnemy, bool Show );

	bool CheckCollision( CEnemy *cEnemy, int WhichCollisionToUse, BaseCharacter *cPlayer );

};

extern ControlCollision CollisionController;
