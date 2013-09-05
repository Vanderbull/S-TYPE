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
#include "Objects.h"
#include "Enemies.h"
#include "TImers.h"
#include "Paralaxlayers.h"
#include "Animals.h"
#include "Bullets.h"
#include "MainMenu.h"
#include "Collision.h"
#include "OutroFinish.h"
#include "GetInput.h"
#include "CBoss.h"
#include "World\CWorld.h"

Gamestate gamestate;


Gamestate::Gamestate()
{
	WorldController.CreateWorld();
	cout << "Initializing Gamestate...." << endl;

	State = MENU_MAIN_STATE;
	cout << "GameCondition: MENU_MAIN_STATE" << endl;

	//BossStart = false;	// Tells game if you have reached the boss
	//IntroDone = false;	// Used in Gamestate::Loading might be removed
			
	gBoss.SetSurface(1);

	//pBoss = NULL; // Pointer to Boss object
	//Intro = NULL; // Pointer to introtalk object
	outro = NULL; // Pointer to outro object
	//font = NULL;  //Pointer to font
	//srfText = NULL;	// Pointer to Text surface

	//PreviousFrame = 0;
	//CurrentFrame = 0;
	//m_parallax = 0;
	Parallax = 0.0f;
	//LevelProgress = 0;

	//dt = 0.0f;
	DeltaTime = 0.0f;
}
void Gamestate::KeyMapping(SDL_Event _event)
{
	bool KEYS[322];  // 322 is the number of SDLK_DOWN events


	for(int i = 0; i < 322; i++) { // init them all to false
	   KEYS[i] = false;
	}

	SDL_EnableKeyRepeat(0,0); // you can configure this how you want, but it makes it nice for when you want to register a key continuously being held down

	if( BCPlayer.GetState() == BaseCharacter::State::MOVING_RIGHT)
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

void Game::HandleEvents( SDL_Event _event )
{	
	if( _event.type == SDL_KEYUP )
	{
		BCPlayer.SetState(BaseCharacter::State::IDLE);

		switch( _event.key.keysym.sym )		
		{
		case SDLK_RIGHT:
			{
				BCPlayer.xVelocity = 0.0f;
			} break;
		case SDLK_LEFT:
			{
				BCPlayer.xVelocity = 0.0f;
			} break;
		case SDLK_UP:
			{
				BCPlayer.yVelocity = 0.0f;
			} break;
		case SDLK_DOWN:
			{
				BCPlayer.yVelocity = 0.0f;
			} break;
		case SDLK_SPACE:
			{
				//cout << "Released SPACEBAR key" << endl;
			} break;
		case SDLK_LALT:
			{
				//cout << "Released the LEFT ALT key" << endl;
			} break;
		}
	}
	else if( _event.type == SDL_QUIT  )
	{
		Quit = true;
	}
	else if( _event.type == SDL_KEYDOWN )
	{
		switch( _event.key.keysym.sym )
		{
		case SDLK_RIGHT:
			{
				BCPlayer.AddAction("RIGHT");
				BCPlayer.xVelocity = 1.0f;
			} break;
		case SDLK_LEFT:
			{
				BCPlayer.AddAction("LEFT");
				BCPlayer.xVelocity = -1.0f;
			} break;
		case SDLK_UP:
			{
				BCPlayer.AddAction("UP");
				BCPlayer.yVelocity = 1.0f;
			} break;
		case SDLK_DOWN:
			{
				BCPlayer.AddAction("DOWN");
				BCPlayer.yVelocity = -1.0f;
			} break;
		case SDLK_SPACE:
			{
				BulletController.Create_Bullets();
				BCPlayer.AddAction("FIRE");
				BCPlayer.AddBeam("Laser");
				cout << BCPlayer.GetBeam() << endl;
				SDL_Rect srcRect = { 0, 0, 800, 600 };
				Gfx.FLIP();
			} break;
		case SDLK_LALT:
			{
				BCPlayer.AddAction("FIRE_SPECIAL");
			} break;
		case SDLK_BACKSPACE:
			{
				if( gamestate.demonName.length() != 0 )
				{
					gamestate.demonName.erase( gamestate.demonName.length() - 1 );
				}
			} break;
		case SDLK_RETURN:
			{
				BCPlayer.AddAction("RETURN");
			} break;
		default:
			{
				BCPlayer.AddAction("DEFAULT");
			}
		}
	}
	else
	{
		//cout << "no key presses or releases are made" << endl;
		BCPlayer.SetState(BaseCharacter::State::IDLE);
	}
	// if intro checks mouseposition and checks for presses
	if( gamestate.State == MENU_MAIN_STATE )
	{
		SDL_GetMouseState(&MouseXCoordinates, &MouseYCoordinates);
		cout << "(" << MouseXCoordinates << "," << MouseYCoordinates << ")" << endl;
		for( int i = 0; i < 8; i++ )
		{
			if(MouseXCoordinates > gamestate.TitleScreen->DestClips[ i ].x && 
			MouseXCoordinates < gamestate.TitleScreen->DestClips[ i ].x + gamestate.TitleScreen->DestClips[ i ].w &&
			MouseYCoordinates > gamestate.TitleScreen->DestClips[ i ].y &&
			MouseYCoordinates < gamestate.TitleScreen->DestClips[ i ].y + gamestate.TitleScreen->DestClips[ i ].h )
			{
				cout << "Entering button " << i << "..." << endl;
			}
		}
		if( _event.type == SDL_MOUSEBUTTONDOWN )
		{
			for( int i = 4; i < 8; i++ )
			{
					if( _event.button.x > gamestate.TitleScreen->DestClips[ i ].x && 
					_event.button.x < gamestate.TitleScreen->DestClips[ i ].x + gamestate.TitleScreen->DestClips[ i ].w &&
					_event.button.y > gamestate.TitleScreen->DestClips[ i ].y &&
					_event.button.y < gamestate.TitleScreen->DestClips[ i ].y + gamestate.TitleScreen->DestClips[ i ].h )
					{
						cout << "Hit button..." << endl;
					}
			}
			//if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))
			//	cout << "Mouse Button 1(left) is pressed." << endl;
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
							case 4: gamestate.TitleScreen->ButtonHighScore = true; break;
							case 5: gamestate.TitleScreen->ButtonCredits = true; break;
							case 6: gamestate.TitleScreen->ButtonSound = true; break;
							case 7: gamestate.TitleScreen->ButtonBack = true; break;
						}
					}
				}

			}
			else
			{
				// checks if mousebutton is pressed at newgame, options or quit
				for( int i = 0; i < 3; i++ )
				{
					if( _event.button.x > gamestate.TitleScreen->DestClips[ i ].x && 
						_event.button.x < gamestate.TitleScreen->DestClips[ i ].x + gamestate.TitleScreen->DestClips[ i ].w &&
						_event.button.y > gamestate.TitleScreen->DestClips[ i ].y &&
						_event.button.y < gamestate.TitleScreen->DestClips[ i ].y + gamestate.TitleScreen->DestClips[ i ].h )
					{
						switch( i )
						{
							case BUTTON_NEW_GAME: cout << "Hoovering new game button" << endl ; break;
							case BUTTON_OPTIONS: cout << "Hoovering options button" << endl; break;
							case BUTTON_QUIT: cout << "Hoovering quit button" << endl; Game::Quit = true; break;
						}
						if( _event.type == SDL_MOUSEBUTTONDOWN )
						{
							switch( i )
							{
								case BUTTON_NEW_GAME: gamestate.TitleScreen->ButtonNewgame = true; break;
								case BUTTON_OPTIONS: gamestate.TitleScreen->ButtonOptions = true; break;
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
	cout << "Resetting Level progress to 0..." << endl;
	LevelProgress = 0;
	Quit = false;
	/*
	if( TTF_Init() == -1 )
	{
		cout << "TTF_INIT FAILED..." << endl;
	}
	else
	{
		gamestate.font = TTF_OpenFont( "Fonts/PressStart2P.ttf", 14 );
		SDL_Quit();
	}
	  */
	// Setup of the application icons
	SDL_WM_SetCaption("", "res/big.ico");
	SDL_WM_SetIcon(SDL_LoadBMP("res/small.bmp"), NULL);

	//gamestate.GameOK = true;
	Init( Gfx.screen );
	
	// h 100 w 130
	//demon.Initiatedemon( demon.demonSurface, GROUND_X, GROUND_Y, demonHEIGHT, demonWIDTH ); 

	gamestate.load_files();
	//demon.Set_clips();
	//new setclips function
	BCPlayer.SetClips();
}

// loads all graphic files and all new files and the font
void Gamestate::load_files()
{	
	m_srfCity = Gfx.Load_imageAlpha( "Graphics/srfCity.png", 0, 0, 0 );
	m_srfClouds = Gfx.Load_imageAlpha( "Graphics/srfClouds.png", 255, 255, 255 );
	m_srfBlack = Gfx.Load_imageAlpha( "Graphics/srfBlack.png", 0, 0, 0 );
	m_srfSky = Gfx.Load_imageAlpha( "Graphics/srfSky.png", 0, 0, 0 );
	m_srfTrees = Gfx.Load_imageAlpha( "Graphics/srfTrees.png", 0, 0, 0 );
	BCPlayer._Surface = Gfx.Load_imageAlpha( "Graphics/demonSurface.png", 255, 255, 255 );
	m_srfEnemyZombie = Gfx.Load_imageAlpha( "Graphics/srfEnemyZombie.png", 255, 0, 255 );
	m_srfSkeleton = Gfx.Load_imageAlpha( "Graphics/srfSkeleton.png", 255, 0, 255  );
	m_srfCrow = Gfx.Load_imageAlpha( "Graphics/srfCrow.png", 255, 255, 255 );
	m_srfCoffin  = Gfx.Load_imageAlpha( "Graphics/srfCoffin.png", 97, 68, 43 );
	m_srfBoss = Gfx.Load_imageAlpha( "Graphics/srfBoss.png", 255, 255, 255 );
	m_srfdemonLife = Gfx.Load_imageAlpha( "Graphics/srfdemonLife.png", 255, 255, 255 );
	m_srfdemonHealthAndFire = Gfx.Load_imageAlpha( "Graphics/srfdemonHealthAndFire.png", 0, 0, 0 );
	m_srfDragon = Gfx.Load_imageAlpha( "Graphics/srfDragon.png", 0, 0, 0 );
	m_srfStart = Gfx.Load_imageAlpha( "Graphics/srfStart.png", 237, 234, 214 );
	m_srfButtons = Gfx.Load_imageAlpha( "Graphics/srfButtons.png", 255, 255, 255 );
	m_srfIntro = Gfx.Load_imageAlpha( "Graphics/srfIntro.png", 255, 255, 255 );
	m_srfMorphing = Gfx.Load_imageAlpha( "Graphics/srfMorphing.png", 255, 255, 241 );
	m_srfReaper = Gfx.Load_imageAlpha( "Graphics/srfReaper.png", 255, 255, 255 );
	m_srfOutro = Gfx.Load_imageAlpha( "Graphics/srfOutro2.png", 0, 0, 0 );
	m_srfButton = Gfx.Load_imageAlpha( "Graphics/srfButton.png", 0, 0, 0 );
	m_srfHealth = Gfx.Load_imageAlpha( "Graphics/srfHealth.png", 0, 0, 0 );
	m_srfLaser = Gfx.Load_imageAlpha( "Graphics/srfLaser.png", 255, 255, 255 );
	
 
 /*
	m_srfCity = Load_imageAlpha( "Graphics/srfCity.png", 0, 0, 0 );
	m_srfClouds = Load_imageAlpha( "Graphics/srfClouds.png", 0, 0, 0 );
	m_srfBlack = Load_imageAlpha( "Graphics/srfBlack.png", 0, 0, 0 );
	m_srfSky = Load_imageAlpha( "Graphics/srfSky.png", 0, 0, 0 );
	m_srfTrees = Load_imageAlpha( "Graphics/srfTrees.png", 0, 0, 0 );
	demon.demonSurface = Load_imageAlpha( "Graphics/demonSurface.png", 255, 255, 255 );
	m_srfEnemyZombie = Load_imageAlpha( "Graphics/srfEnemyZombie.png", 255, 0, 255 );
	m_srfSkeleton = Load_imageAlpha( "Graphics/srfSkeleton.png", 255, 0, 255  );
	m_srfCrow = Load_imageAlpha( "Graphics/srfCrow.png", 255, 255, 255 );
	m_srfCoffin  = Load_imageAlpha( "Graphics/srfCoffin.png", 255, 0, 255 );
	m_srfBoss = Load_imageAlpha( "Graphics/srfBoss.png", 255, 255, 255 );
	m_srfdemonLife = Load_imageAlpha( "Graphics/srfdemonLife.png", 255, 255, 255 );
	m_srfdemonHealthAndFire = Load_imageAlpha( "Graphics/srfdemonHealthAndFire.png", 0, 0, 0 );
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
		MorphingPics[ i ].x = i * SDL_GetVideoSurface()->w;
		MorphingPics[ i ].y = 0;
		MorphingPics[ i ].h = SDL_GetVideoSurface()->h;
		MorphingPics[ i ].w = SDL_GetVideoSurface()->w;
	}

	setUpParallaxLayers();
}

void Gamestate::CreateNewThings()
{
	Dragon = new DancingDragon( m_srfDragon );
	TitleScreen = new MainMenu( 290,  m_srfStart, m_srfButtons ); 
	//Intro = new IntroTalk( gamestate.m_srfIntro );
	name = new StringInput();
	ListHighScore = new FillHighScore();
}


// ----------------------------------------------------------------------------
// DrawObjects() - Draws all objects, coffins, health etc.
// ----------------------------------------------------------------------------
//void Gamestate::DrawObjects()
//{
//	if( gamestate.GameCondition == GS_LEVEL1BOSS )
//	{
//		ControlObjects.DrawObjects();
//	}
//	else
//	{						  
//		demon.Update();
//		AnimalController.Draw_Animals();
//		EnemyController.Update();
//		EnemyController.Draw_Enemies();
//		ControlObjects.DrawObjects();
//	}	
//}
// ----------------------------------------------------------------------------
// CreateBoss() - Creates the boss gives collisionCircle and pos
// ----------------------------------------------------------------------------
Boss * Gamestate::CreateBoss( int xPos, int yPos, int surface )
{
	Boss * temp = new Boss;
	temp->Surface = surface;
	temp->_Position.x = xPos;
	temp->_Position.y = yPos;

	temp->Radius = ( temp->BossWidth > temp->BossHeight ) ? temp->BossWidth / 2 : temp->BossHeight  / 2;

	return temp;
}

// ----------------------------------------------------------------------------
// MorphMyDude - does the morphing sequence
// ----------------------------------------------------------------------------
void Gamestate::MorphMyDude()
{
	int State = 3;
	SDL_Rect destRect = { 0, 0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h };
	//while( State != -1 )
	//{
	//	
	//	Gfx.DrawBackgroundBlack();
	//
	//	switch( State )
	//	{
	//	case 0:
	//		{
	//			if( timer.MorphPics > 10 )
	//			{
	//				SDL_BlitSurface(	Gfx.GetSurface( m_srfMorphing ), &MorphingPics[ State ], 
	//									Gfx.BackBuffer, &destRect );
	//				State--;
	//				timer.MorphPics = 0;
	//			}
	//			else
	//			{
	//				SDL_BlitSurface(	Gfx.GetSurface( m_srfMorphing ), &MorphingPics[ State ], 
	//				Gfx.BackBuffer, &destRect );
	//				timer.MorphPics++;
	//			}

	//			break;
	//		}
	//	case 1:
	//		{
	//			if( timer.MorphPics > 10 )
	//			{
	//				SDL_BlitSurface(	Gfx.GetSurface( m_srfMorphing ), &MorphingPics[ State ], 
	//									Gfx.BackBuffer, &destRect );
	//				State--;
	//				timer.MorphPics = 0;
	//			}
	//			else
	//			{
	//				SDL_BlitSurface(	Gfx.GetSurface( m_srfMorphing ), &MorphingPics[ State ], 
	//				Gfx.BackBuffer, &destRect );
	//				timer.MorphPics++;
	//			}

	//			break;
	//		}
	//	case 2:
	//		{
	//			if( timer.MorphPics > 10 )
	//			{
	//				SDL_BlitSurface(	Gfx.GetSurface( m_srfMorphing ), &MorphingPics[ State ], 
	//									Gfx.BackBuffer, &destRect );
	//				State--;
	//				timer.MorphPics = 0;
	//			}
	//			else
	//			{
	//				SDL_BlitSurface(	Gfx.GetSurface( m_srfMorphing ), &MorphingPics[ State ], 
	//				Gfx.BackBuffer, &destRect );
	//				timer.MorphPics++;
	//			}
	//			break;
	//		}
	//	case 3:
	//		{
	//			if( timer.MorphPics > 10 )
	//			{
	//				SDL_BlitSurface(	Gfx.GetSurface( m_srfMorphing ), &MorphingPics[ State ], 
	//									Gfx.BackBuffer, &destRect );
	//				State--;
	//				timer.MorphPics = 0;
	//			}
	//			else
	//			{
	//				SDL_BlitSurface(	Gfx.GetSurface( m_srfMorphing ), &MorphingPics[ State ], 
	//				Gfx.BackBuffer, &destRect );
	//				timer.MorphPics++;
	//			}
	//			break;
	//		}
	//	}
	//	//gamestate.FLIP();
	//	Gfx.FLIP();
	//}

	gamestate.State = GAME_RUNNING_STATE;
}

// ----------------------------------------------------------------------------
// DrawBackgroundBlack - draws a background black with the size of screen
// ----------------------------------------------------------------------------
//void Gamestate::DrawBackgroundBlack()
//{
//	if( gamestate.GameCondition == GS_OUTRO )
//	{
//		SDL_FillRect(gamestate.BackBuffer, NULL, SDL_MapRGB(gamestate.BackBuffer->format, 0,0,0));
//		/*
//		ParallaxLayer  * MyParaBackGround;
//		MyParaBackGround = gamestate.Paralax->getLayer( gamestate.m_srfBlack );
//
//		SDL_Rect scRect = { 0, 0,	100, 70 };
//									
//		SDL_Rect dtRect = {	600, 530, 100, 50 };
//
//		SDL_BlitSurface( gamestate.GetSurface( gamestate.m_srfBlack ), &scRect, gamestate.BackBuffer, &dtRect ); 
//		*/
//	}
//	else
//	{
//		SDL_FillRect(gamestate.BackBuffer, NULL, SDL_MapRGB(gamestate.BackBuffer->format, 0,0,0));
//		/*
//		ParallaxLayer  * MyParaBackGround;
//		MyParaBackGround = gamestate.Paralax->getLayer( gamestate.m_srfBlack );
//
//		SDL_Rect scRect = { 0, 0,	MyParaBackGround->m_width, 
//									600 };
//
//		SDL_Rect dtRect = {	0, 0, MyParaBackGround->m_width, 600 };
//
//		SDL_BlitSurface( gamestate.GetSurface( gamestate.m_srfBlack ), &scRect, gamestate.BackBuffer, &dtRect );
//		*/
//	}
//}

void Gamestate::ResetBoss()
{
	//if( gamestate.pBoss != NULL )
	//{
	//	delete gamestate.pBoss;
	//}
}

void Gamestate::ResetEnemies()
{
	if(EnemyController.Enemies.size() != NULL )
	{
		EnemyController.Enemies.clear();
	}
}

// ----------------------------------------------------------------------------
// ResetObjects() - resets all object to its starting values
// ----------------------------------------------------------------------------
void Gamestate::ResetObjects()
{
	if( ObjectController.List_Coffins.size() != NULL )
	{
		ObjectController.List_Coffins.clear();
	}

	if( ObjectController.List_FireBalls.size() != NULL )
	{
		ObjectController.List_FireBalls.clear();
	}

	if( ObjectController.List_PowerUps.size() != NULL )
	{
		ObjectController.List_PowerUps.clear();
	}

	ObjectController.FrameHealth = 0;
	ObjectController.PowerUpMan = false;
	if( ObjectController.WereWolf != NULL )
	{
		delete ObjectController.WereWolf;
		ObjectController.WereWolf = NULL;
	}

	ObjectController.WhichLifeToShow = 0;
	
	return;
}

void Game::Audiotonic()
{
}
// ----------------------------------------------------------------------------
// Update() - Updates the whole game depending on which state it is in
// ----------------------------------------------------------------------------
void Game::Update( SDL_Event input, int iElapsedTime )
{
	CollisionController.Box(BulletController.GetBullets());
	cout << BCPlayer.GetAction() << endl;
	// WhereIsEnd is @ image width + screenwidth 800+5100
	//if( demon.WhereIsEnd >= 5700 ) 
	//if( gamestate.LevelProgress >= 0 )
	//{
	//	gamestate.GameCondition = GS_LEVEL1BOSS;
	//}

	// Check game state
	switch( gamestate.State )
	{
		case MENU_MAIN_STATE:
			{
				//Handle_events( input );
				gamestate.MainScreen(iElapsedTime);
				//gamestate.FLIP();
				//Gfx.FLIP();
			} break;
		//case GS_ENTERNAME:
		//	{
		//		gamestate.EnterName();
		//		//gamestate.FLIP();
		//		//Gfx.FLIP();
		//	} break;	
		case GAME_STORY_STATE:
			{
				gamestate.DoIntroTalk();
				//gamestate.FLIP();
				//Gfx.FLIP();
			} break;
		case GAME_LOADING_STATE:
			{
				gamestate.Loading();
			} break;
		case GAME_RUNNING_STATE:
			{
				//gamestate.LevelProgress++;
				//gamestate.LevelProgress = gamestate.LevelProgress + (60*gamestate.DeltaTime);
				//cout << gamestate.LevelProgress << endl;

				// handles events what the user does with the character
				//Handle_events( input );
				
				//draws layers
				//gamestate.drawParallaxLayers();
				Gfx.DrawParallaxLayers();
				//gamestate.DrawObjects();
				Gfx.DrawObjects();
				//gamestate.DrawSprite();
				Gfx.DrawSprite();
				Gfx.DrawScore();
				
				gamestate.DrawAllText();
				
				//gamestate.FLIP();
				//Gfx.FLIP();
			} break;
		case GAME_BOSS_STATE:
			{
				// handles events what the user does with the character
				//Handle_events( input );

				//draws layers
				//gamestate.drawParallaxLayers();
				//Gfx.DrawParallaxLayers();
				//gamestate.DrawObjects();
				//Gfx.DrawObjects();
				//gamestate.DrawBoss();
				//Gfx.DrawBoss();
				//gamestate.DrawAllText();
				//gamestate.DrawSprite();
				//Gfx.DrawSprite();
				Gfx.DrawScore();
				//gamestate.FLIP();
				//Gfx.FLIP();

				//if( gamestate.pBoss->BossDead == true )
				//{
				//	gamestate.GameCondition = GS_OUTRO;
				//}
			} break;
		case GAME_OUTRO_STATE:
			{
				gamestate.PlayOutro();
			} break;
		case GAME_PLAYER_DIED_STATE:
			{
				//gamestate.demonDied();
				BCPlayer.Died();
			} break;
	}
}

// ----------------------------------------------------------------------------
// PlayOutro() - Plays the whole outro sequence
// ----------------------------------------------------------------------------
void Gamestate::PlayOutro()
{
	SDL_Rect srcRect = { 0, 0, 800, 600 };
	SDL_Rect destRect = { 0, 0, 800, 600 };
	SDL_BlitSurface(	Gfx.GetSurface( gamestate.m_srfOutro ),
					&srcRect, Gfx.BackBuffer, &destRect );
	Gfx.FLIP();

	SDL_Event input;

	while( gamestate.State == GAME_OUTRO_STATE )
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
	}

	gamestate.RestartGame();

	return;

	//demon.Update();
	////demon.Updatedemon();

	//int IntroState = 0;
	//int Letter = 0, LetterWidth = 0, Line = 0;
	//string FinishLine = "On Marjuras northwestern coast claimed that there are graves after a fallen kingdom. Grave Robber think there is gold and riches and Marjuras indigenous kvurerna believe that somewhere in the graves is a powerful weapon that can relieve Marjura from evil. Are you up for the task?";
	//string FinishSlow[ 7 ];
	//int Counter = 0;
	//SDL_Surface * FinishSurface;

	//bool Walk = true;

	////SDL_Color textColor = { 255, 255, 255 };

	//float speedJumpdemon = 0.0;

	//bool JumpDown = false, JumpUp = true;

	//Timer speed;
	//speed.Start();

	////SDL_Rect srcRect = { 0, 0, 800, 600 };
	////SDL_Rect destRect = { 0, 0, 800, 600 };

	//bool Finish = false;
	//while( Finish != true )
	//{
	//	while( speed.GetTicks() < 1000 / 40 )
 //       {
 //           //wait    
	//		
 //       }
	//	
	//	switch( IntroState )
	//	{
	//		speedJumpdemon += 100.0f * ( gamestate.DeltaTime / 1000 );

	//	case 0:
	//		{
	//			if( demon.GetPosition().x > 580 )
	//			{
	//				Walk = false;
	//				if( JumpUp ) 
	//				{
	//					//demon.yPos -= abs( 20 * cos( speedJumpdemon ) );
	//					//demon.xPos += abs( 5 * cos( speedJumpdemon ) );
	//					//demon.xVel += abs( 5 * cos( speedJumpdemon ) );
	//					//demon.yVel -= abs( 20 * cos( speedJumpdemon ) );
	//					/*
	//					if( demon.yPos < GROUND_Y - 100 )
	//					{
	//						JumpUp = false;
	//						JumpDown = true;
	//					}*/
	//				}
	//				else if( JumpDown )
	//				{
	//					//demon.yPos += abs( 10 * cos( speedJumpdemon ) );
	//					//demon.yVel += abs( 10 * cos( speedJumpdemon ) );
	//					if( demon.GetPosition().y > GROUND_Y + 80 )
	//					{
	//						IntroState = 1;
	//					}
	//				}
	//				
	//			}
	//			else if( demon.GetPosition().x < 580 && Walk == true )
	//			{
 //   					demon.isMovingRight = true;
	//			}

	//			//gamestate.drawParallaxLayers();
	//			Gfx.DrawParallaxLayers();
	//			//gamestate.DrawSprite();
	//			Gfx.DrawSprite();
	//			//gamestate.DrawBackgroundBlack();
	//			Gfx.DrawBackgroundBlack();
	//			break;
	//		}
	//	case 1:
	//		{
	//			SDL_BlitSurface(	Gfx.GetSurface( gamestate.m_srfOutro ),
	//								&srcRect, Gfx.BackBuffer, &destRect );
	//			if( Counter > 2 )
	//			{
	//				Counter = 0;
	//				
	//				LetterWidth++;

	//				if( Letter < FinishLine.length() )
	//				{
	//					Letter++;
	//				}
	//				else
	//				{
	//					IntroState = 2;
	//				}

	//				FinishSlow[ Line ] += FinishLine[ Letter ];
	//				for( int i = 0; i < 7; i++ )
	//				{
	//					FinishSurface = TTF_RenderText_Solid( Gfx.DefaultFont, FinishSlow[ i ].c_str(), Gfx.WhiteRGB );
	//					//gamestate.apply_surface( 300, i * 40, FinishSurface, gamestate.BackBuffer );
	//					Gfx.apply_surface( 300, i * 40, FinishSurface, Gfx.BackBuffer );
	//				}
	//			}

	//			for( int i = 0; i < 7; i++ )
	//			{
	//				FinishSurface = TTF_RenderText_Solid( Gfx.DefaultFont, FinishSlow[ i ].c_str(), Gfx.WhiteRGB );
	//				//gamestate.apply_surface( 300, i * 40, FinishSurface, gamestate.BackBuffer );
	//				Gfx.apply_surface( 300, i * 40, FinishSurface, Gfx.BackBuffer );
	//			}
	//			
	//			if( LetterWidth > 20 )
	//			{
	//				LetterWidth = 0;
	//				Line++;
	//			}

	//			Counter++;
	//			break;
	//		}
	//	case 2:
	//		{
	//			Finish = true;
	//			break;
	//		}
	//	}
	//	//gamestate.FLIP();
	//	Gfx.FLIP();

	//}
	//gamestate.State = MENU_MAIN_STATE;
}

// ----------------------------------------------------------------------------
// DoIntroTalk() - does the intro where all the talking takes place.
// ----------------------------------------------------------------------------
void Gamestate::DoIntroTalk()
{
	//Intro->Story();
	//Intro->DoTalk();
}

// ----------------------------------------------------------------------------
// demonDied() - Plays the whole death sequence
// ----------------------------------------------------------------------------
//void Gamestate::demonDied()
//{
//	SDL_Rect srcRect = { 0, 0, 800, 600 };
//	SDL_Rect destRect = { 0, 0, 800, 600 };
//
//
//	SDL_Event input;
//
//	while( gamestate.GameCondition == GS_DEAD )
//	{
//		SDL_PollEvent( &input );
//		if( input.type == SDL_KEYDOWN )
//		{
//  			switch( input.key.keysym.sym )
//			{
//			case SDLK_SPACE:
//				gamestate.GameCondition = GS_INTRO;
//				break;
//			}
//		}
//		Gfx.DrawBackgroundBlack();
//		SDL_BlitSurface( Gfx.GetSurface( gamestate.m_srfOutro ),	&srcRect, Gfx.BackBuffer, &destRect );
//		//SDL_Color textColor = { 255, 255, 255 };
//		//SDL_Color textColor2 = { 0, 0, 0 };
//		//sprintf_s( gamestate.Text, 256, " Press Space For Menu " );
//		Gfx.srfText = TTF_RenderText_Shaded( Gfx.DefaultFont, " Press Space For Menu ", Gfx.WhiteRGB, Gfx.BlackRGB );
//		//gamestate.apply_surface( 250, 500, gamestate.textIntro, gamestate.BackBuffer );
//		Gfx.apply_surface( 250, 500, Gfx.srfText, Gfx.BackBuffer );
//		//gamestate.FLIP();
//		Gfx.FLIP();
//	}
//	
//	ListHighScore->sort( gamestate.name->str.c_str(), _Score );
//	ListHighScore->Save();
//
//	int demonDieState = 0;
//	outro = new Outro;
//	int Letter = 0;
//	int LetterWidth = 0;
//	int Line = 0;
//	int Counter = 0;
//	string DeathTalks = " Your sole is mine fallen one, At this rate all the souls of the earth will be mine soon!!! Ha Ha Ha ";
//	string DeathTalkSlow[ 8 ];
//
//	SDL_Color textColor = { 255, 255, 255 };
//	SDL_Event input;
//
//	SDL_Color Stone = { 105, 105, 136 };
//	SDL_Color StoneFront = { 0, 0, 0, 255 };
//
//	bool PlayDeadAnimation = true; 
//	while( PlayDeadAnimation == true )
//	{
//		SDL_PollEvent( &input );
//		if( input.type == SDL_KEYDOWN )
//		{
//			switch( input.key.keysym.sym )
//			{
//			case SDLK_SPACE:
//				demonDieState = 2;
//				break;
//			}
//		}
//
//		DrawBackgroundBlack();
//		gamestate.DrawAllText();
//		switch( demonDieState )
//		{
//		case 0:
//			{
//				if( timer.Timer_ShowDead > 10 )
//				{
//					demonDieState = 1;
//					timer.Timer_ShowDead = 0.0f;
//				}
//
//				timer.Timer_ShowDead++;
//				//SDL_BlitSurface(	Gfx.GetSurface( outro->surface ), &outro->ClipsOutro[ 0 ],
//				//					gamestate.BackBuffer, &outro->ClipsOutro[ 1 ] );
//				break;
//			}
//		case 1:
//			{
//				if( Counter > 5 )
//				{
//					Counter = 0;
//
//					if( Letter < DeathTalks.length() )
//					{
//						Letter++;
//					}
//					else
//					{
//						demonDieState = 2;
//					}
//
//					DeathTalkSlow[ Line ] += DeathTalks[ Letter ];
//					for( int i = 0; i < 8; i++ )
//					{
//						DeathSurface[ 0 ] = TTF_RenderText_Solid( gamestate.font, DeathTalkSlow[ i ].c_str(), textColor );
//						gamestate.apply_surface( 300, i * 40, DeathSurface[ 0 ], gamestate.BackBuffer );
//					}
//
//					LetterWidth++;
//				}
//						
//				SDL_BlitSurface(	Gfx.GetSurface( outro->surface ), &outro->ClipsOutro[ 0 ],
//									gamestate.BackBuffer, &outro->ClipsOutro[ 1 ] );
//
//				for( int i = 0; i < 8; i++ )
//				{
//					DeathSurface[ 0 ] = TTF_RenderText_Solid( gamestate.font, DeathTalkSlow[ i ].c_str(), textColor );
//					gamestate.apply_surface( 300, i * 40, DeathSurface[ 0 ], gamestate.BackBuffer );
//				}
//				
//					
//				if( LetterWidth > 20 )
//				{
//					LetterWidth = 0;
//					Line++;
//				}
//
//				Counter++;
//				break;
//			}
//		case 2:
//			{
//				PlayDeadAnimation = false;
//				break;
//			}	
//		}
//		
//		DeathSurface[ 1 ] = TTF_RenderText_Blended( gamestate.font, gamestate.name->str.c_str(), StoneFront );
//		gamestate.apply_surface( 160, 450, DeathSurface[ 1 ], gamestate.BackBuffer );
//		//gamestate.FLIP();
//		Gfx.FLIP();
//	}
//
//	gamestate.GameCondition = GS_INTRO;	
//
//}

// ----------------------------------------------------------------------------
// DrawAllText() - draws all text thats currently shown on the screen.
// ----------------------------------------------------------------------------
void Gamestate::DrawAllText()
{
	if( State == GAME_STORY_STATE || State == GAME_PLAYER_DIED_STATE )
	{
		//SDL_Color textColor = { 255, 255, 255 };
		//SDL_Color textColor2 = { 0, 0, 0 };
		
		if( State == GAME_PLAYER_DIED_STATE )
		{
			//sprintf_s( gamestate.Text, 256, " Press Space For Menu " );
			Gfx.srfText = TTF_RenderText_Shaded( Gfx.DefaultFont, " Press Space For Menu ", Gfx.WhiteRGB, Gfx.BlackRGB );
			//gamestate.apply_surface( 200, 500, gamestate.textIntro, gamestate.BackBuffer );
			Gfx.apply_surface( 200, 500, Gfx.srfText, Gfx.BackBuffer );
		}
		else
		{
			//sprintf_s( gamestate.Text, 256, " Press Space To Start " );		
			Gfx.srfText = TTF_RenderText_Shaded( Gfx.DefaultFont, " Press Space To Start ", Gfx.WhiteRGB, Gfx.BlackRGB );
			//gamestate.apply_surface( 200, 500, gamestate.textIntro, gamestate.BackBuffer );
			Gfx.apply_surface( 200, 500, Gfx.srfText, Gfx.BackBuffer );
		}
	}
	else
	{
		//The color of the font
		//SDL_Color textColor = { 251, 245, 32 };

		// print out the score
		//sprintf_s(gamestate.Text, 256, "%i ", gamestate.GetScore() );		
		//gamestate.srfText = TTF_RenderText_Solid( gamestate.font, Text, Gfx.WhiteRGB );
		//gamestate.apply_surface( 100, 20, gamestate.srfText, gamestate.BackBuffer );
		//Gfx.apply_surface( 100, 20, gamestate.srfText, Gfx.BackBuffer );
	}
}

// ----------------------------------------------------------------------------
// Loading() - draws the loading screen on the screen. Dragon dancing
// ----------------------------------------------------------------------------
void Gamestate::Loading()
{
	//currentAnimFrame += deltaTime * animFramesPerSecond;
	SDL_SetAlpha( m_surfaceList[  Dragon->surface ], SDL_SRCALPHA, 255 );

	float Speed = 1000.0f * ( gamestate.DeltaTime / 1000.0f );	// AddTick call here instead
	SDL_Rect dstRect = { Dragon->xPos, Dragon->yPos, Dragon->Width, Dragon->Height };
	//if ( gamestate.IntroDone == false )
	//{
					SDL_BlitSurface(	Gfx.GetSurface( Dragon->surface ), &Dragon->Clips[ Dragon->Frame ],
								Gfx.BackBuffer, &dstRect );
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
		
	//}
}

// ----------------------------------------------------------------------------
// DrawBoss() - hmmm.
// ----------------------------------------------------------------------------
//void Gamestate::DrawBoss()
//{
//	//SDL_Rect srcRect = { 0, 0, 150, 300 };
//	//gamestate.pBoss->UpdateFrame();
//	//				SDL_BlitSurface( Gfx.GetSurface( gamestate.pBoss->Surface ), 
//	//				&gamestate.pBoss->GetClips( gamestate.pBoss->GetFrame() ),
//	//							gamestate.BackBuffer, &srcRect );
//	//Sleep(100);
//	//gamestate.pBoss->UpdateBoss();
//	gBoss.Update();
//}

// ----------------------------------------------------------------------------
// GetSurface() - hmmm.
// ----------------------------------------------------------------------------
//SDL_Surface * Gamestate::GetSurface( int WhichSurface )
//{
//	return m_surfaceList[ WhichSurface ];	
//}

// ----------------------------------------------------------------------------
// GetSurface() - gives backbuffer to destination buffer streches and all
// ----------------------------------------------------------------------------
//void Gamestate::FLIP()
//{
//	//SDL_Rect srcRect = { 0, 0, gamestate.BackBuffer->w, gamestate.BackBuffer->h };
//	//SDL_Rect destRect = { 0, 0, gamestate.SCREEN_WIDTH, gamestate.SCREEN_HEIGHT };
//					
//	//gamestate.PasteScreenToAnother( srcRect, destRect );
//	Gfx.PasteScreenToAnother( SDL_GetVideoSurface()->clip_rect, SDL_GetVideoSurface()->clip_rect);
//	//flips screen
//	if( SDL_Flip( gamestate.screen ) == -1)
//	{
//		gamestate.GameOK = false;
//	}
//}

// ----------------------------------------------------------------------------
// MainScreen() - Draws the mainscreen, checks conditions. MenuScreen
// ----------------------------------------------------------------------------
void Gamestate::MainScreen(int iElapsedTime)
{

	//SDL_Surface * Surface_Credits = NULL;
	//SDL_Surface * Surface_HighScore = NULL;

	//ParallaxLayer  * MyParaBackGround;
	//MyParaBackGround = Parallax->getLayer( TitleScreen->surface );

	//SDL_Rect scRect = { 0, 0, 800, 600 };
	//SDL_Rect dtRect = {	0, 0, 800, 600 };

	SDL_BlitSurface( Gfx.GetSurface( TitleScreen->surface ), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect );
	/*
	for( int i = 0; i < 4; i++ )
	{
		//SDL_FillRect(gamestate.GetSurface( TitleScreen->SurfaceButt),&TitleScreen->DestClips[ i ],SDL_MapRGB(gamestate.GetSurface( TitleScreen->SurfaceButt)->format,255,0,255) );
			
		SDL_BlitSurface(	Gfx.GetSurface( TitleScreen->SurfaceButt ), 
							&TitleScreen->ButtonClips[ i ],
							Gfx.BackBuffer, &TitleScreen->DestClips[ i ] ); 
	}*/

	if( TitleScreen->ButtonNewgame == true )
	{
		gamestate.State = GAME_RUNNING_STATE;
		TitleScreen->ButtonNewgame = false;
	}

	stringstream ss;
	ss << iElapsedTime;
	string str = "Microseconds per frame:";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.BlackRGB );
	//gamestate.apply_surface( 200, 400, srfEnter, gamestate.BackBuffer );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	//if( gamestate.TitleScreen->ButtonHighScore == true )
	//{
	//	ListHighScore->sort( gamestate.name->str.c_str(), gamestate.GetScore() );
	//	ListHighScore->Save();

	//	delete ListHighScore;
	//	ListHighScore = new FillHighScore;

	//	for( int i = 0; i < 5; i++ )
	//	{
	//		char temp[ 256 ];
	//		sprintf_s(	temp, 256, "Name: %s Score: %i", ListHighScore->list[ i ].name.c_str(), ListHighScore->list[ i ].Score );	
	//		gamestate.HighScoreList[ i ] = temp;
	//	}
	//}

	//if( TitleScreen->ButtonOptions == false )
	//{
	//	for( int i = 0; i < 4; i++ )
	//	{
	//		//SDL_FillRect(gamestate.GetSurface( TitleScreen->SurfaceButt),&TitleScreen->DestClips[ i ],SDL_MapRGB(gamestate.GetSurface( TitleScreen->SurfaceButt)->format,255,0,255) );
	//		
	//		SDL_BlitSurface(	Gfx.GetSurface( TitleScreen->SurfaceButt ), 
	//							&TitleScreen->ButtonClips[ i ],
	//							gamestate.BackBuffer, &TitleScreen->DestClips[ i ] ); 
	//	}
	//}
	//else if( TitleScreen->ButtonHighScore == true )
	//{
	//	/*
	//	SDL_BlitSurface(	gamestate.GetSurface( TitleScreen->SurfaceButt ),
	//						&TitleScreen->ButtonClips[ 4 ],
	//						gamestate.BackBuffer, &TitleScreen->DestClips[ 8 ] ); 	
	//						*/

	//	SDL_BlitSurface(	Gfx.GetSurface( TitleScreen->SurfaceButt ),
	//						&TitleScreen->ButtonClips[ 7 ],
	//						gamestate.BackBuffer, &TitleScreen->DestClips[ 7 ] ); 

	//	SDL_Color textColor = { 0,0,0 };
	//	
	//	for( int i = 0; i < 5; i++ )
	//	{
	//		Surface_HighScore =		TTF_RenderText_Solid( gamestate.font, 
	//								gamestate.HighScoreList[ i ].c_str(), textColor );
	//		apply_surface( 50, 270 + i * 40, Surface_HighScore, gamestate.BackBuffer );
	//	}

	//}
	//else if( TitleScreen->ButtonCredits == true )
	//{
	//	SDL_BlitSurface(	Gfx.GetSurface( TitleScreen->SurfaceButt ),
	//						&TitleScreen->ButtonClips[ 8 ],
	//						gamestate.BackBuffer, &TitleScreen->DestClips[ 9 ] ); 

	//	SDL_BlitSurface(	Gfx.GetSurface( TitleScreen->SurfaceButt ),
	//						&TitleScreen->ButtonClips[ 7 ],
	//						gamestate.BackBuffer, &TitleScreen->DestClips[ 7 ] ); 

	//	
	//	SDL_Color textColor = { 0,255,0 };
	//	
	//
	//	Surface_Credits =		TTF_RenderText_Solid( gamestate.font, 
	//							" A Risk Production ", textColor );
	//	apply_surface( 50, 270, Surface_Credits, gamestate.BackBuffer );
	//}
	//else
	//{
	//	for( int i = 0; i < 8; i++ )
	//	{
	//		if( i == 2 || i == 0 || i == 3 )
	//		{
	//										
	//		}
	//		else
	//		{
	//			SDL_BlitSurface(	Gfx.GetSurface( TitleScreen->SurfaceButt ), &TitleScreen->ButtonClips[ i ],
	//								gamestate.BackBuffer, &TitleScreen->DestClips[ i ] ); 
	//		}
	//	}
	//}
	//
	//if( TitleScreen->ButtonNewgame == true )
	//{
	//	gamestate.GameCondition = GS_INTROSTORY;
	//	TitleScreen->ButtonNewgame = false;

	//	if( Surface_Credits != NULL )
	//	{
	//		SDL_FreeSurface( Surface_Credits );
	//	}
	//	if( Surface_HighScore != NULL )
	//	{
	//		SDL_FreeSurface( Surface_HighScore );
	//	}

	//	gamestate.RestartGame();
	//}
	//if( TitleScreen->ButtonQuit == true )
	//{
	//	gamestate.GameOK = false;
	//	TitleScreen->ButtonQuit == false;
	//}

	//if( TitleScreen->ButtonBack == true )
	//{
	//	TitleScreen->ButtonOptions = false;
	//	TitleScreen->ButtonBack = false;
	//	TitleScreen->ButtonHighScore = false;
	//	TitleScreen->ButtonCredits = false;
	//	TitleScreen->ButtonBack = false;
	//} 					  	   
	//
}

// ----------------------------------------------------------------------------
// EnterName() - checks for input demon name
// ----------------------------------------------------------------------------
void Gamestate::EnterName()
{
	cout << "EnterName gamestate..." << endl;
	SDL_Rect scRect = {	0, 0, 800, 600 };
	SDL_Rect dtRect = {	0, 0, 800, 600 };
	SDL_BlitSurface( Gfx.GetSurface( TitleScreen->surface ), &scRect, Gfx.BackBuffer, &dtRect );
	//SDL_Color textColor = { 0,0,0 };
	SDL_Surface * srfEnter;
	srfEnter = TTF_RenderText_Solid( Gfx.DefaultFont, gamestate.demonName.c_str(), Gfx.BlackRGB );
	//gamestate.apply_surface( 200, 400, srfEnter, gamestate.BackBuffer );
	Gfx.apply_surface( 200, 400, srfEnter, Gfx.BackBuffer );
	//gamestate.name->show_centered();

	if( gamestate.name->handle_input(  ) == false )
	{
		gamestate.State = GAME_STORY_STATE;
	}
	
	//bool Name =  false;
	//SDL_Event input;
	//SDL_Color textColor = { 0,0,0 };
	//gamestate.IntroDone = false;
	//SDL_Surface * srfEnter;
	//
	//while( gamestate.name->handle_input(  ) )
	//{
	//	SDL_Rect scRect = {	0, 0, 800, 600 };
	//	SDL_Rect dtRect = {	0, 0, 800, 600 };
	//	SDL_BlitSurface( gamestate.GetSurface( TitleScreen->surface ), &scRect, gamestate.BackBuffer, &dtRect );
	//	//gamestate.name->handle_input(  );
	//	//SDL_Delay(1000 / 60);
	//	timer.Timer_Name++;

	//	
	//	//TypeName = TTF_RenderText_Solid( font, " Enter your name ", textColor ); 
	//	gamestate.name->show_centered();
	//	//gamestate.apply_surface( 250, 200, TypeName, gamestate.BackBuffer );

	//	srfEnter = TTF_RenderText_Solid( font, " Press Enter To Finish ", textColor );
	//	gamestate.apply_surface( 200, 400, srfEnter, gamestate.BackBuffer );

	//	//gamestate.FLIP();
	//	Gfx.FLIP();
	//}

	//gamestate.GameCondition = GS_INTROSTORY;
	
}

void Gamestate::RestartGame()
{
	BCPlayer.Reset();
	ResetBoss();
	ResetEnemies();
	ResetObjects();
	ResetRest();

	timer.RestartTimers();

	//BCPlayer.Initiatedemon( BCPlayer.Surface, GROUND_X, 0, demonHEIGHT, demonWIDTH );
	//gamestate.Score = 0;
	//gamestate.m_parallax = 0;
	gamestate.Parallax = 0.0f;
	gamestate.State = MENU_MAIN_STATE;
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
	//if( Intro != NULL )
	//{
	//	delete Intro;
	//}
	if( ListHighScore != NULL )
	{
		delete ListHighScore;
	}

	gamestate.CreateNewThings();
}

// Frees surfaces and deletes thing thats not NULL
void Gamestate::EndAll()
{
	for( int i = 0; i < ParallaxBG->getLayerCount(); i++ )
	{
		SDL_FreeSurface( m_surfaceList[ i ] );
	}

	//if( gamestate.Intro != NULL )
	//{
	//	delete Intro;
	//}
	//if( gamestate.pBoss != NULL )
	//{
	//	delete gamestate.pBoss;
	//}
	if( gamestate.outro != NULL )
	{ 
		delete outro;
	}
	if( gamestate.Dragon != NULL )
	{
		delete Dragon;
	}


	//ListHighScore->sort( gamestate.name->str, gamestate.GetScore() );
	//ListHighScore->Save();

	if( gamestate.name != NULL )
	{
		delete name;
	}

}

void Game::Cleanup()
{
	TTF_Quit();
	SDL_Quit();
}

// loads image with chosen value to not show
//int Gamestate::Load_imageAlpha( std::string filename, int r, int g, int b )
//{
//	//temp storage for the image loaded
//	SDL_Surface * loadedimage = NULL;
//
//	//optimized image for storage and flipping
//	SDL_Surface * optimizedImage = NULL;
//
//	//load image 
//	loadedimage = IMG_Load( filename.c_str() );
//
//	//if something went wrong
//	if( loadedimage != NULL )
//	{
//		//create an optimized image 
//		optimizedImage = SDL_DisplayFormat( loadedimage );
//
//		//free old image
//		SDL_FreeSurface( loadedimage );
//	}
//
//	if(optimizedImage != NULL)
//	{
//		SDL_SetColorKey(optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, r, g, b ) );
//	}
//	
//	int index = findAvailableIndex();
//	if( index == -1 )
//	{
//		return -1;
//	}
//
//	m_surfaceList[ index ] = optimizedImage;
//	return index;
//}

// inits sdl, font and videomode
bool Game::Init(SDL_Surface * &screen)
{
	Gfx.screen = 0;


	//initialize all SDL subystems
/*	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1)
	{
		return false;
	} */


	//set up the screen
	Gfx.screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

 SDL_Rect** modes;
   int i;
   
    /* Get available fullscreen/hardware modes */
    modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);
    
    /* Check if there are any modes available */
    if (modes == (SDL_Rect**)0) {
        printf("No modes available!\n");
       exit(-1);
   }
   
   /* Check if our resolution is restricted */
   if (modes == (SDL_Rect**)-1) {
       printf("All resolutions available.\n");
   }
   else{
       /* Print valid modes */
       printf("Available Modes\n");
       for (i=0; modes[i]; ++i)
         printf("  %d x %d\n", modes[i]->w, modes[i]->h);
   }

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
	SDL_WM_SetCaption( " S-TYPE ", NULL);

	/* Create a 32-bit surface with the bytes of each pixel in R,G,B,A order,
       as expected by OpenGL for textures */
    Uint32 rmask, gmask, bmask, amask;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	   on the endianness (byte order) of the machine */

	rmask = 0x00000000;
	gmask = 0x00000000;
	bmask = 0x00000000;
	amask = 0x00000000;



	Gfx.BackBuffer = SDL_CreateRGBSurface( SDL_HWSURFACE, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h, SDL_GetVideoSurface()->format->BitsPerPixel,
								   rmask, gmask, bmask, amask);
	
	if( Gfx.BackBuffer == NULL )
	{
		return false;																							
	}
	return true;
}

// ----------------------------------------------------------------------------
// drawParallaxLayers() - renders parallax-layers to backbuffer and gives it to Main Surface
// ----------------------------------------------------------------------------
//void Gamestate::drawParallaxLayers()
//{
//	if( gamestate.GameCondition != GS_LEVEL1BOSS && gamestate.GameCondition != GS_OUTRO )
//	{
//		/*
//		if( demon.xVel >= STARTSCROLLING - 50 )
//		{
//			// Updating the background to scroll when character is moving
//			if( demon.isMovingRight )
//			{
//				gamestate.m_paralax += 20;
//			}
//			else if( demon.isMovingLeft )
//			{
//				gamestate.m_paralax -= 20;
//			}
//		}
//		*/
//		gamestate.CreateAll();
//	}
//	else
//	{
//		//if( !BossStart )
//		//{
//		//	//demon.demonHunter = true;
//		//	//demon.SmallHunter = false;
//		//	gamestate.pBoss = gamestate.CreateBoss( SDL_GetVideoSurface()->w - 180, GROUND_Y - 210, m_srfBoss );
//		//	BossStart = true;
//		//}
//	}
//
//		//// Draw parallax layers
//		ParallaxLayer  * MyParaBackGround;
//		MyParaBackGround = Parallax->getLayer( 0 );
//
//		SDL_Rect scRect = { 0, 0,	MyParaBackGround->m_width, 
//									MyParaBackGround->m_height };
//
//		SDL_Rect dtRect = {	0, 0, MyParaBackGround->DW, MyParaBackGround->DH };
//
//		SDL_BlitSurface( Gfx.GetSurface(MyParaBackGround->m_surface), &scRect, gamestate.BackBuffer, &dtRect );
//		//SDL_BlitSurface( m_surfaceList[ MyParaBackGround->m_surface ], &scRect, gamestate.BackBuffer, &dtRect ); 
//
//		//gamestate.stretchPicToBackBuffer( MyParaBackGround, scRect, dtRect );
//
//		int x = 0;
//		for( int i = 1; i < Parallax->getLayerCount(); ++i )
//		{		
//			// Calc rects
//			MyParaBackGround = Parallax->getLayer( i );
//			if( MyParaBackGround->m_surface == m_srfClouds )
//			{
//				MyParaBackGround->AnimClouds += 100.0f * gamestate.DeltaTime;
//
//				//////// Calc parallax position
//				x = (int)( MyParaBackGround->m_parallax * (float)( +MyParaBackGround->AnimClouds ) );  
//				if( x < 0 )	// neg -> pos
//				{
//					x *= -1;	// invert sign, because % only works with positive integers
//					x = MyParaBackGround->m_width - (x % MyParaBackGround->m_width);
//				}
//				else
//				{
//					x %= MyParaBackGround->m_width;
//				}
//
//				x -= MyParaBackGround->m_width;	// move one back
//			}
//			else
//			{
//
//				//////// Calc parallax position
//				x = (int)( MyParaBackGround->m_parallax * (float)( +gamestate.m_parallax ) );  
//				if( x < 0 )	// neg -> pos
//				{
//					x *= -1;	// invert sign, because % only works with positive integers
//					x = MyParaBackGround->m_width - (x % MyParaBackGround->m_width);
//				}
//				else
//				{
//					x %= MyParaBackGround->m_width;
//				}
//
//				x -= MyParaBackGround->m_width;	// move one back
//			}
//
//			for( int i = 0; i < 2; i++ )
//			{
//				SDL_Rect sourceRect = { 0 + x, MyParaBackGround->m_surfaceYOffset,
//										MyParaBackGround->m_width, MyParaBackGround->m_height };
//
//				SDL_Rect destinationRect = {	MyParaBackGround->DX, MyParaBackGround->DY, 
//												MyParaBackGround->DW, MyParaBackGround->DH };
//
//				SDL_BlitSurface( Gfx.GetSurface( MyParaBackGround->m_surface ), &sourceRect, gamestate.BackBuffer, &destinationRect ); 			
//				//SDL_BlitSurface( m_surfaceList[ MyParaBackGround->m_surface ], &sourceRect, gamestate.BackBuffer, &destinationRect ); 
//				
//				
//				x += MyParaBackGround->m_width;
//			}
//
//
//			MyParaBackGround->HowFarGone = MyParaBackGround->Xpos - MyParaBackGround->m_width;
//
//		}
		//gamestate.m_parallax += 500 * gamestate.DeltaTime;
//}

void Gamestate::CreateAll()
{
	AnimalController.Create_Animals();
	EnemyController.Create_Enemies();
	ObjectController.CreateObjects();
}

// draws MyFellow on the screen and changes animations
//void Gamestate::DrawSprite()
//{
//		//SDL_Rect demonDest = { demon.xPos, demon.yPos, demon.demon_Width, demon.demon_Height };
//		//demonDest = demon.GetPosition();
//		if( demon.isImmortal )
//		{
//			if( demon.AlphaImmortal < SDL_ALPHA_OPAQUE - 100 )
//			{
//				demon.AlphaImmortal += 50;
//			}
//			else
//			{
//				demon.AlphaImmortal -= 50;
//			}
//			SDL_SetAlpha( Gfx.GetSurface( demon.demonSurface ), SDL_SRCALPHA | SDL_RLEACCEL, demon.AlphaImmortal );
//		}
//		else
//		{
//			SDL_SetAlpha( Gfx.GetSurface( demon.demonSurface ), SDL_SRCALPHA | SDL_RLEACCEL, SDL_ALPHA_OPAQUE );
//		}
//
//		
//			//Current_Frame = demon.Updatedemon();
//			//demon.Updatedemon();
//			demon.Update();
//		
//			// Rendering demon Character
//			/*
//			SDL_BlitSurface(	m_surfaceList[ demon.demonSurface ], 
//								&demon.AnimationArrays[ Current_AnimArray ][ Current_Frame ],
//								gamestate.BackBuffer, &demonDest );*/
//			if( CurrentFrame == 3 )
//			{
//				CurrentFrame = 0;
//			}
//			
//			SDL_BlitSurface(	Gfx.GetSurface( demon.demonSurface ), 
//				&demon.AnimationArrays[ demon.GetState() ][ ++CurrentFrame ],
//				gamestate.BackBuffer, &demon.GetPosition() );
//			/*
//			SDL_BlitSurface(	m_surfaceList[ emon.demonSurface ], 
//				&demon.AnimationArrays[ demon.GetState() ][ ++CurrentFrame ],
//								gamestate.BackBuffer, &demonDest );*/
//
//
//			PreviousFrame = CurrentFrame;
//}


void Gamestate::AddTick()
{
	 //float Speed = 1000.0f * ( gamestate.DeltaTime / 1000.0f );
	 //UpdateAnimationSpeed += Speed;
	UpdateAnimationSpeed += ( 1000.0f * ( gamestate.DeltaTime / 1000.0f ) );
}

//void Gamestate::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
//{
//    //Holds offsets
//    SDL_Rect offset;
//    
//    //Get offsets
//    offset.x = x;
//    offset.y = y;
//    
//    //Blit
//    SDL_BlitSurface( source, clip, destination, &offset );
//}

//void Gamestate::stretchPicToBackBuffer( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect )	
//{			
//
//	int srcWidth = srcRect.w - srcRect.x;
//	int srcHeight = srcRect.h - srcRect.y,
//		DestWidth = destRect.w - destRect.x,
//		DestHeight = destRect.h - destRect.y;
//
//	SDL_LockSurface( gamestate.BackBuffer );
//	SDL_LockSurface( m_surfaceList[ layer->m_surface ] );
//
//	int dstPitch = gamestate.BackBuffer->pitch;
//	int pitch = m_surfaceList[ layer->m_surface ]->pitch;
//
//	DWORD * dst = ( DWORD * )gamestate.BackBuffer->pixels;
//
//	DWORD * src = ( DWORD * )m_surfaceList[ layer->m_surface ]->pixels;
//
//	float scaleWidth = srcWidth / ( float )DestWidth;
//	float scaleHeight = srcHeight / ( float )DestHeight; 
//
//
//	float fSrcX = srcRect.x,
//		  fSrcY = srcRect.y;
//
//	for(int y = destRect.y;  y < destRect.y + destRect.h; y++ )
//	{
//		fSrcX = 0;
//
//		for(int x = destRect.x ;  x < destRect.x + destRect.w ; x++)
//		{
//			dst[ ( y * dstPitch / 4) + ( x ) ] = src[ int( ( fSrcY ) * ( pitch / 4 ) + int( fSrcX ) )];
//
//			fSrcX += scaleWidth;
//		}
//
//		fSrcY += scaleHeight;	
//	}
//
//	SDL_UnlockSurface( gamestate.BackBuffer );
//	SDL_UnlockSurface( m_surfaceList[ layer->m_surface ] );
//
//}

//void Gamestate::stretchBlit( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect )	
//{			
//	SDL_LockSurface( gamestate.BackBuffer );
//	SDL_LockSurface( m_surfaceList[ layer->m_surface ] );
//
//	int dstPitch = gamestate.BackBuffer->pitch;
//	int pitch = m_surfaceList[ layer->m_surface ]->pitch;
//
//	DWORD * dst = ( DWORD * )gamestate.BackBuffer->pixels;
//
//	DWORD * src = ( DWORD * )m_surfaceList[ layer->m_surface ]->pixels;
//
//	float scaleWidth = srcRect.w / ( float )destRect.w;
//	float scaleHeight = srcRect.h / ( float )destRect.h; 
//
//
//	float fSrcX = srcRect.x,
//		  fSrcY = srcRect.y;
//
//	for(int y = destRect.y;  y < destRect.y + destRect.h; y++ )
//	{
//		fSrcX = srcRect.x;
//
//		for(int x = destRect.x ;  x < destRect.x + destRect.w ; x++)
//		{
//			dst[ (y * dstPitch / 4) + (x) ] = src[ int((fSrcY) * (pitch / 4) + int(fSrcX) )];
//
//			fSrcX += scaleWidth;
//		}
//		fSrcY += scaleHeight;	
//	}
//
//	SDL_UnlockSurface( gamestate.BackBuffer );
//	SDL_UnlockSurface( m_surfaceList[ layer->m_surface ] );
//
//}

//void Gamestate::PasteScreenToAnother( SDL_Rect srcRect, SDL_Rect destRect )	
//{
//	SDL_LockSurface( gamestate.screen );
//	SDL_LockSurface( gamestate.BackBuffer );
//
//	int dstPitch = gamestate.screen->pitch;
//	int pitch = gamestate.BackBuffer->pitch;
//
//	DWORD * dst = ( DWORD * )gamestate.screen->pixels;
//	DWORD * src = ( DWORD * )gamestate.BackBuffer->pixels;
//
//	float scaleWidth = gamestate.BackBuffer->w / ( float )destRect.w;
//	float scaleHeight = gamestate.BackBuffer->h / ( float )destRect.h; 
//
//
//	float fSrcX = 0.0f,
//		  fSrcY = 0.0f;
//
//	for(int y = destRect.y;  y < destRect.y + destRect.h; y++ )
//	{
//		fSrcX = 0.0f;
//
//		for(int x = destRect.x ;  x < destRect.x + destRect.w ; x++)
//		{
//			dst[ (y * dstPitch / 4) + (x) ] = src[ int(fSrcY) * (pitch / 4) + int(fSrcX) ];
//
//			fSrcX += scaleWidth;
//		}
//
//		fSrcY += scaleHeight;	
//	}
//
//	SDL_UnlockSurface( gamestate.screen );
//	SDL_UnlockSurface( gamestate.BackBuffer );
//}

// ----------------------------------------------------------------------------
// setUpParallaxLayers() - initializes parallax-struct
// ----------------------------------------------------------------------------
void Gamestate::setUpParallaxLayers()
{
	// Create background
	ParallaxBG = new ParallaxBackground();
	ParallaxBG->createLayers( 10 );

	//Firstlayer
	ParallaxBG->setLayer( 0, 0.0f, m_srfBlack, 
						0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h, 0, 0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );

	////sky
	ParallaxBG->setLayer( 1, 0.0f, m_srfSky, 
						0, SDL_GetVideoSurface()->w, 400, 0, 0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );

	// trees
	ParallaxBG->setLayer( 2, 0.7f, m_srfTrees, 
						0, 1172, 170, 0, 370, SDL_GetVideoSurface()->w, 170 ); 

	//clouds
	ParallaxBG->setLayer(	3, 0.5f, m_srfClouds, 
						0, SDL_GetVideoSurface()->w, 38, 0, 0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );

	ParallaxBG->setLayer(	4, 0.4f, m_srfClouds, 
						38, SDL_GetVideoSurface()->w, 87, 0, 38, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );

	ParallaxBG->setLayer(	5, 0.3f, m_srfClouds, 
						126, SDL_GetVideoSurface()->w, 46, 0, 126, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );

	ParallaxBG->setLayer(	6, 0.2f, m_srfClouds, 
						172, SDL_GetVideoSurface()->w, 21, 0, 172, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );

	ParallaxBG->setLayer(	7, 0.1f, m_srfClouds, 
						193, SDL_GetVideoSurface()->w, 12, 0, 193, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );

	ParallaxBG->setLayer( 8, 0.7f, m_srfCity, 
						0, 5100, 535, 0, 0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );

	ParallaxBG->setLayer(	9, 1.0f, m_srfCity, 
						540, 5100, 60, 0, 535, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );
}