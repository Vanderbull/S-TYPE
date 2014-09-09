#pragma once
#include "Enemies.h"
#include "Game.h"
#include <list>
#include "Objects.h"
#include "Collision.h"
#include "ControlGfx.h"

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

Control_Enemies EnemyController;

CEnemy::CEnemy()
{
	CEnemy::Speed = 300;
}

void CEnemy::Set_Clips( int WhichTypeOfEnemy )
{
    // setting the clips
}

// sets frame for skeleton
void CEnemy::SetFrame()
{
	PrevFrame = Frame;
}

void Control_Enemies::Update()
{
	Collide = false;
	list< CEnemy* >::iterator i = Enemies.begin();

	i = Enemies.begin();
	while(i != Enemies.end() )
	{
		(*i)->Update();
		if( (*i)->_Position.x <= 200 )
		{
			i = Enemies.erase(i);
		}
		else
		{
			++i;
		}
	}
}
// draws all enemies skeleton, skull, zombies, checks collision and updates frame
void Control_Enemies::Draw_Enemies()
{
}

// Memory leak here because of missing delete, code not used though so its not critical
CEnemy * Control_Enemies::CreateEnemy( Sint16 xPos, Sint16 yPos, int surface )
{
	CEnemy * temp = new CEnemy;
	temp->Surface = surface;
	temp->AnimCounter = 1;
	temp->PrevFrame = 0;
	
	temp->_Position.x = xPos;
	temp->_Position.y = yPos;

	temp->Height = 96;
	temp->Width = 96;

	int Height, Width;
	Height = temp->Height / 2;
	Width = temp->Width / 2;

	return temp;
}

void Control_Enemies::Create_Enemies()
{
}

Control_Enemies::Control_Enemies()
{
	Attack = false;
	Collide = false;
	CollideFire = false;
	SpawnTimer = 0;
}

