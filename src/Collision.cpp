#include "Collision.h"
#include <cmath>

ControlCollision CollisionController;

// ----------------------------------------------------------------------------
// ChecksCollision - test if any collision occurs with BCPlayer
// ----------------------------------------------------------------------------
bool ControlCollision::CheckCollision( CEnemy *MyEnemy, int WhichCollisionToUse, BaseCharacter *Mydemon )
{
	return CollisionBox( Mydemon, MyEnemy, true );
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