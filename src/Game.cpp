#pragma once

#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <utility>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Global\Global.h"
#include "Game.h"
#include "SpaceShip.h"
#include "ControlGfx.h"
#include "Audio\Audio.h"
#include "Objects.h"
#include "Enemies\Powerup.h"
#include "Enemies.h"
#include "Enemies\PurpleShip.h"
#include "Enemies\BlueShip.h"
#include "Enemies\Cubes.h"
#include "Enemies\BlueFish.h"
#include "Bullets.h"
#include "MainMenu.h"
#include "Credits.h"
#include "Load.h"
#include "Save.h"
#include "Collision.h"
#include "OutroFinish.h"
#include "GetInput.h"


#ifdef _WIN32
#ifdef _DEBUG
   #include <crtdbg.h>
   #undef THIS_FILE
   static char THIS_FILE[] = __FILE__;
   #define new       new( _NORMAL_BLOCK, __FILE__, __LINE__)
   #define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif

Gamestate gamestate;
Game Engine;

Gamestate::Gamestate()
{
	GameState.push(MENU_MAIN_STATE);

	Parallax = 0.0f;
	DeltaTime = 0.0f;
}

struct SaveGameData
{
    int version;
    int difficulty;
    int sound;
    int music;
    int score;
    int progress;
    int powerup;

    SaveGameData(){version = 1; difficulty = DIFFICULTY; sound = SOUND; music = MUSIC; };
} Savegame;

void Game::HandleEvents( SDL_Event _event )
{
    logger.write(__LINE__,__FILE__);

	switch ( _event.type )
	{
		// Handle mouse button events
        case SDL_MOUSEBUTTONDOWN:
        {
        } break;
		case SDL_MOUSEBUTTONUP:
		{
			switch( gamestate.GameState.top()  )
			{
				case MENU_MAIN_STATE:
				{
				} break;
				case GAME_RUNNING_STATE:
				{
                    gamestate.RestartGame();
				} break;

                case GAME_LOADING_STATE:
                {
                        SetGameOptionButtons();
                        int MouseXCoordinates, MouseYCoordinates;
                        SDL_GetMouseState(&MouseXCoordinates, &MouseYCoordinates);
                        cout << "(" << MouseXCoordinates << "," << MouseYCoordinates << ")" << endl;
                        for (int i = 0; i < 3; i++)
                        {
                            if (MouseXCoordinates > ButtonClips[i].x &&
                                MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                MouseYCoordinates > ButtonClips[i].y &&
                                MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                            {
                                cout << "Difficuty set to -> " << i << "..." << endl;
                                DIFFICULTY = i;
                                Savegame.difficulty = i;
                            }
                        }
                        for (int i = 3; i < 5; i++)
                        {
                            if (MouseXCoordinates > ButtonClips[i].x &&
                                MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                MouseYCoordinates > ButtonClips[i].y &&
                                MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                            {
                                cout << "Sound set to -> " << i << "..." << endl;
                                SOUND = i;
                                Savegame.sound = i;
                            }
                        }
                        for (int i = 5; i < 7; i++)
                        {
                            if (MouseXCoordinates > ButtonClips[i].x &&
                                MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                MouseYCoordinates > ButtonClips[i].y &&
                                MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                            {
                                cout << "Music set to -> " << i << "..." << endl;
                                MUSIC = i;
                                Savegame.music = i;
                            }
                        }
                        for (int i = 7; i < 8; i++)
                        {
                            if (MouseXCoordinates > ButtonClips[i].x &&
                                MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                MouseYCoordinates > ButtonClips[i].y &&
                                MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                            {
                                cout << "Returning to main menu -> " << i << "..." << endl;
                                gamestate.GameState.pop();
                                gamestate.GameState.push(MENU_MAIN_STATE);
                                _event.type = 0;
                            }
                        }
                        for (int i = 0; i < 8; i++)
                        {
                            if (MouseXCoordinates > ButtonClips[i].x &&
                                MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                MouseYCoordinates > ButtonClips[i].y &&
                                MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                            {
                                cout << "Entering button " << i << "..." << endl;
                            }
                        }
                } break;

                case GAME_SAVING_STATE:
                {
                        SetGameOptionButtons();
                        int MouseXCoordinates, MouseYCoordinates;
                        SDL_GetMouseState(&MouseXCoordinates, &MouseYCoordinates);
                        cout << "(" << MouseXCoordinates << "," << MouseYCoordinates << ")" << endl;
                        for (int i = 0; i < 3; i++)
                        {
                            if (MouseXCoordinates > ButtonClips[i].x &&
                                MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                MouseYCoordinates > ButtonClips[i].y &&
                                MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                            {
                                cout << "Saving -> " << i << "..." << endl;
                                std::ofstream of("./saves/game.sav", std::ios::out);
                                if (of.is_open())
                                {
                                    of << Savegame.version << endl;
                                    of << Savegame.difficulty << endl;
                                    of << Savegame.music << endl;
                                    of << Savegame.sound << endl;
                                    of << "save\n";
                                    MessageBox(NULL, "Do you really want to save over savegame", "Override savegame", MB_YESNO | MB_ICONWARNING);
                                }
                                else
                                {
                                    MessageBox(NULL, "Do you really want to save over savegame", "Override savegame", MB_OK | MB_ICONERROR);
                                }
                            }
                        }
                        for (int i = 3; i < 5; i++)
                        {
                            if (MouseXCoordinates > ButtonClips[i].x &&
                                MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                MouseYCoordinates > ButtonClips[i].y &&
                                MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                            {
                                cout << "Sound set to -> " << i << "..." << endl;
                                SOUND = i;
                            }
                        }
                        for (int i = 5; i < 7; i++)
                        {
                            if (MouseXCoordinates > ButtonClips[i].x &&
                                MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                MouseYCoordinates > ButtonClips[i].y &&
                                MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                            {
                                cout << "Music set to -> " << i << "..." << endl;
                                MUSIC = i;
                            }
                        }
                        for (int i = 7; i < 8; i++)
                        {
                            if (MouseXCoordinates > ButtonClips[i].x &&
                                MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                MouseYCoordinates > ButtonClips[i].y &&
                                MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                            {
                                cout << "Returning to main menu -> " << i << "..." << endl;
                                gamestate.GameState.pop();
                                gamestate.GameState.push(MENU_MAIN_STATE);
                                _event.type = 0;
                            }
                        }
                        for (int i = 0; i < 8; i++)
                        {
                            if (MouseXCoordinates > ButtonClips[i].x &&
                                MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                MouseYCoordinates > ButtonClips[i].y &&
                                MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                            {
                                cout << "Entering button " << i << "..." << endl;
                            }
                        }
                } break;


				case GAME_OPTIONS_STATE:
				{
					SetGameOptionButtons();
					int MouseXCoordinates, MouseYCoordinates;
					SDL_GetMouseState(&MouseXCoordinates, &MouseYCoordinates);
					cout << "(" << MouseXCoordinates << "," << MouseYCoordinates << ")" << endl;
					for( int i = 0; i < 3; i++ )
					{
						if(MouseXCoordinates > ButtonClips[ i ].x && 
						MouseXCoordinates < ButtonClips[ i ].x + ButtonClips[ i ].w &&
						MouseYCoordinates > ButtonClips[ i ].y &&
						MouseYCoordinates < ButtonClips[ i ].y + ButtonClips[ i ].h )
						{
							cout << "Difficuty set to -> " << i << "..." << endl;
							DIFFICULTY = i;
						}
					}
					for( int i = 3; i < 5; i++ )
					{
						if(MouseXCoordinates > ButtonClips[ i ].x && 
						MouseXCoordinates < ButtonClips[ i ].x + ButtonClips[ i ].w &&
						MouseYCoordinates > ButtonClips[ i ].y &&
						MouseYCoordinates < ButtonClips[ i ].y + ButtonClips[ i ].h )
						{
							cout << "Sound set to -> " << i << "..." << endl;
							SOUND = i;
						}
					}
					for( int i = 5; i < 7; i++ )
					{
						if(MouseXCoordinates > ButtonClips[ i ].x && 
						MouseXCoordinates < ButtonClips[ i ].x + ButtonClips[ i ].w &&
						MouseYCoordinates > ButtonClips[ i ].y &&
						MouseYCoordinates < ButtonClips[ i ].y + ButtonClips[ i ].h )
						{
							cout << "Music set to -> " << i << "..." << endl;
							MUSIC = i;
						}
					}
					for( int i = 7; i < 8; i++ )
					{
						if(MouseXCoordinates > ButtonClips[ i ].x && 
						MouseXCoordinates < ButtonClips[ i ].x + ButtonClips[ i ].w &&
						MouseYCoordinates > ButtonClips[ i ].y &&
						MouseYCoordinates < ButtonClips[ i ].y + ButtonClips[ i ].h )
						{
							cout << "Returning to main menu -> " << i << "..." << endl;
							gamestate.GameState.pop();
							gamestate.GameState.push(MENU_MAIN_STATE);
							_event.type = 0;
						}
					}
					for( int i = 0; i < 8; i++ )
					{
						if(MouseXCoordinates > ButtonClips[ i ].x && 
						MouseXCoordinates < ButtonClips[ i ].x + ButtonClips[ i ].w &&
						MouseYCoordinates > ButtonClips[ i ].y &&
						MouseYCoordinates < ButtonClips[ i ].y + ButtonClips[ i ].h )
						{
							cout << "Entering button " << i << "..." << endl;
						}
					}
				} break;
			}
		} break; // END OF MOUSEUP

		case SDL_KEYDOWN:
		{
			switch( gamestate.GameState.top()  )
			{
				case MENU_MAIN_STATE:
				{
					switch( _event.key.keysym.sym )		
					{
						case SDLK_ESCAPE:
						{
							std::cout << "Trying to quit the game" << endl;
						} break;
					}
				} break;
				case GAME_CREDITS_STATE:
				{
					switch( _event.key.keysym.sym )
					{
						case SDLK_ESCAPE:
						{
							gamestate.GameState.pop();
							gamestate.GameState.push(MENU_MAIN_STATE);
						} break;
					}
				} break;
				case GAME_SAVING_STATE:
				{
					switch( _event.key.keysym.sym )
					{
						case SDLK_ESCAPE:
						{
							gamestate.GameState.pop();
							gamestate.GameState.push(MENU_MAIN_STATE);
						} break;
					}
				} break;
				case GAME_LOADING_STATE:
				{
					switch( _event.key.keysym.sym )
					{
						case SDLK_ESCAPE:
						{
							gamestate.GameState.pop();
							gamestate.GameState.push(MENU_MAIN_STATE);
						} break;
					}
				} break;
				case GAME_RUNNING_STATE:
				{
 
				} break;
				case GAME_OPTIONS_STATE:
				{
					switch( _event.key.keysym.sym )
					{
						case SDLK_ESCAPE:
						{
							gamestate.GameState.pop();
							gamestate.GameState.push(MENU_MAIN_STATE);
						} break;
					}
				} break;
			}
		} break;
		case SDL_KEYUP:
		{
			switch( gamestate.GameState.top()  )
			{
				case MENU_MAIN_STATE:
				{
				} break;
				case GAME_RUNNING_STATE:
				{
                    GamePad->HandleInput(_event);
				} break;
			}
		} break;
		case SDL_ACTIVEEVENT:
		{
			std::cout << "Hey stop focusing on other windows, get back here!" << endl;
		} break;
		case SDL_QUIT:
		{
			Quit = true;
		} break;
        default:
        {
            cout << "Unknown event please try again.." << endl;
        }
	}

	if(gamestate.GameState.top() == MENU_MAIN_STATE)
	{
		//if( MUSIC == 5 )
			Audio.PlayMusic( 3 );
		//else
			//Audio.PauseMusic();

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
		if (_event.type == SDL_MOUSEBUTTONUP )
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
							Audio.PauseMusic();
							gamestate.RestartGame();
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
    logger.write(__LINE__, __FILE__);

	SPAWN_POSITION_X = 0;
	SPAWN_POSITION_Y = 1080/2;
	_SCORE = 0;

	Quit = false;

	Init( Gfx.screen );
	
	gamestate.load_files();

	//new setclips function
    Spaceship.SetClips();
	
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
    logger.write(__LINE__, __FILE__);

    // Backdrops and logos
	m_srfBackdrop = Gfx.Load_imageAlpha( "assets/gfx/backdrops/srfBackdrop_1920x1080.png", 0, 0, 0 );
	m_srfBlack = Gfx.Load_imageAlpha( "assets/gfx/backdrops/srfMooPie_1920x1080.png", 0, 0, 0 );

    // Player spaceship
	Spaceship._SurfaceID = Gfx.Load_imageAlpha( "assets/gfx/spaceship/srfSpaceship.png", 0, 0, 0 );
	
	m_srfStart = Gfx.Load_imageAlpha( "assets/gfx/backdrops/srfMainMenu_1920x1080.png", 0, 0, 0 );
	m_srfHealth = Gfx.Load_imageAlpha( "assets/gfx/gui/srfHealth.png", 0, 0, 0 );
	m_srfLaser = Gfx.Load_imageAlpha( "assets/gfx/lasers/srfLaserBlue.png", 0, 0, 0 );
	m_srfButtonActive = Gfx.Load_imageAlpha( "assets/gfx/backdrops/srfButtonActive_101x33.png", 255, 255, 255 );

    // Sub menus & Screens
    m_srfCredits = Gfx.Load_imageAlpha("assets/gfx/backdrops/srfCredits_1920x1080.png", 0, 0, 0);
    m_srfOptions = Gfx.Load_imageAlpha("assets/gfx/backdrops/srfOptions_1920x1080.png", 0, 0, 0);
    m_srfLoad = Gfx.Load_imageAlpha("assets/gfx/backdrops/srfLoad_1920x1080.png", 0, 0, 0);
    m_srfSave = Gfx.Load_imageAlpha("assets/gfx/backdrops/srfSave_1920x1080.png", 0, 0, 0);
    m_srfGameover = Gfx.Load_imageAlpha("assets/gfx/backdrops/srfGameover_1920x1080.png", 0, 0, 0);

    // Laser colors
    m_srfLaser = Gfx.Load_imageAlpha("assets/gfx/lasers/srfLaserBlue.png", 0, 0, 0);

    // Powerups
    m_srfRedPowerup = Gfx.Load_imageAlpha("assets/gfx/powerups/srfRedPowerup.png", 0, 0, 0);
    m_srfGreenPowerup = Gfx.Load_imageAlpha("assets/gfx/pPowerups/srfGreenPowerup.png", 0, 0, 0);
    m_srfBluePowerup = Gfx.Load_imageAlpha("assets/gfx/powerups/srfBluePowerup.png", 0, 0, 0);
    // Enemies
    m_srfPurpleShip = Gfx.Load_imageAlpha("assets/gfx/enemies/srfPurpleShip_128x128.png", 0, 0, 0);
    m_srfBlueShip = Gfx.Load_imageAlpha("assets/gfx/enemies/srfBlueShip.png", 0, 0, 0);
    m_srfBlueFish = Gfx.Load_imageAlpha("assets/gfx/enemies/srfBlueFish.png", 0, 0, 0);
    //Bosses
    m_srfOctoBoss = Gfx.Load_imageAlpha("assets/gfx/bosses/octopus.png", 0, 0, 0);
    OctoController.LoadImageAlpha("assets/gfx/bosses/octopus.png",0,0,0);
    OctoBossman.LoadImageAlpha("assets/gfx/bosses/octopus.png", 0, 0, 0);


	MainMenuScreen = new MainMenu( 290,  m_srfStart, m_srfButtons );
	CreditsScreen = new Credits( 290,  m_srfCredits, m_srfButtons );
	OptionsScreen = new Options( 290, m_srfOptions, m_srfButtons );
	LoadsScreen = new Load( 290, m_srfLoad, m_srfButtons );
	SavesScreen = new Save( 290, m_srfSave, m_srfButtons );
    GameOverScreen = new GameOver(290, m_srfSave, m_srfButtons);
}

// ----------------------------------------------------------------------------
// Update() - Updates the whole game depending on which state it is in
// ----------------------------------------------------------------------------
void Game::Update( SDL_Event input, int iElapsedTime )
{
    logger.write(__LINE__, __FILE__);
	
	// Check game state
	switch( gamestate.GameState.top() )
	{
        case GAMEOVER_STATE:
            {
                gamestate.Gameover(iElapsedTime);
            } break;
		case MENU_MAIN_STATE:
			{
                if (SDL_ShowCursor(SDL_QUERY) == SDL_DISABLE)
                    SDL_ShowCursor(SDL_ENABLE);

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
                if( SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE)
                    SDL_ShowCursor(SDL_DISABLE);

                if (PowerLevel < 100)
                {
                    PowerLevel += 1;
                }

                if ( PowerLevelSecond < 5 )
                {
                    PowerLevelSecond += 1;
                }
				
                LevelProgress += iElapsedTime / 150;

                gamestate.CreateAll();

                Gfx.DrawBackgroundBlack();
                
                SDL_Rect Scroller;
                Scroller.h = 1080;
                Scroller.w = 1920;
                Scroller.x = Progressbar();
                Scroller.y = 0;
                
                SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfBackdrop), &Scroller, Gfx.BackBuffer, 0);
                                
                Scroller.h = 1080;
                Scroller.w = 1920;
                Scroller.x = 1620;
                Scroller.y = 0;
                static int Bossy = 0;
                static int Direction = 0;
                if (Progressbar() > 1000)
                {
                    OctoBossman.Update();
                    OctoBossman.Draw();
                    if (OctoBossman.onCollision(Spaceship.GetCollisionBox()))
                    {
                        OctoBossman.onDestruction();
                        Spaceship.Died();
                        Spaceship.Reset();
                    }
                    //Scroller.y = Bossy;
                    //SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfOctoBoss), 0, Gfx.BackBuffer, &Scroller);
                    //OctoBulletController.CreateOctoBullets();
                    //if (Direction == 0)
                    //{
                    //    if ( Bossy == 1000)
                    //    Direction = 1;
                    //    else
                    //    Bossy += 10;
                    //}                        
                    //else
                    //{
                    //    if ( Bossy == 0)
                    //    Direction = 0;
                    //    else
                    //    Bossy -= 10;
                    //}
                    //

                   
                }
                if (Progressbar() < 5000)
                {
                    Gfx.srfText = TTF_RenderText_Blended(Gfx.TitleFont, "CHAPTER 1 - Chase of the octopus", Gfx.WhiteRGB);
                    Gfx.apply_surface(Gfx.BackBuffer->w / 4, Gfx.BackBuffer->h / 2, Gfx.srfText, Gfx.BackBuffer);
                }
				Gfx.DrawObjects();				
				
                // Collision controllers for objects and player spaceship
                CollisionController.ObjectCollider(BulletController.BulletArrayRef, PurpleShipController.PurpleShipArrayRef);
                CollisionController.ObjectCollider( BulletController.BulletArrayRef, BlueShipController.BlueShipArrayRef );
				CollisionController.ObjectCollider( BulletController.BulletArrayRef, BlueFishController.BlueFishArrayRef );
                
                CollisionController.SpaceshipCollider(Spaceship, PurpleShipController.PurpleShipArrayRef);
                CollisionController.SpaceshipCollider( Spaceship, BlueShipController.BlueShipArrayRef );
				CollisionController.SpaceshipCollider( Spaceship,BlueFishController.BlueFishArrayRef );
                CollisionController.SpaceshipCollider( Spaceship,OctoBossman);

                CollisionController.SpaceshipCollider( Spaceship, PowerupController.PowerupArrayRef);

                Gfx.DrawScore(Gfx.BackBuffer->w / 2, 0, UpdateScore());

                Gfx.srfText = TTF_RenderText_Blended(Gfx.ScoreFont, std::to_string(UpdateScore()).c_str(), Gfx.WhiteRGB);
                Gfx.apply_surface(Gfx.BackBuffer->w / 2, 0, Gfx.srfText, Gfx.BackBuffer);
                
                Gfx.DrawScore(Gfx.BackBuffer->w / 2, 50, Progressbar());

                Gfx.srfText = TTF_RenderText_Blended(Gfx.ScoreFont, std::to_string(Progressbar()).c_str(), Gfx.WhiteRGB);
                Gfx.apply_surface(Gfx.BackBuffer->w - 150, 0, Gfx.srfText, Gfx.BackBuffer);

                Gfx.DrawSprite();

                // Gui options
                SDL_Rect Powerlevel;
                Powerlevel.x = 200;
                Powerlevel.y = 0;
                Powerlevel.h = 20;
                Powerlevel.w = PowerLevel;
                SDL_FillRect(Gfx.BackBuffer, &Powerlevel, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 255, 0, 0));

				Gfx.FLIP();
			} break;
		case GAME_PLAYER_DIED_STATE:
			{
				Spaceship._Lives--;
				if( Spaceship._Lives > 0 )
				{
					gamestate.Reset();
					gamestate.GameState.pop();
					gamestate.GameState.push(GAME_RUNNING_STATE);
				}
				else
				{
					gamestate.GameState.pop();
                    gamestate.GameState.push(GAMEOVER_STATE);
				}
			} break;
	}
}

// ----------------------------------------------------------------------------
// MainScreen() - Draws the mainscreen, checks conditions. MenuScreen
// ----------------------------------------------------------------------------
void Gamestate::MainScreen(int iElapsedTime)
{
    logger.write(__LINE__, __FILE__);
    SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 0, 0));
    SDL_BlitSurface(&Gfx.m_SurfaceCollection["assets/gfx/backdrops/srfMooPie_1920x1080.png"], 0, Gfx.BackBuffer, 0);
	SDL_BlitSurface( &Gfx.m_SurfaceCollection["assets/gfx/backdrops/srfMainMenu_1920x1080.png"], 0, Gfx.BackBuffer, 0 );

	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "MainScreen @ ";
	str.append(ss.str());
	
    Gfx.RenderText(str.c_str(), 0, 50);
}

// ----------------------------------------------------------------------------
// LoadScreen() - Draws the credit screen
// ----------------------------------------------------------------------------
void Gamestate::LoadScreen(int iElapsedTime)
{
    logger.write(__LINE__, __FILE__);
    SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 0, 0));
    SDL_BlitSurface(&Gfx.m_SurfaceCollection["assets/gfx/backdrops/srfLoad_1920x1080.png"], 0, Gfx.BackBuffer, 0);

    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[0]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[1]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[2]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[3]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[4]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[5]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[6]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[7]);

	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "LoadScreen @";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.WhiteRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	if( LoadsScreen->ButtonNewgame == true )
	{
		gamestate.GameState.pop();
		gamestate.GameState.push(GAME_RUNNING_STATE);
		LoadsScreen->ButtonNewgame = false;
	}
}

// ----------------------------------------------------------------------------
// SaveScreen() - Draws the save screen
// ----------------------------------------------------------------------------
void Gamestate::SaveScreen(int iElapsedTime)
{
    logger.write(__LINE__, __FILE__);
    SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 0, 0));
    SDL_BlitSurface(&Gfx.m_SurfaceCollection["assets/gfx/backdrops/srfSave_1920x1080.png"], 0, Gfx.BackBuffer, 0);

    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[0]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[1]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[2]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[3]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[4]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[5]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[6]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[7]);

	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "SaveScreen @";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.WhiteRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	if( SavesScreen->ButtonNewgame == true )
	{
		gamestate.GameState.pop();
		gamestate.GameState.push(GAME_RUNNING_STATE);
		SavesScreen->ButtonNewgame = false;
	}
}

// ----------------------------------------------------------------------------
// Gameover() - Draws the gameover screen
// ----------------------------------------------------------------------------

void Gamestate::Gameover(int iElapsedTime)
{
    OctoBossman.onDestruction();
    logger.write(__LINE__, __FILE__);
    SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 0, 0));
    SDL_BlitSurface(&Gfx.m_SurfaceCollection["assets/gfx/backdrops/srfGameover_1920x1080.png"], 0, Gfx.BackBuffer, 0);
    
    SDL_Surface * srfGameoverText;
    srfGameoverText = TTF_RenderText_Solid(Gfx.GameoverFont, "GAME OVER", Gfx.WhiteRGB);
    Gfx.apply_surface(500, 500, srfGameoverText, Gfx.BackBuffer);
    if (GameOverScreen->ButtonNewgame == true)
    {
        gamestate.GameState.pop();
        gamestate.GameState.push(GAME_RUNNING_STATE);
        GameOverScreen->ButtonNewgame = false;
    }
}

// ----------------------------------------------------------------------------
// CreditScreen() - Draws the credit screen
// ----------------------------------------------------------------------------
void Gamestate::CreditScreen(int iElapsedTime)
{
    logger.write(__LINE__, __FILE__);
    SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 0, 0));
    SDL_BlitSurface(&Gfx.m_SurfaceCollection["assets/gfx/backdrops/srfCredits_1920x1080.png"], 0, Gfx.BackBuffer, 0);
	
	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "CreditsScreen @";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.WhiteRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
}

// ----------------------------------------------------------------------------
// OptionScreen() - Draws the option screen
// ----------------------------------------------------------------------------
void Gamestate::OptionScreen(int iElapsedTime)
{
    logger.write(__LINE__, __FILE__);
    SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 0, 0));
    SDL_BlitSurface(&Gfx.m_SurfaceCollection["assets/gfx/backdrops/srfOptions_1920x1080.png"], 0, Gfx.BackBuffer, 0);
	
	if( DIFFICULTY == 0 )
	{
			SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 0 ]);
	}
	else
	if( DIFFICULTY == 1 )
	{
		SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 1 ]);
	}
	else
	if( DIFFICULTY == 2 )
	{
		SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 2 ]);
	}
	if( SOUND == 3 )
	{
		SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 3 ]);
	}
	else
	if( SOUND == 4 )
	{
		SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 4 ]);
	}
	if( MUSIC == 5 )
	{
		SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 5 ]);
		//Audio.PlayMusic( std::rand() % 3 );
	}
	else
	if( MUSIC == 6 )
	{
		SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 6 ]);
		Audio.PauseMusic();
	}

	SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 7 ]);

	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "OptionsScreen @";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.WhiteRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
}

void Gamestate::RestartGame()
{
    logger.write(__LINE__, __FILE__);
    OctoBossman.onDestruction();
	Spaceship.Reset();

    PurpleShipController.Destroy();
    BlueShipController.Destroy();
	BlueFishController.BlueFishArrayRef.clear();

	_SCORE = 0;
	Spaceship._Lives = 3;
    Engine.Progressbar(0,1);
}

void Gamestate::Reset()
{
    logger.write(__LINE__, __FILE__);
	Spaceship.Reset();

    PurpleShipController.Destroy();
    BlueShipController.Destroy();
	BlueFishController.BlueFishArrayRef.clear();
}

void Gamestate::Cleanup()
{
    logger.write(__LINE__, __FILE__);
	if( MainMenuScreen != NULL )
	{
		delete MainMenuScreen;
	}
	if( CreditsScreen != NULL )
	{
		delete CreditsScreen;
	}
	if( gamestate.name != NULL )
	{
		delete name;
	}
	if( gamestate.OptionsScreen != NULL )
	{
		delete OptionsScreen;
	}
	if( gamestate.LoadsScreen != NULL )
	{
		delete LoadsScreen;
	}
	if( gamestate.SavesScreen != NULL )
	{
		delete SavesScreen;
	}
}

void Game::Cleanup()
{
    logger.write(__LINE__, __FILE__);
    atexit(TTF_Quit); // Ensure TTF_Quit() is called when we exit
	SDL_Quit();
}

// inits sdl, font and videomode
bool Game::Init(SDL_Surface * &screen)
{
    logger.write(__LINE__, __FILE__);

    //Testing
    SDL_putenv("SDL_VIDEO_CENTERED=center"); //Center the game Window
	screen = 0;
    Uint32 flags = SDL_HWSURFACE | SDL_DOUBLEBUF; //| SDL_FULLSCREEN;
    flags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_NOFRAME;
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        cout << "SDL INIT FAILED..." << endl;
        SDL_Quit();
    }
    else
    {
        cout << "SDL_INIT_EVERYTHING..." << endl;
    }
    const SDL_VideoInfo* info = SDL_GetVideoInfo();
    ScreenSize.w = info->current_w;
    ScreenSize.h = info->current_h;
	//set up the screen
	screen = SDL_SetVideoMode(ScreenSize.w, ScreenSize.h, 32, flags);
 
    // Get the current video hardware information
    const SDL_VideoInfo* myPointer = SDL_GetVideoInfo();
    
    screen = SDL_SetVideoMode(myPointer->current_w, myPointer->current_h, 32, flags);
    Gfx.m_SurfaceCollection["Screen"] = *SDL_SetVideoMode(ScreenSize.w, ScreenSize.h, 32, flags);
    
    //Uint32 flags = SDL_SWSURFACE; /* Start with whatever flags you prefer */
    //flags = screen->flags; /* Save the current flags in case toggling fails */
    //screen = SDL_SetVideoMode(0, 0, 0, screen->flags ^ SDL_FULLSCREEN); /*Toggles FullScreen Mode */
    //if (screen == NULL) screen = SDL_SetVideoMode(0, 0, 0, flags); /* If toggle FullScreen failed, then switch back */
    //if (screen == NULL) exit(1); /* If you can't switch back for some reason, then epic fail */

	SDL_Rect** modes;
	int i;
   
    /* Get available fullscreen/hardware modes */
    modes = SDL_ListModes(NULL, SDL_FULLSCREEN | SDL_HWSURFACE);
    
    /* Check if there are any modes available */
    if (modes == (SDL_Rect**)0) 
	{
        cout << "No modes available!" << endl;
        exit(-1);
	}
   
   /* Check if our resolution is restricted */
   if (modes == (SDL_Rect**)-1) 
   {
       cout << "All resolutions available." << endl;
   }
   else
   {
       /* Print valid modes */
       cout << "Available Modes" << endl;
       for (i = 0; modes[i]; ++i)
       {
           cout << modes[i]->w << " x " << modes[i]->h << endl;
       }
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

	//rmask = 0x00000000;
	//gmask = 0x00000000;
	//bmask = 0x00000000;
	//amask = 0x00000000;

	//Gfx.BackBuffer = SDL_CreateRGBSurface( SDL_HWSURFACE, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h, SDL_GetVideoSurface()->format->BitsPerPixel,
	//							   rmask, gmask, bmask, amask);

    Gfx.BackBuffer = SDL_CreateRGBSurface(0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h, SDL_GetVideoSurface()->format->BitsPerPixel, 0, 0, 0, 0);
	
	if( Gfx.BackBuffer == NULL )
	{
		return false;																							
	}

	return true;
}

int Game::UpdateScore(int add_score)
{
    logger.write(__LINE__, __FILE__);
    return _SCORE += add_score;
}

int Game::Progressbar(int progress, int _reset)
{
    double t = 0.0;
    double dt = 1.0 / 60.0;
    if ( _reset == 1 )
        _Progress = 0;

    logger.write(__LINE__, __FILE__);
    if ( progress == 0 )
        return _Progress += dt * 20;
    else
        return _Progress += dt * 20;

}

void Gamestate::CreateAll()
{
    logger.write(__LINE__, __FILE__);
    PurpleShipController.CreatePurpleShip(Engine.Progressbar());
    BlueShipController.CreateBlueShip(Engine.Progressbar());
    BlueFishController.CreateBlueFish(Engine.Progressbar());
	EnemyController.Create_Enemies();
	ObjectController.CreateObjects();
}