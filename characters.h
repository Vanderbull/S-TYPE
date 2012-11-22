#pragma once

// @date 2012-08-07

#include <SDL.h>
#include <SDL_image.h>

class DemonInterface
 {
public:
	 virtual void Update()=0;
	 virtual void SetClips()=0;
};

class Demon : public DemonInterface
{
public:

	enum State
	{
		IDLE,
		MOVING_RIGHT,
		MOVING_LEFT,
		JUMPING,
		CROUCHING,
		KICKING,
		PUNCHING,
		GETTING_UP,
		GETTING_HIT
	};

	enum MorphState
	{
		SMALL_HUNTER,
		MEDIUM_HUNTER,
		LARGE_HUNTER,
		DEMON_HUNTER
	};

	Demon();
	Demon(int surface, int Xpos, int Ypos, int height, int width);
	void InitiateDemon( int surface, int Xpos, int Ypos, int height, int width ); 

	void Set_clips();
	void UpdateEndPosition();
	int  UpdatePlayer();
	void UpdateXPos();
	bool IsInStateAttack();
	bool CheckBoundaries();

	bool SmallHunter, MediumHunter, LargeHunter, DemonHunter;

	// States the character can be in
	bool isMovingRight;
	bool isMovingLeft;
	bool isJumping;
	bool isCrouching;
	bool isKicking;
	bool isPunching;
	bool isGettingUp;
	bool isHit;
	bool isImmortal;

	bool CrouchFireBall;
	bool TriangleAttack;

	bool LifeFull_Small;
	bool LifeMedium_Small;
	bool LifeLittle_Small;

	//bool Crouch, Jump, Punch, FireBall, CrouchFire, Triangle;
	bool FireBall, CrouchFire, Triangle;

	bool DieOneLife, Demon_Dead;
	
	int Demon_Height;
	int Demon_Width;
	int DemonSurface;
	int Demon_Health;
	int Demon_Life;
	int Last_Xpos;
	int LastEnd_Pos;
	//int xPosHotSpot;

	int AlphaImmortal;
	int LengthOfTriangle;


	int Feet_W, Feet_H, Fist_W, Fist_H;

	int WhichFrame;
	int WhereAnimation;
	int WhereIsEnd;
	int DieState, TriangleState;

	int WhereWalkRight, WhereWalkLeft;
	int WhereJumpLeft, WhereJumpRight;
	int KickRight, KickLeft;
	int CrouchRight, CrouchLeft;
	int PunchRight, PunchLeft;
	int TriangleFireLeft, TriangleFireRight;
	int DieRightDemon, DieLeftDemon;

	int WalkLeft_Demon, WalkRight_Demon;
	int FireBallRight_Demon, FireBallLeft_Demon;
	int JumpRight_Demon, JumpLeft_Demon;
	int CrouchRightFire, CrouchLeftFire;
	int FireBallRight, FireBallLeft;
	
	int Radius, RadiusFist, RadiusFeet;

	bool Right, Left;
	bool MovementDirection; // false = left, true = right

	float xPos, yPos;
	float xVelocity, yVelocity;

	SDL_Rect AnimationArrays[ 4 ][ 48 ];

	// New update functionality
	void Update();
	void SetClips();
	void UpdatePosition(float x, float y); 
	void SetState( Demon::State state )
	{
		_State = state;
	}
	Demon::State GetState() const
	{
	   return _State;
	}
	void SetMorphState( Demon::MorphState state )
	{
		_MorphState = state;
	}
	Demon::MorphState GetMorphState() const
	{
	   return _MorphState;
	}


private:
	Demon::State _State;
	Demon::MorphState _MorphState;
};

extern Demon demon;



