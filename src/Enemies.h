#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <list>
#include "Objects.h"
#include "Enemies\MovingThings.h"
#include "Enemies\CSkeleton.h"
#include "Enemies\CDwarf.h"

enum{ ENEMY_SKELETON,ENEMY_DWARF };
enum{ SKELETON = 7, SKULL = 8, DWARF};

// holds info for all the enemies

class CEnemy : public MovingThings
{
public:
	
	CEnemy();
	void Set_Clips( int WhichTypeOfEnemy ); // Should be replaced by objects SetClips
	void SetFrame();
	
	// New update functionality
	SDL_Rect GetPosition()
	{
		return CEnemy::_Position;
	}
	void Update()
	{
		CEnemy::_Position.w = CEnemy::Width;
		CEnemy::_Position.h = CEnemy::Height;
	}

	int PrevFrame, Frame, Radius, 
		WalkFrameLeft, WalkFrameRight, 
		AttackFrameRight, AttackFrameLeft, 
		DieFrameLeft, DieFrameRight, 
		AnimCounter;

	bool Walk, Attack, Die, LeftOfPlayer, RightOfPlayer;

	std::list<SDL_Rect> Clips;
	SDL_Rect SkeletonClips[ 4 ][ 14 ];
	SDL_Rect DwarfClips[ 4 ][ 14 ];

private:
};

// controls the enemies and creates the enemies
class Control_Enemies
{
public:
	Control_Enemies();
	void Update();
	void Draw_Enemies();
	void Create_Enemies();
	std::list<CDwarf*> _Dwarves;
	std::list<CSkeleton*> _Skeletons;
	std::list< CEnemy* > Enemies;
	CEnemy * CreateEnemy( int xPos, int yPos, int surface );	
private:

	int SpawnTimer;
	bool Collide;
	bool CollideFire;
	bool Attack;
};

extern Control_Enemies EnemyController;


