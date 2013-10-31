#pragma once

#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

#include "Global\Global.h"
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
#include "Enemies\Cubes.h"
#include "Triangles.h"
#include "Bullets.h"
#include "MainMenu.h"
#include "Credits.h"
#include "GameOver.h"
#include "Load.h"
#include "Save.h"
#include "Collision.h"
#include "OutroFinish.h"
#include "GetInput.h"
#include "CBoss.h"
#include "World\CWorld.h"

Gamestate gamestate;

Gamestate::Gamestate()
{
	cout << "Gamestate::Loading Audio..." << endl;
	Audio.LoadAudio();
	cout << "Gamestate::Creating the world..." << endl;
	WorldController.CreateWorld();

	GameState.push(MENU_MAIN_STATE);

	gBoss.SetSurface(1);

	Parallax = 0.0f;
	DeltaTime = 0.0f;
}

void Gamestate::KeyMapping(SDL_Event _event)
{
	bool KEYS[322];  // 322 is the number of SDLK_DOWN events


	for(int i = 0; i < 322; i++) { // init them all to false
	   KEYS[i] = false;
	}

	SDL_EnableKeyRepeat(0,0); // you can configure this how you want, but it makes it nice for when you want to register a key continuously being held down

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
		case SDLK_ESCAPE:
			{
				std::cout << "Trying to get to the menu eeeyyy!!" << endl;
				gamestate.GameState.push(MENU_MAIN_STATE);
			} break;
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
	else if( _event.type == SDL_ACTIVEEVENT  )
	{
		std::cout << "Hey stop focusing on other windows, get back here!" << endl;
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
				Gfx.FLIP();
				if( gamestate.GameState.top() == GAME_RUNNING_STATE && SOUND == 3 )
				{
					Audio.PlaySoundEffect( 1 );
				}
			} break;
		case SDLK_LALT:
			{
				BCPlayer.AddAction("FIRE_SPECIAL");
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
		BCPlayer.SetState(BaseCharacter::State::IDLE);
	}

	if(gamestate.GameState.top() == MENU_MAIN_STATE)
	{
		if( MUSIC == 5 )
		Audio.PlayMusic(0);
		else
			Audio.PauseMusic();
		SDL_GetMouseState(&MouseXCoordinates, &MouseYCoordinates);
		cout << "(" << MouseXCoordinates << "," << MouseYCoordinates << ")" << endl;
		for( int i = 0; i < 8; i++ )
		{
			if(MouseXCoordinates > gamestate.MainMenuScreen->ButtonClips[ i ].x && 
			MouseXCoordinates < gamestate.MainMenuScreen->ButtonClips[ i ].x + gamestate.MainMenuScreen->ButtonClips[ i ].w &&
			MouseYCoordinates > gamestate.MainMenuScreen->ButtonClips[ i ].y &&
			MouseYCoordinates < gamestate.MainMenuScreen->ButtonClips[ i ].y + gamestate.MainMenuScreen->ButtonClips[ i ].h )
			{
				cout << "Entering button " << i << "..." << endl;
			}
		}
		if( _event.type == SDL_MOUSEBUTTONDOWN )
		{
			// if mouse click within boundries of one of the buttons
			for( int i = 0; i < 8; i++ )
			{
					if( _event.button.x > gamestate.MainMenuScreen->ButtonClips[ i ].x && 
					_event.button.x < gamestate.MainMenuScreen->ButtonClips[ i ].x + gamestate.MainMenuScreen->ButtonClips[ i ].w &&
					_event.button.y > gamestate.MainMenuScreen->ButtonClips[ i ].y &&
					_event.button.y < gamestate.MainMenuScreen->ButtonClips[ i ].y + gamestate.MainMenuScreen->ButtonClips[ i ].h )
					{
						if( i == 7 )
						{
							Game::Quit = true;
						}
						if( i == 6 )
						{
							gamestate.GameState.pop();
							gamestate.GameState.push(GAME_CREDITS_STATE);
						}
						if( i == 4 )
						{
							gamestate.GameState.pop();
							gamestate.GameState.push(GAME_OPTIONS_STATE);
						}
						if( i == 3 )
						{
							gamestate.GameState.pop();
							gamestate.GameState.push(GAME_SAVING_STATE);
						}
						if( i == 2 )
						{
							gamestate.GameState.pop();
							gamestate.GameState.push(GAME_LOADING_STATE);
						}
						if( i == 1 )
						{
							ResetScore();
							BCPlayer.Reset();
							gamestate.RestartGame();
							Audio.PauseMusic();
							gamestate.GameState.pop();
							gamestate.GameState.push(GAME_RUNNING_STATE);
						}
						if( i == 0 )
						{
							Audio.PauseMusic();
							gamestate.GameState.pop();
							gamestate.GameState.push(GAME_RUNNING_STATE);
						}
						cout << "Hit button..." << i << endl;
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
	ResetScore();
	Quit = false;

	// Setup of the application icons
	//SDL_WM_SetCaption("", "res/big.ico");
	
	//SDL_WM_SetIcon(SDL_LoadBMP("res/small.bmp"), NULL);

	Init( Gfx.screen );
	
	gamestate.load_files();

	//new setclips function
	BCPlayer.SetClips();
	
	// New button stuff
	
	objRectangle(_Button["BName::RESUME_GAME"], 401, 130, 350, 45 );
	objRectangle(_Button["BName::LOAD_GAME" ], 401, 242, 350, 45 );
	objRectangle(_Button["BName::SAVE_GAME" ], 401, 298, 350, 45 );
	objRectangle(_Button["BName::OPTIONS" ], 401, 355, 350, 45 );
	objRectangle(_Button["BName::UNKNOWN" ], 401, 410, 350, 45 );
	objRectangle(_Button["BName::CREDITS "], 401, 465, 350, 45 );
	objRectangle(_Button["BName::QUIT_GAME" ], 401, 519, 350, 45 );
	objRectangle(_Button["BName::UNKNOWN" ], 0, 0, 0, 0 );
	objRectangle(_Button["BName::UNKNOWN" ], 0, 0, 0, 0 );
}

// loads all graphic files and all new files and the font
void Gamestate::load_files()
{
	std::ifstream file;
	file.open("graphics.txt");
	if (!file)
	{
		cout << "CFG: File couldn't be found!\n" << endl;
		MessageBox(NULL,"CFG: File couldn't be found!\n","Failed Loading",MB_OK);
		exit(1);
	}

	std::string line;
	size_t lineNo = 0;
	while (std::getline(file, line))
	{
		lineNo++;
		std::string temp = line;

		if (temp.empty())
			continue;
	}

	file.close();

	file.open("highscore.txt");
	if (!file)
	{
		cout << "CFG: File couldn't be found!\n" << endl;
		MessageBox(NULL,"CFG: File couldn't be found!\n","Failed Loading",MB_OK);
		cin.get();
		cin.get();
		//exit(1);
	}

	lineNo = 0;
	while (std::getline(file, line))
	{
		lineNo++;
		HIGHSCORE = line;

		if (HIGHSCORE.empty())
			continue;
	}

	file.close();

	m_srfCity = Gfx.Load_imageAlpha( "Graphics/srfCity.png", 0, 0, 0 );
	m_srfClouds = Gfx.Load_imageAlpha( "Graphics/srfClouds.png", 255, 255, 255 );
	m_srfBlack = Gfx.Load_imageAlpha( "Graphics/srfBlack.png", 0, 0, 0 );
	m_srfSky = Gfx.Load_imageAlpha( "Graphics/srfSky.png", 0, 0, 0 );
	BCPlayer._Surface = Gfx.Load_imageAlpha( "Graphics/demonSurface.png", 255, 255, 255 );
	m_srfEnemyZombie = Gfx.Load_imageAlpha( "Graphics/srfEnemyZombie.png", 255, 0, 255 );
	m_srfCrow = Gfx.Load_imageAlpha( "Graphics/srfCrow.png", 255, 255, 255 );
	m_srfdemonLife = Gfx.Load_imageAlpha( "Graphics/srfdemonLife.png", 255, 255, 255 );
	m_srfdemonHealthAndFire = Gfx.Load_imageAlpha( "Graphics/srfdemonHealthAndFire.png", 0, 0, 0 );
	m_srfDragon = Gfx.Load_imageAlpha( "Graphics/srfDragon.png", 0, 0, 0 );
	m_srfStart = Gfx.Load_imageAlpha( "Graphics/srfStart.png", 237, 234, 214 );
	m_srfButtons = Gfx.Load_imageAlpha( "Graphics/srfButtons.png", 255, 255, 255 );
	m_srfIntro = Gfx.Load_imageAlpha( "Graphics/srfIntro.png", 255, 255, 255 );
	m_srfMorphing = Gfx.Load_imageAlpha( "Graphics/srfMorphing.png", 255, 255, 241 );
	m_srfOutro = Gfx.Load_imageAlpha( "Graphics/srfOutro.png", 0, 0, 0 );
	m_srfButton = Gfx.Load_imageAlpha( "Graphics/srfButton.png", 0, 0, 0 );
	m_srfHealth = Gfx.Load_imageAlpha( "Graphics/srfHealth.png", 0, 0, 0 );
	m_srfLaser = Gfx.Load_imageAlpha( "Graphics/srfLaser.png", 255, 255, 255 );
	m_srfCredits = Gfx.Load_imageAlpha( "Graphics/srfCredits.png", 255, 255, 255 );
	m_srfOptions = Gfx.Load_imageAlpha( "Graphics/srfOptions.png", 255, 255, 255 );
	m_srfLoad = Gfx.Load_imageAlpha( "Graphics/srfLoad.png", 255, 255, 255 );
	m_srfSave = Gfx.Load_imageAlpha( "Graphics/srfSave.png", 255, 255, 255 );
	m_srfCube = Gfx.Load_imageAlpha( "Graphics/srfCube.png", 255, 255, 255 );
	m_srfTriangle = Gfx.Load_imageAlpha( "Graphics/srfTriangle.png", 255, 255, 255 );
	
	MainMenuScreen = new MainMenu( 290,  m_srfStart, m_srfButtons );
	CreditsScreen = new Credits( 290,  m_srfCredits, m_srfButtons );
	OptionsScreen = new Options( 290, m_srfOptions, m_srfButtons );
	LoadsScreen = new Load( 290, m_srfLoad, m_srfButtons );
	SavesScreen = new Save( 290, m_srfSave, m_srfButtons );
	GameOverScreen = new GameOver( 290,  m_srfStart, m_srfButtons );

	name = new StringInput();

	setUpParallaxLayers();
}

void Gamestate::ResetEnemies()
{
	if(EnemyController.Enemies.size() != NULL )
	{
		EnemyController.Enemies.clear();
	}
}

void Game::Audiotonic()
{
	// does nothing
}

// ----------------------------------------------------------------------------
// Update() - Updates the whole game depending on which state it is in
// ----------------------------------------------------------------------------
void Game::Update( SDL_Event input, int iElapsedTime )
{
	Asteroid SnowAsteroid(0,0,0);
	// calling base class function instead of derived class
	SnowAsteroid.Asteroid::isActive();
	ObjectController.Report(SnowAsteroid);

	std::vector<Bullet> test;

	ObjectController.RemoveActiveObjects();
	test = BulletController.GetVBulletsByReference();
	

	//CollisionController.Box(BulletController.GetBullets(), AnimalController.GetAnimal());
	cout << BCPlayer.GetAction() << endl;


	// Check game state
	switch( gamestate.GameState.top() )
	{
		case MENU_MAIN_STATE:
			{
				gamestate.MainScreen(iElapsedTime);
			} break;
		case GAME_CREDITS_STATE:
			{
				gamestate.CreditScreen(iElapsedTime);
			} break;
		case GAME_OPTIONS_STATE:
			{
				gamestate.OptionScreen(iElapsedTime);
			} break;
		case GAME_LOADING_STATE:
			{
				gamestate.LoadScreen(iElapsedTime);
			} break;
		case GAME_SAVING_STATE:
			{
				gamestate.SaveScreen(iElapsedTime);
			} break;
		case GAME_RUNNING_STATE:
			{
				CollisionController.ObjectCollider( BulletController.BulletArrayRef, AnimalController.AnimalArrayRef );
				CollisionController.SpaceshipCollider(BCPlayer,AnimalController.AnimalArrayRef );
				Gfx.DrawParallaxLayers();
				Gfx.DrawObjects();
				Gfx.DrawSprite();
				Gfx.DrawScore(300,25,UpdateScore());
				
				gamestate.DrawAllText();
			} break;
		case GAME_BOSS_STATE:
			{
				Gfx.DrawScore(300,0,UpdateScore());
			} break;
		case GAME_OUTRO_STATE:
			{
				gamestate.PlayOutro();
			} break;
		case GAME_PLAYER_DIED_STATE:
			{
				BCPlayer.Died();
			} break;
	}
}

// ----------------------------------------------------------------------------
// PlayOutro() - Plays the whole outro sequence
// ----------------------------------------------------------------------------
void Gamestate::PlayOutro()
{
	SDL_BlitSurface( Gfx.GetSurface( gamestate.m_srfOutro ),
					&ScreenSize, Gfx.BackBuffer, &ScreenSize );
	Gfx.FLIP();

	SDL_Event input;

	while( gamestate.GameState.top() == GAME_OUTRO_STATE )
	{
		SDL_PollEvent( &input );
		if( input.type == SDL_KEYDOWN )
		{
  			switch( input.key.keysym.sym )
			{
			case SDLK_SPACE:
				gamestate.GameState.push(MENU_MAIN_STATE);
				break;
			}
		}
	}

	gamestate.RestartGame();

	return;
}

// ----------------------------------------------------------------------------
// DrawAllText() - draws all text thats currently shown on the screen.
// ----------------------------------------------------------------------------
void Gamestate::DrawAllText()
{
	//if( State == GAME_STORY_STATE || State == GAME_PLAYER_DIED_STATE )
	if( gamestate.GameState.top() == GAME_STORY_STATE  || gamestate.GameState.top() == GAME_PLAYER_DIED_STATE )
	{
		if( gamestate.GameState.top() == GAME_PLAYER_DIED_STATE )
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
	}
}

// ----------------------------------------------------------------------------
// Loading() - draws the loading screen on the screen. Dragon dancing
// ----------------------------------------------------------------------------
void Gamestate::Loading()
{
	//does nothing
}


// ----------------------------------------------------------------------------
// MainScreen() - Draws the mainscreen, checks conditions. MenuScreen
// ----------------------------------------------------------------------------
void Gamestate::MainScreen(int iElapsedTime)
{
	SDL_BlitSurface( Gfx.GetSurface( MainMenuScreen->surface ), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect );

	//SDL_FillRect(Gfx.GetSurface( TitleScreen->surface),&TitleScreen->ButtonClips[ 0 ],SDL_MapRGB(Gfx.GetSurface( TitleScreen->surface)->format,255,0,255) );
	//SDL_FillRect(Gfx.GetSurface( TitleScreen->surface),&TitleScreen->ButtonClips[ 1 ],SDL_MapRGB(Gfx.GetSurface( TitleScreen->surface)->format,255,0,255) );
	//SDL_FillRect(Gfx.GetSurface( TitleScreen->surface),&TitleScreen->ButtonClips[ 2 ],SDL_MapRGB(Gfx.GetSurface( TitleScreen->surface)->format,255,0,255) );
	//SDL_FillRect(Gfx.GetSurface( TitleScreen->surface),&TitleScreen->ButtonClips[ 3 ],SDL_MapRGB(Gfx.GetSurface( TitleScreen->surface)->format,255,0,255) );
	//SDL_FillRect(Gfx.GetSurface( TitleScreen->surface),&TitleScreen->ButtonClips[ 4 ],SDL_MapRGB(Gfx.GetSurface( TitleScreen->surface)->format,255,0,255) );
	//SDL_FillRect(Gfx.GetSurface( TitleScreen->surface),&TitleScreen->ButtonClips[ 5 ],SDL_MapRGB(Gfx.GetSurface( TitleScreen->surface)->format,255,0,255) );
	//SDL_FillRect(Gfx.GetSurface( TitleScreen->surface),&TitleScreen->ButtonClips[ 6 ],SDL_MapRGB(Gfx.GetSurface( TitleScreen->surface)->format,255,0,255) );
	//SDL_FillRect(Gfx.GetSurface( TitleScreen->surface),&TitleScreen->ButtonClips[ 7 ],SDL_MapRGB(Gfx.GetSurface( TitleScreen->surface)->format,255,0,255) );
	//SDL_FillRect(Gfx.GetSurface( TitleScreen->surface),&TitleScreen->ButtonClips[ 8 ],SDL_MapRGB(Gfx.GetSurface( TitleScreen->surface)->format,255,0,255) );
	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "MainScreen @ ";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.WhiteRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	return;
}

// ----------------------------------------------------------------------------
// LoadScreen() - Draws the credit screen
// ----------------------------------------------------------------------------
void Gamestate::LoadScreen(int iElapsedTime)
{
	std::cout << "Rendering load screen like a god!!!!" << endl;
	SDL_BlitSurface( Gfx.GetSurface( LoadsScreen->surface ), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect );
	
	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "LoadScreen @";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.BlackRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	if( LoadsScreen->ButtonNewgame == true )
	{
		gamestate.GameState.pop();
		gamestate.GameState.push(GAME_RUNNING_STATE);
		LoadsScreen->ButtonNewgame = false;
	}
	return;
}

// ----------------------------------------------------------------------------
// SaveScreen() - Draws the save screen
// ----------------------------------------------------------------------------
void Gamestate::SaveScreen(int iElapsedTime)
{
	std::cout << "Rendering save screen like a god!!!!" << endl;
	SDL_BlitSurface( Gfx.GetSurface( SavesScreen->surface ), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect );
	
	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "SaveScreen @";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.BlackRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	if( SavesScreen->ButtonNewgame == true )
	{
		gamestate.GameState.pop();
		gamestate.GameState.push(GAME_RUNNING_STATE);
		SavesScreen->ButtonNewgame = false;
	}
	return;
}

// ----------------------------------------------------------------------------
// CreditScreen() - Draws the credit screen
// ----------------------------------------------------------------------------
void Gamestate::CreditScreen(int iElapsedTime)
{
	std::cout << "Rendering credits screen like a god!!!!" << endl;
	SDL_BlitSurface( Gfx.GetSurface( CreditsScreen->surface ), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect );
	
	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "CreditsScreen @";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.BlackRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	return;
}
// ----------------------------------------------------------------------------
// OptionScreen() - Draws the option screen
// ----------------------------------------------------------------------------
void Gamestate::OptionScreen(int iElapsedTime)
{
	Sleep(100);
	SDL_Event _event;
	SDL_PollEvent( &_event );
	if( _event.type == SDL_MOUSEBUTTONDOWN )
	{
		int MouseXCoordinates, MouseYCoordinates;
		SDL_GetMouseState(&MouseXCoordinates, &MouseYCoordinates);
		cout << "(" << MouseXCoordinates << "," << MouseYCoordinates << ")" << endl;
		for( int i = 0; i < 3; i++ )
		{
			if(MouseXCoordinates > OptionsScreen->ButtonClips[ i ].x && 
			MouseXCoordinates < OptionsScreen->ButtonClips[ i ].x + OptionsScreen->ButtonClips[ i ].w &&
			MouseYCoordinates > OptionsScreen->ButtonClips[ i ].y &&
			MouseYCoordinates < OptionsScreen->ButtonClips[ i ].y + OptionsScreen->ButtonClips[ i ].h )
			{
				cout << "Difficuty set to -> " << i << "..." << endl;
				DIFFICULTY = i;
			}
		}
		for( int i = 3; i < 5; i++ )
		{
			if(MouseXCoordinates > OptionsScreen->ButtonClips[ i ].x && 
			MouseXCoordinates < OptionsScreen->ButtonClips[ i ].x + OptionsScreen->ButtonClips[ i ].w &&
			MouseYCoordinates > OptionsScreen->ButtonClips[ i ].y &&
			MouseYCoordinates < OptionsScreen->ButtonClips[ i ].y + OptionsScreen->ButtonClips[ i ].h )
			{
				cout << "Sound set to -> " << i << "..." << endl;
				SOUND = i;
			}
		}
		for( int i = 5; i < 7; i++ )
		{
			if(MouseXCoordinates > OptionsScreen->ButtonClips[ i ].x && 
			MouseXCoordinates < OptionsScreen->ButtonClips[ i ].x + OptionsScreen->ButtonClips[ i ].w &&
			MouseYCoordinates > OptionsScreen->ButtonClips[ i ].y &&
			MouseYCoordinates < OptionsScreen->ButtonClips[ i ].y + OptionsScreen->ButtonClips[ i ].h )
			{
				cout << "Music set to -> " << i << "..." << endl;
				MUSIC = i;
			}
		}

		for( int i = 0; i < 8; i++ )
		{
			if(MouseXCoordinates > OptionsScreen->ButtonClips[ i ].x && 
			MouseXCoordinates < OptionsScreen->ButtonClips[ i ].x + OptionsScreen->ButtonClips[ i ].w &&
			MouseYCoordinates > OptionsScreen->ButtonClips[ i ].y &&
			MouseYCoordinates < OptionsScreen->ButtonClips[ i ].y + OptionsScreen->ButtonClips[ i ].h )
			{
				cout << "Entering button " << i << "..." << endl;
			}
		}
	}
	OptionsScreen->ButtonClips[ 0 ].h = 30;
	OptionsScreen->ButtonClips[ 0 ].w = 103;
	OptionsScreen->ButtonClips[ 0 ].x = 280;
	OptionsScreen->ButtonClips[ 0 ].y = 130;

	OptionsScreen->ButtonClips[ 1 ].h = 30;
	OptionsScreen->ButtonClips[ 1 ].w = 103;
	OptionsScreen->ButtonClips[ 1 ].x = 412;
	OptionsScreen->ButtonClips[ 1 ].y = 130;

	OptionsScreen->ButtonClips[ 2 ].h = 30;
	OptionsScreen->ButtonClips[ 2 ].w = 103;
	OptionsScreen->ButtonClips[ 2 ].x = 554;
	OptionsScreen->ButtonClips[ 2 ].y = 130;

	OptionsScreen->ButtonClips[ 3 ].h = 30;
	OptionsScreen->ButtonClips[ 3 ].w = 103;
	OptionsScreen->ButtonClips[ 3 ].x = 280;
	OptionsScreen->ButtonClips[ 3 ].y = 170;

	OptionsScreen->ButtonClips[ 4 ].h = 30;
	OptionsScreen->ButtonClips[ 4 ].w = 103;
	OptionsScreen->ButtonClips[ 4 ].x = 412;
	OptionsScreen->ButtonClips[ 4 ].y = 170;

	OptionsScreen->ButtonClips[ 5 ].h = 30;
	OptionsScreen->ButtonClips[ 5 ].w = 103;
	OptionsScreen->ButtonClips[ 5 ].x = 280;
	OptionsScreen->ButtonClips[ 5 ].y = 220;

	OptionsScreen->ButtonClips[ 6 ].h = 30;
	OptionsScreen->ButtonClips[ 6 ].w = 103;
	OptionsScreen->ButtonClips[ 6 ].x = 412;
	OptionsScreen->ButtonClips[ 6 ].y = 220;

	OptionsScreen->ButtonClips[ 7 ].h = 30;
	OptionsScreen->ButtonClips[ 7 ].w = 103;
	OptionsScreen->ButtonClips[ 7 ].x = 632;
	OptionsScreen->ButtonClips[ 7 ].y = 534;


	SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0,0,0,0));

	SDL_BlitSurface( Gfx.GetSurface( OptionsScreen->surface ),&SDL_GetVideoSurface()->clip_rect,Gfx.BackBuffer,&SDL_GetVideoSurface()->clip_rect);

	if( DIFFICULTY == 0 )
	SDL_FillRect(Gfx.BackBuffer,&OptionsScreen->ButtonClips[ 0 ],SDL_MapRGB(Gfx.GetSurface( OptionsScreen->surface)->format,255,0,255) );
	else
	if( DIFFICULTY == 1 )
	SDL_FillRect(Gfx.BackBuffer,&OptionsScreen->ButtonClips[ 1 ],SDL_MapRGB(Gfx.GetSurface( OptionsScreen->surface)->format,255,0,255) );
	else
	if( DIFFICULTY == 2 )
	SDL_FillRect(Gfx.BackBuffer,&OptionsScreen->ButtonClips[ 2 ],SDL_MapRGB(Gfx.GetSurface( OptionsScreen->surface)->format,255,0,255) );

	if( SOUND == 3 )
	SDL_FillRect(Gfx.BackBuffer,&OptionsScreen->ButtonClips[ 3 ],SDL_MapRGB(Gfx.GetSurface( OptionsScreen->surface)->format,255,0,255) );
	else
	if( SOUND == 4 )
	SDL_FillRect(Gfx.BackBuffer,&OptionsScreen->ButtonClips[ 4 ],SDL_MapRGB(Gfx.GetSurface( OptionsScreen->surface)->format,255,0,255) );
	
	if( MUSIC == 5 )
	SDL_FillRect(Gfx.BackBuffer,&OptionsScreen->ButtonClips[ 5 ],SDL_MapRGB(Gfx.GetSurface( OptionsScreen->surface)->format,255,0,255) );
	else
	if( MUSIC == 6 )
	SDL_FillRect(Gfx.BackBuffer,&OptionsScreen->ButtonClips[ 6 ],SDL_MapRGB(Gfx.GetSurface( OptionsScreen->surface)->format,255,0,255) );

	SDL_FillRect(Gfx.BackBuffer,&OptionsScreen->ButtonClips[ 7 ],SDL_MapRGB(Gfx.GetSurface( OptionsScreen->surface)->format,255,0,255) );


	std::cout << "Rendering options screen like a god!!!!" << endl;

	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "OptionsScreen @";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.BlackRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	return;
}
// ----------------------------------------------------------------------------
// EnterName() - checks for input demon name
// ----------------------------------------------------------------------------
void Gamestate::EnterName()
{
	SDL_BlitSurface( Gfx.GetSurface( MainMenuScreen->surface ), &ScreenSize, Gfx.BackBuffer, &ScreenSize );
	SDL_Surface * srfEnter = 0;
	//srfEnter = TTF_RenderText_Solid( Gfx.DefaultFont, gamestate.demonName.c_str(), Gfx.BlackRGB );
	Gfx.apply_surface( 200, 400, srfEnter, Gfx.BackBuffer );

	if( gamestate.name->handle_input(  ) == false )
	{
		gamestate.GameState.pop();
		gamestate.GameState.push(GAME_STORY_STATE);
	}
}

void Gamestate::RestartGame()
{
	// does nothing yet!
}

void Gamestate::Cleanup()
{
	if( MainMenuScreen != NULL )
	{
		delete MainMenuScreen;
	}
	if( CreditsScreen != NULL )
	{
		delete CreditsScreen;
	}
	for( int i = 0; i < ParallaxBG->getLayerCount(); i++ )
	{
		SDL_FreeSurface( m_surfaceList[ i ] );
	}
	if( gamestate.name != NULL )
	{
		delete name;
	}
}

void Gamestate::ResetRest()
{
	if( MainMenuScreen != NULL )
	{
		delete MainMenuScreen;
	}
	if( CreditsScreen != NULL )
	{
		delete CreditsScreen;
	}
}

void Game::Cleanup()
{
	TTF_Quit();
	SDL_Quit();
}

// inits sdl, font and videomode
bool Game::Init(SDL_Surface * &screen)
{
	Gfx.screen = 0;

	//set up the screen
	Gfx.screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	SDL_Rect** modes;
	int i;
   
    /* Get available fullscreen/hardware modes */
    modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);
    
    /* Check if there are any modes available */
    if (modes == (SDL_Rect**)0) 
	{
        printf("No modes available!\n");
       exit(-1);
	}
   
   /* Check if our resolution is restricted */
   if (modes == (SDL_Rect**)-1) 
   {
       printf("All resolutions available.\n");
   }
   else
   {
       /* Print valid modes */
       printf("Available Modes\n");
       for (i=0; modes[i]; ++i)
         printf("  %d x %d\n", modes[i]->w, modes[i]->h);
   }

	if( screen == NULL )
	{
		return false;
	}

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

void Gamestate::CreateAll()
{
	static int iScore = 0;

	AnimalController.CreateAnimals(iScore++);
	CubeController.CreateCubes( iScore );
	TriangleController.CreateTriangles( iScore );
	EnemyController.Create_Enemies();
	ObjectController.CreateObjects();
}

void Gamestate::AddTick()
{
	UpdateAnimationSpeed += ( 1000.0f * ( gamestate.DeltaTime / 1000.0f ) );
}

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

	// trees must be here otherwise division by zero currently
	ParallaxBG->setLayer( 2, 0.7f, m_srfSky, 
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


