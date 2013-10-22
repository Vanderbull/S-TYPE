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
bool ControlCollision::CollisionBox( BaseCharacter *cPlayer, CEnemy *cEnemy, bool Show = true)
{
	SDL_FillRect(Gfx.BackBuffer, &cPlayer->GetPosition(), 0xFFFFFF);
	SDL_FillRect(Gfx.BackBuffer, &cEnemy->GetPosition(), 0xFFFFFF);
	
	return (abs(cEnemy->GetPosition().x - cPlayer->GetPosition().x) * 2 < (cEnemy->GetPosition().w + cPlayer->GetPosition().w)) &&
         (abs(cEnemy->GetPosition().y - cPlayer->GetPosition().y) * 2 < (cEnemy->GetPosition().h + cPlayer->GetPosition().h)); 
};