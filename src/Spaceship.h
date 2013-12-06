#pragma once

#include <queue>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class SpaceshipInterface
{
public:
	int _SurfaceID;
	int _Speed;
	int _Acceleration;
	int _Scale;

	SDL_Rect _Velocity;
	SDL_Rect CollisionBox;
	
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