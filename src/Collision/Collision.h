#pragma once
#include "../Objects/Spaceship.h"
#include "../Game.h"
#include "../Enemies/Powerup.h"
#include "../Objects/Objects.h"
#include "../Enemies.h"
#include "../GfxController/ControlGfx.h"
#include "../Objects/Bullets.h"
#include "../Enemies/PurpleShip.h"
#include "../Enemies/Robotnic.h"
#include "../Enemies/Powerup.h"
#include "../Enemies/BlueFish.h"
#include "../Audio/Audio.h"

class ControlCollision
{
public:

    void ObjectCollider(std::vector<Bullet> &VBullets, std::vector<PurpleShip> &VPurpleShip)
    {
        for (vector< Bullet >::iterator iBullet = VBullets.begin(); iBullet != VBullets.end();)
        {
            for (vector< PurpleShip >::iterator iPurpleShip = VPurpleShip.begin(); iPurpleShip != VPurpleShip.end();)
            {
                if (!(
                    iBullet->GetCollisionBox().x > iPurpleShip->LocAndSize.x + iPurpleShip->LocAndSize.w ||
                    iBullet->GetCollisionBox().x + iBullet->GetCollisionBox().w < iPurpleShip->LocAndSize.x ||
                    iBullet->GetCollisionBox().y > iPurpleShip->LocAndSize.y + iPurpleShip->LocAndSize.h ||
                    iBullet->GetCollisionBox().y + iBullet->GetCollisionBox().h < iPurpleShip->LocAndSize.y
                    ))
                {
                    PowerupController.CreatePowerup(iPurpleShip->LocAndSize);
                    Audio.SetVolume(10, 5);
                    Audio.PlaySoundEffect(5);
                    iPurpleShip = VPurpleShip.erase(iPurpleShip);
                    iBullet->DeActivate();
                    PopupScore.push_back(50);
                    _SCORE += 100;
                }
                else
                {
                    ++iPurpleShip;
                }
            }
            if (!iBullet->isActive())
                iBullet = VBullets.erase(iBullet);
            else
                ++iBullet;
        }
    };
    void ObjectCollider(std::vector<Bullet> &VBullets, std::vector<Robotnic> &VRobotnic)
	{
 		for(vector< Bullet >::iterator iBullet = VBullets.begin(); iBullet != VBullets.end(); )
		{
            for (vector< Robotnic >::iterator iRobotnic = VRobotnic.begin(); iRobotnic != VRobotnic.end();)
			{
				if( !(
                    iBullet->GetCollisionBox().x > iRobotnic->LocAndSize.x + iRobotnic->LocAndSize.w ||
                    iBullet->GetCollisionBox().x + iBullet->GetCollisionBox().w < iRobotnic->LocAndSize.x ||
                    iBullet->GetCollisionBox().y > iRobotnic->LocAndSize.y + iRobotnic->LocAndSize.h ||
                    iBullet->GetCollisionBox().y + iBullet->GetCollisionBox().h < iRobotnic->LocAndSize.y
					) )
				{
                    PowerupController.CreatePowerup(iRobotnic->LocAndSize);
                    Audio.SetVolume(10, 5);
					Audio.PlaySoundEffect( 5 );
                    iRobotnic = VRobotnic.erase(iRobotnic);
					iBullet->DeActivate();
					//PopupScore.push_back(50);
					_SCORE += 100;
				}
				else
				{
					++iRobotnic;
				}
			}
			if( !iBullet->isActive() )
				iBullet = VBullets.erase(iBullet);
			else
				++iBullet;
		}
	};

	void ObjectCollider( std::vector<Bullet> &VBullets, std::vector<BlueFish> &VBlueFish )
	{
		for(vector< Bullet >::iterator iBullet = VBullets.begin(); iBullet != VBullets.end(); )
		{
			for(vector< BlueFish >::iterator iBlueFish = VBlueFish.begin(); iBlueFish != VBlueFish.end(); )
			{
                if (!(
                    iBullet->GetCollisionBox().x > iBlueFish->LocAndSize.x + iBlueFish->LocAndSize.w ||
                    iBullet->GetCollisionBox().x + iBullet->GetCollisionBox().w < iBlueFish->LocAndSize.x ||
                    iBullet->GetCollisionBox().y > iBlueFish->LocAndSize.y + iBlueFish->LocAndSize.h ||
                    iBullet->GetCollisionBox().y + iBullet->GetCollisionBox().h < iBlueFish->LocAndSize.y
                    ))
                {
					Audio.PlaySoundEffect( 5 );
					iBlueFish = VBlueFish.erase(iBlueFish);
					iBullet->DeActivate();
					PopupScore.push_back(50);
					_SCORE += 100;
				}
				else
				{
					++iBlueFish;
				}
			}
			if( !iBullet->isActive() )
				iBullet = VBullets.erase(iBullet);
			else
				++iBullet;
		}
	};

    void ObjectCollider(std::vector<Bullet> &VBullets, OctoBoss &OctoBoss)
    {
        for (vector< Bullet >::iterator iBullet = VBullets.begin(); iBullet != VBullets.end();)
        {
            if (!(
                iBullet->GetCollisionBox().x > OctoBoss.LocAndSize.x + OctoBoss.LocAndSize.w ||
                iBullet->GetCollisionBox().x + iBullet->GetCollisionBox().w < OctoBoss.LocAndSize.x ||
                iBullet->GetCollisionBox().y > OctoBoss.LocAndSize.y + OctoBoss.LocAndSize.h ||
                iBullet->GetCollisionBox().y + iBullet->GetCollisionBox().h < OctoBoss.LocAndSize.y
                ))
            {
                Audio.PlaySoundEffect(5);
                OctoBoss.isWounded(10);
                iBullet->DeActivate();
            }
            else
            {
            }
            if (!iBullet->isActive())
                iBullet = VBullets.erase(iBullet);
            else
                ++iBullet;
        }
    };

    void ObjectCollider(std::vector<Bullet> &VBullets, BaseSpaceShip Spaceship)
    {
        for (vector< Bullet >::iterator iBullet = VBullets.begin(); iBullet != VBullets.end();)
        {
            if (!(
                iBullet->GetCollisionBox().x > Spaceship.GetCollisionBox().x + Spaceship.GetCollisionBox().w ||
                iBullet->GetCollisionBox().x + iBullet->GetCollisionBox().w < Spaceship.GetCollisionBox().x ||
                iBullet->GetCollisionBox().y > Spaceship.GetCollisionBox().y + Spaceship.GetCollisionBox().h ||
                iBullet->GetCollisionBox().y + iBullet->GetCollisionBox().h < Spaceship.GetCollisionBox().y
                ))
            {
                Audio.PlaySoundEffect(5);
                Spaceship.Died();
                Spaceship.Reset();
                iBullet->DeActivate();
            }
            else
            {
            }
            if (!iBullet->isActive())
                iBullet = VBullets.erase(iBullet);
            else
                ++iBullet;
        }
    };

    void SpaceshipCollider(BaseSpaceShip Spaceship, std::vector<PurpleShip> &VPurpleShip)
    {
        if (Spaceship._SpawnTimer > 0)
            return;

        if (VPurpleShip.empty() || VPurpleShip.size() < 1)
        {
            return;
        }
        for (vector< PurpleShip >::iterator iPurpleShip = VPurpleShip.begin(); iPurpleShip != VPurpleShip.end();)
        {
            if (!(
                Spaceship.GetCollisionBox().x > iPurpleShip->LocAndSize.x + iPurpleShip->LocAndSize.w ||
                Spaceship.GetCollisionBox().x + Spaceship.GetCollisionBox().w < iPurpleShip->LocAndSize.x ||
                Spaceship.GetCollisionBox().y > iPurpleShip->LocAndSize.y + iPurpleShip->LocAndSize.h ||
                Spaceship.GetCollisionBox().y + Spaceship.GetCollisionBox().h < iPurpleShip->LocAndSize.y
                ))
            {
                Audio.PlaySoundEffect(5);
                iPurpleShip = VPurpleShip.erase(iPurpleShip);
                Spaceship.Died();
            }
            else
            {
                ++iPurpleShip;
            }
        }
    };

	void SpaceshipCollider( BaseSpaceShip Spaceship, std::vector<Robotnic> &VRobotnic )
	{
        if (Spaceship._SpawnTimer > 0)
            return;

        if (VRobotnic.empty() || VRobotnic.size() < 1)
		{
			return;
		}
        for (vector< Robotnic >::iterator iRobotnic = VRobotnic.begin(); iRobotnic != VRobotnic.end();)
			{
				if( !(
                    Spaceship.GetCollisionBox().x > iRobotnic->LocAndSize.x + iRobotnic->LocAndSize.w ||
                    Spaceship.GetCollisionBox().x + Spaceship.GetCollisionBox().w < iRobotnic->LocAndSize.x ||
                    Spaceship.GetCollisionBox().y > iRobotnic->LocAndSize.y + iRobotnic->LocAndSize.h ||
                    Spaceship.GetCollisionBox().y + Spaceship.GetCollisionBox().h < iRobotnic->LocAndSize.y
					) )
				{
					Audio.PlaySoundEffect( 5 );
                    iRobotnic = VRobotnic.erase(iRobotnic);
					Spaceship.Died();
				}
				else
				{
                    ++iRobotnic;
				}
			}
	};

	void SpaceshipCollider( BaseSpaceShip Spaceship, std::vector<BlueFish> &VBlueFish )
	{
        if (Spaceship._SpawnTimer > 0)
            return;

		for(vector< BlueFish >::iterator iBlueFish = VBlueFish.begin(); iBlueFish != VBlueFish.end(); )
		{
            if (!(
                Spaceship.GetCollisionBox().x > iBlueFish->LocAndSize.x + iBlueFish->LocAndSize.w ||
                Spaceship.GetCollisionBox().x + Spaceship.GetCollisionBox().w < iBlueFish->LocAndSize.x ||
                Spaceship.GetCollisionBox().y > iBlueFish->LocAndSize.y + iBlueFish->LocAndSize.h ||
                Spaceship.GetCollisionBox().y + Spaceship.GetCollisionBox().h < iBlueFish->LocAndSize.y
                ))
            {
				Audio.PlaySoundEffect( 5 );
				iBlueFish = VBlueFish.erase(iBlueFish);
				Spaceship.Died();
			}
			else
			{
				++iBlueFish;
			}
		}
	};

    void SpaceshipCollider(BaseSpaceShip Spaceship, std::vector<Powerup> &VPowerups)
    {
        if (Spaceship._SpawnTimer > 0)
            return;

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

    void SpaceshipCollider(BaseSpaceShip Spaceship, OctoBoss &OctoBoss)
    {
        if( OctoBoss.onCollision(Spaceship.GetPosition()) )
        {
            Audio.PlaySoundEffect(5);
            Spaceship.Died();
            Spaceship.Reset();
        }
    };

	// Old collision controlls
	bool CollisionBox( BaseSpaceShip *cPlayer, CEnemy *cEnemy, bool Show );

	bool CheckCollision( CEnemy *cEnemy, int WhichCollisionToUse, BaseSpaceShip *cPlayer );

};

extern ControlCollision CollisionController;
