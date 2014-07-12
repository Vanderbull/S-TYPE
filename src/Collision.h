#pragma once
#include "SpaceShip.h"
#include "Game.h"
#include "Objects.h"
#include "Enemies.h"
#include "ControlGfx.h"
#include "Bullets.h"
#include "Animals.h"
#include "Enemies\Cubes.h"
#include "Triangles.h"
#include "Audio.h"

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
					iBullet->GetCollisionBox().x > iAnimal->LocAndSize.x + iAnimal->LocAndSize.w || 
					iBullet->GetCollisionBox().x + iBullet->GetCollisionBox().w < iAnimal->LocAndSize.x || 
					iBullet->GetCollisionBox().y > iAnimal->LocAndSize.y + iAnimal->LocAndSize.h || 
					iBullet->GetCollisionBox().y + iBullet->GetCollisionBox().h < iAnimal->LocAndSize.y
					) )
				{
					Audio.PlaySoundEffect( 5 );
					iAnimal = VAnimals.erase(iAnimal);
					iBullet->DeActivate();
					PopupScore.push_back(50);
					_SCORE += 100;
					SDL_Surface * SrfProgress;
					SrfProgress = TTF_RenderText_Solid( Gfx.DefaultFont, "POWER UP COOL *YEA GRIIM!!!!!", Gfx.WhiteRGB );
					Gfx.apply_surface( 150, 150, SrfProgress, Gfx.BackBuffer );
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
		for(vector< Bullet >::iterator iBullet = VBullets.begin(); iBullet != VBullets.end(); )
		{
			for(vector< Cube >::iterator iCube = VCubes.begin(); iCube != VCubes.end(); )
			{
				if( !( 
					iBullet->GetCollisionBox().x > iCube->xPos + iCube->Width || 
					iBullet->GetCollisionBox().x + iBullet->GetCollisionBox().w < iCube->xPos || 
					iBullet->GetCollisionBox().y > iCube->yPos + iCube->Height || 
					iBullet->GetCollisionBox().y + iBullet->GetCollisionBox().h < iCube->yPos
					) )
				{
 					Audio.PlaySoundEffect( 5 );
					iCube = VCubes.erase(iCube);
					iBullet->DeActivate();
					PopupScore.push_back(50);
                    _SCORE += 100;
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
		for(vector< Bullet >::iterator iBullet = VBullets.begin(); iBullet != VBullets.end(); )
		{
			for(vector< Triangle >::iterator iTriangle = VTriangles.begin(); iTriangle != VTriangles.end(); )
			{
				if( !( 
					iBullet->GetCollisionBox().x > iTriangle->xPos + iTriangle->Width || 
					iBullet->GetCollisionBox().x + iBullet->GetCollisionBox().w < iTriangle->xPos || 
					iBullet->GetCollisionBox().y > iTriangle->yPos + iTriangle->Height || 
					iBullet->GetCollisionBox().y + iBullet->GetCollisionBox().h < iTriangle->yPos
					) )
				{
					Audio.PlaySoundEffect( 5 );
					iTriangle = VTriangles.erase(iTriangle);
					iBullet->DeActivate();
					PopupScore.push_back(50);
					_SCORE += 100;

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

	void SpaceshipCollider( BaseSpaceShip Spaceship, std::vector<Animal> &VAnimals )
	{
		if(VAnimals.empty() || VAnimals.size() < 1)
		{
			return;
		}
			for(vector< Animal >::iterator iAnimal = VAnimals.begin(); iAnimal != VAnimals.end(); )
			{
				if( !( 
					Spaceship.GetCollisionBox().x > iAnimal->LocAndSize.x + iAnimal->LocAndSize.w || 
					Spaceship.GetCollisionBox().x + Spaceship.GetCollisionBox().w < iAnimal->LocAndSize.x || 
					Spaceship.GetCollisionBox().y > iAnimal->LocAndSize.y + iAnimal->LocAndSize.h || 
					Spaceship.GetCollisionBox().y + Spaceship.GetCollisionBox().h < iAnimal->LocAndSize.y
					) )
				{
					Audio.PlaySoundEffect( 5 );
					iAnimal = VAnimals.erase(iAnimal);
					Spaceship.Died();
				}
				else
				{
					++iAnimal;
				}
			}
	};
	void SpaceshipCollider( BaseSpaceShip Spaceship, std::vector<Cube> &VCubes )
	{
			for(vector< Cube >::iterator iCube = VCubes.begin(); iCube != VCubes.end(); )
			{
				if( !( 
					Spaceship.GetCollisionBox().x > iCube->xPos + iCube->Width || 
					Spaceship.GetCollisionBox().x + Spaceship.GetCollisionBox().w < iCube->xPos || 
					Spaceship.GetCollisionBox().y > iCube->yPos + iCube->Height || 
					Spaceship.GetCollisionBox().y + Spaceship.GetCollisionBox().h < iCube->yPos
					) )
				{
					Audio.PlaySoundEffect( 5 );
					iCube = VCubes.erase(iCube);
					Spaceship.Died();
				}
				else
				{
					++iCube;
				}
			}
	};
	void SpaceshipCollider( BaseSpaceShip Spaceship, std::vector<Triangle> &VTriangles )
	{
			for(vector< Triangle >::iterator iTriangle = VTriangles.begin(); iTriangle != VTriangles.end(); )
			{
				if( !( 
					Spaceship.GetCollisionBox().x > iTriangle->xPos + iTriangle->Width || 
					Spaceship.GetCollisionBox().x + Spaceship.GetCollisionBox().w < iTriangle->xPos || 
					Spaceship.GetCollisionBox().y > iTriangle->yPos + iTriangle->Height || 
					Spaceship.GetCollisionBox().y + Spaceship.GetCollisionBox().h < iTriangle->yPos
					) )
				{
					Audio.PlaySoundEffect( 5 );
					iTriangle = VTriangles.erase(iTriangle);
					Spaceship.Died();
				}
				else
				{
					++iTriangle;
				}
			}
	};
	// Old collision controlls
	bool CollisionBox( BaseSpaceShip *cPlayer, CEnemy *cEnemy, bool Show );

	bool CheckCollision( CEnemy *cEnemy, int WhichCollisionToUse, BaseSpaceShip *cPlayer );

};

extern ControlCollision CollisionController;
