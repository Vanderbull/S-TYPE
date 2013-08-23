#pragma once

#include<queue>
#include <SDL.h>
#include <SDL_image.h>

class BaseCharacterInterface
{
public:
	int _HealthPoints;
	int _Surface;
	int _Lives;
	int _AlphaImmortal;

	virtual void Update()=0;
	virtual void SetClips()=0;
	virtual std::string GetAction()=0;
	virtual void AddAction(std::string action_event)=0;
	virtual std::string GetVelocity()=0;
	virtual void AddVelocity(std::string velocity_event)=0;
};

namespace Actor
{ 
}

class BaseCharacter : public BaseCharacterInterface
{
public:

	enum State
	{
		IDLE,
		MOVING_RIGHT,
		MOVING_LEFT,
		//JUMPING,
		//KICKING,
		//PUNCHING,
		//GETTING_UP,
		//GETTING_HIT
	};

	enum AliveState
	{
		DEAD,
		IMMORTAL,
		ALIVE
	};

	BaseCharacter();
	BaseCharacter(int surface, int Xpos, int Ypos, int height, int width);
	//void Initiatedemon( int surface, int Xpos, int Ypos, int height, int width );
	void Reset();
	void Died();

	//int  Updatedemon();
	bool IsInStateAttack();
	bool CheckBoundaries();
	//void SetLives(int Lives);
	//int GetLives();

	//bool SmallHunter;
	//bool MediumHunter; 
	//bool LargeHunter;
	//bool demonHunter;

	// States the character can be in
	bool isMovingRight;
	bool isMovingLeft;
	//bool isJumping;
	//bool isKicking;
	//bool isPunching;
	//bool isGettingUp;
	bool isHit;
	//bool isImmortal;

	//bool LifeFull_Small;
	//bool LifeMedium_Small;
	//bool LifeLittle_Small;

	//bool Crouch, Jump, Punch, FireBall, CrouchFire, Triangle;
	//bool FireBall;

	//bool DieOneLife, 
	//bool demon_Dead;
	
	//int demon_Height;
	//int demon_Width;
	//int Surface;
	//int Health;
	//int demon_Life;
	//int Last_Xpos;
	//int LastEnd_Pos;
	//int Score;
	//int JumpingSpeed;
	//int JumpingVelocity;
	//int JumpingGravity;
	//int xPosHotSpot;

	//int AlphaImmortal;
	//int LengthOfTriangle;


	int Feet_W, Feet_H, Fist_W, Fist_H;

	//int WhichFrame;
	//int WhereAnimation;
	//int DieState;

	//int WhereWalkRight, WhereWalkLeft;
	//int WhereJumpLeft, WhereJumpRight;
	//int KickRight, KickLeft;
	//int PunchRight, PunchLeft;
	//int TriangleFireLeft, TriangleFireRight;
	//int DieRightdemon, DieLeftdemon;

	//int WalkLeft_demon, WalkRight_demon;
	//int FireBallRight_demon, FireBallLeft_demon;
	//int JumpRight_demon, JumpLeft_demon;
	//int FireBallRight, FireBallLeft;
	
	int Radius, RadiusFist, RadiusFeet;

	//bool Right, Left;
	//bool MovementDirection; // false = left, true = right

	//float xPos, yPos;
	float xVelocity, yVelocity;

	SDL_Rect AnimationArrays[ 9 ][ 48 ];

#define TICK_INTERVAL    125

	Uint32 TimeLeft(void)
	{
		static Uint32 next_time = 0;
		Uint32 now;

		now = SDL_GetTicks();
		if ( next_time <= now ) {
			next_time = now+TICK_INTERVAL;
			return(0);
		}
		return(next_time-now);
	}

	int Animate()
	{
		if( this->_AnimationFrame > 6 )
			this->_AnimationFrame = 0;
		if(this->TimeLeft() == 0 )
			++_AnimationFrame;
		return _AnimationFrame;
	}
	// New update functionality
	SDL_Rect GetPosition()
	{
		return BaseCharacter::_Position;
	}

	void Update();
	void SetClips();
	void UpdatePosition(float x, float y); 
	void SetState( BaseCharacter::State state )
	{
		_State = state;
	}
	BaseCharacter::State GetState() const
	{
	   return _State;
	}

	//void SetMorphState( BaseCharacter::MorphState state )
	//{
	//	_MorphState = state;
	//}
	//BaseCharacter::MorphState GetMorphState() const
	//{
	//   return _MorphState;
	//}
	void SetAliveState( BaseCharacter::AliveState state )
	{
		_AliveState = state;
	}
	BaseCharacter::AliveState GetAliveState() const
	{
	   return _AliveState;
	}

	std::string BaseCharacter::GetAction()
	{
		if( !Action.empty() )
		{
			std::string returnAction = Action.front();
			Action.pop();
			return returnAction;
		}
		else
		{
			return "No actions...";
		}
	}

	void BaseCharacter::AddAction(std::string action_event)
	{
		Action.push(action_event);
	}

	std::string BaseCharacter::GetVelocity()
	{
		return "No actions...";
	}

	void BaseCharacter::AddVelocity(std::string velocity_event)
	{
		//Action.push(action_event);
	}

private:
	BaseCharacter::State _State;
	//BaseCharacter::MorphState _MorphState;
	BaseCharacter::AliveState _AliveState;
	SDL_Rect _Position;
	int _LeftMostPosition;
	int _RightMostPosition;
	int _AnimationFrame;
	std::queue<std::string> Action;

};

extern BaseCharacter BCPlayer;



