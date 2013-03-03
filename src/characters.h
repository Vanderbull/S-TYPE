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

	enum AliveState
	{
		DEAD,
		IMMORTAL,
		ALIVE
	};

	Demon();
	Demon(int surface, int Xpos, int Ypos, int height, int width);
	void InitiateDemon( int surface, int Xpos, int Ypos, int height, int width ); 

	//int  UpdatePlayer();
	bool IsInStateAttack();
	bool CheckBoundaries();
	bool Alive();
	//void SetLives(int Lives);
	//int GetLives();
	void Died();

	//bool SmallHunter;
	//bool MediumHunter; 
	//bool LargeHunter;
	//bool DemonHunter;

	// States the character can be in
	bool isMovingRight;
	bool isMovingLeft;
	bool isJumping;
	bool isKicking;
	bool isPunching;
	bool isGettingUp;
	bool isHit;
	bool isImmortal;

	bool LifeFull_Small;
	bool LifeMedium_Small;
	bool LifeLittle_Small;

	//bool Crouch, Jump, Punch, FireBall, CrouchFire, Triangle;
	//bool FireBall;

	//bool DieOneLife, 
	//bool Demon_Dead;
	
	//int Demon_Height;
	//int Demon_Width;
	int DemonSurface;
	int DemonHealth;
	//int Demon_Life;
	//int Last_Xpos;
	//int LastEnd_Pos;
	//int Score;
	//int JumpingSpeed;
	//int JumpingVelocity;
	//int JumpingGravity;
	//int xPosHotSpot;

	int AlphaImmortal;
	//int LengthOfTriangle;


	int Feet_W, Feet_H, Fist_W, Fist_H;

	int WhichFrame;
	//int WhereAnimation;
	//int DieState;

	//int WhereWalkRight, WhereWalkLeft;
	//int WhereJumpLeft, WhereJumpRight;
	//int KickRight, KickLeft;
	//int PunchRight, PunchLeft;
	//int TriangleFireLeft, TriangleFireRight;
	//int DieRightDemon, DieLeftDemon;

	//int WalkLeft_Demon, WalkRight_Demon;
	//int FireBallRight_Demon, FireBallLeft_Demon;
	//int JumpRight_Demon, JumpLeft_Demon;
	//int FireBallRight, FireBallLeft;
	
	int Radius, RadiusFist, RadiusFeet;

	bool Right, Left;
	bool MovementDirection; // false = left, true = right

	//float xPos, yPos;
	float xVelocity, yVelocity;

	SDL_Rect AnimationArrays[ 9 ][ 48 ];

	// New update functionality
	SDL_Rect GetPosition()
	{
		return Demon::_Position;
	}

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
	void SetAliveState( Demon::AliveState state )
	{
		_AliveState = state;
	}
	Demon::AliveState GetAliveState() const
	{
	   return _AliveState;
	}

private:
	Demon::State _State;
	Demon::MorphState _MorphState;
	Demon::AliveState _AliveState;
	SDL_Rect _Position;
	int _LeftMostPosition;
	int _RightMostPosition;
};

extern Demon demon;



