#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <list>
#include "Objects.h"
#include "Enemies\MovingThings.h"
#include "Enemies\CSkeleton.h"
#include "Enemies\CZombie.h"
#include "Enemies\CHeads.h"

enum{ ENEMY_ZOMBIE, ENEMY_SKELETON };
enum{ ZOMBIE = 6, SKELETON = 7, SKULL = 8};
/*
class MovingThings
{
public:
	float xPos, yPos;
	int Frame;
	int Radius;
	int Width, Height;
	int Speed;
	
	int surface;
	SDL_Rect Clips[ 16 ];
};
*/
/*
class CZombie : public MovingThings
{
public:
	
	CZombie();
	void Set_Clips( int WhichTypeOfEnemy ); // Should be replaced by objects SetClips
	void SetFrame();

	int xPos, yPos;
	int Width, Height;
	int Surface;
	int PrevFrame, Frame, Radius, 
		WalkFrameLeft, WalkFrameRight, 
		AttackFrameRight, AttackFrameLeft, 
		DieFrameLeft, DieFrameRight, 
		AnimCounter;

	bool Walk, Attack, Die, LeftOf_Demon, RightOf_Demon;

	SDL_Rect ZombieClips[ 10 ];

private:
};
*/
/*
class CSkeleton : public MovingThings
{
public:
	
	CSkeleton();
	void Set_Clips( int WhichTypeOfEnemy ); // Should be replaced by objects SetClips
	void SetFrame();

	int xPos, yPos;
	int Width, Height;
	int Surface;
	int PrevFrame, Frame, Radius, 
		WalkFrameLeft, WalkFrameRight, 
		AttackFrameRight, AttackFrameLeft, 
		DieFrameLeft, DieFrameRight, 
		AnimCounter;

	bool Walk, Attack, Die, LeftOf_Demon, RightOf_Demon;

	

	SDL_Rect SkeletonClips[ 4 ][ 14 ];

private:
};
*/

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
		CEnemy::_Position.x = CEnemy::xPos;
		CEnemy::_Position.y = CEnemy::yPos;
		CEnemy::_Position.w = CEnemy::Width;
		CEnemy::_Position.h = CEnemy::Height;
	}

	//int xPos, yPos;
	//int Width, Height;
	//int Surface;
	int PrevFrame, Frame, Radius, 
		WalkFrameLeft, WalkFrameRight, 
		AttackFrameRight, AttackFrameLeft, 
		DieFrameLeft, DieFrameRight, 
		AnimCounter;

	bool Walk, Attack, Die, LeftOf_Demon, RightOf_Demon;

	std::list<SDL_Rect> Clips;
	SDL_Rect SkeletonClips[ 4 ][ 14 ];
	SDL_Rect ZombieClips[ 10 ];

private:
		SDL_Rect _Position;
};

class Heads : public MovingThings
{
public:
	Heads();
	int GetFrame();
	void SetFrame( int WhichFrame );
	void UpdateFrame();

	SDL_Rect GetClips( int WhichClip );

	float length;
	float HowFarSpeed;
	float HowFar;
	int state;
	float HeadTimer;

	int HeadHeight, HeadWidth;
};

class Boss : public MovingThings
{
public:
	Boss();
	float GetTimerAttack();
	int GetFrame();
	int GetState();

	int radius_Second;

	int BossWidth, BossHeight;
	int BossLife;
	bool BossDead;

	void ResetAttackTimer();
	void UpdateAttackTimer();

	void SetFrame( int WhichFrame );
	void UpdateFrame();

	void SetState( int WhichState );
	void UpdateBoss();
	void UpdateHeads();

	Heads * CreateBossHeads( int xPos, int yPos, int surface, int lengthOfTravel );

	SDL_Rect GetClips( int WhichClip );
	SDL_Rect ReturnDestRect();

	bool HeadsComing;
	bool HeadAnimation;

	float AnimPaceBoss;
	float HeadTimer;
	float SizeHeads;

	std::list< Heads* > My_BossHead;
	std::list< CHeads* > _BossHeads;

private:
	int State; 
};

// controls the enemies and creates the enemies
class Control_Enemies
{
public:
	Control_Enemies();
	void Update();
	void Draw_Enemies();
	void Create_Enemies();
	std::list<CZombie*> _Zombies;
	std::list<CSkeleton*> _Skeletons;
	std::list< CEnemy* > Enemies;
	CEnemy * CreateEnemy( int xPos, int yPos, int surface );	
private:

	//std::list< CZombie* > _DeadZombies;
	//std::list< CSkeleton* > _DeadSkeletons;
	//std::list< CEnemy* > Enemies_dead;
	
	//int Zombie, Skeleton, Skull;

	bool Collide;
	bool CollideFire;
	bool Attack;
};

extern Control_Enemies Control_ENEMY;


