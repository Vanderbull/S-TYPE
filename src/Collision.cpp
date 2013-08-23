#include "Collision.h"
#include <cmath>

ControlCollision CollisionController;

// checks collision
bool ControlCollision::CollisionCircle( BaseCharacter *Mydemon, CEnemy *MyEnemy, bool Show = true )
{
	// Cache
	double	dx = ( ( Mydemon->GetPosition().x + demonWIDTHREAL / 2 ) - ( MyEnemy->_Position.x + MyEnemy->Width / 2 ) ),
			dy = ( ( Mydemon->GetPosition().y + demonHEIGHTREAL / 2 + 45 ) - ( MyEnemy->_Position.y + MyEnemy->Height / 2 ) );

	double	dx1 = 0,
			dy1 = 0;

	double	dx2 = 0,
			dy2 = 0;

		//if( BCPlayer.isKicking )
		//{
			//if( BCPlayer.isMovingRight )
			//{
				// Cache
				//dx1 = ( ( ( Mydemon->GetPosition().x + BCPlayer.Feet_W / 2 ) + 60 ) - ( MyEnemy->_Position.x + MyEnemy->Width / 2 ) ),
				//dy1 = ( ( ( Mydemon->GetPosition().y + BCPlayer.Feet_H / 2 ) + 75 ) - ( MyEnemy->_Position.y + MyEnemy->Height / 2 ) );
			//}
			//else
			//{
				// Cache
				//dx1 = ( ( Mydemon->GetPosition().x + BCPlayer.Feet_W / 2 ) - ( MyEnemy->_Position.x + MyEnemy->Width / 2 ) ),
				//dy1 = ( ( ( Mydemon->GetPosition().y + BCPlayer.Feet_H / 2 ) + 75 ) - ( MyEnemy->_Position.y + MyEnemy->Height / 2 ) );
			//}
		//}
		//else
		//{
			// Cache
			//dx1 = ( ( ( Mydemon->GetPosition().x + BCPlayer.Feet_W / 2 )+ 15 ) - ( MyEnemy->_Position.x + MyEnemy->Width / 2 ) ),
			//dy1 = ( ( ( Mydemon->GetPosition().y + BCPlayer.Feet_H / 2 ) + 80 ) - ( MyEnemy->_Position.y + MyEnemy->Height / 2 ) );
		//}

		//if( BCPlayer.isPunching )
		//{
			// Cache
			//dx2 = ( ( ( Mydemon->GetPosition().x + BCPlayer.Fist_W / 2 )+ 55 ) - ( MyEnemy->_Position.x + MyEnemy->Width / 2 ) ),
			//dy2 = ( ( ( Mydemon->GetPosition().y + BCPlayer.Fist_H / 2 ) + 40 ) - ( MyEnemy->_Position.y + MyEnemy->Height / 2 ) );
			//int dist3 = ( int )sqrt( dx2 * dx2 + dy2 * dy2 );
			//if( dist3 < Mydemon->Radius + MyEnemy->Radius )
			//{
				//return true;	// Yep, collision
			//}
		//}
		//else
		//{
			// Cache
			//dx2 = ( ( ( Mydemon->GetPosition().x + BCPlayer.Fist_W / 2 )+ 20 ) - ( MyEnemy->_Position.x + MyEnemy->Width / 2 ) ),
			//dy2 = ( ( ( Mydemon->GetPosition().y + BCPlayer.Fist_H / 2 ) + 40 ) - ( MyEnemy->_Position.y + MyEnemy->Height / 2 ) );
			//int dist3 = ( int )sqrt( dx2 * dx2 + dy2 * dy2 );
			//if( dist3 < Mydemon->Radius + MyEnemy->Radius )
			//{
				//return true;	// Yep, collision
			//}
		//}

		if( Show )
		{
			//if( BCPlayer.isKicking )
			//{
			//	if( BCPlayer.isMovingRight )
			//	{
			//		Circle( Mydemon->GetPosition().x + BCPlayer.Feet_W / 2 + 60, Mydemon->GetPosition().y + BCPlayer.Feet_H / 2 + 75, Mydemon->RadiusFeet );
			//	}
			//	else
			//	{
			//		Circle( Mydemon->GetPosition().x + BCPlayer.Feet_W / 2, Mydemon->GetPosition().y + BCPlayer.Feet_H / 2 + 75, Mydemon->RadiusFeet );
			//	}

			//}
			//else
			//{
			//	Circle( Mydemon->GetPosition().x + BCPlayer.Feet_W / 2 + 15, Mydemon->GetPosition().y + BCPlayer.Feet_H / 2 + 80, Mydemon->RadiusFeet );
			//}
			//Circle( Mydemon->GetPosition().x + demonWIDTHREAL / 2, Mydemon->GetPosition().y + demonHEIGHTREAL / 2 + 45, Mydemon->Radius );
			//
			//if( BCPlayer.isPunching )
			//{
			//	Circle( Mydemon->GetPosition().x + BCPlayer.Fist_W / 2 + 55, Mydemon->GetPosition().y + BCPlayer.Fist_H / 2 + 40, Mydemon->RadiusFist );
			//}
			//else
			//{
			//	Circle( Mydemon->GetPosition().x + BCPlayer.Fist_W / 2 + 20, Mydemon->GetPosition().y + BCPlayer.Fist_H / 2 + 40, Mydemon->RadiusFist );
			//}
		}

	int dist = ( int )sqrt( dx * dx + dy * dy );
	int dist2 = ( int )sqrt( dx1 * dx1 + dy1 * dy1 );
	

	// Do circles overlap?
	if(	dist < Mydemon->Radius + MyEnemy->Radius || dist2 < Mydemon->Radius + MyEnemy->Radius )
	{
		return true;	// Yep, collision
	}
 
	// No collision
	return false;
}

// checks collision
bool ControlCollision::CollisionCircle( BaseCharacter *Mydemon, Heads *EnemyHead, bool Show = true)
{
	if( BCPlayer.isMovingLeft == true )
	{
		// Cache
		double	dx = ( ( Mydemon->GetPosition().x + demonWIDTHREAL / 2 + 70) - ( EnemyHead->_Position.x + EnemyHead->HeadWidth / 2 + 18) ),
				dy = ( ( Mydemon->GetPosition().y + demonHEIGHTREAL / 2 + 45 ) - ( EnemyHead->_Position.y + EnemyHead->HeadHeight / 2 +35) );

		double	dx1 = ( ( Mydemon->GetPosition().x + demonWIDTHREAL / 2 + 25) - ( EnemyHead->_Position.x + EnemyHead->HeadWidth / 2 + 18) ),
				dy1 = ( ( Mydemon->GetPosition().y + demonHEIGHTREAL / 2 + 45 ) - ( EnemyHead->_Position.y + EnemyHead->HeadHeight / 2 +35) );

		int dist = ( int )sqrt( dx * dx + dy * dy );
		int dist1 = ( int )sqrt( dx1 * dx1 + dy1 * dy1 );

		// Do circles overlap?
		if(	dist < Mydemon->Radius + EnemyHead->Radius || dist1 < Mydemon->Radius + EnemyHead->Radius )	
		{
			return true;	// Yep, collision
		}
	}
	else
	{
		// Cache
		double	dx = ( ( Mydemon->GetPosition().x + demonWIDTHREAL / 2 + 20) - ( EnemyHead->_Position.x + EnemyHead->HeadWidth / 2 + 18) ),
				dy = ( ( Mydemon->GetPosition().y + demonHEIGHTREAL / 2 + 45 ) - ( EnemyHead->_Position.y + EnemyHead->HeadHeight / 2 +35) );

		double	dx1 = ( ( Mydemon->GetPosition().x + demonWIDTHREAL / 2 + 5) - ( EnemyHead->_Position.x + EnemyHead->HeadWidth / 2 + 18) ),
				dy1 = ( ( Mydemon->GetPosition().y + demonHEIGHTREAL / 2 + 45 ) - ( EnemyHead->_Position.y + EnemyHead->HeadHeight / 2 +35) );

		int dist = ( int )sqrt( dx * dx + dy * dy );
		int dist1 = ( int )sqrt( dx1 * dx1 + dy1 * dy1 );

		// Do circles overlap?
		if(	dist < Mydemon->Radius + EnemyHead->Radius || dist1 < Mydemon->Radius + EnemyHead->Radius )	
		{
			return true;	// Yep, collision
		}
	}
	// test boss against the triangle attack and the BCPlayer itself.
	/*
	if( BCPlayer.demonHunter )
	{
		double	dx2 = 0,
				dy2 = 0;


		if( Show )
		{
			if( BCPlayer.isMovingLeft == true )
			{
				Circle( Mydemon->xPos + demonWIDTHREAL / 2 + 70, 
						Mydemon->yPos + demonHEIGHTREAL / 2 + 45,
						Mydemon->Radius );

				Circle( Mydemon->xPos + demonWIDTHREAL / 2 + 25, 
						Mydemon->yPos + demonHEIGHTREAL / 2 + 45,
						Mydemon->Radius );
			}
			else
			{
				Circle( Mydemon->xPos + demonWIDTHREAL / 2 + 20, 
						Mydemon->yPos + demonHEIGHTREAL / 2 + 45,
						Mydemon->Radius );

				Circle( Mydemon->xPos + demonWIDTHREAL / 2 + 5, 
						Mydemon->yPos + demonHEIGHTREAL / 2 + 45,
						Mydemon->Radius );
			}
		}
	}
 	 */
	// No collision
	return false;
}

// checks collision
bool ControlCollision::CollisionCircle( BaseCharacter *Mydemon, Boss *Myboss, bool Show = true )
{
	// Cache
	double	dx =	( ( Mydemon->GetPosition().x + demonWIDTHREAL / 2 ) - ( Myboss->_Position.x + Myboss->BossWidth / 2 + 100 ) ),
			dy =	( ( Mydemon->GetPosition().y + demonHEIGHTREAL / 2 + 45 ) - ( Myboss->_Position.y + Myboss->BossHeight / 2 - 30 ) );

	double  dx1 =	( ( Mydemon->GetPosition().x + demonWIDTHREAL / 2 ) - ( Myboss->_Position.x + Myboss->BossWidth / 2 + 95 ) ),
			dy1 =	( ( Mydemon->GetPosition().y + demonHEIGHTREAL / 2 + 45 ) - ( Myboss->_Position.y + Myboss->BossHeight / 2 + 220 ) );

	// test boss against the triangle attack and the BCPlayer itself.
	/*
	if( BCPlayer.demonHunter )
	{
		double	dx2 = 0,
				dy2 = 0,
				dx3 = 0,
				dy3 = 0;


			// Cache
			dx2 = ( ( ( Mydemon->xPos + BCPlayer.Fist_W / 2 ) - 35) - ( Myboss->xPos + Myboss->BossWidth / 2 ) + 100 ),
			dy2 = ( ( ( Mydemon->yPos + BCPlayer.Fist_H / 2 ) + 65 ) - ( Myboss->yPos + Myboss->BossHeight / 2 ) - 30 );
			dx3 =	( ( ( Mydemon->xPos + BCPlayer.Fist_W / 2 )+ 35 ) - ( Myboss->xPos + Myboss->BossWidth / 2 + 95 ) ),
			dy3 =	( ( ( Mydemon->yPos + BCPlayer.Fist_H / 2 )+ 65 ) - ( Myboss->yPos + Myboss->BossHeight / 2 + 220 ) );

			
		if( Show )
		{
				Circle( Mydemon->xPos + BCPlayer.Fist_W / 2 - 35, Mydemon->yPos + BCPlayer.Fist_H / 2 + 65, Mydemon->RadiusFeet );
		}

		int dist3 = ( int )sqrt( dx2 * dx2 + dy2 * dy2 );
		int dist4 = ( int )sqrt( dx3 * dx3 + dy3 * dy3 );
			// Do circles overlap?
		if( dist3 < Mydemon->Radius + Myboss->Radius || dist4 < Mydemon->Radius + Myboss->Radius )	
		{
			return true;	// Yep, collision
		}

	}
	  */
	int dist = ( int )sqrt( dx * dx + dy * dy );
	int dist1 = ( int )sqrt( dx1 * dx1 + dy1 * dy1 );
	

	// Do circles overlap?
	if(	dist < Mydemon->Radius + Myboss->Radius || dist1 < Mydemon->Radius + Myboss->Radius )	
	{
		return true;	// Yep, collision
	}
 
	// No collision
	return false;
}

// checks collision
bool ControlCollision::CollisionCircle( Fireball *MyFire, Boss *My_boss, bool Show = true)
{
	// Cache
	double	dx = ( ( MyFire->xPos + MyFire->Width / 2 - 10 ) - ( My_boss->_Position.x + My_boss->BossWidth / 2 + 100 ) ),
			dy = ( ( MyFire->yPos + MyFire->Height / 2 ) - ( My_boss->_Position.y + My_boss->BossHeight/ 2 - 30) );
	
	double	dx1 = ( ( MyFire->xPos + MyFire->Width / 2 - 10 ) - ( My_boss->_Position.x + My_boss->BossWidth / 2 + 95 ) ),
			dy1 = ( ( MyFire->yPos + MyFire->Height / 2 ) - ( My_boss->_Position.y + My_boss->BossHeight  / 2 + 220 ) );
	
	if( Show )
	{
		Circle( MyFire->xPos + MyFire->Width / 2, MyFire->yPos + MyFire->Height / 2, MyFire->Radius ) ;
	}

	int dist = (int)sqrt( dx * dx + dy * dy );
	int dist1 = (int)sqrt( dx1 * dx1 + dy1 * dy1 );

	// Do circles overlap?
	if( dist < MyFire->Radius + My_boss->Radius || dist1 < MyFire->Radius + My_boss->Radius )
	{
		return true;	// Yep, collision
	}

	// No collision
	return false;
}


// checks collision
bool ControlCollision::CollisionCircle( Fireball *MyFire, Heads *EnemyHead, bool Show = true )
{
	// Cache
 	double	dx = ( ( MyFire->xPos + MyFire->Width / 2 - 10 ) - ( EnemyHead->_Position.x + EnemyHead->HeadWidth / 2 ) ),
			dy = ( ( MyFire->yPos + MyFire->Height / 2 ) - ( EnemyHead->_Position.y + EnemyHead->HeadHeight / 2 ) );
	
	if( Show )
	{
		Circle( MyFire->xPos + MyFire->Width / 2, MyFire->yPos + MyFire->Height / 2, MyFire->Radius ) ;
	}

	int dist = (int)sqrt( dx*dx + dy*dy );

	// Do circles overlap?
	if( dist < MyFire->Radius + EnemyHead->Radius )
	{
		return true;	// Yep, collision
	}

	// No collision
	return false;
}

// checks collision
bool ControlCollision::CollisionCircle( Fireball *MyFire, CEnemy * MyEnemy, bool Show = true)
{
	// Cache
	double	dx = ( ( MyFire->xPos + MyFire->Width / 2 - 10 ) - ( MyEnemy->_Position.x + MyEnemy->Width / 2 ) ),
			dy = ( ( MyFire->yPos + MyFire->Height / 2 ) - ( MyEnemy->_Position.y + MyEnemy->Height / 2 ) );
	
	if( Show )
	{
		Circle( MyFire->xPos + MyFire->Width / 2, MyFire->yPos + MyFire->Height / 2, MyFire->Radius ) ;
	}

	int dist = (int)sqrt( dx*dx + dy*dy );

	// Do circles overlap?
	if( dist < MyFire->Radius + MyEnemy->Radius )
	{
		return true;	// Yep, collision
	}

	// No collision
	return false;
}

// checks collision
bool ControlCollision::CollisionCircle( BaseCharacter *Mydemon, PowerUp *TransForm, bool Show = true)
{
	// Cache
	double	dx = ( ( Mydemon->GetPosition().x + demonWIDTHREAL / 2 - 10 ) - ( TransForm->xPos + TransForm->Width / 2 ) ),
			dy = ( ( Mydemon->GetPosition().y + demonHEIGHTREAL / 2 - 10 ) - ( TransForm->yPos + TransForm->Height / 2 ) );

		// Cache
	double	dx1 = ( ( Mydemon->GetPosition().x + demonWIDTHREAL / 2 + 20 ) - ( TransForm->xPos + TransForm->Width / 2 ) ),
			dy1 = ( ( Mydemon->GetPosition().y + demonHEIGHTREAL / 2 + 40 ) - ( TransForm->yPos + TransForm->Height / 2 ) );
	
	if( Show )
	{
		Circle( TransForm->xPos + TransForm->Width / 2, TransForm->yPos + TransForm->Height / 2, TransForm->Radius ) ;
		Circle( Mydemon->GetPosition().x + demonWIDTHREAL - 10 / 2, Mydemon->GetPosition().y + demonHEIGHTREAL / 2 - 10, Mydemon->Radius );
		Circle( Mydemon->GetPosition().x + demonWIDTHREAL + 20 / 2, Mydemon->GetPosition().y + demonHEIGHTREAL / 2 + 40, Mydemon->Radius );
	}

	int dist = (int)sqrt( dx * dx + dy * dy );
	int dist2 = (int)sqrt( dx1 * dx1 + dy1 * dy1 );

	// Do circles overlap?
	if( dist < Mydemon->Radius + TransForm->Radius || 
		dist2 < Mydemon->Radius + TransForm->Radius )
	{
		return true;	// Yep, collision
	}

	// No collision
	return false;
}

// checks collision
bool ControlCollision::CheckCollisionWithdemon( PowerUp *TransForm, int WhichCollisionToUse )
{
	
	bool temp = false;

	if( WhichCollisionToUse == 1 )
	{
		temp = CollisionCircle( &BCPlayer, TransForm, true );
	}

	return temp;
}

// checks collision
void ControlCollision::Circle( long centerx, long centery, long radius )
{
         long d, y, x;

		 // setup
         d = 3 - (2 * radius);
         x = 0;
         y = radius;

         // draw the thing
         while (y > x) {
                 SetPixelMine( centerx + x,centery + y );
                 SetPixelMine( centerx + y,centery + x );
                 SetPixelMine( centerx - x,centery + y );
                 SetPixelMine( centerx - y,centery + x );
                 SetPixelMine( centerx + x,centery - y );
                 SetPixelMine( centerx + y,centery - x );
                 SetPixelMine( centerx - x,centery - y );
                 SetPixelMine( centerx - y,centery - x );

                 if (d < 0) {
                         d = d + ( 4 * x ) + 6;
                 } else {
                         d = d + 4 * ( x - y ) + 10;
                         y--;
                 }
                 x++;
         }
}

// checks collision
void ControlCollision::SetPixelMine( int xPos, int yPos  )
{
  	SDL_LockSurface( Gfx.BackBuffer );

	COLORREF color( RGB( 255, 0, 0 ) );

	int dstPitch = Gfx.BackBuffer->pitch;

	DWORD * dst = ( DWORD * )Gfx.BackBuffer->pixels;
	
	dst[ ( yPos * dstPitch / 4 ) + ( xPos ) ] = color;

	SDL_UnlockSurface( Gfx.BackBuffer );

}


// ----------------------------------------------------------------------------
// ChecksCollision - test if any collision occurs with BCPlayer
// ----------------------------------------------------------------------------
bool ControlCollision::CheckCollisionWithdemon( CEnemy *MyEnemy, int WhichCollisionToUse, BaseCharacter *Mydemon )
{
	return CollisionBox( Mydemon, MyEnemy, true );

	/*
	if( MyEnemy->xPos - BCPLayer.xPos >= 150 )
	{
		return temp;
	}
	
	if( MyEnemy->Die == true )
	{
		return false;
	}

	if( WhichCollisionToUse == 1 )
	{
		temp = CollisionCircle( &BCPlayer, MyEnemy, true );
	}
	if( temp )
	{
		temp = CollisionBox( &BCPlayer, MyEnemy, true );
	}

	return temp;
	*/
}

// ----------------------------------------------------------------------------
// CheckBoxCollision - test if box collision occurs
// ----------------------------------------------------------------------------
bool ControlCollision::CollisionBox( BaseCharacter *Mydemon, CEnemy *MyEnemy, bool Show = true)
{
	SDL_Rect demonCollisionBox = Mydemon->GetPosition();
	SDL_Rect EnemyCollisionBox = MyEnemy->GetPosition();
	//SDL_FillRect(Gfx.BackBuffer, &demonCollisionBox, 0xFFFFFF);
	//SDL_FillRect(Gfx.BackBuffer, &EnemyCollisionBox, 0xFFFFFF);
	
	return (abs(EnemyCollisionBox.x - demonCollisionBox.x) * 2 < (EnemyCollisionBox.w + demonCollisionBox.w)) &&
         (abs(EnemyCollisionBox.y - demonCollisionBox.y) * 2 < (EnemyCollisionBox.h + demonCollisionBox.h)); 
};

bool ControlCollision::CollisionPixel( BaseCharacter *Mydemon, CEnemy *MyEnemy )
{
	return false;
}