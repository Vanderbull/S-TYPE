#include <SDL.h>
#include <SDL_image.h>
#include "characters.h"
#include "Game.h"
#include <cmath>
#include "Audio.h"

Demon demon(0,GROUND_X, GROUND_Y, DEMONHEIGHT, DEMONWIDTH);

Demon::Demon()
{
	// Not used
}

Demon::Demon(int surface, int Xpos, int Ypos, int height, int width)
{
	Demon::SetAliveState(AliveState::ALIVE);
	//Demon::SetLives(3);

	isMovingRight    = false;
	isMovingLeft     = false;
	isJumping        = false;
	isKicking        = false;
	isPunching       = false;
	isImmortal       = false;

	isHit            = false; 
	//DieOneLife       = false;

	//SmallHunter      = true;
	//MediumHunter     = false;
	//LargeHunter      = false;
	//DemonHunter      = false;

	LifeFull_Small   = true;
	LifeMedium_Small = false;
	LifeLittle_Small = false;

	//Demon_Dead       = false;

	isGettingUp      = false;

	//KickRight        = 5;
	//KickLeft         = 28;
	//WhereWalkLeft    = 24;
	//WhereWalkRight   = 0;
	//WhereJumpLeft    = 35;
	//WhereJumpRight   = 12;
	//PunchRight       = 8; 
	//PunchLeft        = 31;

	//WalkLeft_Demon   = 22;
	//WalkRight_Demon  = 1;
	//FireBallRight_Demon = 9;
	//FireBallLeft_Demon = 30;
	//JumpRight_Demon  = 5;
	//JumpLeft_Demon   = 26;
	//FireBallRight    = 39;
	//FireBallLeft     = 42;
	//Score = 0;

	AlphaImmortal    = SDL_ALPHA_OPAQUE;

	//Demon_Life       = 2;

	//TriangleFireLeft = 34;
	//TriangleFireRight = 13;

	//DieRightDemon    = 44;
	//DieLeftDemon     = 40;

	Radius           = 0;
	RadiusFist       = 0;
	RadiusFeet       = 0;
	DemonHealth     = 100;

	Feet_W           = 10;
	Feet_H           = 10;
	Fist_W           = 15;
	Fist_H           = 15;

	demon.xVelocity = 15.0f;
	_LeftMostPosition = 0;
	_RightMostPosition = 800;
	//this->Demon_Height = height;
	//this->Demon_Width = width;

	this->Radius = ( DEMONWIDTHREAL > DEMONHEIGHTREAL ) ? DEMONWIDTHREAL / 2 : DEMONHEIGHTREAL / 2;
	this->RadiusFist  = ( Feet_W > Feet_H ) ? Feet_W / 2 : Feet_H / 2;
	this->RadiusFeet  = ( Fist_W > Fist_H ) ? Fist_W / 2 : Fist_H / 2;

	//this->xPos = Xpos;
	//this->yPos = Ypos;
	this->_Position.x = Xpos;
	this->_Position.y = Ypos;
	this->_Position.h = 100;
	this->_Position.w = 130;

	this->DemonSurface = surface;

	this->xVelocity = 15.0f; 
	this->yVelocity = 0;
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
	{
		return false;
	}
}

void Demon::InitiateDemon(	int surface, int Xpos, int Ypos, 
							int height, int width )
{
	//this->Demon_Height = height;
	//this->Demon_Width = width;

	this->Radius = ( DEMONWIDTHREAL > DEMONHEIGHTREAL ) ? DEMONWIDTHREAL / 2 : DEMONHEIGHTREAL / 2;
	this->RadiusFist  = ( Feet_W > Feet_H ) ? Feet_W / 2 : Feet_H / 2;
	this->RadiusFeet  = ( Fist_W > Fist_H ) ? Fist_W / 2 : Fist_H / 2;

	//this->xPos = Xpos;
	//this->yPos = Ypos;
	this->_Position.x = Xpos;
	this->_Position.y = Ypos;

	this->DemonSurface = surface;

	this->xVelocity = 15.0f;
	this->yVelocity = 0;
}

// updates player animations and moving, moved code to Update function
/*
int Demon::UpdatePlayer()
{
	return 0;
}
*/

void Demon::Update()
{
	//Demon::_Position.y = GROUND_Y;
	if( this->isMovingRight && _Position.x <= _RightMostPosition )
		Demon::_Position.x += 500.0f * gamestate.dt;
	if( this->isMovingLeft && _Position.x >= _LeftMostPosition )
		Demon::_Position.x -= 500.0f * gamestate.dt;
	if( this->isJumping )
		Demon::_Position.y -= 10.0f * gamestate.dt;
	else if( Demon::_Position.y < GROUND_Y )
	{
		Demon::_Position.y += 5.0f;
	}
	else
	{
		Demon::_Position.y = GROUND_Y;
	}
	//Demon::_Position.w = 64; //Demon::Demon_Width;
	//Demon::_Position.h = 64;//Demon::Demon_Height;

	//float JumpSpeed = 2500.0f;

	//float speed = 2500.0f * ( gamestate.dt / 1000.0f );
	//float speedJump = 2500.0f * ( gamestate.dt / 1000.0f );
	//float speedJumpDemon = 800.0f * ( gamestate.dt / 1000.0f );
	//float TriangleSpeed = 2500.0f * ( gamestate.dt / 1000.0f );

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

	if( this->isKicking )
	{
		isKicking      = true;
		isJumping      = false;
		isPunching     = false;
	}
	if( this->isJumping )
	{
		isKicking      = false;
		isJumping      = true;
		isPunching     = false;
	}
	if( this->isPunching )
	{
		isPunching     = true;
		isKicking      = false;
		isJumping      = false;
	}
	if( this->isGettingUp )
	{
		// cout << "demon is getting backup from falling..." << endl;
	}			
	if( this->isHit )
	{
		//demon.Demon_Life--;
		Audio.PlaySoundEffect( SOUND_GETS_HIT );
		demon.isHit = false;
		Control_OBJ.WhichLifeToShow++;

		if( demon.DemonHealth <= 50 )
		{
			if( Control_OBJ.WhichLifeToShow >= 6 )
			{
				Control_OBJ.WhichLifeToShow = 0;
				demon.SetAliveState(DEAD);	
				//demon.DieOneLife = true;
				demon.isImmortal = true;
				//demon.Demon_Dead = true;
				gamestate.GameCondition = GS_DEAD;
			}
		}
		/*
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
		*/
	}

	/*
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

		if(demon.yPos > GROUND_Y)
		{
			demon.yPos = GROUND_Y;
			demon.isJumping = false;
			demon.JumpingVelocity = 2;
		}
	}
	*/
}


void Demon::SetClips()
{
	int ArraySizeColumns = sizeof(AnimationArrays) / sizeof(AnimationArrays[0]);
	int ArraySizeRows = sizeof(AnimationArrays[0]) / sizeof(AnimationArrays[0][0]);
	for( int Column = 0; Column < ArraySizeColumns; Column++ )
	{
		for( int Row = 0; Row < ArraySizeRows; Row++ )
		{
			demon.AnimationArrays[ Column ][ Row ].x = Row * this->_Position.w;//demon.Demon_Width;
			demon.AnimationArrays[ Column ][ Row ].y = Column * this->_Position.h;//demon.Demon_Height;
			demon.AnimationArrays[ Column ][ Row ].h = this->_Position.h;//demon.Demon_Height;
			demon.AnimationArrays[ Column ][ Row ].w = this->_Position.w;//demon.Demon_Width;
		}
	}
}


void Demon::UpdatePosition(float xUnits, float yUnits)
{
	this->_Position.x += xUnits * gamestate.dt;
	this->_Position.y += xUnits * gamestate.dt;
	//this->_Position.w = 64;//this->Demon_Width;
	//this->_Position.h = 64;//this->Demon_Height;

	this->_Position.x += xUnits * gamestate.dt;
	this->_Position.y += yUnits * gamestate.dt;

	
	if( this->_Position.x < 0.0f )
	{
		// Bumps the character to the right a bit if the player isn't moving and to far to the left
		this->_Position.x += 100.0f * gamestate.dt;
	}
	else
	{
		// Makes the character follow the parallax scrolling speed to make it look like he is standing still
		this->_Position.x -= 2.0f * gamestate.dt;
	}
}

/*
void Demon::SetLives(int Lives)
{
	_Lives = Lives;
}


int Demon::GetLives()
{
	return _Lives;
}
*/
