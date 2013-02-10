#include <SDL.h>
#include <SDL_image.h>
#include "characters.h"
#include "Game.h"
#include <cmath>
#include "Audio.h"

// @date 2012-08-07

Demon demon(0,GROUND_X, GROUND_Y, DEMONHEIGHT, DEMONWIDTH);

Demon::Demon()
{
	Demon::SetAliveState(AliveState::ALIVE);
	Demon::SetLives(3);

	isMovingRight    = false;
	isMovingLeft     = false;
	isJumping        = false;
	isKicking        = false;
	isPunching       = false;
	isImmortal       = false;

	isHit            = false; 
	DieOneLife       = false;

	SmallHunter      = true;
	MediumHunter     = false;
	LargeHunter      = false;
	DemonHunter      = false;

	LifeFull_Small   = true;
	LifeMedium_Small = false;
	LifeLittle_Small = false;

	Demon_Dead       = false;

	isGettingUp      = false;

	KickRight        = 5;
	KickLeft         = 28;
	WhereWalkLeft    = 24;
	WhereWalkRight   = 0;
	WhereJumpLeft    = 35;
	WhereJumpRight   = 12;
	PunchRight       = 8; 
	PunchLeft        = 31;

	WalkLeft_Demon   = 22;
	WalkRight_Demon  = 1;
	FireBallRight_Demon = 9;
	FireBallLeft_Demon = 30;
	JumpRight_Demon  = 5;
	JumpLeft_Demon   = 26;
	FireBallRight    = 39;
	FireBallLeft     = 42;
	Score = 0;

	AlphaImmortal    = SDL_ALPHA_OPAQUE;

	Demon_Life       = 2;
	LengthOfTriangle = 0;

	TriangleFireLeft = 34;
	TriangleFireRight = 13;

	DieRightDemon    = 44;
	DieLeftDemon     = 40;

	DieState         = 0;

	Radius           = 0;
	RadiusFist       = 0;
	RadiusFeet       = 0;
	Demon_Health     = 100;

	Feet_W           = 10;
	Feet_H           = 10;
	Fist_W           = 15;
	Fist_H           = 15;

	WhereIsEnd       = 0;
	LastEnd_Pos      = 0;

	demon.xVelocity = 15.0f;
}

Demon::Demon(int surface, int Xpos, int Ypos, int height, int width)
{
	demon.Demon_Height = height;
	demon.Demon_Width = width;

	demon.Radius = ( DEMONWIDTHREAL > DEMONHEIGHTREAL ) ? DEMONWIDTHREAL / 2 : DEMONHEIGHTREAL / 2;
	RadiusFist  = ( Feet_W > Feet_H ) ? Feet_W / 2 : Feet_H / 2;
	RadiusFeet  = ( Fist_W > Fist_H ) ? Fist_W / 2 : Fist_H / 2;

	demon.xPos = Xpos;
	demon.yPos = Ypos;

	demon.DemonSurface = surface;

	demon.xVelocity = 15.0f; 
	demon.yVelocity = 0;
}

//What is end position and what is it used for???
void Demon::UpdateEndPosition()
{
	//demon.WhereIsEnd += demon.xPosHotSpot - LastEnd_Pos;
	//LastEnd_Pos = demon.xPosHotSpot;
	demon.WhereIsEnd += gamestate.LevelProgress - LastEnd_Pos;
	LastEnd_Pos = gamestate.LevelProgress;
}

// checks if OK to move
bool Demon::CheckBoundaries()
{
	/*
	Last_Xpos = demon.xPos;
	float TriangleSpeed = 2500.0f * ( gamestate.dt / 1000.0f );
	if( demon.Left )
	{
		if( (demon.Last_Xpos -= abs( 70 * cos( TriangleSpeed ) ) )  < 20 )
		{
			demon.TriangleState = 0;
			demon.Triangle = false;
			return false;
		}
	}
	else
	{
		if( (demon.Last_Xpos += abs( 70 * cos( TriangleSpeed ) ) )  > 621 )
		{
			if( gamestate.GameCondition == GS_LEVEL1BOSS )
			{
				if( (demon.Last_Xpos += abs( 70 * cos( TriangleSpeed ) ) )  > 700 )
				{
					demon.TriangleState = 0;
					demon.Triangle = false;
					return false;
				}
				return true;
			}
			demon.TriangleState = 0;
			demon.Triangle = false;
			return false;
		}
	} 
	*/
	return true;
}

bool Demon::IsInStateAttack()
{
	if( demon.isKicking == true || demon.isPunching == true )
	{
		return true;
	}
	else
		return false;
}

void Demon::InitiateDemon(	int surface, int Xpos, int Ypos, 
							int height, int width )
{
	demon.Demon_Height = height;
	demon.Demon_Width = width;

	demon.Radius = ( DEMONWIDTHREAL > DEMONHEIGHTREAL ) ? DEMONWIDTHREAL / 2 : DEMONHEIGHTREAL / 2;
	RadiusFist  = ( Feet_W > Feet_H ) ? Feet_W / 2 : Feet_H / 2;
	RadiusFeet  = ( Fist_W > Fist_H ) ? Fist_W / 2 : Fist_H / 2;

	demon.xPos = Xpos;
	demon.yPos = Ypos;

	demon.DemonSurface = surface;

	demon.xVelocity = 15.0f;
	demon.yVelocity = 0;
}

// updates player animations and moving
int Demon::UpdatePlayer()
{
	float JumpSpeed = 2500.0f;

	float speed = 2500.0f * ( gamestate.dt / 1000.0f );
	float speedJump = 2500.0f * ( gamestate.dt / 1000.0f );
	float speedJumpDemon = 800.0f * ( gamestate.dt / 1000.0f );
	float TriangleSpeed = 2500.0f * ( gamestate.dt / 1000.0f );

	if( IDLE == demon.GetState() )
	{
		//cout << "Character is standing around doing nothing...." << endl;
	}
	if( KICKING == demon.GetState() )
	{
		//cout << "Character is kicking...." << endl;
		//demon.SetState(demon.IDLE);
	}
	if( JUMPING == demon.GetState() )
	{
		//cout << "Character is jumping...." << endl;
		//demon.SetState(demon.IDLE);
	}
	if( PUNCHING == demon.GetState() )
	{
		//cout << "Character is punching...." << endl;
		//demon.SetState(demon.IDLE);
	}
	if( GETTING_UP == demon.GetState() )
	{
		//cout << "Character is getting up after falling...." << endl;
		//demon.SetState(demon.IDLE);
	}
	if( GETTING_HIT == demon.GetState() )
	{
		//cout << "Character is getting hit by the enemy...." << endl;
		//demon.SetState(demon.IDLE);
	}
	// checks which animation to play

	if( isKicking )
	{
		isKicking      = true;
		isJumping      = false;
		isPunching     = false;
	}
	if( isJumping )
	{
		isKicking      = false;
		isJumping      = true;
		isPunching     = false;
	}
	if( isPunching )
	{
		isPunching     = true;
		isKicking      = false;
		isJumping      = false;
	}

	if( demon.isGettingUp )
	{
		// cout << "demon is getting backup from falling..." << endl;
	}

	if( demon.isHit )
	{
		demon.Demon_Life--;
		Audio.PlaySoundEffect( SOUND_GETS_HIT );
		demon.isHit = false;

		if( demon.Demon_Health <= 50 )
		{
			Control_OBJ.WhichLifeToShow++;

			if( Control_OBJ.WhichLifeToShow >= 6 )
			{
				Control_OBJ.WhichLifeToShow = 0;
				demon.Died();	
				demon.DieOneLife = true;
				demon.isImmortal = true;
			}
		}	
		if( Demon::GetLives() == 3 )
		{
			LifeFull_Small = true;
		}
		else if( Demon::GetLives() == 2 )
		{
			LifeFull_Small = false;
			LifeMedium_Small = true;
		}
		else if( Demon::GetLives() == 1 )
		{
			LifeMedium_Small = false;
			LifeLittle_Small = true;
		}
						
		if( Demon::GetLives() <= 0 )
		{
			demon.Demon_Dead = true;
			gamestate.GameCondition = GS_DEAD;
		}
	}

	if(!demon.isJumping)
	{
		demon.yPos = GROUND_Y;
		demon.isJumping = false;
	}

	if( demon.isJumping )
	{
		demon.JumpingSpeed--;
		demon.JumpingVelocity = 2;
		demon.JumpingGravity = 1;
		demon.yPos -= demon.JumpingVelocity;
		demon.JumpingVelocity -= demon.JumpingGravity;

		if(demon.yPos > 400)
		{
			demon.yPos = 400;
			demon.isJumping = false;
			demon.JumpingVelocity = 2;
		}
	}

	if( demon.isMovingRight )
	{
		if( demon.xPos < 600.0f )
		{
			demon.xPos += demon.xVelocity;
		}
	}

	if( demon.isMovingLeft )
	{
		// Character maximum distance to the left edge of the screen
		if( demon.xPos > 15.0f )
		{
			demon.xPos -= demon.xVelocity;
		}				
	}

	return 0;
}

void Demon::Set_clips()
{
	for( int i = 0; i < 9; i++ )
	{
		for( int j = 0; j < 48; j++ )
		{
			demon.AnimationArrays[ i ][ j ].x = j * demon.Demon_Width;
			demon.AnimationArrays[ i ][ j ].y = i * demon.Demon_Height;
			demon.AnimationArrays[ i ][ j ].h = demon.Demon_Height;
			demon.AnimationArrays[ i ][ j ].w = demon.Demon_Width;
		}
	}
}

void Demon::Update()
{
}

void Demon::SetClips()
{
	int ArraySize = sizeof(AnimationArrays) / sizeof(AnimationArrays[0]);
	for( int i = 0; i < ArraySize; i++ )
	{
	}
}

void Demon::UpdatePosition(float xUnits, float yUnits)
{
	Demon::_Position.x += xUnits;
	Demon::_Position.y += yUnits;
	Demon::_Position.w = Demon::Demon_Width;
	Demon::_Position.h = Demon::Demon_Height;

	Demon::_Position.x = xPos += xUnits;
	Demon::_Position.y = yPos += yUnits;

	
	if( xPos < 0.0f )
	{
		// Bumps the character to the right a bit if the player isn't moving and to far to the left
		xPos += 10.0f;
	}
	else
	{
		// Makes the character follow the parallax scrolling speed to make it look like he is standing still
		xPos -= 2.0f;
	}
}

bool Demon::Alive()
{
	return true;
}

void Demon::SetLives(int Lives)
{
	_Lives = Lives;
}

int Demon::GetLives()
{
	return _Lives;
}

void Demon::Died()
{
	if( _Lives > 0 )
	{
		_Lives--;
	}
	else
	{
		//Change gamestate to Outro
	}
}
