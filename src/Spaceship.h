#pragma once

#include <queue>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class SpaceshipInterface
{
public:
	Sint16 _Lives;
	Sint16 _SurfaceID;
	Sint16 _Speed;
	Sint16 _Acceleration;
	Sint16 _Scale;

	SDL_Rect _Velocity;
	SDL_Rect _CollisionBox;
	
	int CalculateVelocity()
	{
		_Velocity.x = _Speed + _Scale;
		_Velocity.y = _Speed + _Scale;

	};
	virtual void Update() = 0;
	virtual void SetClips() = 0;
	virtual std::string GetAction() = 0;
	virtual void AddAction(std::string action_event) = 0;
	virtual std::string GetVelocity() = 0;
	virtual void AddVelocity(std::string velocity_event) = 0;
	virtual std::string GetBeam() = 0;
	virtual void AddBeam(std::string beam_event) = 0;
	virtual SDL_Rect GetCollisionBox() = 0;
	virtual int isColliding( SDL_Rect CollisionObject ) = 0;
};

class BaseSpaceShip : public SpaceshipInterface
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

	BaseSpaceShip();
	BaseSpaceShip(int surface, int Xpos, int Ypos, int height, int width);
	void Reset();
	void Died();

	bool IsAttacking();
	bool CheckBoundaries();
	bool isHit;

	float xVelocity, yVelocity;

	SDL_Rect AnimationArrays[ 9 ][ 48 ];

#define TICK_INTERVAL    125

	Uint32 TimeLeft(void);

	int Animate();

	SDL_Rect GetPosition()
	{
		return BaseSpaceShip::_Position;
	}

	void Update();
	void SetClips();
	void UpdatePosition(float x, float y); 
	void SetState( BaseSpaceShip::State state )
	{
		_State = state;
	}
	BaseSpaceShip::State GetState() const
	{
	   return _State;
	}

	void SetAliveState( BaseSpaceShip::AliveState state )
	{
		_AliveState = state;
	}
	BaseSpaceShip::AliveState GetAliveState() const
	{
	   return _AliveState;
	}

	std::string BaseSpaceShip::GetAction()
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

	void BaseSpaceShip::AddAction(std::string action_event)
	{
		//Action.push(action_event);
	}

	std::string BaseSpaceShip::GetVelocity()
	{
		return "No actions...";
	}

	void BaseSpaceShip::AddVelocity(std::string velocity_event)
	{
		//Action.push(action_event);
	}

	std::string BaseSpaceShip::GetBeam()
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

	void BaseSpaceShip::AddBeam(std::string beam_event)
	{
		//Action.push(action_event);
	}

	void BaseSpaceShip::SetCollisionBox(Sint16 x, Sint16 y, Sint16 h, Sint16 w)
	{
		_CollisionBox.x = x;
		_CollisionBox.y = y;
		_CollisionBox.h = h;
		_CollisionBox.w = w;
	}

	SDL_Rect BaseSpaceShip::GetCollisionBox()
	{
		return _CollisionBox;
	}

	int BaseSpaceShip::isColliding( SDL_Rect CollisionObject )
	{
		Sint16 PlayerRight = GetPosition().x + GetPosition().w;
		Sint16 PlayerLeft = GetPosition().x;
		Sint16 PlayerTop = GetPosition().y;
		Sint16 PlayerBottom = GetPosition().x + GetPosition().h;

		Sint16 CollisionObjectRight = CollisionObject.x + CollisionObject.w;
		Sint16 CollisionObjectLeft = CollisionObject.x;
		Sint16 CollisionObjectTop = CollisionObject.y;
		Sint16 CollisionObjectBottom = CollisionObject.y + CollisionObject.h;

		if (CollisionObjectBottom < PlayerTop) return(0);
		if (CollisionObjectTop > PlayerBottom) return(0);
  
		if (CollisionObjectRight < PlayerLeft) return(0);
		if (CollisionObjectLeft > PlayerRight) return(0);

		return(1);
	}

private:
	BaseSpaceShip::State _State;
	BaseSpaceShip::AliveState _AliveState;
	SDL_Rect _Position;
	int _AnimationFrame;
	std::queue<std::string> Action;
	std::queue<std::string> Beam;
};

extern BaseSpaceShip BCSpaceShip;