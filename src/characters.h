#pragma once

#include<queue>
#include <SDL.h>
#include <SDL_image.h>

class BaseCharacterInterface
{
public:
	int _Surface;
	int _Lives;
	int _AlphaImmortal;
	SDL_Rect CollisionBox;

	virtual void Update()=0;
	virtual void SetClips()=0;
	virtual std::string GetAction()=0;
	virtual void AddAction(std::string action_event)=0;
	virtual std::string GetVelocity()=0;
	virtual void AddVelocity(std::string velocity_event)=0;
	virtual std::string GetBeam()=0;
	virtual void AddBeam(std::string beam_event)=0;
	virtual SDL_Rect GetCollisionBox()=0;
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
	};

	enum AliveState
	{
		DEAD,
		IMMORTAL,
		ALIVE
	};

	BaseCharacter();
	BaseCharacter(int surface, int Xpos, int Ypos, int height, int width);
	void Reset();
	void Died();

	bool IsAttacking();
	bool CheckBoundaries();
	bool isHit;

	//int Feet_W, Feet_H, Fist_W, Fist_H;

	//int Radius, RadiusFist, RadiusFeet;

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
		if( _AnimationFrame > 6 )
			_AnimationFrame = 0;
		if(TimeLeft() == 0 )
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

	std::string BaseCharacter::GetBeam()
	{
		if( !Beam.empty() )
		{
			std::string returnBeam = Beam.front();
			Beam.pop();
			return returnBeam;
		}
		else
		{
			return "No beam...";
		}
	}

	void BaseCharacter::AddBeam(std::string beam_event)
	{
		//Action.push(action_event);
	}
	SDL_Rect BaseCharacter::GetCollisionBox()
	{
		return CollisionBox;
	}

private:
	BaseCharacter::State _State;
	BaseCharacter::AliveState _AliveState;
	SDL_Rect _Position;
	int _AnimationFrame;
	std::queue<std::string> Action;
	std::queue<std::string> Beam;

};

extern BaseCharacter BCPlayer;



