#include "Collision.h"
#include <cmath>

// 1. this should go into every .cpp , after all header inclusions
#ifdef _WIN32
#ifdef _DEBUG
   #include <crtdbg.h>
   #undef THIS_FILE
   static char THIS_FILE[] = __FILE__;
   #define new       new( _NORMAL_BLOCK, __FILE__, __LINE__)
   #define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif

ControlCollision CollisionController;

// ----------------------------------------------------------------------------
// ChecksCollision - test if any collision occurs with BCPlayer
// ----------------------------------------------------------------------------
bool ControlCollision::CheckCollision( CEnemy *MyEnemy, int WhichCollisionToUse, BaseSpaceShip *Mydemon )
{
	return CollisionBox( Mydemon, MyEnemy, true );
}

// ----------------------------------------------------------------------------
// CheckBoxCollision - test if box collision occurs
// ----------------------------------------------------------------------------
bool ControlCollision::CollisionBox( BaseSpaceShip *cPlayer, CEnemy *cEnemy, bool Show = true)
{
    return true;
};
