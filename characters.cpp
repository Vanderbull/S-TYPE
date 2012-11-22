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
	isMovingRight    = false;
	isMovingLeft     = false;
	isJumping        = false;
	isCrouching      = false;
	isKicking        = false;
	isPunching       = false;
	CrouchFireBall   = false;
	Right            = false;
	Left             = false;
	isImmortal         = false;

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

	//Crouch           = false;
	//Kick             = false; 
	//Jump             = false;
	//Punch            = false;
	FireBall         = false;
	CrouchFire       = false;
	TriangleAttack   = false;
	Triangle         = false;
	isGettingUp      = false;

	KickRight        = 5;
	KickLeft         = 28;
	WhereWalkLeft    = 24;
	WhereWalkRight   = 0;
	WhereJumpLeft    = 35;
	WhereJumpRight   = 12;
	CrouchRight      = 19;
	CrouchLeft       = 41;
	PunchRight       = 8; 
	PunchLeft        = 31;

	WalkLeft_Demon   = 22;
	WalkRight_Demon  = 1;
	FireBallRight_Demon = 9;
	FireBallLeft_Demon = 30;
	JumpRight_Demon  = 5;
	JumpLeft_Demon   = 26;
	CrouchRightFire  = 14;
	CrouchLeftFire   = 35;
	FireBallRight    = 39;
	FireBallLeft     = 42;

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

	TriangleState    = 0;
	//xPosHotSpot      = 0;
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

	xVelocity = 0;
	yVelocity = 0;
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
	if( demon.isKicking == true || demon.isPunching == true ||
		demon.CrouchFireBall == true || demon.TriangleAttack == true || demon.Triangle == true)
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

	xVelocity = 0;
	yVelocity = 0;
}

// updates player animations and moving
int Demon::UpdatePlayer()
{
	float JumpSpeed = 10.0f;

	float speed = 2500.0f * ( gamestate.dt / 1000.0f );
	float speedJump = 2500.0f * ( gamestate.dt / 1000.0f );
	float speedJumpDemon = 800.0f * ( gamestate.dt / 1000.0f );
	float TriangleSpeed = 2500.0f * ( gamestate.dt / 1000.0f );

	if( IDLE == demon.GetState() )
	{
		cout << "Character is standing around doing nothing...." << endl;
	}
	if( CROUCHING == demon.GetState() )
	{
		cout << "Character is crouching...." << endl;
		demon.SetState(demon.IDLE);
	}
	if( KICKING == demon.GetState() )
	{
		cout << "Character is kicking...." << endl;
		demon.SetState(demon.IDLE);
	}
	if( JUMPING == demon.GetState() )
	{
		cout << "Character is jumping...." << endl;
		demon.SetState(demon.IDLE);
	}
	if( PUNCHING == demon.GetState() )
	{
		cout << "Character is punching...." << endl;
		demon.SetState(demon.IDLE);
	}
	if( GETTING_UP == demon.GetState() )
	{
		cout << "Character is getting up after falling...." << endl;
		demon.SetState(demon.IDLE);
		if( demon.Right )
		{
			return 46;
		}
		else
		{
			return 43;
		}
	}
	if( GETTING_HIT == demon.GetState() )
	{
		cout << "Character is getting hit by the enemy...." << endl;
		demon.SetState(demon.IDLE);
	}
	// checks which animation to play
	if( isCrouching )
	{
		isKicking      = false;
		isJumping      = false;
		//isCrouching    = true;
		isPunching     = false;
		CrouchFireBall = false;
		TriangleAttack = false;
	}

	else if( isKicking )
	{
		//isKicking      = true;
		isJumping      = false;
		isCrouching    = false;
		isPunching     = false;
		CrouchFireBall = false;
		TriangleAttack = false;
	}

	else if( isJumping )
	{
		isKicking      = false;
		//isJumping      = true;
		isCrouching    = false;
		isPunching     = false;
		CrouchFireBall = false;
		TriangleAttack = false;
	}
	else if( isPunching )
	{
		//isPunching     = true;
		isKicking      = false;
		isJumping      = false;
		isCrouching    = false;
		CrouchFireBall = false;
		TriangleAttack = false;
	}
	else if( FireBall )
	{
		isPunching     = false;
		isKicking      = true;
		isJumping      = false;
		isCrouching    = false;
		CrouchFireBall = false;
  		TriangleAttack = false;
	}
	else if( CrouchFire )
	{
		isJumping      = false;
		isKicking      = true;
		isJumping      = false;
		isCrouching    = true;
		TriangleAttack = false;
	}
	else if( Triangle )
	{
		isPunching     = false;
		isKicking      = false;
		isJumping      = false;
		isCrouching    = false;
		CrouchFireBall = false;
		TriangleAttack = true;
	}

	if( demon.isGettingUp )
	{
		demon.isGettingUp = false;

		if( demon.Right )
		{
			return 46;
		}
		else
		{
			return 43;
		}
	}

	if( demon.isHit )
	{
		if( demon.Demon_Health <= 50 )
		{
			Control_OBJ.WhichLifeToShow++;
			demon.Demon_Health = 100;

			if( Control_OBJ.WhichLifeToShow >= 6 )
			{
				Control_OBJ.WhichLifeToShow = 0;
				demon.Demon_Life--;
				demon.DieOneLife = true;
				demon.isImmortal = true;
			}
		}

		demon.isHit = false;
	
		if( Demon_Life == 2 )
		{
			LifeFull_Small = true;
		}
		else if( Demon_Life == 1 )
		{
			LifeFull_Small = false;
			LifeMedium_Small = true;
		}
		else if( Demon_Life == 0 )
		{
			LifeMedium_Small = false;
			LifeLittle_Small = true;
		}
						
		if( Demon_Life <= -1 )
		{
			demon.Demon_Dead = true;
			gamestate.GameCondition = GS_DEAD;
		}
	
		if( demon.SmallHunter )
		{
			//Nothing
		}
		else
		{
			Audio.PlaySoundEffect( SOUND_GETS_HIT );

			if( Right )
			{
				if( demon.xVelocity - speed <= gamestate.SCREEN_WIDTH - gamestate.SCREEN_WIDTH + 50 )
				{
					
				}
				else
				{
					demon.xPos -= speed + 20.0f;
					demon.xVelocity -= speed + 20.0f;
					//xPosHotSpot--;
				}
				return 43;
			}
			else
			{
				if( demon.xVelocity >= STARTSCROLLING )
				{

				}
				else
				{
					demon.xPos += speed + 20.0f;
					demon.xVelocity += speed + 20.0f;
					//xPosHotSpot++;
					
				}
				return 39;
			}
		}
	}

	if( demon.DieOneLife )
	{
		if( demon.SmallHunter )
		{
			demon.DieOneLife = false;
		}
		else
		{

			if( Right )
			{	
				switch( demon.DieState )
				{
				case 0:
					{
						if( demon.xVelocity <= gamestate.SCREEN_WIDTH - gamestate.SCREEN_WIDTH + 50 )
						{
							//demon.xPosHotSpot--;
							demon.xPos = 51;
							demon.xVelocity = 51;
						}
						else
						{
							//demon.yPos -= abs( 16 * cos( speedJumpDemon ) );
							demon.xPos -= abs( 16 * cos( speedJumpDemon ) );
							demon.xVelocity -= abs( 16 * cos( speedJumpDemon ) );
							//demon.xPosHotSpot--;

							if( demon.yPos < GROUND_Y - 50 )
							{
								demon.DieState = 1;
							}
							
						}
						break;
					}
				case 1:
					{
						if( demon.xVelocity <= gamestate.SCREEN_WIDTH - gamestate.SCREEN_WIDTH + 50 )
						{
							//demon.xPosHotSpot--;
							demon.xPos = 51;
							demon.xVelocity = 51;
						}
						else
						{
							//demon.yPos += abs( 15 * cos( speedJumpDemon ) );
							demon.xPos -= abs( 10 * cos( speedJumpDemon ) );
							demon.xVelocity -= abs( 10 * cos( speedJumpDemon ) );
							//demon.xPosHotSpot--;
		
							if( demon.yPos > GROUND_Y )
							{
								demon.yPos = GROUND_Y;
								demon.DieRightDemon++;
								demon.DieState = 2;
							}
						}
						break;
					}
				case 2:
					{
						
						demon.DieRightDemon++;
						demon.DieOneLife = false;
						demon.DieState = 0;	
						demon.isGettingUp = true;
						break;
					}
				}

				if( demon.DieRightDemon == 46 )
				{
					demon.DieRightDemon = 44;
				}

				return demon.DieRightDemon;
			}
			else
			{
				switch( demon.DieState )
				{
				case 0:
					{
						if( demon.xVelocity + abs( 10 * cos( speedJumpDemon ) ) >= gamestate.SCREEN_WIDTH - 50 )
						{
							//demon.xPosHotSpot++;
						}
						else
						{
							demon.yPos -= abs( 15 * cos( speedJumpDemon ) );
							demon.xPos += abs( 10 * cos( speedJumpDemon ) );
							demon.xVelocity += abs( 10 * cos( speedJumpDemon ) );
							//demon.xPosHotSpot++;

							if( demon.yPos < GROUND_Y - 50 )
							{
								demon.DieState = 1;
							}
						}
						break;
					}
				case 1:
					{
						if( demon.xVelocity + abs( 5 * cos( speedJumpDemon ) ) >= gamestate.SCREEN_WIDTH - 50 )
						{
							//demon.xPosHotSpot++;
						}
						else
						{
							demon.yPos += abs( 15 * cos( speedJumpDemon ) );
							demon.xPos += abs( 5 * cos( speedJumpDemon ) );
							demon.xVelocity += abs( 5 * cos( speedJumpDemon ) );
							//demon.xPosHotSpot++;
							
							if( demon.yPos > GROUND_Y )
							{
								demon.yPos = GROUND_Y;
								demon.DieLeftDemon++;
								demon.DieState = 2;
							}
						}
						break;
					}
				case 2:
					{
						
						demon.DieLeftDemon++;
						demon.DieOneLife = false;
						demon.DieState = 0;	
						demon.isGettingUp = true;
						break;
					}
				}

				if( demon.DieLeftDemon == 42 )
				{
					demon.DieLeftDemon = 40;
				}

				return demon.DieLeftDemon;
			}

		}
	}

	if( isJumping || isPunching || isCrouching || isKicking || isMovingLeft || isMovingRight || FireBall || CrouchFireBall || TriangleAttack || Triangle )
	{
	// checks which sprites to use
		if( isJumping || isPunching || isCrouching || demon.isKicking || FireBall || CrouchFireBall || TriangleAttack || Triangle )
		{
			if( isCrouching == true && isKicking == true )
			{
				CrouchFire = true;
				isCrouching = false;
				isKicking = false;

				if( Right )
				{
					if( CrouchRightFire == 17 )
					{
						CrouchRightFire = 14;
						CrouchFire = false;
						demon.isCrouching = true;
					}
					else if( CrouchRightFire == 16 )
					{
						Control_OBJ.List_FireBalls.push_back( Control_OBJ.CreateFireBall( demon.xPos + 40, demon.yPos + 55, gamestate.m_srfDemonHealthAndFire, Right, Left ) );
						CrouchRightFire++;
					}
					else
					{
						CrouchRightFire++;
					}
					return CrouchRightFire;
				}
				else
				{
					if( CrouchLeftFire == 38 )
					{
						CrouchLeftFire = 35;
						CrouchFire = false;
						demon.isCrouching = true;
						
					}
					else if( CrouchLeftFire == 37 )
					{
						Control_OBJ.List_FireBalls.push_back(	Control_OBJ.CreateFireBall( demon.xPos - 40, 
																demon.yPos + 55, gamestate.m_srfDemonHealthAndFire, 
																Right, Left ) );
						CrouchLeftFire++;
					}
					else
					{
						CrouchLeftFire++;
					}
					return CrouchLeftFire;
				}
			}
			else if( isCrouching )
			{

				if( Right )
				{
					if( demon.SmallHunter )
					{
						CrouchRight = 19;
						return CrouchRight;
					}
					else
					{
						CrouchRight = 14;
						return CrouchRight;
					}
				}
				else if( Left )
				{
					if( demon.SmallHunter )
					{
						CrouchLeft = 41;
						return CrouchLeft;
					}
					else
					{
						CrouchLeft = 35;
						return CrouchLeft;
					}
				}
			}

			// checks if demon is kicking if animation pace is higher than 150
			// continue to check2, play the animation 3 times for a full kick
			else if( isKicking )
			{
				if( demon.SmallHunter )
				{
					//Kick = true;
					
					if( Right )
					{
						if( KickRight == 8 )
						{
							//Kick = false;
							demon.isKicking = false;
							KickRight = 5;
						}
						else
						{
							KickRight++;
						}

						return KickRight;
					}
					else if( Left )
					{
						if( KickLeft == 31 )
						{
							//Kick = false;
							demon.isKicking = false;
							KickLeft = 28;
						}
						else
						{
							KickLeft++;
						}

						return KickLeft;
					}
				}
				else if( demon.DemonHunter )
				{
					FireBall = true;
					if( Right )
					{
						if( FireBallRight_Demon == 11 )
						{
							Audio.PlaySoundEffect( SOUND_FIRE );
							Control_OBJ.List_FireBalls.push_back(	Control_OBJ.CreateFireBall( demon.xPos - 15,
																	demon.yPos + 35, gamestate.m_srfDemonHealthAndFire, Right, Left ) );
							FireBallRight_Demon++;
						}

						else if( FireBallRight_Demon == 12 )
						{
							FireBallRight_Demon = 9;
							demon.isKicking = false;
							FireBall = false;
						}
						else
						{
							FireBallRight_Demon++;
						}

						return FireBallRight_Demon;
					}

					else if( Left )
					{
						if( FireBallLeft_Demon == 32 )
						{
							Audio.PlaySoundEffect( SOUND_FIRE );
							Control_OBJ.List_FireBalls.push_back(	Control_OBJ.CreateFireBall( demon.xPos - 40,
																	demon.yPos + 35, gamestate.m_srfDemonHealthAndFire, Right, Left ) );
							FireBallLeft_Demon++;
						}

						else if( FireBallLeft_Demon == 33 )
						{
							FireBallLeft_Demon = 30;
							demon.isKicking = false;
							FireBall = false;
						}
						else
						{
							FireBallLeft_Demon++;
						}

						return FireBallLeft_Demon;
					}
				}
			}	
			else if( demon.TriangleAttack )
			{
				Triangle = true;
				bool CanIMove = demon.CheckBoundaries();
				demon.TriangleAttack = false;
				
					
				if( Right )
				{
					if( CanIMove )
					{

						switch( TriangleState )
						{
						case 0:
							{			
								demon.LengthOfTriangle++;
								if( demon.LengthOfTriangle >= 3 )
								{
									TriangleState = 1;
									demon.LengthOfTriangle = 0;
								}
								
								demon.xVelocity += abs( 70 * cos( TriangleSpeed ) );
								demon.xPos += abs( 70 * cos( TriangleSpeed ) );
								//demon.xPosHotSpot++;
								break;
							}
						case 1:
							{
								demon.xVelocity += abs( 70 * cos( TriangleSpeed ) );
								demon.xPos += abs( 70 * cos( TriangleSpeed ) );
								//demon.xPosHotSpot++;
								TriangleState = 0;
								Triangle = false;
								break;
							}
						}

					}
					return demon.TriangleFireRight;
				}
				else
				{		
					if( CanIMove )
					{
						switch( TriangleState )
						{
						case 0:
							{
								if( demon.LengthOfTriangle >= 3 )
								{
									demon.LengthOfTriangle = 0;
									TriangleState = 1;
								}
								demon.xVelocity -= abs( 70 * cos( TriangleSpeed ) );
								demon.xPos -= abs( 70 * cos( TriangleSpeed ) );
								demon.LengthOfTriangle++;
								//demon.xPosHotSpot--;						
								break;
							}
				
						case 1:
							{
								demon.xVelocity -= abs( 70 * cos( TriangleSpeed ) );
								demon.xPos -= abs( 70 * cos( TriangleSpeed ) );
								//demon.xPosHotSpot--;
							
								TriangleState = 0;
								Triangle = false;
								break;
							}
						}
					return demon.TriangleFireLeft;
					}
				}
			}
			else if( isPunching )
			{
				if( demon.SmallHunter )
				{
					//Punch = true;
					if( Right )
					{
						if( PunchRight == 11 )
						{
							PunchRight = 8;
							//Punch = false;
							demon.isPunching = false;
						}
						else
						{
							PunchRight++;
						}

						return PunchRight;
					}
					else
					{
						if( PunchLeft == 34 )
						{
							PunchLeft = 31;
							//7Punch = false;
							demon.isPunching = false;
						}
						else
						{
							PunchLeft++;
						}

						return PunchLeft;
					}
				}
			}
			

			//checks for jump, checks for right or left, loops through the jump animation
			// kickass
			else if( demon.isJumping )
			{
				//Jump = true;

				if( Right )
				{
					if( demon.SmallHunter )
					{
						if( WhereJumpRight == 13 || WhereJumpRight == 14 )
						{
							demon.yPos -= speedJump;
							WhereJumpRight++;
						}
						else if( WhereJumpRight == 15 )
						{
							demon.yPos += speedJump;
							WhereJumpRight++;
						}
						else if( WhereJumpRight == 16 )
						{
							demon.yPos += speedJump;
							//Jump = false;
							demon.isJumping = false;
							WhereJumpRight = 12;
						}
						else
						{
							demon.yPos -= speedJump;
							WhereJumpRight++;
						}
						
						return WhereJumpRight;
					}
					else
					{
						if( JumpRight_Demon == 5 )
						{
							demon.yPos -= speedJumpDemon;
							JumpRight_Demon++;
						}
						else if( JumpRight_Demon == 6 )
						{
							demon.yPos -= speedJumpDemon;
							JumpRight_Demon++;
						}
						else if( JumpRight_Demon == 7 )
						{
						demon.yPos += speedJumpDemon;
						//Jump = false;
						demon.isJumping = false;
						
						JumpRight_Demon = 5;
						}

						return JumpRight_Demon;
					}
				}
				else if( Left )
				{
					if( demon.SmallHunter )
					{
						if( WhereJumpLeft == 35 || WhereJumpLeft == 36 )
						{
							demon.yPos -= speedJump;
							WhereJumpLeft++;
						}
						else if( WhereJumpLeft == 37 )
						{
							demon.yPos -= speedJump;
							WhereJumpLeft++;
						}
						else if( WhereJumpLeft == 38 )
						{
							demon.yPos += speedJump;
							//Jump = false;
							demon.isJumping = false;
			
							WhereJumpLeft = 35;
						}
						else
						{
							demon.yPos -= speed;
							WhereJumpLeft++;

						}
		
						return WhereJumpLeft;
					}
					else
					{
						if( JumpLeft_Demon == 26 )
						{
							demon.yPos -= speedJumpDemon;
							JumpLeft_Demon++;
						}
						else if( JumpLeft_Demon == 27 )
						{
							demon.yPos -= speedJumpDemon;
							JumpLeft_Demon++;
						}
						else if( JumpLeft_Demon == 28 )
						{
							demon.yPos += speedJumpDemon;
							//Jump = false;
							demon.isJumping = false;
			
							JumpLeft_Demon = 26;
						}
		
						return JumpLeft_Demon;
					}
				}
			}
		}
		else if( demon.isMovingLeft || demon.isMovingRight )
		{
			// Character movement left and right
			if( gamestate.GameCondition != GS_OUTRO )
			{
				//demon.yPos = GROUND_Y;
			}

			// checks if demon is moving right, also checks which clip to use for
			// the right demon in sprite sheet
			if( demon.isMovingRight )
			{
				if( demon.xPos < 600.0f )
				{
					demon.xPos += 15.0f;
				}

				demon.Right = true;
				demon.Left = false;

				if( gamestate.GameCondition == GS_OUTRO )
				{
					demon.xPos += 2;
					demon.xVelocity += 2;	
				}
				else if( demon.xVelocity >= STARTSCROLLING - 50)
				{
					if( gamestate.GameCondition == GS_LEVEL1BOSS )
					{
						if( demon.xVelocity >= STARTSCROLLING + 100 )
						{

						}
						else
						{
							//demon.xPos += speed;
							//demon.xVel = 2500.0f;
							//demon.xVel += speed;
						}
					}
					// Updating to see where on the map the character is
					//demon.xPosHotSpot++;
				}
				else
				{
					// Enter here when meeting the boss and get hurt
					//First movement right
 					//demon.xPos += speed;
					//demon.xVel = 2500.0f;
					//demon.xVel += speed;
					//demon.xPosHotSpot++;
				}
				// Walking animation frames 
				if( demon.SmallHunter )
				{
					if( WhereWalkRight > 3 )
					{
						WhereWalkRight = 1;
					}
					else 
					{
						WhereWalkRight++;
					}
					return WhereWalkRight;
				}
				else
				{
					if( WalkRight_Demon > 3 )
					{
						WalkRight_Demon = 1;
					}
					else
					{
						WalkRight_Demon++;
					
					}
					return WalkRight_Demon;
				}
			}
			
			// checks if deom is moving left, also checks which clip to use for
			// the right demon in sprite sheet
			else if( demon.isMovingLeft )
			{
				// Character maximum distance to the left edge of the screen
				if( demon.xPos > 15.0f )
				{
					demon.xPos -= 15.0f;
				}
				if( demon.xVelocity <= gamestate.SCREEN_WIDTH - gamestate.SCREEN_WIDTH + 25 )
				{
					//demon.xPosHotSpot--;
				}
				else
				{
					//demon.xPos -= speed;
					//demon.xVel -= speed;
					//demon.xPosHotSpot--;
				}
				
				demon.Right = false;
				demon.Left = true;

				// What sprites to use when drawing the main character
				if( demon.SmallHunter )
				{
					if( WhereWalkLeft > 26 )
					{
						WhereWalkLeft = 24;
					}
					else
					{
						WhereWalkLeft++;
					}

					return WhereWalkLeft;
				}
				else
				{
					if( WalkLeft_Demon > 24 )
					{
						WalkLeft_Demon = 22;
					}
					else
					{
						WalkLeft_Demon++;
					}

					return WalkLeft_Demon;
				}	
			}
		}
	}
	if( gamestate.GameCondition != GS_OUTRO )
	{
		demon.yPos = GROUND_Y;
	}
	
	if( Left )
	{
		if( demon.SmallHunter )
		{
			return 23;
		}
		else
			return 21;
	}

	return 0;
}

void Demon::UpdateXPos()
{
	if( demon.isMovingRight )
	{
		//MovementDirection = true; // Right
		//demon.Right = true;
		//demon.Left = false;
	}
		
	// checks if demom is moving left, also checks which clip to use for
	// the right demon in sprite sheet
	else if( demon.isMovingLeft )
	{
		//MovementDirection = false; // Left
		//demon.Right = false;
		//demon.Left = true;
	}	
}

void Demon::Set_clips()
{
	for( int i = 0; i < 4; i++ )
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
	xPos += xUnits;
	yPos += yUnits;

	
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