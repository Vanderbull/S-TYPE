#pragma once
#include "SpaceShip.h"
#include "Game.h"
#include "Enemies\Powerup.h"
#include "Objects.h"
#include "Enemies.h"
#include "ControlGfx.h"
#include "Bullets.h"
#include "BlueShip.h"
#include "Enemies\Cubes.h"
#include "Enemies\Powerup.h"
#include "Triangles.h"
#include "Audio.h"

class ControlCollision
{
public:

	void ObjectCollider( std::vector<Bullet> &VBullets, std::vector<BlueShip> &VBlueShip )
	{
 		for(vector< Bullet >::iterator iBullet = VBullets.begin(); iBullet != VBullets.end(); )
		{
			for(vector< BlueShip >::iterator iBlueShip = VBlueShip.begin(); iBlueShip != VBlueShip.end(); )
			{
				if( !( 
					iBullet->GetCollisionBox().x > iBlueShip->LocAndSize.x + iBlueShip->LocAndSize.w || 
					iBullet->GetCollisionBox().x + iBullet->GetCollisionBox().w < iBlueShip->LocAndSize.x || 
					iBullet->GetCollisionBox().y > iBlueShip->LocAndSize.y + iBlueShip->LocAndSize.h || 
					iBullet->GetCollisionBox().y + iBullet->GetCollisionBox().h < iBlueShip->LocAndSize.y
					) )
				{
                    PowerupController.CreatePowerup( iBlueShip->LocAndSize );
                    Audio.SetVolume(10, 5);
					Audio.PlaySoundEffect( 5 );
					iBlueShip = VBlueShip.erase(iBlueShip);
					iBullet->DeActivate();
					PopupScore.push_back(50);
					_SCORE += 100;
					SDL_Surface * SrfProgress;
					SrfProgress = TTF_RenderText_Solid( Gfx.DefaultFont, "POWER UP COOL *YEA GRIIM!!!!!", Gfx.WhiteRGB );
					Gfx.apply_surface( 150, 150, SrfProgress, Gfx.BackBuffer );
				}
				else
				{
					++iBlueShip;
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

	void SpaceshipCollider( BaseSpaceShip Spaceship, std::vector<BlueShip> &VBlueShip )
	{
        if (VBlueShip.empty() || VBlueShip.size() < 1)
		{
			return;
		}
        for (vector< BlueShip >::iterator iBlueShip = VBlueShip.begin(); iBlueShip != VBlueShip.end();)
			{
				if( !( 
                    Spaceship.GetCollisionBox().x > iBlueShip->LocAndSize.x + iBlueShip->LocAndSize.w ||
                    Spaceship.GetCollisionBox().x + Spaceship.GetCollisionBox().w < iBlueShip->LocAndSize.x ||
                    Spaceship.GetCollisionBox().y > iBlueShip->LocAndSize.y + iBlueShip->LocAndSize.h ||
                    Spaceship.GetCollisionBox().y + Spaceship.GetCollisionBox().h < iBlueShip->LocAndSize.y
					) )
				{
					Audio.PlaySoundEffect( 5 );
                    iBlueShip = VBlueShip.erase(iBlueShip);
					Spaceship.Died();
				}
				else
				{
                    ++iBlueShip;
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

    void SpaceshipCollider(BaseSpaceShip Spaceship, std::vector<Powerup> &VPowerups)
    {
        if (VPowerups.empty() || VPowerups.size() < 1)
        {
            return;
        }
        for (vector< Powerup >::iterator iPowerup = VPowerups.begin(); iPowerup != VPowerups.end();)
        {
            if (!(
                Spaceship.GetCollisionBox().x > iPowerup->LocAndSize.x + iPowerup->LocAndSize.w ||
                Spaceship.GetCollisionBox().x + Spaceship.GetCollisionBox().w < iPowerup->LocAndSize.x ||
                Spaceship.GetCollisionBox().y > iPowerup->LocAndSize.y + iPowerup->LocAndSize.h ||
                Spaceship.GetCollisionBox().y + Spaceship.GetCollisionBox().h < iPowerup->LocAndSize.y
                ))
            {
                Audio.PlaySoundEffect(10);
                
                iPowerup = VPowerups.erase(iPowerup);
            }
            else
            {
                ++iPowerup;
            }
        }
    };

	// Old collision controlls
	bool CollisionBox( BaseSpaceShip *cPlayer, CEnemy *cEnemy, bool Show );

	bool CheckCollision( CEnemy *cEnemy, int WhichCollisionToUse, BaseSpaceShip *cPlayer );

};

extern ControlCollision CollisionController;
