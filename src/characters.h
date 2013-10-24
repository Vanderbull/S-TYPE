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
	virtual int isColliding( SDL_Rect CollisionObject )=0;
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

	int BaseCharacter::isColliding( SDL_Rect CollisionObject )
	{
		int PlayerRight = GetPosition().x + GetPosition().w;
		int PlayerLeft = GetPosition().x;
		int PlayerTop = GetPosition().y;
		int PlayerBottom = GetPosition().x + GetPosition().h;

		int CollisionObjectRight = CollisionObject.x + CollisionObject.w;
		int CollisionObjectLeft = CollisionObject.x;
		int CollisionObjectTop = CollisionObject.y;
		int CollisionObjectBottom = CollisionObject.y + CollisionObject.h;

		if (CollisionObjectBottom < PlayerTop) return(0);
		if (CollisionObjectTop > PlayerBottom) return(0);
  
		if (CollisionObjectRight < PlayerLeft) return(0);
		if (CollisionObjectLeft > PlayerRight) return(0);

		return(1);
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



