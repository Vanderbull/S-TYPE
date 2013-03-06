#pragma once

#include <iostream>
#include <windows.h>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Game.h"
#include "characters.h"
#include "ControlGfx.h"
#include "Audio.h"
#include "Objects.h"
#include "Enemies.h"
#include "TImers.h"
#include "Paralaxlayers.h"
#include "Animals.h"
#include "FirstScreen.h"
#include "Collision.h"
#include "OutroFinish.h"
#include "GetInput.h"

Gamestate gamestate;

Gamestate::Gamestate()
{
	cout << "Initializing Gamestate" << endl;
	SCREEN_HEIGHT = 600;
	SCREEN_WIDTH = 800;
	SCREEN_BPP = 32;
	cout << "Resolution: " << SCREEN_HEIGHT << "x" << SCREEN_WIDTH << "x" << SCREEN_BPP << endl;
	dt = 0.0f;
	CheckingHighScore = false;
	BossStart = false;
	IntroDone = false;

	FirstLevel = true;
	cout << "Setting FirstLevel" << endl;

	GameCondition = GS_INTRO;
	cout << "GameCondition: GS_INTRO" << endl;

	boss = NULL;
	Intro = NULL;
	outro = NULL;
	
	PreviousAnimArray = 0;
	PreviousFrame = 0;
	CurrentAnimArray = 0;
	CurrentFrame = 0;

	font = NULL;
	srfText = NULL;

	m_parallax = 0;

	//Score = 0;
	LevelProgress = 0;

	// Loading files

}
void Gamestate::KeyMapping(SDL_Event _event)
{
	bool KEYS[322];  // 322 is the number of SDLK_DOWN events


	for(int i = 0; i < 322; i++) { // init them all to false
	   KEYS[i] = false;
	}

	SDL_EnableKeyRepeat(0,0); // you can configure this how you want, but it makes it nice for when you want to register a key continuously being held down

	if( demon.GetState() == Demon::State::MOVING_RIGHT)
		cout << "DO DA MOVA MOVA!!!!!" << endl;

	switch (_event.type) 
	{
		case SDL_KEYDOWN:
			KEYS[_event.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            KEYS[_event.key.keysym.sym] = false;
            break;
	}  
}

void Game::Handle_events( SDL_Event _event )
{	
	if( _event.type == SDL_KEYUP )
	{
		demon.SetState(Demon::State::IDLE);

		switch( _event.key.keysym.sym )		
		{
		case SDLK_RIGHT:
			{
				cout << "Released the RIGHT arrow key" << endl;
				demon.isMovingRight = false;
				demon.isMovingLeft = false;
			} break;
		case SDLK_LEFT:
			{
				cout << "Released the LEFT arrow key" << endl;
				demon.isMovingRight = false;
				demon.isMovingLeft = false;
			} break;
		case SDLK_UP:
			{
				cout << "Released the UP arrow key" << endl;
				demon.isJumping = false;
			} break;
		case SDLK_SPACE:
			{
				cout << "Released SPACEBAR key" << endl;
				demon.isKicking = false;
			} break;
		case SDLK_LALT:
			{
				cout << "Released the LEFT ALT key" << endl;
				demon.isPunching = false;
			} break;
		}
	}
	else if( _event.type == SDL_KEYDOWN )
	{
		switch( _event.key.keysym.sym )
		{
		case SDLK_RIGHT:
			{
				cout << "Pressing down right arrow" << endl;
				demon.SetState(Demon::State::MOVING_RIGHT);
				if( demon.isHit == false && demon.isKicking == false && demon.isPunching == false && demon.isJumping == false && demon.GetPosition().y == GROUND_Y )
				{	
					demon.isMovingRight = true;
				}
			} break;
		case SDLK_LEFT:
			{
				cout << "Pressing down left arrow" << endl;
				demon.SetState(Demon::State::MOVING_LEFT);
				if( demon.isHit == false && demon.isKicking == false && demon.isPunching == false && demon.isJumping == false && demon.GetPosition().y == GROUND_Y )
				{
					demon.isMovingLeft = true;
				}
			} break;
		case SDLK_UP:
			{
				cout << "Pressing down up arrow" << endl;
				if( !demon.isJumping )
				{
					demon.SetState(Demon::State::JUMPING);
				}

				if( demon.isHit == false && demon.isPunching == false && demon.isKicking == false && demon.isJumping == false && demon.GetPosition().y == GROUND_Y )
				{
					demon.isJumping = true;
				}
			} break;
		case SDLK_SPACE:
			{
				cout << "Pressing down spacebar arrow" << endl;
				demon.SetState(Demon::State::KICKING);
				if( demon.isHit == false && demon.isPunching == false && demon.isKicking == false && demon.isJumping == false && demon.GetPosition().y == GROUND_Y )
				{
					/*
					if( demon.DemonHunter == true )
					{
						
						if( timer.Timer_FireBall > 15 )
						{
							timer.Timer_FireBall = 0;
							demon.isKicking = true;
							break;
						}

						break;
					}
					 */
					demon.isKicking = true;
					Audio.PlaySoundEffect( SOUND_HIT );
											
					break;
				}
			} break;
		case SDLK_LALT:
			{
				cout << "Pressing down lalt arrow" << endl;
				demon.SetState(Demon::State::PUNCHING);
				if( demon.isHit == false && demon.isPunching == false && demon.isKicking == false && demon.isJumping == false && demon.GetPosition().y == GROUND_Y )
				{
					demon.isPunching = true; 
					Audio.PlaySoundEffect( SOUND_HIT );
					/*
					if( demon.SmallHunter )
					{ 
						demon.isPunching = true; 
						Audio.PlaySoundEffect( SOUND_HIT );
					}
					else
					{ 
						if( timer.Timer_TriangleAttackOK > 15 )
						{
							timer.Timer_TriangleAttackOK = 0;
							Audio.PlaySoundEffect( SOUND_FIRE );
						}
					}
					*/
				}
			} break;
		case SDLK_BACKSPACE:
			{
				if( gamestate.PlayerName.length() != 0 )
				{
					gamestate.PlayerName.erase( gamestate.PlayerName.length() - 1 );
				}
			} break;
		case SDLK_RETURN:
			{
				if( gamestate.GameCondition == GS_ENTERNAME )
				{
					gamestate.GameCondition = GS_INTROSTORY;
				}
			} break;
		default:
			{
				if( gamestate.GameCondition == GS_ENTERNAME )
				{
					gamestate.PlayerName +=  _event.key.keysym.unicode;
				}
			}
		}
	}
	else
	{
		cout << "no key presses or releases are made" << endl;
		demon.SetState(Demon::State::IDLE);
	}
	// if intro checks mouseposition and checks for presses
	if( gamestate.GameCondition == GS_INTRO )
	{
		if( _event.type == SDL_MOUSEMOTION || _event.type == SDL_MOUSEBUTTONDOWN )
		{
			// check if mouse is over something
			if( gamestate.TitleScreen->ButtonOptions == true )
			{
				for( int i = 4; i < 8; i++ )
				{
					if( _event.button.x > gamestate.TitleScreen->DestClips[ i ].x && 
					_event.button.x < gamestate.TitleScreen->DestClips[ i ].x + gamestate.TitleScreen->DestClips[ i ].w &&
					_event.button.y > gamestate.TitleScreen->DestClips[ i ].y &&
					_event.button.y < gamestate.TitleScreen->DestClips[ i ].y + gamestate.TitleScreen->DestClips[ i ].h )
					
					if( _event.type == SDL_MOUSEBUTTONDOWN )
					{
						switch( i )
						{
							case 4:
							{
									gamestate.TitleScreen->ButtonHighScore = true;
									gamestate.CheckingHighScore = true;
							} break;
							case 5: gamestate.TitleScreen->ButtonCredits = true; break;
							case 6: gamestate.TitleScreen->ButtonSound = true; break;
							case 7: gamestate.TitleScreen->ButtonBack = true; break;

						}
					}
				}

			}
			else
			{
				// checks if musebutton is pressed at newgame, options or quit
				for( int i = 0; i < 3; i++ )
				{
					if( _event.button.x > gamestate.TitleScreen->DestClips[ i ].x && 
						_event.button.x < gamestate.TitleScreen->DestClips[ i ].x + gamestate.TitleScreen->DestClips[ i ].w &&
						_event.button.y > gamestate.TitleScreen->DestClips[ i ].y &&
						_event.button.y < gamestate.TitleScreen->DestClips[ i ].y + gamestate.TitleScreen->DestClips[ i ].h )
					{
						//hoovering effect
						switch( i )
						{
							case BUTTON_NEW_GAME: cout << "Hoovering new game"; break;
							case BUTTON_OPTIONS: break;
							case BUTTON_QUIT: break;
						}
						if( _event.type == SDL_MOUSEBUTTONDOWN )
						{
							switch( i )
							{
								case BUTTON_NEW_GAME: gamestate.TitleScreen->ButtonNewgame = true; break;
								case BUTTON_OPTIONS: gamestate.TitleScreen->ButtonOptions = true; break;
								case BUTTON_QUIT: gamestate.TitleScreen->ButtonQuit = true; break;
							}
						}
					}					
				}
			}
		}


	}
	else
	{
		return;
	}
}

Game::Game()
{
	//initialize all SDL subystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1)
	{
		cout << "SDL INIT FAILED..." << endl;
		SDL_Quit();
	}
	else
	{
		cout << "SDL_INIT_EVERYTHING..." << endl;
	}

	if( TTF_Init() == -1 )
	{
		cout << "TTF_INIT FAILED..." << endl;
	}
	else
	{
		gamestate.font = TTF_OpenFont( "Fonts/PressStart2P.ttf", 14 );
		SDL_Quit();

	}

	// Setup of the application icons
	SDL_WM_SetCaption("", "res/big.ico");
	SDL_WM_SetIcon(SDL_LoadBMP("res/small.bmp"), NULL);

	gamestate.GameOK = true;
	gamestate.GameOK = Init( gamestate.screen );
	
	// h 100 w 130
	//demon.InitiateDemon( demon.DemonSurface, GROUND_X, GROUND_Y, DEMONHEIGHT, DEMONWIDTH ); 

	gamestate.load_files();
	//demon.Set_clips();
	//new setclips function
	demon.SetClips();
}

// loads all graphic files and all new files and the font
void Gamestate::load_files()
{
	
	m_srfCity = Gfx.Load_imageAlpha( "Graphics/srfCity.png", 0, 0, 0 );
	m_srfClouds = Gfx.Load_imageAlpha( "Graphics/srfClouds.png", 0, 0, 0 );
	m_srfBlack = Gfx.Load_imageAlpha( "Graphics/srfBlack.png", 0, 0, 0 );
	m_srfSky = Gfx.Load_imageAlpha( "Graphics/srfSky.png", 0, 0, 0 );
	m_srfTrees = Gfx.Load_imageAlpha( "Graphics/srfTrees.png", 2, 2, 2 );
	demon.DemonSurface = Gfx.Load_imageAlpha( "Graphics/DemonSurface.png", 255, 255, 255 );
	m_srfEnemyZombie = Gfx.Load_imageAlpha( "Graphics/srfEnemyZombie.png", 255, 0, 255 );
	m_srfSkeleton = Gfx.Load_imageAlpha( "Graphics/srfSkeleton.png", 255, 0, 255  );
	m_srfCrow = Gfx.Load_imageAlpha( "Graphics/srfCrow.png", 255, 255, 255 );
	m_srfCoffin  = Gfx.Load_imageAlpha( "Graphics/srfCoffin.png", 97, 68, 43 );
	m_srfBoss = Gfx.Load_imageAlpha( "Graphics/srfBoss.png", 255, 255, 255 );
	m_srfDemonLife = Gfx.Load_imageAlpha( "Graphics/srfDemonLife.png", 255, 255, 255 );
	m_srfDemonHealthAndFire = Gfx.Load_imageAlpha( "Graphics/srfDemonHealthAndFire.png", 0, 0, 0 );
	m_srfDragon = Gfx.Load_imageAlpha( "Graphics/srfDragon.png", 0, 0, 0 );
	m_srfStart = Gfx.Load_imageAlpha( "Graphics/srfStart.png", 237, 234, 214 );
	m_srfButtons = Gfx.Load_imageAlpha( "Graphics/srfButtons.png", 255, 255, 255 );
	m_srfIntro = Gfx.Load_imageAlpha( "Graphics/srfIntro.png", 255, 255, 255 );
	m_srfMorphing = Gfx.Load_imageAlpha( "Graphics/srfMorphing.png", 255, 255, 241 );
	m_srfReaper = Gfx.Load_imageAlpha( "Graphics/srfReaper.png", 255, 255, 255 );
	m_srfOutro = Gfx.Load_imageAlpha( "Graphics/srfOutro.png", 0, 0, 0 );
	m_srfButton = Gfx.Load_imageAlpha( "Graphics/srfButton.png", 0, 0, 0 );
	m_srfHealth = Gfx.Load_imageAlpha( "Graphics/srfHealth.png", 0, 0, 0 );
	
 
 /*
	m_srfCity = Load_imageAlpha( "Graphics/srfCity.png", 0, 0, 0 );
	m_srfClouds = Load_imageAlpha( "Graphics/srfClouds.png", 0, 0, 0 );
	m_srfBlack = Load_imageAlpha( "Graphics/srfBlack.png", 0, 0, 0 );
	m_srfSky = Load_imageAlpha( "Graphics/srfSky.png", 0, 0, 0 );
	m_srfTrees = Load_imageAlpha( "Graphics/srfTrees.png", 0, 0, 0 );
	demon.DemonSurface = Load_imageAlpha( "Graphics/DemonSurface.png", 255, 255, 255 );
	m_srfEnemyZombie = Load_imageAlpha( "Graphics/srfEnemyZombie.png", 255, 0, 255 );
	m_srfSkeleton = Load_imageAlpha( "Graphics/srfSkeleton.png", 255, 0, 255  );
	m_srfCrow = Load_imageAlpha( "Graphics/srfCrow.png", 255, 255, 255 );
	m_srfCoffin  = Load_imageAlpha( "Graphics/srfCoffin.png", 255, 0, 255 );
	m_srfBoss = Load_imageAlpha( "Graphics/srfBoss.png", 255, 255, 255 );
	m_srfDemonLife = Load_imageAlpha( "Graphics/srfDemonLife.png", 255, 255, 255 );
	m_srfDemonHealthAndFire = Load_imageAlpha( "Graphics/srfDemonHealthAndFire.png", 0, 0, 0 );
	m_srfDragon = Load_imageAlpha( "Graphics/srfDragon.png", 0, 0, 0 );
	m_srfStart = Load_imageAlpha( "Graphics/srfStart.png", 237, 234, 214 );
	m_srfButtons = Load_imageAlpha( "Graphics/srfButtons.png", 255, 255, 255 );
	m_srfIntro = Load_imageAlpha( "Graphics/srfIntro.png", 255, 255, 255 );
	m_srfMorphing = Load_imageAlpha( "Graphics/srfMorphing.png", 255, 255, 241 );
	m_srfReaper = Load_imageAlpha( "Graphics/srfReaper.png", 255, 255, 255 );
	m_srfOutro = Load_imageAlpha( "Graphics/srfOutro.png", 255, 255, 255 );
	m_srfButton = Load_imageAlpha( "Graphics/srfButton.png", 0, 0, 0 );
	m_srfHealth = Load_imageAlpha( "Graphics/srfHealth.png", 0, 0, 0 );
*/	

	gamestate.CreateNewThings();

	for( int i = 0; i < 4; i++ )
	{
		MorphingPics[ i ].x = i * SCREEN_WIDTH;
		MorphingPics[ i ].y = 0;
		MorphingPics[ i ].h = SCREEN_HEIGHT;
		MorphingPics[ i ].w = SCREEN_WIDTH;
	}

	setUpParallaxLayers();
}

void Gamestate::CreateNewThings()
{
	Dragon = new DancingDragon( m_srfDragon );
	TitleScreen = new FirstScreen( 290,  m_srfStart, m_srfButtons ); 
	Intro = new IntroTalk( gamestate.m_srfIntro );
	name = new StringInput();
	ListHighScore = new FillHighScore();
}


// ----------------------------------------------------------------------------
// findAvailableIndex() - find free slot in surface list and return its index
// ----------------------------------------------------------------------------
int Gamestate::findAvailableIndex()
{
	for( int i = 0; i < MAX_SURFACE; i++ )
	{
		if( !m_surfaceList[i] )
		{
			return i;
		}
	}

	// None available
	return -1;
}

// ----------------------------------------------------------------------------
// DrawObjects() - Draws all objects, coffins, health etc.
// ----------------------------------------------------------------------------
void Gamestate::DrawObjects()
{
	if( gamestate.GameCondition == GS_LEVEL1BOSS )
	{
		Control_OBJ.DrawObjects();
	}
	else
	{						  
		demon.Update();
		AnimalController.Draw_Animals();
		Control_ENEMY.Update();
		Control_ENEMY.Draw_Enemies();
		Control_OBJ.DrawObjects();
	}	
}
// ----------------------------------------------------------------------------
// CreateBoss() - Creates the boss gives collisionCircle and pos
// ----------------------------------------------------------------------------
Boss * Gamestate::CreateBoss( int xPos, int yPos, int surface )
{
	Boss * temp = new Boss;
	temp->Surface = surface;
	temp->xPos = xPos;
	temp->yPos = yPos;

	temp->Radius = ( temp->BossWidth > temp->BossHeight ) ? temp->BossWidth / 2 : temp->BossHeight  / 2;

	return temp;
}

// ----------------------------------------------------------------------------
// MorphMyDude - does the morphing sequence
// ----------------------------------------------------------------------------
void Gamestate::MorphMyDude()
{
	Audio.PlaySoundEffect( SOUND_MORPH );

	int State = 3;
	SDL_Rect destRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	while( State != -1 )
	{
		
		DrawBackgroundBlack();
	
		switch( State )
		{
		case 0:
			{
				if( timer.MorphPics > 10 )
				{
					SDL_BlitSurface(	Gfx.GetSurface( m_srfMorphing ), &MorphingPics[ State ], 
										gamestate.BackBuffer, &destRect );
					State--;
					timer.MorphPics = 0;
				}
				else
				{
					SDL_BlitSurface(	Gfx.GetSurface( m_srfMorphing ), &MorphingPics[ State ], 
					gamestate.BackBuffer, &destRect );
					timer.MorphPics++;
				}

				break;
			}
		case 1:
			{
				if( timer.MorphPics > 10 )
				{
					SDL_BlitSurface(	Gfx.GetSurface( m_srfMorphing ), &MorphingPics[ State ], 
										gamestate.BackBuffer, &destRect );
					State--;
					timer.MorphPics = 0;
				}
				else
				{
					SDL_BlitSurface(	Gfx.GetSurface( m_srfMorphing ), &MorphingPics[ State ], 
					gamestate.BackBuffer, &destRect );
					timer.MorphPics++;
				}

				break;
			}
		case 2:
			{
				if( timer.MorphPics > 10 )
				{
					SDL_BlitSurface(	Gfx.GetSurface( m_srfMorphing ), &MorphingPics[ State ], 
										gamestate.BackBuffer, &destRect );
					State--;
					timer.MorphPics = 0;
				}
				else
				{
					SDL_BlitSurface(	Gfx.GetSurface( m_srfMorphing ), &MorphingPics[ State ], 
					gamestate.BackBuffer, &destRect );
					timer.MorphPics++;
				}
				break;
			}
		case 3:
			{
				if( timer.MorphPics > 10 )
				{
					SDL_BlitSurface(	Gfx.GetSurface( m_srfMorphing ), &MorphingPics[ State ], 
										gamestate.BackBuffer, &destRect );
					State--;
					timer.MorphPics = 0;
				}
				else
				{
					SDL_BlitSurface(	Gfx.GetSurface( m_srfMorphing ), &MorphingPics[ State ], 
					gamestate.BackBuffer, &destRect );
					timer.MorphPics++;
				}
				break;
			}
		}
		gamestate.FLIP();
	}

	gamestate.GameCondition = GS_LEVEL1;

	// safety Check
	//demon.SmallHunter = false;
	//demon.DemonHunter = true;
	demon.isJumping = false;
	demon.isPunching = false;
	demon.isKicking = false;
	//demon.Crouch = false;
	//demon.Kick = false;
	//demon.Punch = false;
	//demon.Jump = false;
	demon.isMovingLeft = false;
	demon.isMovingRight = false;
}

// ----------------------------------------------------------------------------
// DrawBackgroundBlack - draws a background black with the size of screen
// ----------------------------------------------------------------------------
void Gamestate::DrawBackgroundBlack()
{
	if( gamestate.GameCondition == GS_OUTRO )
	{
		SDL_FillRect(gamestate.BackBuffer, NULL, SDL_MapRGB(gamestate.BackBuffer->format, 0,0,0));
		/*
		ParallaxLayer  * MyParaBackGround;
		MyParaBackGround = gamestate.Paralax->getLayer( gamestate.m_srfBlack );

		SDL_Rect scRect = { 0, 0,	100, 70 };
									
		SDL_Rect dtRect = {	600, 530, 100, 50 };

		SDL_BlitSurface( gamestate.GetSurface( gamestate.m_srfBlack ), &scRect, gamestate.BackBuffer, &dtRect ); 
		*/
	}
	else
	{
		SDL_FillRect(gamestate.BackBuffer, NULL, SDL_MapRGB(gamestate.BackBuffer->format, 0,0,0));
		/*
		ParallaxLayer  * MyParaBackGround;
		MyParaBackGround = gamestate.Paralax->getLayer( gamestate.m_srfBlack );

		SDL_Rect scRect = { 0, 0,	MyParaBackGround->m_width, 
									600 };

		SDL_Rect dtRect = {	0, 0, MyParaBackGround->m_width, 600 };

		SDL_BlitSurface( gamestate.GetSurface( gamestate.m_srfBlack ), &scRect, gamestate.BackBuffer, &dtRect );
		*/
	}
}

void Gamestate::ResetBoss()
{
	if( gamestate.boss != NULL )
	{
		delete gamestate.boss;
	}
}

void Gamestate::ResetEnemies()
{
	if( Control_ENEMY.Enemies.size() != NULL )
	{
		Control_ENEMY.Enemies.clear();
	}
}

// ----------------------------------------------------------------------------
// ResetObjects() - resets all object to its starting values
// ----------------------------------------------------------------------------
void Gamestate::ResetObjects()
{
	if( Control_OBJ.List_Coffins.size() != NULL )
	{
		Control_OBJ.List_Coffins.clear();
	}

	if( Control_OBJ.List_FireBalls.size() != NULL )
	{
		Control_OBJ.List_FireBalls.clear();
	}

	if( Control_OBJ.List_PowerUps.size() != NULL )
	{
		Control_OBJ.List_PowerUps.clear();
	}

	Control_OBJ.FrameHealth = 0;
	Control_OBJ.PowerUpMan = false;
	if( Control_OBJ.WereWolf != NULL )
	{
		delete Control_OBJ.WereWolf;
		Control_OBJ.WereWolf = NULL;
	}

	Control_OBJ.WhichLifeToShow = 0;
	
	return;
}

// ----------------------------------------------------------------------------
// ResetPlayer() - resets the player to its starting values
// ----------------------------------------------------------------------------
void Gamestate::ResetPlayer()
{
	demon.isMovingRight = false;
	demon.isMovingLeft = false;
	demon.isJumping = false;
	demon.isKicking = false;
	demon.isPunching = false;
	demon.Right = false;
	demon.Left = false;
	demon.isImmortal = false;
	

	demon.isHit = false; 
	//demon.DieOneLife = false;

	//demon.SmallHunter = true;
	//demon.MediumHunter = false;
	//demon.LargeHunter = false;
	//demon.DemonHunter = false;

	demon.LifeFull_Small = true;
	demon.LifeMedium_Small = false;
	demon.LifeLittle_Small = false;

	//demon.Demon_Dead = false;

	demon.isGettingUp = false;

	//demon.KickRight = 5;
	//demon.KickLeft = 28;
	//demon.WhereWalkLeft = 24;
	//demon.WhereWalkRight = 0;
	//demon.WhereJumpLeft = 35;
	//demon.WhereJumpRight = 12;
	//demon.PunchRight = 8; 
	//demon.PunchLeft = 31;

	//demon.WalkLeft_Demon = 22;
	//demon.WalkRight_Demon = 1;
	//demon.FireBallRight_Demon = 9;
	//demon.FireBallLeft_Demon = 30;
	//demon.JumpRight_Demon = 5;
	//demon.JumpLeft_Demon = 26;
	//demon.FireBallRight = 39;
	//demon.FireBallLeft = 42;

	demon.AlphaImmortal = SDL_ALPHA_OPAQUE;

	//demon.Demon_Life = 2;

	//demon.TriangleFireLeft = 34;
	//demon.TriangleFireRight = 13;

	//demon.DieRightDemon = 44;
	//demon.DieLeftDemon = 40;

	demon.Radius = 0;
	demon.RadiusFist = 0;
	demon.RadiusFeet = 0;
	demon.DemonHealth = 100;

	demon.Feet_W = 10;
	demon.Feet_H = 10;
	demon.Fist_W = 15;
	demon.Fist_H = 15;
}

// ----------------------------------------------------------------------------
// Update() - Updates the whole game depending on which state it is in
// ----------------------------------------------------------------------------
void Game::upDate( SDL_Event input )
{
	// WhereIsEnd is @ image width + screenwidth 800+5100
	//if( demon.WhereIsEnd >= 5700 ) 
	if( gamestate.LevelProgress >= 6100 )
	{
		gamestate.GameCondition = GS_LEVEL1BOSS;
		//Audio.PlaySoundEffect( SOUND_BOSS );
	}

	// Check game state
	switch( gamestate.GameCondition )
	{
		// Intro sequence
		case GS_INTRO:
			{
				//Audio.PlayIntroSong();
				//Handle_events( input );
				gamestate.MainScreen();
				gamestate.FLIP();
			} break;
		case GS_ENTERNAME:
			{
				//Audio.PlayIntroSong();
				gamestate.EnterName();
				gamestate.FLIP();
			} break;	
		case GS_INTROSTORY:
			{
				//Audio.PlayIntroSong();
				gamestate.DoIntroTalk();
				gamestate.FLIP();
			} break;
		case GS_LOADING:
			{
				Audio.PauseMusic();
				gamestate.Loading();
			} break;
		case GS_MORPH:
			{
				Audio.PauseMusic();
				gamestate.MorphMyDude();
			} break;
		case GS_LEVEL1:
			{
				//gamestate.LevelProgress++;
				gamestate.LevelProgress = gamestate.LevelProgress + (60*gamestate.dt);
				cout << gamestate.LevelProgress << endl;

				/*
				if( Audio.MusicPaused == true )
				{
					Audio.UnpauseMusic();
				}

				if( Audio.LevelSong == false )
				{
					Audio.PlayMusic( 0 );
				}
				*/
				// handles events what the user does with the character
				//Handle_events( input );
				
				//draws layers
				gamestate.drawParallaxLayers();
				gamestate.DrawObjects();
				gamestate.DrawSprite();
				
				gamestate.DrawAllText();
				
				gamestate.FLIP();
			} break;
		case GS_LEVEL1BOSS:
			{
				if( Audio.MusicPaused == true )
				{
					Audio.UnpauseMusic();
				}

				// handles events what the user does with the character
				//Handle_events( input );

				//draws layers
				gamestate.drawParallaxLayers();
				gamestate.DrawObjects();
				gamestate.DrawBoss();
				gamestate.DrawAllText();
				gamestate.DrawSprite();
				gamestate.FLIP();

				if( gamestate.boss->BossDead == true )
				{
					gamestate.GameCondition = GS_OUTRO;
				}
			} break;
		case GS_OUTRO:
			{
				//Audio.PauseMusic();
				//Audio.PlayMusic( 2 );
				gamestate.PlayOutro();
			} break;
		case GS_DEAD:
			{
				//Audio.PauseMusic();
				//Audio.PlaySoundEffect( SOUND_DIE );
				gamestate.PlayerDied();
			} break;
	}
	
}

// ----------------------------------------------------------------------------
// PlayOutro() - Plays the whole outro sequence
// ----------------------------------------------------------------------------
void Gamestate::PlayOutro()
{	
	demon.isKicking = false;
	demon.isJumping = false;
	demon.isPunching = false;
	demon.isMovingRight = true;

	demon.Update();
	//demon.UpdatePlayer();

	int IntroState = 0;
	int Letter = 0, LetterWidth = 0, Line = 0;
	string FinishLine = "On Marjuras northwestern coast claimed that there are graves after a fallen kingdom. Grave Robber think there is gold and riches and Marjuras indigenous kvurerna believe that somewhere in the graves is a powerful weapon that can relieve Marjura from evil. Are you up for the task?";
	string FinishSlow[ 7 ];
	int Counter = 0;
	SDL_Surface * FinishSurface;

	bool Walk = true;

	SDL_Color textColor = { 255, 255, 255 };

	float speedJumpDemon = 0.0;

	bool JumpDown = false, JumpUp = true;

	Timer speed;
	speed.Start();

	SDL_Rect srcRect = { 0, 0, 800, 600 };
	SDL_Rect destRect = { 0, 0, 800, 600 };

	bool Finish = false;
	while( Finish != true )
	{
		while( speed.GetTicks() < 1000 / 40 )
        {
            //wait    
			
        }
		
		switch( IntroState )
		{
			speedJumpDemon += 100.0f * ( gamestate.dt / 1000 );

		case 0:
			{
				if( demon.GetPosition().x > 580 )
				{
					Walk = false;
					if( JumpUp ) 
					{
						//demon.yPos -= abs( 20 * cos( speedJumpDemon ) );
						//demon.xPos += abs( 5 * cos( speedJumpDemon ) );
						//demon.xVel += abs( 5 * cos( speedJumpDemon ) );
						//demon.yVel -= abs( 20 * cos( speedJumpDemon ) );
						/*
						if( demon.yPos < GROUND_Y - 100 )
						{
							JumpUp = false;
							JumpDown = true;
						}*/
					}
					else if( JumpDown )
					{
						//demon.yPos += abs( 10 * cos( speedJumpDemon ) );
						//demon.yVel += abs( 10 * cos( speedJumpDemon ) );
						if( demon.GetPosition().y > GROUND_Y + 80 )
						{
							IntroState = 1;
						}
					}
					
				}
				else if( demon.GetPosition().x < 580 && Walk == true )
				{
    					demon.isMovingRight = true;
				}

				gamestate.drawParallaxLayers();
				gamestate.DrawSprite();
				gamestate.DrawBackgroundBlack();
				break;
			}
		case 1:
			{
				SDL_BlitSurface(	Gfx.GetSurface( gamestate.m_srfOutro ),
									&srcRect, gamestate.BackBuffer, &destRect );
				if( Counter > 2 )
				{
					Counter = 0;
					
					LetterWidth++;

					if( Letter < FinishLine.length() )
					{
						Letter++;
					}
					else
					{
						IntroState = 2;
					}

					FinishSlow[ Line ] += FinishLine[ Letter ];
					for( int i = 0; i < 7; i++ )
					{
						FinishSurface = TTF_RenderText_Solid( gamestate.font, FinishSlow[ i ].c_str(), textColor );
						gamestate.apply_surface( 300, i * 40, FinishSurface, gamestate.BackBuffer );
					}
				}

				for( int i = 0; i < 7; i++ )
				{
					FinishSurface = TTF_RenderText_Solid( gamestate.font, FinishSlow[ i ].c_str(), textColor );
					gamestate.apply_surface( 300, i * 40, FinishSurface, gamestate.BackBuffer );
				}
				
				if( LetterWidth > 20 )
				{
					LetterWidth = 0;
					Line++;
				}

				Counter++;
				break;
			}
		case 2:
			{
				Finish = true;
				break;
			}
		}
		gamestate.FLIP();

	}
	gamestate.GameCondition = GS_INTRO;
}

// ----------------------------------------------------------------------------
// DoIntroTalk() - does the intro where all the talking takes place.
// ----------------------------------------------------------------------------
void Gamestate::DoIntroTalk()
{
	Intro->DoTalk();
}

// ----------------------------------------------------------------------------
// PlayerDied() - Plays the whole death sequence
// ----------------------------------------------------------------------------
void Gamestate::PlayerDied()
{
	SDL_Rect srcRect = { 0, 0, 800, 600 };
	SDL_Rect destRect = { 0, 0, 800, 600 };


	SDL_Event input;

	while( gamestate.GameCondition == GS_DEAD )
	{
		SDL_PollEvent( &input );
		if( input.type == SDL_KEYDOWN )
		{
  			switch( input.key.keysym.sym )
			{
			case SDLK_SPACE:
				gamestate.GameCondition = GS_INTRO;
				break;
			}
		}
		DrawBackgroundBlack();
		SDL_BlitSurface( Gfx.GetSurface( gamestate.m_srfOutro ),	&srcRect, gamestate.BackBuffer, &destRect );
		SDL_Color textColor = { 255, 255, 255 };
		SDL_Color textColor2 = { 0, 0, 0 };
		sprintf_s( gamestate.Text, 256, " Press Space For Menu " );
		gamestate.textIntro = TTF_RenderText_Shaded( gamestate.font, gamestate.Text, textColor, textColor2 );
		gamestate.apply_surface( 250, 500, gamestate.textIntro, gamestate.BackBuffer );
		gamestate.FLIP();
	}
	/*
	ListHighScore->sort( gamestate.name->str.c_str(), _Score );
	ListHighScore->Save();

	int PlayerDieState = 0;
	outro = new Outro;
	int Letter = 0;
	int LetterWidth = 0;
	int Line = 0;
	int Counter = 0;
	string DeathTalks = " Your sole is mine fallen one, At this rate all the souls of the earth will be mine soon!!! Ha Ha Ha ";
	string DeathTalkSlow[ 8 ];

	SDL_Color textColor = { 255, 255, 255 };
	SDL_Event input;

	SDL_Color Stone = { 105, 105, 136 };
	SDL_Color StoneFront = { 0, 0, 0, 255 };

	bool PlayDeadAnimation = true; 
	while( PlayDeadAnimation == true )
	{
		SDL_PollEvent( &input );
		if( input.type == SDL_KEYDOWN )
		{
			switch( input.key.keysym.sym )
			{
			case SDLK_SPACE:
				PlayerDieState = 2;
				break;
			}
		}

		DrawBackgroundBlack();
		gamestate.DrawAllText();
		switch( PlayerDieState )
		{
		case 0:
			{
				if( timer.Timer_ShowDead > 10 )
				{
					PlayerDieState = 1;
					timer.Timer_ShowDead = 0.0f;
				}

				timer.Timer_ShowDead++;
				//SDL_BlitSurface(	Gfx.GetSurface( outro->surface ), &outro->ClipsOutro[ 0 ],
				//					gamestate.BackBuffer, &outro->ClipsOutro[ 1 ] );
				break;
			}
		case 1:
			{
				if( Counter > 5 )
				{
					Counter = 0;

					if( Letter < DeathTalks.length() )
					{
						Letter++;
					}
					else
					{
						PlayerDieState = 2;
					}

					DeathTalkSlow[ Line ] += DeathTalks[ Letter ];
					for( int i = 0; i < 8; i++ )
					{
						DeathSurface[ 0 ] = TTF_RenderText_Solid( gamestate.font, DeathTalkSlow[ i ].c_str(), textColor );
						gamestate.apply_surface( 300, i * 40, DeathSurface[ 0 ], gamestate.BackBuffer );
					}

					LetterWidth++;
				}
						
				SDL_BlitSurface(	Gfx.GetSurface( outro->surface ), &outro->ClipsOutro[ 0 ],
									gamestate.BackBuffer, &outro->ClipsOutro[ 1 ] );

				for( int i = 0; i < 8; i++ )
				{
					DeathSurface[ 0 ] = TTF_RenderText_Solid( gamestate.font, DeathTalkSlow[ i ].c_str(), textColor );
					gamestate.apply_surface( 300, i * 40, DeathSurface[ 0 ], gamestate.BackBuffer );
				}
				
					
				if( LetterWidth > 20 )
				{
					LetterWidth = 0;
					Line++;
				}

				Counter++;
				break;
			}
		case 2:
			{
				PlayDeadAnimation = false;
				break;
			}	
		}
		
		DeathSurface[ 1 ] = TTF_RenderText_Blended( gamestate.font, gamestate.name->str.c_str(), StoneFront );
		gamestate.apply_surface( 160, 450, DeathSurface[ 1 ], gamestate.BackBuffer );
		gamestate.FLIP();
	}

	gamestate.GameCondition = GS_INTRO;	*/

}

// ----------------------------------------------------------------------------
// DrawAllText() - draws all text thats currently shown on the screen.
// ----------------------------------------------------------------------------
void Gamestate::DrawAllText()
{
	Audio.PauseMusic();
	if( GameCondition == GS_INTROSTORY || GameCondition == GS_DEAD )
	{
		SDL_Color textColor = { 255, 255, 255 };
		SDL_Color textColor2 = { 0, 0, 0 };
		
		if( GameCondition == GS_DEAD )
		{
			sprintf_s( gamestate.Text, 256, " Press Space For Menu " );
			gamestate.textIntro = TTF_RenderText_Shaded( gamestate.font, gamestate.Text, textColor, textColor2 );
			gamestate.apply_surface( 200, 500, gamestate.textIntro, gamestate.BackBuffer ); 
		}
		else
		{
			sprintf_s( gamestate.Text, 256, " Press Space To Start " );		
			gamestate.textIntro = TTF_RenderText_Shaded( gamestate.font, gamestate.Text, textColor, textColor2 );
			gamestate.apply_surface( 200, 500, gamestate.textIntro, gamestate.BackBuffer ); 
		}
	}
	else
	{
		//The color of the font
		SDL_Color textColor = { 251, 245, 32 };

		// print out the score
		sprintf_s(gamestate.Text, 256, "%i ", gamestate.GetScore() );		
		gamestate.srfText = TTF_RenderText_Solid( gamestate.font, Text, textColor );
		gamestate.apply_surface( 100, 20, gamestate.srfText, gamestate.BackBuffer ); 
	}
}

// ----------------------------------------------------------------------------
// Loading() - draws the loading screen on the screen. Dragon dancing
// ----------------------------------------------------------------------------
void Gamestate::Loading()
{
	//currentAnimFrame += deltaTime * animFramesPerSecond;
	SDL_SetAlpha( m_surfaceList[  Dragon->surface ], SDL_SRCALPHA, 255 );

	float Speed = 1000.0f * ( dt / 1000.0f );
	SDL_Rect dstRect = { Dragon->xPos, Dragon->yPos, Dragon->Width, Dragon->Height };
	if ( gamestate.IntroDone == false )
	{
					SDL_BlitSurface(	Gfx.GetSurface( Dragon->surface ), &Dragon->Clips[ Dragon->Frame ],
								gamestate.BackBuffer, &dstRect );
			//Dragon->PrevFrame = Dragon->Frame;
			Dragon->SetFrame();		
			/*
		if( timer.Timer_Dancing >= (1000.f /dt) / 60 )
		{
			timer.Timer_Dancing = 0;
			
			SDL_BlitSurface(	m_surfaceList[ Dragon->surface ], &Dragon->Clips[ Dragon->Frame ],
								gamestate.BackBuffer, &dstRect );
			Dragon->PrevFrame = Dragon->Frame;
			Dragon->SetFrame();		
		}
		else
		{
			SDL_BlitSurface(	m_surfaceList[ Dragon->surface ], &Dragon->Clips[ Dragon->PrevFrame ],
								gamestate.BackBuffer, &dstRect );
			timer.Timer_Dancing++;
		}*/
		
	}
}

// ----------------------------------------------------------------------------
// DrawBoss() - hmmm.
// ----------------------------------------------------------------------------
void Gamestate::DrawBoss()
{
	gamestate.boss->UpdateBoss();
}

// ----------------------------------------------------------------------------
// GetSurface() - hmmm.
// ----------------------------------------------------------------------------
SDL_Surface * Gamestate::GetSurface( int WhichSurface )
{
	return m_surfaceList[ WhichSurface ];	
}

// ----------------------------------------------------------------------------
// GetSurface() - gives backbuffer to destination buffer streches and all
// ----------------------------------------------------------------------------
void Gamestate::FLIP()
{
	SDL_Rect srcRect = { 0, 0, gamestate.BackBuffer->w, gamestate.BackBuffer->h };
	SDL_Rect destRect = { 0, 0, gamestate.SCREEN_WIDTH, gamestate.SCREEN_HEIGHT };
					
	gamestate.PasteScreenToAnother( srcRect, destRect );

	//flips screen
	if( SDL_Flip( gamestate.screen ) == -1)
	{
		gamestate.GameOK = false;
	}
}

// ----------------------------------------------------------------------------
// MainScreen() - Draws the mainscreen, checks conditions. MenuScreen
// ----------------------------------------------------------------------------
void Gamestate::MainScreen()
{
	SDL_Surface * Surface_Credits = NULL;
	SDL_Surface * Surface_HighScore = NULL;

	ParallaxLayer  * MyParaBackGround;
	MyParaBackGround = Parallax->getLayer( TitleScreen->surface );

	SDL_Rect scRect = { 0, 0, 800, 600 };

	SDL_Rect dtRect = {	0, 0, 800, 600 };

	SDL_BlitSurface( Gfx.GetSurface( TitleScreen->surface ), &scRect, gamestate.BackBuffer, &dtRect ); 
	if( CheckingHighScore == true )
	{
		ListHighScore->sort( gamestate.name->str.c_str(), gamestate.GetScore() );
		ListHighScore->Save();

		delete ListHighScore;
		ListHighScore = new FillHighScore;
		CheckingHighScore = false;

		for( int i = 0; i < 5; i++ )
		{
			char temp[ 256 ];
			sprintf_s(	temp, 256, "Name: %s Score: %i", ListHighScore->list[ i ].name.c_str(), ListHighScore->list[ i ].Score );	
			gamestate.HighScoreList[ i ] = temp;
		}
	}

	if( TitleScreen->ButtonOptions == false )
	{
		for( int i = 0; i < 4; i++ )
		{
			//SDL_FillRect(gamestate.GetSurface( TitleScreen->SurfaceButt),&TitleScreen->DestClips[ i ],SDL_MapRGB(gamestate.GetSurface( TitleScreen->SurfaceButt)->format,255,0,255) );
			
			SDL_BlitSurface(	Gfx.GetSurface( TitleScreen->SurfaceButt ), 
								&TitleScreen->ButtonClips[ i ],
								gamestate.BackBuffer, &TitleScreen->DestClips[ i ] ); 
		}
	}
	else if( TitleScreen->ButtonHighScore == true )
	{
		/*
		SDL_BlitSurface(	gamestate.GetSurface( TitleScreen->SurfaceButt ),
							&TitleScreen->ButtonClips[ 4 ],
							gamestate.BackBuffer, &TitleScreen->DestClips[ 8 ] ); 	
							*/

		SDL_BlitSurface(	Gfx.GetSurface( TitleScreen->SurfaceButt ),
							&TitleScreen->ButtonClips[ 7 ],
							gamestate.BackBuffer, &TitleScreen->DestClips[ 7 ] ); 

		SDL_Color textColor = { 0,0,0 };
		
		for( int i = 0; i < 5; i++ )
		{
			Surface_HighScore =		TTF_RenderText_Solid( gamestate.font, 
									gamestate.HighScoreList[ i ].c_str(), textColor );
			apply_surface( 50, 270 + i * 40, Surface_HighScore, gamestate.BackBuffer );
		}

	}
	else if( TitleScreen->ButtonCredits == true )
	{
		SDL_BlitSurface(	Gfx.GetSurface( TitleScreen->SurfaceButt ),
							&TitleScreen->ButtonClips[ 8 ],
							gamestate.BackBuffer, &TitleScreen->DestClips[ 9 ] ); 

		SDL_BlitSurface(	Gfx.GetSurface( TitleScreen->SurfaceButt ),
							&TitleScreen->ButtonClips[ 7 ],
							gamestate.BackBuffer, &TitleScreen->DestClips[ 7 ] ); 

		
		SDL_Color textColor = { 0,0,0 };
		
	
		Surface_Credits =		TTF_RenderText_Solid( gamestate.font, 
								" A Risk Production ", textColor );
		apply_surface( 50, 270, Surface_Credits, gamestate.BackBuffer );
	}
	else
	{
		for( int i = 0; i < 8; i++ )
		{
			if( i == 2 || i == 0 || i == 3 )
			{
											
			}
			else
			{
				SDL_BlitSurface(	Gfx.GetSurface( TitleScreen->SurfaceButt ), &TitleScreen->ButtonClips[ i ],
									gamestate.BackBuffer, &TitleScreen->DestClips[ i ] ); 
			}
		}
	}
	
	if( TitleScreen->ButtonNewgame == true )
	{
		gamestate.GameCondition = GS_ENTERNAME;
		TitleScreen->ButtonNewgame = false;

		if( Surface_Credits != NULL )
		{
			SDL_FreeSurface( Surface_Credits );
		}
		if( Surface_HighScore != NULL )
		{
			SDL_FreeSurface( Surface_HighScore );
		}

		gamestate.RestartGame();
	}
	if( TitleScreen->ButtonQuit == true )
	{
		gamestate.GameOK = false;
		TitleScreen->ButtonQuit == false;
	}

	if( TitleScreen->ButtonBack == true )
	{
		TitleScreen->ButtonOptions = false;
		TitleScreen->ButtonBack = false;
		TitleScreen->ButtonHighScore = false;
		TitleScreen->ButtonCredits = false;
		TitleScreen->ButtonBack = false;
	}
}

// ----------------------------------------------------------------------------
// EnterName() - checks for input player name
// ----------------------------------------------------------------------------
void Gamestate::EnterName()
{
	cout << "EnterName gamestate..." << endl;
		SDL_Rect scRect = {	0, 0, 800, 600 };
		SDL_Rect dtRect = {	0, 0, 800, 600 };
		SDL_BlitSurface( Gfx.GetSurface( TitleScreen->surface ), &scRect, gamestate.BackBuffer, &dtRect );
			SDL_Color textColor = { 0,0,0 };
			SDL_Surface * srfEnter;
			srfEnter = TTF_RenderText_Solid( font, gamestate.PlayerName.c_str(), textColor );
		gamestate.apply_surface( 200, 400, srfEnter, gamestate.BackBuffer );
		//gamestate.name->show_centered();
	if( gamestate.name->handle_input(  ) == false )
	{
		gamestate.GameCondition = GS_INTROSTORY;
	}
	/*
	bool Name =  false;
	SDL_Event input;
	SDL_Color textColor = { 0,0,0 };
	gamestate.IntroDone = false;
	SDL_Surface * srfEnter;
	
	while( gamestate.name->handle_input(  ) )
	{
		SDL_Rect scRect = {	0, 0, 800, 600 };
		SDL_Rect dtRect = {	0, 0, 800, 600 };
		SDL_BlitSurface( gamestate.GetSurface( TitleScreen->surface ), &scRect, gamestate.BackBuffer, &dtRect );
		//gamestate.name->handle_input(  );
		//SDL_Delay(1000 / 60);
		timer.Timer_Name++;

		
		//TypeName = TTF_RenderText_Solid( font, " Enter your name ", textColor ); 
		gamestate.name->show_centered();
		//gamestate.apply_surface( 250, 200, TypeName, gamestate.BackBuffer );

		srfEnter = TTF_RenderText_Solid( font, " Press Enter To Finish ", textColor );
		gamestate.apply_surface( 200, 400, srfEnter, gamestate.BackBuffer );

		gamestate.FLIP();
	}

	gamestate.GameCondition = GS_INTROSTORY;
	*/
}

void Gamestate::RestartGame()
{
	ResetPlayer();
	ResetBoss();
	ResetEnemies();
	ResetObjects();
	ResetRest();

	timer.RestartTimers();

	demon.InitiateDemon( demon.DemonSurface, GROUND_X, GROUND_Y, DEMONHEIGHT, DEMONWIDTH );
	//gamestate.Score = 0;
	gamestate.m_parallax = 0;

}

void Gamestate::ResetRest()
{
	if( Dragon != NULL )
	{
		delete Dragon;
	}
	if( TitleScreen != NULL )
	{
		delete TitleScreen;
	}
	if( Intro != NULL )
	{
		delete Intro;
	}
	if( ListHighScore != NULL )
	{
		delete ListHighScore;
	}

	gamestate.CreateNewThings();
}

// Frees surfaces and deletes thing thats not NULL
void Gamestate::EndAll()
{
	for( int i = 0; i < Parallax->getLayerCount(); i++ )
	{
		SDL_FreeSurface( m_surfaceList[ i ] );
	}

	if( gamestate.Intro != NULL )
	{
		delete Intro;
	}
	if( gamestate.boss != NULL )
	{
		delete boss;
	}
	if( gamestate.outro != NULL )
	{ 
		delete outro;
	}
	if( gamestate.Dragon != NULL )
	{
		delete Dragon;
	}


	ListHighScore->sort( gamestate.name->str, gamestate.GetScore() );
	ListHighScore->Save();

	if( gamestate.name != NULL )
	{
		delete name;
	}

}

void Game::cleanUp()
{
	TTF_Quit();
	SDL_Quit();
}

// writes to file 
void Gamestate::RecordAllData()
{
	ParallaxLayer * LayerToFile;
	ofstream OutToFile("LevelOptions.txt");
	for( int i = 0; i < Parallax->getLayerCount(); i++ )
	{
		LayerToFile = Parallax->getLayer( i );
		OutToFile << "WhichLayer: " << i << endl;
		OutToFile << "Layer_Surface: " << LayerToFile->m_surface << endl;
		OutToFile << "Layer_Width: " << LayerToFile->m_width << endl;
		OutToFile << "Layer_Height: " << LayerToFile->m_height << endl;
		OutToFile << "Layer_WhereOn_Y: " << LayerToFile->m_surfaceYOffset << endl;
		OutToFile << "Layer_Parallax: " << LayerToFile->m_parallax << endl;
		OutToFile << "Destination_X: " << LayerToFile->DX << endl;
		OutToFile << "Destination_Y: " << LayerToFile->DY << endl;
		OutToFile << "Destination_Width: " << LayerToFile->DW << endl;
		OutToFile << "Destination_Height: " << LayerToFile->DH << endl;
		OutToFile << endl;
	}
}

// loads image with chosen value to not show
int Gamestate::Load_imageAlpha( std::string filename, int r, int g, int b )
{
	//temp storage for the image loaded
	SDL_Surface * loadedimage = NULL;

	//optimized image for storage and flipping
	SDL_Surface * optimizedImage = NULL;

	//load image 
	loadedimage = IMG_Load( filename.c_str() );

	//if something went wrong
	if( loadedimage != NULL )
	{
		//create an optimized image 
		optimizedImage = SDL_DisplayFormat( loadedimage );

		//free old image
		SDL_FreeSurface( loadedimage );
	}

	if(optimizedImage != NULL)
	{
		SDL_SetColorKey(optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, r, g, b ) );
	}
	
	int index = findAvailableIndex();
	if( index == -1 )
	{
		return -1;
	}

	m_surfaceList[ index ] = optimizedImage;
	return index;
}

// inits sdl, font and videomode
bool Game::Init(SDL_Surface * &screen)
{
	gamestate.screen = 0;


	//initialize all SDL subystems
/*	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1)
	{
		return false;
	} */
	//SDL_WM_SetCaption("", "res/big.ico");
	//SDL_WM_SetIcon(SDL_LoadBMP("res/small.bmp"), NULL);

	//set up the screen
	gamestate.screen = SDL_SetVideoMode(gamestate.SCREEN_WIDTH, gamestate.SCREEN_HEIGHT, gamestate.SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if( screen == NULL )
	{
		return false;
	}

/*	if( TTF_Init() == -1 )
	{
		return false;
	}
	else
	{
		gamestate.font = TTF_OpenFont( "cour.ttf", 28 );
	} */
	
	//set window caption
	SDL_WM_SetCaption( " Demon hunter ", NULL);
	
	/* Create a 32-bit surface with the bytes of each pixel in R,G,B,A order,
       as expected by OpenGL for textures */
    Uint32 rmask, gmask, bmask, amask;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	   on the endianness (byte order) of the machine */

	rmask = 0x00000000;
	gmask = 0x00000000;
	bmask = 0x00000000;
	amask = 0x00000000;

	gamestate.BackBuffer = SDL_CreateRGBSurface( SDL_HWSURFACE, gamestate.SCREEN_WIDTH, gamestate.SCREEN_HEIGHT, gamestate.SCREEN_BPP,
								   rmask, gmask, bmask, amask);
	
	if( gamestate.BackBuffer == NULL )
	{
		return false;
	}
	return true;
}

// ----------------------------------------------------------------------------
// drawParallaxLayers() - renders parallax-layers to backbuffer and gives it to Main Surface
// ----------------------------------------------------------------------------
void Gamestate::drawParallaxLayers()
{
	if( gamestate.GameCondition != GS_LEVEL1BOSS && gamestate.GameCondition != GS_OUTRO )
	{
		/*
		if( demon.xVel >= STARTSCROLLING - 50 )
		{
			// Updating the background to scroll when character is moving
			if( demon.isMovingRight )
			{
				gamestate.m_paralax += 20;
			}
			else if( demon.isMovingLeft )
			{
				gamestate.m_paralax -= 20;
			}
		}
		*/
		gamestate.CreateAll();
	}
	else
	{
		if( !BossStart )
		{
			//demon.DemonHunter = true;
			//demon.SmallHunter = false;
			gamestate.boss = gamestate.CreateBoss( SCREEN_WIDTH - 180, GROUND_Y - 210, m_srfBoss );
			BossStart = true;
		}
	}

		//// Draw parallax layers
		ParallaxLayer  * MyParaBackGround;
		MyParaBackGround = Parallax->getLayer( 0 );

		SDL_Rect scRect = { 0, 0,	MyParaBackGround->m_width, 
									MyParaBackGround->m_height };

		SDL_Rect dtRect = {	0, 0, MyParaBackGround->DW, MyParaBackGround->DH };

		SDL_BlitSurface( Gfx.GetSurface(MyParaBackGround->m_surface), &scRect, gamestate.BackBuffer, &dtRect );
		//SDL_BlitSurface( m_surfaceList[ MyParaBackGround->m_surface ], &scRect, gamestate.BackBuffer, &dtRect ); 

		//gamestate.stretchPicToBackBuffer( MyParaBackGround, scRect, dtRect );

		int x = 0;
		for( int i = 1; i < Parallax->getLayerCount(); ++i )
		{		
			// Calc rects
			MyParaBackGround = Parallax->getLayer( i );
			if( MyParaBackGround->m_surface == m_srfClouds )
			{
				MyParaBackGround->AnimClouds += 100.0f * gamestate.dt;

				//////// Calc parallax position
				x = (int)( MyParaBackGround->m_parallax * (float)( +MyParaBackGround->AnimClouds ) );  
				if( x < 0 )	// neg -> pos
				{
					x *= -1;	// invert sign, because % only works with positive integers
					x = MyParaBackGround->m_width - (x % MyParaBackGround->m_width);
				}
				else
				{
					x %= MyParaBackGround->m_width;
				}

				x -= MyParaBackGround->m_width;	// move one back
			}
			else
			{

				//////// Calc parallax position
				x = (int)( MyParaBackGround->m_parallax * (float)( +gamestate.m_parallax ) );  
				if( x < 0 )	// neg -> pos
				{
					x *= -1;	// invert sign, because % only works with positive integers
					x = MyParaBackGround->m_width - (x % MyParaBackGround->m_width);
				}
				else
				{
					x %= MyParaBackGround->m_width;
				}

				x -= MyParaBackGround->m_width;	// move one back
			}

			for( int i = 0; i < 2; i++ )
			{
				SDL_Rect sourceRect = { 0 + x, MyParaBackGround->m_surfaceYOffset,
										MyParaBackGround->m_width, MyParaBackGround->m_height };

				SDL_Rect destinationRect = {	MyParaBackGround->DX, MyParaBackGround->DY, 
												MyParaBackGround->DW, MyParaBackGround->DH };

				SDL_BlitSurface( Gfx.GetSurface( MyParaBackGround->m_surface ), &sourceRect, gamestate.BackBuffer, &destinationRect ); 			
				//SDL_BlitSurface( m_surfaceList[ MyParaBackGround->m_surface ], &sourceRect, gamestate.BackBuffer, &destinationRect ); 
				
				
				x += MyParaBackGround->m_width;
			}


			MyParaBackGround->HowFarGone = MyParaBackGround->Xpos - MyParaBackGround->m_width;

		}
		gamestate.m_parallax += 500 * gamestate.dt;
}

void Gamestate::CreateAll()
{
	AnimalController.Create_Animals();
	Control_ENEMY.Create_Enemies();
	Control_OBJ.CreateObjects();
}

// draws MyFellow on the screen and changes animations
void Gamestate::DrawSprite()
{
		//SDL_Rect demonDest = { demon.xPos, demon.yPos, demon.Demon_Width, demon.Demon_Height };
		//demonDest = demon.GetPosition();
		if( demon.isImmortal )
		{
			if( demon.AlphaImmortal < SDL_ALPHA_OPAQUE - 100 )
			{
				demon.AlphaImmortal += 50;
			}
			else
			{
				demon.AlphaImmortal -= 50;
			}
			SDL_SetAlpha( Gfx.GetSurface( demon.DemonSurface ), SDL_SRCALPHA | SDL_RLEACCEL, demon.AlphaImmortal );
		}
		else
		{
			SDL_SetAlpha( Gfx.GetSurface( demon.DemonSurface ), SDL_SRCALPHA | SDL_RLEACCEL, SDL_ALPHA_OPAQUE );
		}

		
			//Current_AnimArray = gamestate.WhichMorphType();
			//Current_Frame = demon.UpdatePlayer();
			//demon.UpdatePlayer();
			demon.Update();
		
			// Rendering Demon Character
			/*
			SDL_BlitSurface(	m_surfaceList[ demon.DemonSurface ], 
								&demon.AnimationArrays[ Current_AnimArray ][ Current_Frame ],
								gamestate.BackBuffer, &demonDest );*/
			if( CurrentFrame == 3 )
			{
				CurrentFrame = 0;
			}
			
			SDL_BlitSurface(	Gfx.GetSurface( demon.DemonSurface ), 
				&demon.AnimationArrays[ demon.GetState() ][ ++CurrentFrame ],
				gamestate.BackBuffer, &demon.GetPosition() );
			/*
			SDL_BlitSurface(	m_surfaceList[ emon.DemonSurface ], 
				&demon.AnimationArrays[ demon.GetState() ][ ++CurrentFrame ],
								gamestate.BackBuffer, &demonDest );*/


			gamestate.resetAnimationPace();
			PreviousAnimArray = CurrentAnimArray;
			PreviousFrame = CurrentFrame;
			if( gamestate.GameCondition == GS_OUTRO )
			{
				gamestate.resetAnimationPace();
			}
}

// checks which state the demon is in which animation to use
int Gamestate::WhichMorphType()
{
	return demon.GetMorphState();
/*
	if( demon.SmallHunter )
	{
		return 0;
	}

	else if( demon.MediumHunter )
	{
		return 1;
	}

	else if( demon.LargeHunter )
	{
		return 2;
	}

	else if( demon.DemonHunter )
	{
		return 3;
	}

	return 0;*/
}

// checks if OK to move
bool Gamestate::OK_Pace()
{
	if( GameCondition != GS_OUTRO )
	{
		if( UpdateAnimationSpeed > ANIMPACE )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if( UpdateAnimationSpeed > ANIMPACESLOWER )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

// if enemy OK to move
bool Gamestate::OK_PaceEnemy()
{
	if( UpdateAnimationSpeed > ANIMPACEENEMY )
	{
		return true;
	}
	return false;
}

void Gamestate::AddTick()
{
	 float Speed = 1000.0f * ( gamestate.dt / 1000.0f );
	 UpdateAnimationSpeed += Speed;
}

void Gamestate::resetAnimationPace()
{
	UpdateAnimationSpeed = 0;
}

void Gamestate::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

void Gamestate::stretchPicToBackBuffer( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect )	
{			

	int srcWidth = srcRect.w - srcRect.x;
	int srcHeight = srcRect.h - srcRect.y,
		DestWidth = destRect.w - destRect.x,
		DestHeight = destRect.h - destRect.y;

	SDL_LockSurface( gamestate.BackBuffer );
	SDL_LockSurface( m_surfaceList[ layer->m_surface ] );

	int dstPitch = gamestate.BackBuffer->pitch;
	int pitch = m_surfaceList[ layer->m_surface ]->pitch;

	DWORD * dst = ( DWORD * )gamestate.BackBuffer->pixels;

	DWORD * src = ( DWORD * )m_surfaceList[ layer->m_surface ]->pixels;

	float scaleWidth = srcWidth / ( float )DestWidth;
	float scaleHeight = srcHeight / ( float )DestHeight; 


	float fSrcX = srcRect.x,
		  fSrcY = srcRect.y;

	for(int y = destRect.y;  y < destRect.y + destRect.h; y++ )
	{
		fSrcX = 0;

		for(int x = destRect.x ;  x < destRect.x + destRect.w ; x++)
		{
			dst[ ( y * dstPitch / 4) + ( x ) ] = src[ int( ( fSrcY ) * ( pitch / 4 ) + int( fSrcX ) )];

			fSrcX += scaleWidth;
		}

		fSrcY += scaleHeight;	
	}

	SDL_UnlockSurface( gamestate.BackBuffer );
	SDL_UnlockSurface( m_surfaceList[ layer->m_surface ] );

}

void Gamestate::stretchBlit( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect )	
{			

	SDL_LockSurface( gamestate.BackBuffer );
	SDL_LockSurface( m_surfaceList[ layer->m_surface ] );

	int dstPitch = gamestate.BackBuffer->pitch;
	int pitch = m_surfaceList[ layer->m_surface ]->pitch;

	DWORD * dst = ( DWORD * )gamestate.BackBuffer->pixels;

	DWORD * src = ( DWORD * )m_surfaceList[ layer->m_surface ]->pixels;

	float scaleWidth = srcRect.w / ( float )destRect.w;
	float scaleHeight = srcRect.h / ( float )destRect.h; 


	float fSrcX = srcRect.x,
		  fSrcY = srcRect.y;

	for(int y = destRect.y;  y < destRect.y + destRect.h; y++ )
	{
		fSrcX = srcRect.x;

		for(int x = destRect.x ;  x < destRect.x + destRect.w ; x++)
		{
			dst[ (y * dstPitch / 4) + (x) ] = src[ int((fSrcY) * (pitch / 4) + int(fSrcX) )];

			fSrcX += scaleWidth;
		}
		fSrcY += scaleHeight;	
	}

	SDL_UnlockSurface( gamestate.BackBuffer );
	SDL_UnlockSurface( m_surfaceList[ layer->m_surface ] );

}

void Gamestate::PasteScreenToAnother( SDL_Rect srcRect, SDL_Rect destRect )	
{			

	SDL_LockSurface( gamestate.screen );
	SDL_LockSurface( gamestate.BackBuffer );

	int dstPitch = gamestate.screen->pitch;
	int pitch = gamestate.BackBuffer->pitch;

	DWORD * dst = ( DWORD * )gamestate.screen->pixels;
	DWORD * src = ( DWORD * )gamestate.BackBuffer->pixels;

	float scaleWidth = gamestate.BackBuffer->w / ( float )destRect.w;
	float scaleHeight = gamestate.BackBuffer->h / ( float )destRect.h; 


	float fSrcX = 0.0f,
		  fSrcY = 0.0f;

	for(int y = destRect.y;  y < destRect.y + destRect.h; y++ )
	{
		fSrcX = 0.0f;

		for(int x = destRect.x ;  x < destRect.x + destRect.w ; x++)
		{
			dst[ (y * dstPitch / 4) + (x) ] = src[ int(fSrcY) * (pitch / 4) + int(fSrcX) ];

			fSrcX += scaleWidth;
		}

		fSrcY += scaleHeight;	
	}

	SDL_UnlockSurface( gamestate.screen );
	SDL_UnlockSurface( gamestate.BackBuffer );

}

// --------------------------------------------------------------------------------------
// blit() - blits offscreen surface to (xpos,ypos) on backbuffer
// --------------------------------------------------------------------------------------
void Gamestate::blit( int index, int xpos, int ypos, bool transparent )
{
	// Calc rects
	SDL_Rect srcRect = { 0, 0, m_surfaceList[ index ]->w, m_surfaceList[ index ]->h };
	SDL_Rect destRect = { xpos, ypos, xpos+m_surfaceList[ index ]->w, ypos+m_surfaceList[ index ]->h };


	// Blit!
	if( transparent )
		SDL_BlitSurface(m_surfaceList[index], &destRect, gamestate.screen, &srcRect );
		/*m_lpddsBackbuffer->Blt( &destRect, m_surfaceList[index], &srcRect, DDBLT_WAIT|DDBLT_KEYSRC, 0 );*/
	else
		SDL_BlitSurface(m_surfaceList[index], &destRect, gamestate.screen, &srcRect );

}

// ----------------------------------------------------------------------------
// setUpParallaxLayers() - initializes parallax-struct
// ----------------------------------------------------------------------------
void Gamestate::setUpParallaxLayers()
{
	// Create background
	int i = 0;
	Parallax = new ParallaxBackground();
	Parallax->createLayers( 10 );

	//Firstlayer
	Parallax->setLayer( 0, 0, m_srfBlack, 0, gamestate.BackBuffer->w, gamestate.BackBuffer->h, 0, 0, gamestate.BackBuffer->w, gamestate.BackBuffer->h );

	////sky
	Parallax->setLayer( 1, 0.0f, m_srfSky, 0, 800, 400, 0, 0, gamestate.BackBuffer->w, gamestate.BackBuffer->h );


	//clouds
	Parallax->setLayer(	3, 0.5f, m_srfClouds, 
						0, 800, 38, 0, 0, gamestate.BackBuffer->w, 
						gamestate.BackBuffer->h );

	Parallax->setLayer(	4, 0.4f, m_srfClouds, 
						38, 800, 87, 0, 38, gamestate.BackBuffer->w, 
						gamestate.BackBuffer->h );

	Parallax->setLayer(	5, 0.3f, m_srfClouds, 
						126, 800, 46, 0, 126, gamestate.BackBuffer->w, 
						gamestate.BackBuffer->h );

	Parallax->setLayer(	6, 0.2f, m_srfClouds, 
						172, 800, 21, 0, 172, gamestate.BackBuffer->w, 
						gamestate.BackBuffer->h );

	Parallax->setLayer(	7, 0.1f, m_srfClouds, 
						193, 800, 12, 0, 193, gamestate.BackBuffer->w, 
						gamestate.BackBuffer->h );

	// City
	Parallax->setLayer( 8, 0.7f, m_srfCity, 0, 5100, 535, 0, 0, gamestate.BackBuffer->w, gamestate.BackBuffer->h );

	// trees
	Parallax->setLayer( 2, 0.7f, m_srfTrees, 0, 1172, 170, 0, 370, gamestate.BackBuffer->w, 170 ); 

	// WalkPath
	Parallax->setLayer(	9, 1.0f, m_srfCity, 
						540, 5100, 60, 0, 535, gamestate.BackBuffer->w, 
						gamestate.BackBuffer->h );

	//gamestate.RecordAllData();
}

void Gamestate::AddScore(int value)
{
	_Score += value;	
}

int Gamestate::GetScore()
{
	return _Score;
}