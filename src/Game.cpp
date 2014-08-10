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

#include "Global\Global.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Game.h"
#include "SpaceShip.h"
#include "ControlGfx.h"
#include "Audio.h"
#include "Objects.h"
#include "Enemies\Powerup.h"
#include "Enemies.h"
#include "Timers.h"
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
#include "World\CWorld.h"

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

struct SaveGameData
{
    int version;
    int difficulty;
    int sound;
    int music;
} Savegame;

void Game::HandleEvents( SDL_Event _event )
{
	switch ( _event.type )
	{
		// Handle mouse button events
        case SDL_MOUSEBUTTONDOWN:
        {} break;
		case SDL_MOUSEBUTTONUP:
		{
			switch( gamestate.GameState.top()  )
			{
				case MENU_MAIN_STATE:
				{
					cout << "Release mouse button" << endl;
				} break;
				case GAME_RUNNING_STATE:
				{
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
                                }
                                else
                                {
                                    exit(1);
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
                    //GamePad->HandleInput(_event);
                    /*
						switch( _event.key.keysym.sym )
						{
							case SDLK_RIGHT:
							{
                                Spaceship.xVelocity = MAX_VELOCITY;
							} break;
							case SDLK_LEFT:
							{
                                Spaceship.xVelocity = -MIN_VELOCITY;
							} break;
							case SDLK_UP:
							{
                                Spaceship.yVelocity = MAX_VELOCITY;
							} break;
							case SDLK_DOWN:
							{
                                Spaceship.yVelocity = -MIN_VELOCITY;
							} break;
							case SDLK_SPACE:
							{
								if( FIRED == 0 )
								{
									BulletController.Create_Bullets();
									FIRED = 1;
									Gfx.FLIP();
									Audio.PlaySoundEffect( 4 );
								}
							} break;
							case SDLK_LALT:
							{
								Spaceship.AddAction("FIRE_SPECIAL");
							} break;
							case SDLK_RETURN:
							{
								Spaceship.AddAction("RETURN");
							} break;
							case SDLK_ESCAPE:
							{
								std::cout << "Trying to get to the menu eeeyyy!!" << endl;
								gamestate.GameState.push(MENU_MAIN_STATE);
							} break;
							default:
							{
								Spaceship.AddAction("DEFAULT");
							}
					}*/
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
                    
                    /*
					switch( _event.key.keysym.sym )		
					{
						case SDLK_ESCAPE:
						{
							//gamestate.GameState.push(MENU_MAIN_STATE);
						} break;
						case SDLK_RIGHT:
						{
                            Spaceship.xVelocity = NO_VELOCITY;
						} break;
						case SDLK_LEFT:
						{
                            Spaceship.xVelocity = NO_VELOCITY;
						} break;
						case SDLK_UP:
						{
                            Spaceship.yVelocity = NO_VELOCITY;
						} break;
						case SDLK_DOWN:
						{
                            Spaceship.yVelocity = NO_VELOCITY;
						} break;
						case SDLK_SPACE:
						{
                            if (FIRED == 0)
                            {
                                BulletController.Create_Bullets();
                                FIRED = 1;
                                Gfx.FLIP();
                                Audio.PlaySoundEffect(4);
                            }
						} break;
					}*/
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
            cout << "Unknown event please try again.." << endl;
	}

	if(gamestate.GameState.top() == MENU_MAIN_STATE)
	{
		if( MUSIC == 5 )
			Audio.PlayMusic(rand()%3);
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
	cout << "Creating the Game::Game object..." << endl;

    CubeController.LoadSpawnPoints();

	SPAWN_POSITION_X = 0;
	SPAWN_POSITION_Y = 0;
	_SCORE = 0;

	Quit = false;

	// Setup of the application icons
	//SDL_WM_SetCaption("", "res/big.ico");
	
	//SDL_WM_SetIcon(SDL_LoadBMP("res/small.bmp"), NULL);

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
	std::ifstream file;
    file.open(path_assets+"gfx.conf");
	if (!file)
	{
        MessageBox(NULL, "Serious error", "gfx.conf not found", MB_ICONSTOP | MB_SETFOREGROUND);

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

	m_srfBackdrop = Gfx.Load_imageAlpha( "assets/gfx/backdrops/srfBackdrop.png", 0, 0, 0 );
	m_srfBlack = Gfx.Load_imageAlpha( "assets/gfx/srfBlack.png", 0, 0, 0 );
	Spaceship._SurfaceID = Gfx.Load_imageAlpha( "assets/gfx/srfSpaceship.png", 0, 0, 0 );
	m_srfAsteroid = Gfx.Load_imageAlpha( "assets/gfx/srfAsteroid.png", 0, 0, 0 );
	m_srfStart = Gfx.Load_imageAlpha( "assets/gfx/backdrops/srfStart.png", 237, 234, 214 );
	m_srfButtons = Gfx.Load_imageAlpha( "assets/gfx/srfButtons.png", 255, 255, 255 );
	m_srfIntro = Gfx.Load_imageAlpha( "assets/gfx/srfIntro.png", 255, 255, 255 );
	m_srfOutro = Gfx.Load_imageAlpha( "assets/gfx/srfOutro.png", 0, 0, 0 );
	m_srfHealth = Gfx.Load_imageAlpha( "assets/gfx/srfHealth.png", 0, 0, 0 );
	m_srfLaser = Gfx.Load_imageAlpha( "assets/gfx/srfLaser.png", 0, 0, 0 );
	m_srfCredits = Gfx.Load_imageAlpha( "assets/gfx/backdrops/srfCredits.png", 255, 255, 255 );
	m_srfOptions = Gfx.Load_imageAlpha( "assets/gfx/backdrops/srfOptions.png", 255, 255, 255 );
	m_srfLoad = Gfx.Load_imageAlpha( "assets/gfx/backdrops/srfLoad.png", 255, 255, 255 );
	m_srfSave = Gfx.Load_imageAlpha( "assets/gfx/backdrops/srfSave.png", 255, 255, 255 );
	m_srfCube = Gfx.Load_imageAlpha( "assets/gfx/srfCube.png", 255, 255, 255 );
	m_srfTriangle = Gfx.Load_imageAlpha( "assets/gfx/srfTriangle.png", 255, 255, 255 );
	m_srfButtonActive = Gfx.Load_imageAlpha( "assets/gfx/backdrops/srfButtonActive.png", 255, 255, 255 );

    m_srfRedPowerup = Gfx.Load_imageAlpha("assets/gfx/powerups/srfRedPowerup.png", 0, 0, 0);
    m_srfGreenPowerup = Gfx.Load_imageAlpha("assets/gfx/pPowerups/srfGreenPowerup.png", 0, 0, 0);
    m_srfBluePowerup = Gfx.Load_imageAlpha("assets/gfx/powerups/srfBluePowerup.png", 0, 0, 0);
	
	/*
	std::map<string,int> m_SurfaceCollection;
	
	m_SurfaceCollection["Graphics/srfCity.png"] = Gfx.Load_imageAlpha( "Graphics/srfCity.png", 0, 0, 0 );
	m_SurfaceCollection["Graphics/srfClouds.png"] = Gfx.Load_imageAlpha( "Graphics/srfClouds.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfBlack.png"] = Gfx.Load_imageAlpha( "Graphics/srfBlack.png", 0, 0, 0 );
	m_SurfaceCollection["Graphics/srfSky.png"] = Gfx.Load_imageAlpha( "Graphics/srfSky.png", 0, 0, 0 );
	m_SurfaceCollection["Graphics/demonSurface.png"] = Gfx.Load_imageAlpha( "Graphics/demonSurface.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfEnemyZombie.png"] = Gfx.Load_imageAlpha( "Graphics/srfEnemyZombie.png", 255, 0, 255 );
	m_SurfaceCollection["Graphics/srfCrow.png"] = Gfx.Load_imageAlpha( "Graphics/srfCrow.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfdemonLife.png"] = Gfx.Load_imageAlpha( "Graphics/srfdemonLife.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfdemonHealthAndFire.png"] = Gfx.Load_imageAlpha( "Graphics/srfdemonHealthAndFire.png", 0, 0, 0 );
	m_SurfaceCollection["Graphics/srfDragon.png"] = Gfx.Load_imageAlpha( "Graphics/srfDragon.png", 0, 0, 0 );
	m_SurfaceCollection["Graphics/srfStart.png"] = Gfx.Load_imageAlpha( "Graphics/srfStart.png", 237, 234, 214 );
	m_SurfaceCollection["Graphics/srfButtons.png"] = Gfx.Load_imageAlpha( "Graphics/srfButtons.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfIntro.png"] = Gfx.Load_imageAlpha( "Graphics/srfIntro.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfMorphing.png"] = Gfx.Load_imageAlpha( "Graphics/srfMorphing.png", 255, 255, 241 );
	m_SurfaceCollection["Graphics/srfOutro.png"] = Gfx.Load_imageAlpha( "Graphics/srfOutro.png", 0, 0, 0 );
	m_SurfaceCollection["Graphics/srfButton.png"] = Gfx.Load_imageAlpha( "Graphics/srfButton.png", 0, 0, 0 );
	m_SurfaceCollection["Graphics/srfHealth.png"] = Gfx.Load_imageAlpha( "Graphics/srfHealth.png", 0, 0, 0 );
	m_SurfaceCollection["Graphics/srfLaser.png"] = Gfx.Load_imageAlpha( "Graphics/srfLaser.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfCredits.png"] = Gfx.Load_imageAlpha( "Graphics/srfCredits.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfOptions.png"] = Gfx.Load_imageAlpha( "Graphics/srfOptions.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfLoad.png"] = Gfx.Load_imageAlpha( "Graphics/srfLoad.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfSave.png"] = Gfx.Load_imageAlpha( "Graphics/srfSave.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfCube.png"] = Gfx.Load_imageAlpha( "Graphics/srfCube.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfTriangle.png"] = Gfx.Load_imageAlpha( "Graphics/srfTriangle.png", 255, 255, 255 );
	
	for (const auto &p : m_SurfaceCollection)
		std::cout << p.first << " => " << p.second << '\n';
*/

	MainMenuScreen = new MainMenu( 290,  m_srfStart, m_srfButtons );
	CreditsScreen = new Credits( 290,  m_srfCredits, m_srfButtons );
	OptionsScreen = new Options( 290, m_srfOptions, m_srfButtons );
	LoadsScreen = new Load( 290, m_srfLoad, m_srfButtons );
	SavesScreen = new Save( 290, m_srfSave, m_srfButtons );
	GameOverScreen = new GameOver( 290,  m_srfStart, m_srfButtons );

	setUpParallaxLayers();
}

void Gamestate::ResetEnemies()
{
	if(EnemyController.Enemies.size() != NULL )
	{
		EnemyController.Enemies.clear();
	}
}

// ----------------------------------------------------------------------------
// Update() - Updates the whole game depending on which state it is in
// ----------------------------------------------------------------------------
void Game::Update( SDL_Event input, int iElapsedTime )
{
	//Asteroid SnowAsteroid(0,0,0);
	// calling base class function instead of derived class
	//SnowAsteroid.Asteroid::isActive();
	//ObjectController.Report(SnowAsteroid);

	//std::vector<Bullet> test;

	//ObjectController.RemoveActiveObjects();
	//test = BulletController.GetVBulletsByReference();
	
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
				LevelProgress += iElapsedTime / 150;
				Gfx.DrawParallaxLayers();
				Gfx.DrawObjects();
				
				
				CollisionController.ObjectCollider( BulletController.BulletArrayRef, AnimalController.AnimalArrayRef );
				CollisionController.ObjectCollider( BulletController.BulletArrayRef, CubeController.CubeArrayRef );
				CollisionController.ObjectCollider( BulletController.BulletArrayRef, TriangleController.TriangleArrayRef );
				
				CollisionController.SpaceshipCollider(Spaceship,AnimalController.AnimalArrayRef );
				CollisionController.SpaceshipCollider(Spaceship,CubeController.CubeArrayRef );
				CollisionController.SpaceshipCollider(Spaceship,TriangleController.TriangleArrayRef );

                CollisionController.SpaceshipCollider(Spaceship, PowerupController.PowerupArrayRef);
				
				SDL_Surface * SrfProgress;
				SrfProgress = TTF_RenderText_Solid( Gfx.DefaultFont, std::to_string(LevelProgress).c_str(), Gfx.WhiteRGB );
				Gfx.apply_surface( 700, 560, SrfProgress, Gfx.BackBuffer );

				Gfx.DrawScore(600,560,UpdateScore());

				if(LevelProgress < 50000)
				{
					Gfx.srfText = TTF_RenderText_Blended(Gfx.DefaultFont,"You have just escaped from the clutches of the evil empire of 'Are you square or round'. Good luck!",Gfx.WhiteRGB);//TTF_RenderText_Shaded( Gfx.DefaultFont, " YOU DIED STOP PLAYING GOD DAMN YOU!!!!! ", Gfx.WhiteRGB, Gfx.BlackRGB );
					Gfx.apply_surface( Gfx.BackBuffer->w /4, Gfx.BackBuffer->h/2, Gfx.srfText, Gfx.BackBuffer );
				}

				// rising text for score
				static int raise = -1;

				if(!PopupScore.empty())
				{
					if( raise < 0 )
					{
						raise = PopupScore.back();
						PopupScore.pop_back();
					}
				}
				
				if(raise < 0)
				{
					Gfx.srfText = TTF_RenderText_Blended(Gfx.DefaultFont,std::to_string(raise).c_str(),Gfx.WhiteRGB);
					Gfx.apply_surface( Gfx.BackBuffer->w / 2, Gfx.BackBuffer->h / 2 -50, Gfx.srfText, Gfx.BackBuffer );
				}
				else
				{
					Gfx.srfText = TTF_RenderText_Blended(Gfx.DefaultFont,std::to_string(raise).c_str(),Gfx.WhiteRGB);
					Gfx.apply_surface( Gfx.BackBuffer->w / 2, Gfx.BackBuffer->h / 2 + raise, Gfx.srfText, Gfx.BackBuffer );
					raise--;
				}
                Gfx.DrawSprite();
				Gfx.FLIP();
			} break;
		case GAME_BOSS_STATE:
			{
				//Gfx.DrawScore(300,0,UpdateScore());
			} break;
		case GAME_OUTRO_STATE:
			{
				gamestate.PlayOutro();
			} break;
		case GAME_PLAYER_DIED_STATE:
			{
				Spaceship._Lives--;
				if(Spaceship._Lives>0)
				{
					gamestate.Reset();
					gamestate.GameState.pop();
					gamestate.GameState.push(GAME_RUNNING_STATE);
				}
				else
				{
					gamestate.RestartGame();
					gamestate.GameState.pop();
					gamestate.GameState.push(MENU_MAIN_STATE);
				}
			} break;
	}
	if( _SCORE > 10000 ) 
		_SCORE = 0;
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
	return;
}

// ----------------------------------------------------------------------------
// MainScreen() - Draws the mainscreen, checks conditions. MenuScreen
// ----------------------------------------------------------------------------
void Gamestate::MainScreen(int iElapsedTime)
{	
	SDL_BlitSurface( &Gfx.m_SurfaceCollection["assets/gfx/backdrops/srfStart.png"], &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect );

    static int i;
    if ( i > 255 )
    i = 0;
    else
    i++;
    SDL_Surface *surface;

    surface = SDL_LoadBMP("assets/gfx/backdrops/black.bmp");
        SDL_SetAlpha(surface, SDL_RLEACCEL | SDL_SRCALPHA, i);
        SDL_BlitSurface(surface, NULL, Gfx.BackBuffer, NULL);
    //*Gfx.FLIP();
    SDL_FreeSurface(surface);

	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "MainScreena @ ";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.WhiteRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	SDL_FreeSurface(srfElapsedTime);
}

// ----------------------------------------------------------------------------
// LoadScreen() - Draws the credit screen
// ----------------------------------------------------------------------------
void Gamestate::LoadScreen(int iElapsedTime)
{
    SDL_BlitSurface(Gfx.GetSurface(LoadsScreen->surface), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect);

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
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.BlackRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	if( LoadsScreen->ButtonNewgame == true )
	{
		gamestate.GameState.pop();
		gamestate.GameState.push(GAME_RUNNING_STATE);
		LoadsScreen->ButtonNewgame = false;
	}
	SDL_FreeSurface(srfElapsedTime);
}

// ----------------------------------------------------------------------------
// SaveScreen() - Draws the save screen
// ----------------------------------------------------------------------------
void Gamestate::SaveScreen(int iElapsedTime)
{
	SDL_BlitSurface( Gfx.GetSurface( SavesScreen->surface ), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect );

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
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.BlackRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	if( SavesScreen->ButtonNewgame == true )
	{
		gamestate.GameState.pop();
		gamestate.GameState.push(GAME_RUNNING_STATE);
		SavesScreen->ButtonNewgame = false;
	}
    SDL_FreeSurface(srfElapsedTime);
}

// ----------------------------------------------------------------------------
// CreditScreen() - Draws the credit screen
// ----------------------------------------------------------------------------
void Gamestate::CreditScreen(int iElapsedTime)
{
	SDL_BlitSurface( Gfx.GetSurface( CreditsScreen->surface ), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect );
	
	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "CreditsScreen @";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.BlackRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	SDL_FreeSurface(srfElapsedTime);
}
// ----------------------------------------------------------------------------
// OptionScreen() - Draws the option screen
// ----------------------------------------------------------------------------
void Gamestate::OptionScreen(int iElapsedTime)
{
	SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0,0,0,0));


	SDL_BlitSurface( Gfx.GetSurface( OptionsScreen->surface ),&SDL_GetVideoSurface()->clip_rect,Gfx.BackBuffer,&SDL_GetVideoSurface()->clip_rect);
	
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
		Audio.PlayMusic(rand()%3);
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
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.BlackRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	SDL_FreeSurface(srfElapsedTime);
}

// ----------------------------------------------------------------------------
// MainScreen() - Draws the mainscreen, checks conditions. MenuScreen
// ----------------------------------------------------------------------------
void Gamestate::GameoverScreen(int iElapsedTime)
{
	SDL_BlitSurface( Gfx.GetSurface( MainMenuScreen->surface ), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect );

	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "Gameover @ ";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.WhiteRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	SDL_FreeSurface(srfElapsedTime);
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
	Spaceship.Reset();
	AnimalController.Destroy();
	CubeController.CubeArrayRef.clear();
	TriangleController.TriangleArrayRef.clear();
	_SCORE = 0;
	Spaceship._Lives = 3;
}
void Gamestate::Reset()
{
	Spaceship.Reset();
	AnimalController.Destroy();
	CubeController.CubeArrayRef.clear();
	TriangleController.TriangleArrayRef.clear();
	_SCORE = 0;
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
	if( gamestate.ParallaxBG != NULL )
	{
		delete ParallaxBG;
	}
	if( gamestate.GameOverScreen != NULL )
	{
		delete GameOverScreen;
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
	screen = 0;
    Uint32 flags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	//set up the screen
	screen = SDL_SetVideoMode(ScreenSize.w, ScreenSize.h, 32, flags);
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

int Game::UpdateScore(int score)
{
    if ( score == 0 )
        return _SCORE++;
    else
        return _SCORE += score;
}

void Gamestate::CreateAll()
{
	AnimalController.CreateAnimals(_SCORE );
	//PowerupController.CreatePowerup( Spaceship.GetPosition() );
	CubeController.CreateCubes( _SCORE );
	TriangleController.CreateTriangles( _SCORE );
	EnemyController.Create_Enemies();
	ObjectController.CreateObjects();
}

// ----------------------------------------------------------------------------
// setUpParallaxLayers() - initializes parallax-struct
// ----------------------------------------------------------------------------
void Gamestate::setUpParallaxLayers()
{
	ParallaxBG = new ParallaxBackground();
	ParallaxBG->createLayers( 10 );

	ParallaxBG->setLayer( 0, 0.0f, m_srfBlack, 
						0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h, 0, 0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );

	ParallaxBG->setLayer( 1, 0.0f, m_srfBackdrop, 
						0, SDL_GetVideoSurface()->w, 400, 0, 0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );

	// must be here otherwise division by zero currently
	ParallaxBG->setLayer( 2, 0.7f, m_srfBackdrop, 
						0, 1172, 170, 0, 370, SDL_GetVideoSurface()->w, 170 ); 

	ParallaxBG->setLayer(	3, 0.5f, m_srfBackdrop, 
						0, SDL_GetVideoSurface()->w, 38, 0, 0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );

	ParallaxBG->setLayer(	4, 0.4f, m_srfBackdrop, 
						38, SDL_GetVideoSurface()->w, 87, 0, 38, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );

	ParallaxBG->setLayer(	5, 0.3f, m_srfBackdrop, 
						126, SDL_GetVideoSurface()->w, 46, 0, 126, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );

	ParallaxBG->setLayer(	6, 0.2f, m_srfBackdrop, 
						172, SDL_GetVideoSurface()->w, 21, 0, 172, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );

	ParallaxBG->setLayer(	7, 0.1f, m_srfBackdrop, 
						193, SDL_GetVideoSurface()->w, 12, 0, 193, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );

	ParallaxBG->setLayer( 8, 0.7f, m_srfBackdrop, 
						0, 5100, 535, 0, 0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );

	ParallaxBG->setLayer(	9, 0.9f, m_srfBackdrop, 
						540, 5100, 60, 0, 535, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h );
}


