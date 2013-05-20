#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "characters.h"


BaseCharacter BCPlayer(0,GROUND_X, GROUND_Y, demonHEIGHT, demonWIDTH);

BaseCharacter::BaseCharacter()
{
	cout << "Constructor BaseCharacter..." << endl;
}

BaseCharacter::BaseCharacter(int surface, int Xpos, int Ypos, int height, int width)
{
	_HealthPoints = 9;
	BaseCharacter::SetAliveState(AliveState::ALIVE);

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
	//demonHunter      = false;

	//LifeFull_Small   = true;
	//LifeMedium_Small = false;
	//LifeLittle_Small = false;

	//demon_Dead       = false;

	//isGettingUp      = false;

	//KickRight        = 5;
	//KickLeft         = 28;
	//WhereWalkLeft    = 24;
	//WhereWalkRight   = 0;
	//WhereJumpLeft    = 35;
	//WhereJumpRight   = 12;
	//PunchRight       = 8; 
	//PunchLeft        = 31;

	//WalkLeft_demon   = 22;
	//WalkRight_demon  = 1;
	//FireBallRight_demon = 9;
	//FireBallLeft_demon = 30;
	//JumpRight_demon  = 5;
	//JumpLeft_demon   = 26;
	//FireBallRight    = 39;
	//FireBallLeft     = 42;
	//Score = 0;

	AlphaImmortal    = SDL_ALPHA_OPAQUE;

	//demon_Life       = 2;

	//TriangleFireLeft = 34;
	//TriangleFireRight = 13;

	//DieRightdemon    = 44;
	//DieLeftdemon     = 40;

	this->Radius = 0;
	this->RadiusFist = 0;
	this->RadiusFeet = 0;
	this->Health = 0;

	Feet_W           = 10;
	Feet_H           = 10;
	Fist_W           = 15;
	Fist_H           = 15;

	BCPlayer.xVelocity = 15.0f;
	_LeftMostPosition = 0;
	_RightMostPosition = 800;
	//this->demon_Height = height;
	//this->demon_Width = width;

	this->Radius = ( demonWIDTHREAL > demonHEIGHTREAL ) ? demonWIDTHREAL / 2 : demonHEIGHTREAL / 2;
	this->RadiusFist  = ( Feet_W > Feet_H ) ? Feet_W / 2 : Feet_H / 2;
	this->RadiusFeet  = ( Fist_W > Fist_H ) ? Fist_W / 2 : Fist_H / 2;
	this->Health = 5;

	//this->xPos = Xpos;
	//this->yPos = Ypos;
	this->_Position.x = Xpos;
	this->_Position.y = Ypos;
	this->_Position.h = 100;
	this->_Position.w = 130;

	this->Surface = surface;

	this->xVelocity = 15.0f; 
	this->yVelocity = 0;
}

// checks if OK to move
bool BaseCharacter::CheckBoundaries()
{
	/*
	Last_Xpos = BCPlayer.xPos;
	float TriangleSpeed = 2500.0f * ( gamestate.DeltaTime / 1000.0f );
	if( BCPlayer.Left )
	{
		if( (BCPlayer.Last_Xpos -= abs( 70 * cos( TriangleSpeed ) ) )  < 20 )
		{
			BCPlayer.TriangleState = 0;
			BCPlayer.Triangle = false;
			return false;
		}
	}
	else
	{
		if( (BCPlayer.Last_Xpos += abs( 70 * cos( TriangleSpeed ) ) )  > 621 )
		{
			if( gamestate.GameCondition == GS_LEVEL1BOSS )
			{
				if( (BCPlayer.Last_Xpos += abs( 70 * cos( TriangleSpeed ) ) )  > 700 )
				{
					BCPlayer.TriangleState = 0;
					BCPlayer.Triangle = false;
					return false;
				}
				return true;
			}
			BCPlayer.TriangleState = 0;
			BCPlayer.Triangle = false;
			return false;
		}
	} 
	*/
	return true;
}

bool BaseCharacter::IsInStateAttack()
{
	if( BCPlayer.isKicking == true || BCPlayer.isPunching == true )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BaseCharacter::Initiatedemon(	int surface, int Xpos, int Ypos, 
							int height, int width )
{
	//this->demon_Height = height;
	//this->demon_Width = width;

	this->Radius = ( demonWIDTHREAL > demonHEIGHTREAL ) ? demonWIDTHREAL / 2 : demonHEIGHTREAL / 2;
	this->RadiusFist  = ( Feet_W > Feet_H ) ? Feet_W / 2 : Feet_H / 2;
	this->RadiusFeet  = ( Fist_W > Fist_H ) ? Fist_W / 2 : Fist_H / 2;

	//this->xPos = Xpos;
	//this->yPos = Ypos;
	this->_Position.x = Xpos;
	this->_Position.y = Ypos;

	this->Surface = surface;

	this->xVelocity = 15.0f;
	this->yVelocity = 0;
}

// updates BCPlayer animations and moving, moved code to Update function
/*
int BCPlayer::Updatedemon()
{
	return 0;
}
*/
float positionX = 0.0f, positionY = 0.0f;     // Position of the character
float velocityX = 0.0f, velocityY = -12.0f;     // Velocity of the character
float gravity = 0.5f;           // How strong is gravity

void Update(float time)
{
    velocityY += gravity * time;        // Apply gravity to vertical velocity
    positionX += velocityX * time;      // Apply horizontal velocity to X position
    positionY += velocityY * time;      // Apply vertical velocity to Y position
}

void BaseCharacter::Update()
{
	if( this->isMovingRight && _Position.x <= _RightMostPosition )
	{
		BaseCharacter::_Position.x += 500.0f * gamestate.DeltaTime;
	}
	else if( this->isMovingLeft && _Position.x >= _LeftMostPosition )
	{
		BaseCharacter::_Position.x -= 500.0f * gamestate.DeltaTime;
	}
	else if( !this->isMovingLeft || !this->isMovingRight || !this->isJumping )
	{
		//BaseCharacter::_Position.x -= 500.0f * gamestate.DeltaTime;
	}

	if( this->isJumping )
	{
		::Update(gamestate.DeltaTime);
		BaseCharacter::_Position.y -= 1;
		if( BaseCharacter::_Position.y < 200 )
		{
			this->isJumping = false;
		}
	}
	if( !this->isJumping )
	{
		if( BaseCharacter::_Position.y < GROUND_Y )
		{
			BaseCharacter::_Position.y += 1;
		}
	}


	if( IDLE == BCPlayer.GetState() )
	{
		//cout << "Character is standing around doing nothing...." << endl;
	}
	if( KICKING == BCPlayer.GetState() )
	{
		//cout << "Character is kicking...." << endl;
		//BCPlayer.SetState(BCPlayer.IDLE);
	}
	if( JUMPING == BCPlayer.GetState() )
	{
		//cout << "Character is jumping...." << endl;
		//BCPlayer.SetState(BCPlayer.IDLE);
	}
	if( PUNCHING == BCPlayer.GetState() )
	{
		//cout << "Character is punching...." << endl;
		//BCPlayer.SetState(BCPlayer.IDLE);
	}
	if( GETTING_UP == BCPlayer.GetState() )
	{
		//cout << "Character is getting up after falling...." << endl;
		//BCPlayer.SetState(BCPlayer.IDLE);
	}
	if( GETTING_HIT == BCPlayer.GetState() )
	{
		//cout << "Character is getting hit by the enemy...." << endl;
		//BCPlayer.SetState(BCPlayer.IDLE);
	}
	// checks which animation to play

	if( this->isKicking )
	{
		isKicking      = true;
		//isJumping      = false;
		isPunching     = false;
	}
	if( this->isPunching )
	{
		isPunching     = true;
		isKicking      = false;
		//isJumping      = false;
	}
	//if( this->isGettingUp )
	//{
	//	// cout << "BCPlayer is getting backup from falling..." << endl;
	//}			
	if( this->isHit )
	{
		// Remove HP from character
		// Alter characters position to indicate a pushback effect
		// Reset isHit flag

		if( BCPlayer.Health > 0 )
		{
			--BCPlayer.Health;
			BCPlayer._Position.x = 0;
		}
		else
		{
			BCPlayer.Died();
		}

		BCPlayer.isHit = false;
		ObjectController.WhichLifeToShow++;

		//if( BCPlayer.Health <= 50 )
		//{
		//	if( ObjectController.WhichLifeToShow >= 6 )
		//	{
		//		ObjectController.WhichLifeToShow = 0;
		//		BCPlayer.SetAliveState(DEAD);	
		//		//BCPlayer.DieOneLife = true;
		//		BCPlayer.isImmortal = true;
		//		//BCPlayer.demon_Dead = true;
		//		gamestate.State = GAME_PLAYER_DIED_STATE;
		//	}
		//}
		/*
		if( BCPlayer::GetLives() == 3 )
		{
			LifeFull_Small = true;
		}
		else if( BCPlayer::GetLives() == 2 )
		{
			LifeFull_Small = false;
			LifeMedium_Small = true;
		}
		else if( BCPlayer::GetLives() == 1 )
		{
			LifeMedium_Small = false;
			LifeLittle_Small = true;
		}
						
		if( BCPlayer::GetLives() <= 0 )
		{
			BCPlayer.demon_Dead = true;
			gamestate.GameCondition = GS_DEAD;
		}
		*/
	}

	
	//if(!BCPlayer.isJumping)
	//{
	//	BCPlayer.yPos = GROUND_Y;
	//	BCPlayer.isJumping = false;
	//}

	//if( BCPlayer.isJumping )
	//{
	//	BCPlayer.JumpingSpeed--;
	//	BCPlayer.JumpingVelocity = 2;
	//	BCPlayer.JumpingGravity = 1;
	//	BCPlayer.yPos -= BCPlayer.JumpingVelocity;
	//	BCPlayer.JumpingVelocity -= BCPlayer.JumpingGravity;

	//	if(BCPlayer.yPos > GROUND_Y)
	//	{
	//		BCPlayer.yPos = GROUND_Y;
	//		BCPlayer.isJumping = false;
	//		BCPlayer.JumpingVelocity = 2;
	//	}
	//}
}


void BaseCharacter::SetClips()
{
	int ArraySizeColumns = sizeof(AnimationArrays) / sizeof(AnimationArrays[0]);
	int ArraySizeRows = sizeof(AnimationArrays[0]) / sizeof(AnimationArrays[0][0]);
	for( int Column = 0; Column < ArraySizeColumns; Column++ )
	{
		for( int Row = 0; Row < ArraySizeRows; Row++ )
		{
			BCPlayer.AnimationArrays[ Column ][ Row ].x = Row * this->_Position.w;//BCPlayer.demon_Width;
			BCPlayer.AnimationArrays[ Column ][ Row ].y = Column * this->_Position.h;//BCPlayer.demon_Height;
			BCPlayer.AnimationArrays[ Column ][ Row ].h = this->_Position.h;//BCPlayer.demon_Height;				  
			BCPlayer.AnimationArrays[ Column ][ Row ].w = this->_Position.w;//BCPlayer.demon_Width;
		}
	}
}


void BaseCharacter::UpdatePosition(float xUnits, float yUnits)
{
	this->_Position.x += xUnits * gamestate.DeltaTime;
	this->_Position.y += xUnits * gamestate.DeltaTime;
	//this->_Position.w = 64;//this->demon_Width;
	//this->_Position.h = 64;//this->demon_Height;

	this->_Position.x += xUnits * gamestate.DeltaTime;
	this->_Position.y += yUnits * gamestate.DeltaTime;

	
	if( this->_Position.x < 0.0f )
	{
		// Bumps the character to the right a bit if the BCPlayer isn't moving and to far to the left
		this->_Position.x += 100.0f * gamestate.DeltaTime;
	}
	else
	{
		if( !this->isMovingLeft || !this->isMovingRight || !this->isJumping )
		{
			// Makes the character follow the parallax scrolling speed to make it look like he is standing still
			this->_Position.x -= 2.0f * gamestate.DeltaTime;
		}
	}
					this->_Position.y = 0;
}

/*
void BCPlayer::SetLives(int Lives)
{
	_Lives = Lives;
}


int BCPlayer::GetLives()
{
	return _Lives;
}
*/

void BaseCharacter::Reset()
{
	this->isMovingRight = false;
	this->isMovingLeft = false;
	this->isJumping = false;
	this->isKicking = false;
	this->isPunching = false;
	this->isImmortal = false;
	this->isHit = false;
	this->AlphaImmortal = SDL_ALPHA_OPAQUE;
	this->Radius = 0;
	this->RadiusFist = 0;
	this->RadiusFeet = 0;
	this->Health = 5;

	this->Feet_W = 10;
	this->Feet_H = 10;
	this->Fist_W = 15;
	this->Fist_H = 15;
}

void BaseCharacter::Died()
{
	gamestate.RestartGame();

	SDL_Event input;

	while( gamestate.State == GAME_PLAYER_DIED_STATE )
	{
		SDL_PollEvent( &input );
		if( input.type == SDL_KEYDOWN )
		{
  			switch( input.key.keysym.sym )
			{
			case SDLK_SPACE:
				gamestate.State = MENU_MAIN_STATE;
				break;
			}
		}
		Gfx.DrawBackgroundBlack();
		SDL_BlitSurface( Gfx.GetSurface( gamestate.m_srfOutro ), &Gfx.screen->clip_rect, Gfx.BackBuffer, &Gfx.screen->clip_rect );
		Gfx.srfText = TTF_RenderText_Shaded( Gfx.DefaultFont, " Press Space For Menu ", Gfx.WhiteRGB, Gfx.BlackRGB );
		Gfx.apply_surface( 250, 500, Gfx.srfText, Gfx.BackBuffer );
		//Gfx.FLIP();
	}
}
