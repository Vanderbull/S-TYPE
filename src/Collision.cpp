#include "Collision.h"
#include <cmath>

ControlCollision CollisionController;

void myfunction (Bullet* i) {
	std::cout << " coolision " << (*i).CollisionBox.x;
}

int ControlCollision::Box( std::list< Bullet* > My_Bullets, std::list< Animal* > iEnemy )
{
	// not using reference so the lists dont get updated outside function :(
	if(My_Bullets.size() > 0 && iEnemy.size() > 0 )
for(std::list<Bullet*>::iterator iter = My_Bullets.begin(); iter != My_Bullets.end(); iter++) 
{
    Bullet *m = (*iter);
	for(std::list< Animal* >::iterator innerIter = iEnemy.begin(); innerIter != iEnemy.end(); innerIter++ ) 
	{

            Animal *s = (*innerIter);
	
			if ((abs(m->CollisionBox.x - s->CollisionBox.x) * 2 < (m->CollisionBox.w + s->CollisionBox.w)) &&
			   (abs(m->CollisionBox.y - s->CollisionBox.y) * 2 < (m->CollisionBox.h + s->CollisionBox.h)))
			{
				innerIter = iEnemy.erase(innerIter); 
				iter = My_Bullets.erase(iter);

				cout << "COLLISION CRASH BOOMM BANG!!!!!!!" << endl;
				return 0;
			};

            //if(m->getType() == s->getType()) {
            //    break;
            //}

            //if(m->checkCollision(s)) {
            //    m->onCollision(s);
            //    s->onCollision(m);
            //}
    }
}

	//for_each (My_Bullets.begin(), My_Bullets.end(), myfunction);
	
	//return (abs(EnemyBox.x - SpaceshipBox.x) * 2 < (EnemyBox.w + SpaceshipBox.w)) &&
    //     (abs(EnemyBox.y - SpaceshipBox.y) * 2 < (EnemyBox.h + SpaceshipBox.h));
	return 0;
}



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

	if( Show )
	{
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
bool ControlCollision::CheckCollision( CEnemy *MyEnemy, int WhichCollisionToUse, BaseCharacter *Mydemon )
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