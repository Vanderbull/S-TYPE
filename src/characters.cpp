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
	_Lives = 3;
	BaseCharacter::SetAliveState(AliveState::ALIVE);

	isHit            = false; 

	_AlphaImmortal    = SDL_ALPHA_OPAQUE;

	_Position.x = Xpos;
	_Position.y = Ypos;
	_Position.h = 100;
	_Position.w = 130;

	_Surface = surface;

	xVelocity = 0.000015f; 
	yVelocity = 0.0f;
	CollisionBox.x = 0;
	CollisionBox.y = 0;
	CollisionBox.w = width;
	CollisionBox.h = height;
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

bool BaseCharacter::IsAttacking()
{
	return true;
}

//void BaseCharacter::Initiatedemon(	int surface, int Xpos, int Ypos, 
//							int height, int width )
//{
//	//demon_Height = height;
//	//demon_Width = width;
//
//	Radius = ( demonWIDTHREAL > demonHEIGHTREAL ) ? demonWIDTHREAL / 2 : demonHEIGHTREAL / 2;
//	RadiusFist  = ( Feet_W > Feet_H ) ? Feet_W / 2 : Feet_H / 2;
//	RadiusFeet  = ( Fist_W > Fist_H ) ? Fist_W / 2 : Fist_H / 2;
//
//	//xPos = Xpos;
//	//yPos = Ypos;
//	_Position.x = Xpos;
//	_Position.y = Ypos;
//
//	Surface = surface;
//
//	xVelocity = 15.0f;
//	yVelocity = 0;
//}

// updates BCPlayer animations and moving, moved code to Update function

float positionX = 0.0f, positionY = 0.0f;     // Position of the character
float velocityX = 0.0f, velocityY = 0.0f;     // Velocity of the character

void Update(float time)
{
    positionX += velocityX * time;      // Apply horizontal velocity to X position
    positionY += velocityY * time;      // Apply vertical velocity to Y position
}

void BaseCharacter::Update()
{
	if( yVelocity != 0 )
	{
		if( (BaseCharacter::_Position.y + yVelocity > 0) && (BaseCharacter::_Position.y + yVelocity < Gfx.screen->h - 100) )
		{
			BaseCharacter::_Position.y += yVelocity;
		}
	}
	if( xVelocity != 0 )
	{
		if( (BaseCharacter::_Position.x + xVelocity > 0) && (BaseCharacter::_Position.x + xVelocity < Gfx.screen->w - 128) )
		{
			BaseCharacter::_Position.x += xVelocity;
		}
	}

	if( isHit )
	{
		if( BCPlayer._Lives > 0 )
		{
			--BCPlayer._Lives;
			BCPlayer.Reset();
		}
		else
		{
			BCPlayer.Died();
		}

		BCPlayer.isHit = false;
	}
}


void BaseCharacter::SetClips()
{
	int ArraySizeColumns = sizeof(AnimationArrays) / sizeof(AnimationArrays[0]);
	int ArraySizeRows = sizeof(AnimationArrays[0]) / sizeof(AnimationArrays[0][0]);
	for( int Column = 0; Column < ArraySizeColumns; Column++ )
	{
		for( int Row = 0; Row < ArraySizeRows; Row++ )
		{
			BCPlayer.AnimationArrays[ Column ][ Row ].x = Row * _Position.w;
			BCPlayer.AnimationArrays[ Column ][ Row ].y = Column * _Position.h;
			BCPlayer.AnimationArrays[ Column ][ Row ].h = _Position.h;
			BCPlayer.AnimationArrays[ Column ][ Row ].w = _Position.w;
		}
	}
}


void BaseCharacter::UpdatePosition(float xUnits, float yUnits)
{
	_Position.x += xUnits * gamestate.DeltaTime;
	_Position.y += xUnits * gamestate.DeltaTime;

	_Position.x += xUnits * gamestate.DeltaTime;
	_Position.y += yUnits * gamestate.DeltaTime;

	
	if( _Position.x < 0.0f )
	{
		// Bumps the character to the right a bit if the BCPlayer isn't moving and to far to the left
		_Position.x += 100.0f * gamestate.DeltaTime;
	}
	else
	{
		// Makes the character follow the parallax scrolling speed to make it look like he is standing still
		_Position.x -= 2.0f * gamestate.DeltaTime;
	}
	
	_Position.y = 0;
}

void BaseCharacter::Reset()
{
	_Lives = 3;
	BaseCharacter::SetAliveState(AliveState::ALIVE);

	isHit            = false; 

	_AlphaImmortal    = SDL_ALPHA_OPAQUE;

	_Position.x = GROUND_X;
	_Position.y = GROUND_Y;
	_Position.h = demonHEIGHT;
	_Position.w = demonWIDTH;

	xVelocity = 0.000015f; 
	yVelocity = 0.0f;
}

void BaseCharacter::Died()
{

	//Gfx.DrawBackgroundBlack();
	Gfx.srfText = TTF_RenderText_Shaded( Gfx.DefaultFont, " YOU DIED STOP PLAYING GOD DAMN YOU!!!!! ", Gfx.WhiteRGB, Gfx.BlackRGB );
	Gfx.apply_surface( 250, 500, Gfx.srfText, Gfx.BackBuffer );
	Gfx.FLIP();

	gamestate.GameState.push(MENU_MAIN_STATE);
	gamestate.RestartGame();
	Sleep(5000);
	//SDL_Event input;

	//while( gamestate.GameState.top() == MENU_MAIN_STATE )
	//{
	//	SDL_PollEvent( &input );
	//	if( input.type == SDL_KEYDOWN )
	//	{
 // 			switch( input.key.keysym.sym )
	//		{
	//		case SDLK_SPACE:
	//			gamestate.GameState.push(MENU_MAIN_STATE);
	//			break;
	//		}
	//	}
	//	Gfx.DrawBackgroundBlack();
	//	SDL_BlitSurface( Gfx.GetSurface( gamestate.m_srfOutro ), &Gfx.screen->clip_rect, Gfx.BackBuffer, &Gfx.screen->clip_rect );
	//	Gfx.srfText = TTF_RenderText_Shaded( Gfx.DefaultFont, " Press Space For Menu ", Gfx.WhiteRGB, Gfx.BlackRGB );
	//	Gfx.apply_surface( 250, 500, Gfx.srfText, Gfx.BackBuffer );
	//}
}
