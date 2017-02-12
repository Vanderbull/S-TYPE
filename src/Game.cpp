#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <functional>
#include <limits>
#include <iomanip>
using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Global/Global.h"
#include "Game.h"
#include "Objects/Objects.h"
#include "GfxController/ControlGfx.h"
#include "Audio/Audio.h"
#include "Objects/Objects.h"
#include "Enemies/Powerup.h"
#include "Enemies.h"
#include "Enemies/PurpleShip.h"
#include "Enemies/Robotnic.h"
#include "Enemies/BlueFish.h"
#include "Objects/Bullets.h"
#include "Screens/MainMenu.h"
#include "Screens/Credits.h"
#include "Screens/Load.h"
#include "Save/Save.h"
#include "Collision/Collision.h"
#include "OutroFinish.h"
#include "GetInput.h"

bool laserFired = false;

TTF_Font* font;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
SDL_Texture *texture;
SDL_Event event;

// SDL Surfaces used with images and textures
SDL_Surface *srfSpaceshipSurface;

// SDL Textures used with images
SDL_Texture* srfSpaceshipTexture;
SDL_Texture* srfBackdrop_5200x1080;
SDL_Texture* srfLaserBlueTexture;

void LoadScreen(int i);
void SaveScreen(int i);
void OptionScreen(int i);
void CreditScreen(int i);
void RunningScreen(int i);
void MainScreen(int i);

class LevelObj
{
public:
    LevelObj(){ std::cout << "Constructing a LevelObj..." << std::endl; };
    ~LevelObj(){ std:cout << "Destroying a LevelObj..." << std::endl; };
    int GetDifficulty(){ return Difficulty; };
    void SetDifficulty(int iDifficulty){ Difficulty = iDifficulty; };
    //simple number
    int id;
    int Difficulty;

    //image path
    std::string background;

    //position of balls and their color
    //array levelBalls[{position,color}]

    //position of exits and where they lead to
    //array levelExits[{position,idOfNextLevel,idOfNextLevelEntrance}]

    //position of player and facing upon level entrance
    //array levelEntrances[{id,position,rotation}]
};

class LaserBeam
{
public:
    LaserBeam(){ std::cout << "Spawning a Laserbeam..." << std::endl; x=0; y=0; Position.x = 0; Position.y = 0; Position.w = 64; Position.h = 29;};
    ~LaserBeam(){ std::cout << "Vaporizing a Laserbeam..." << std::endl; };

    void Move()
    {
        x++;
        if(x > 800)
        x=0;
        Position.x++;
        if(Position.x > 800)
        Position.x=0;
    };
    int id;
    int color;
    int x;
    int y;
    SDL_Rect Position;
};

std::vector<LaserBeam> LaserBeams;

LevelObj LevelOneObj;
LevelObj LevelTwoObj;
LevelObj LevelThreeObj;

int Progressbar(const SDL_Rect* iRect)
{
    SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
    SDL_RenderDrawRect( renderer, iRect );
    return 0;
}

void RenderVersion()
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << 1.0;
    std::string version = ss.str();
    std::string version_text = "Version: " + version;

    SDL_Color textColor = { 255, 255, 255, 0 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, version_text.c_str(), textColor);
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
    int text_width = textSurface->w;
    int text_height = textSurface->h;
    SDL_FreeSurface(textSurface);
    SDL_Rect renderQuad = { 20, 600 - 30, text_width, text_height };
    SDL_RenderCopy(renderer, text, NULL, &renderQuad);
    SDL_DestroyTexture(text);
};

void RenderText(std::string iText, int iX, int iY, int iZ = 0)
{
    SDL_Color textColor = { 255, 255, 255, 0 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, iText.c_str(), textColor);
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
    int text_width = textSurface->w;
    int text_height = textSurface->h;
    SDL_FreeSurface(textSurface);
    SDL_Rect renderQuad = { iX, iY, text_width, text_height };
    SDL_RenderCopy(renderer, text, NULL, &renderQuad);
    SDL_DestroyTexture(text);
};

void print_num(int i)
{
    std::cout << i << '\n';
}

// store a free function
std::function<void(int)> f_display = print_num;

SDL_Rect ButtonClips[10];

class MouseObject
{
public:

    MouseObject(){ std::cout << "Generating a MouseState object" << std::endl; };
    ~MouseObject(){ std::cout << "Destroying a MouseState object" << std::endl; };
    void GetState(){ SDL_GetMouseState(&XCoordinates,&YCoordinates); };

    int XCoordinates;
    int YCoordinates;

};

// Initializing SDL Font for usage in the game
bool SetupTTF( const std::string &fontName, int fontSize)
{
    // SDL2_TTF needs to be initialized just like SDL2
    if ( TTF_Init() == -1 )
    {
        std::cout << " Failed to initialize TTF : " << SDL_GetError() << std::endl;
        return false;
    }

    // Load our fonts, with a huge size
    font = TTF_OpenFont( fontName.c_str(), fontSize );

    // Error check
    if ( font == nullptr )
    {
        std::cout << " Failed to load font : " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

Game Engine;
Gamestate EngineState;
MouseObject ObjMouse;

Game::Game()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
    }

    if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
    }

    IMG_Init(IMG_INIT_PNG);

    srfSpaceshipTexture = IMG_LoadTexture(renderer, "./assets/gfx/spaceship/srfSpaceship.png");
    srfBackdrop_5200x1080 = IMG_LoadTexture(renderer, "./assets/gfx/backdrops/srfBackdrop_5200x1080.png");
    srfLaserBlueTexture = IMG_LoadTexture(renderer, "./assets/gfx/lasers/srfLaserBlue.png");

    SetupTTF( "./assets/fonts/Mecha.ttf", 24 );

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );
    RenderText("Loading explosions...",0,0,0);
    SDL_RenderPresent(renderer);
    LoadFiles("./assets/gfx/animations/explosion/");
    SDL_RenderClear( renderer );
    RenderText("Loading cubes...",0,0,0);
    SDL_RenderPresent(renderer);
    LoadFiles("./assets/gfx/animations/cube/");
    SDL_RenderClear( renderer );
    RenderText("Loading fireballs...",0,0,0);
    SDL_RenderPresent(renderer);
    LoadFiles("./assets/gfx/animations/fireball/");
    SDL_RenderClear( renderer );
    RenderText("Loading levels...",0,0,0);
    SDL_RenderPresent(renderer);
    LoadFiles("./assets/gfx/backdrops/levels/");
    SDL_RenderClear( renderer );
    RenderText("Loading bosses...",0,0,0);
    SDL_RenderPresent(renderer);
    LoadFiles("./assets/gfx/bosses/");
    SDL_RenderClear( renderer );
    RenderText("Loading enemies...",0,0,0);
    SDL_RenderPresent(renderer);
    LoadFiles("./assets/gfx/enemies/");

    LevelOneObj.SetDifficulty(0);
    LevelTwoObj.SetDifficulty(0);
    LevelThreeObj.SetDifficulty(0);

    f_display = MainScreen;
    std::cout << "Game object created..." << std::endl;

    SPAWN_POSITION_X = 0;
    SPAWN_POSITION_Y = 1080 / 2;
    Quit = false;

    LoadFiles("./assets/gfx/gui/");
    LoadFiles("./assets/gfx/lasers/");
    LoadFiles("./assets/gfx/logos/");
    LoadFiles("./assets/gfx/powerups/");
    LoadFiles("./assets/gfx/spaceship/");

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );

    SDL_SetRenderDrawColor( renderer, 255, 255, 0, 255 );
    SDL_RenderDrawRect( renderer, &Ship.Position );

    SDL_RenderPresent(renderer);

    //SDL_Surface* srfSpaceshipSurface = IMG_Load( "./assets/gfx/spaceship/srfSpaceship.png" );

    //surface = SDL_LoadBMP("./assets/gfx/backdrops/800_600/srfStart_800x600.bmp");
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
    }

    LaserBeam ABeam;
    LaserBeams.push_back(ABeam);
     vector<LaserBeam>::iterator it;

    while (1)
    {

        SDL_PollEvent(&event);
        HandleEvents( event );

        // Render background color for screen
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
        SDL_RenderClear( renderer );

        //SDL_RenderCopy(renderer, srfBackdrop_14978x1080, NULL, NULL);

        f_display(0);

        RenderText(std::to_string(Ship.Position.x),500,0,0);
        SDL_SetRenderDrawColor( renderer, 255, 255, 0, 255 );
        SDL_RenderDrawRect( renderer, &Ship.Position );


        for (it = LaserBeams.begin(); it != LaserBeams.end(); ++it) {
            SDL_RenderCopy(renderer, srfLaserBlueTexture, NULL, &it->Position);
            cout << it->x;
            it->Move();
        }
        for(auto const& aBeam: LaserBeams)
        {
        }

        SDL_RenderPresent(renderer);
        //SDL_Delay(100);
    }

    SDL_FreeSurface(surface);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}


// Utility function for mouse trigger
int Game::MouseButtonTrigger(SDL_Rect TriggerArea)
{
    int XCoordinates, YCoordinates;
    SDL_GetMouseState(&XCoordinates, &YCoordinates);

    if (XCoordinates > TriggerArea.x &&
        XCoordinates < TriggerArea.x + TriggerArea.w &&
        YCoordinates > TriggerArea.y &&
        YCoordinates < TriggerArea.y + TriggerArea.h)
        return 1;
    else
        return 0;
}

void Game::HandleEvents( SDL_Event _event )
{
    std::cout << "Handling events..." << std::endl;
	switch ( _event.type )
	{
        case SDL_MOUSEBUTTONDOWN:
        {
        } break;
        case SDL_MOUSEBUTTONUP:
        {
        } break;
        case SDL_KEYDOWN:
        {
            if(_event.key.keysym.sym==SDLK_LEFT)
            {
                std::cout << "SDL_KEYDOWN: SDLK_LEFT" << std::endl;
                if( Ship.Position.x > 0)
                {
                    Ship.Position.x--;
                }
            }
            if(_event.key.keysym.sym==SDLK_RIGHT)
            {
                std::cout << "SDL_KEYDOWN: SDLK_RIGHT" << std::endl;
                if( Ship.Position.x < 700)
                {
                    Ship.Position.x++;
                }
            }
            if(_event.key.keysym.sym==SDLK_UP)
            {
                std::cout << "SDL_KEYDOWN: SDLK_UP" << std::endl;
                if( Ship.Position.y > 0)
                {
                    Ship.Position.y--;
                }
            }
            if(_event.key.keysym.sym==SDLK_DOWN)
            {
                std::cout << "SDL_KEYDOWN: SDLK_DOWN" << std::endl;
                if( Ship.Position.y < 500)
                {
                    Ship.Position.y++;
                }
            }
            if(_event.key.keysym.sym==SDLK_ESCAPE)
            {
                std::cout << "SDL_KEYDOWN: SDLK_DOWN" << std::endl;
                f_display = MainScreen;
            }
            if(_event.key.keysym.sym==SDLK_SPACE)
            {
                std::cout << "SDL_KEYDOWN: SDLK_DOWN" << std::endl;
                laserFired = true;
            }

        } break;
        case SDL_KEYUP:
        {
            if(_event.key.keysym.sym==SDLK_SPACE)
            {
                std::cout << "SDL_KEYDOWN: SDLK_DOWN" << std::endl;
                laserFired = false;
            }
        } break;
        case SDL_MOUSEMOTION:
        {
            ObjMouse.GetState();
        } break;
        case SDL_QUIT:
        {
            SDL_Quit();
        } break;
    }
/*


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

                        for (int i = 0; i < 3; i++)
                        {
                            if (MouseButtonTrigger(ButtonClips[i]))
                            {
                                cout << "Difficuty set to -> " << i << "..." << endl;
                                DIFFICULTY = i;
                                Savegame.difficulty = i;
                            }
                        }
                        for (int i = 3; i < 5; i++)
                        {
                            if (MouseButtonTrigger(ButtonClips[i]))
                            {
                                cout << "Sound set to -> " << i << "..." << endl;
                                SOUND = i;
                                Savegame.sound = i;
                            }
                        }
                        for (int i = 5; i < 7; i++)
                        {
                            if (MouseButtonTrigger(ButtonClips[i]))
                            {
                                cout << "Music set to -> " << i << "..." << endl;
                                MUSIC = i;
                                Savegame.music = i;
                            }
                        }
                        for (int i = 7; i < 8; i++)
                        {
                            if (MouseButtonTrigger(ButtonClips[i]))
                            {
                                cout << "Returning to main menu -> " << i << "..." << endl;
                                gamestate.GameState.pop();
                                gamestate.GameState.push(MENU_MAIN_STATE);
                                _event.type = 0;
                            }
                        }
                        for (int i = 0; i < 8; i++)
                        {
                            if (MouseButtonTrigger(ButtonClips[i]))
                            {
                                cout << "Entering button " << i << "..." << endl;
                            }
                        }
                } break;

                case GAME_SAVING_STATE:
                {
                        SetGameOptionButtons();
                        for (int i = 0; i < 3; i++)
                        {
                            if (MouseButtonTrigger(ButtonClips[i]))
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
                                    //MessageBox(NULL, "Do you really want to save over savegame", "Override savegame", MB_YESNO | MB_ICONWARNING);
                                }
                                else
                                {
                                    //MessageBox(NULL, "Do you really want to save over savegame", "Override savegame", MB_OK | MB_ICONERROR);
                                }
                            }
                        }
                        for (int i = 3; i < 5; i++)
                        {
                            if (MouseButtonTrigger(ButtonClips[i]))
                            {
                                cout << "Sound set to -> " << i << "..." << endl;
                                SOUND = i;
                            }
                        }
                        for (int i = 5; i < 7; i++)
                        {
                            if (MouseButtonTrigger(ButtonClips[i]))
                            {
                                cout << "Music set to -> " << i << "..." << endl;
                                MUSIC = i;
                            }
                        }
                        for (int i = 7; i < 8; i++)
                        {
                            if (MouseButtonTrigger(ButtonClips[i]))
                            {
                                cout << "Returning to main menu -> " << i << "..." << endl;
                                gamestate.GameState.pop();
                                gamestate.GameState.push(MENU_MAIN_STATE);
                                _event.type = 0;
                            }
                        }
                        for (int i = 0; i < 8; i++)
                        {
                            if (MouseButtonTrigger(ButtonClips[i]))
                            {
                                cout << "Entering button " << i << "..." << endl;
                            }
                        }
                } break;

				case GAME_OPTIONS_STATE:
				{
					SetGameOptionButtons();
					for( int i = 0; i < 3; i++ )
					{
                        if (MouseButtonTrigger(ButtonClips[i]))
						{
							cout << "Difficuty set to -> " << i << "..." << endl;
							DIFFICULTY = i;
						}
					}
					for( int i = 3; i < 5; i++ )
					{
                        if (MouseButtonTrigger(ButtonClips[i]))
						{
							cout << "Sound set to -> " << i << "..." << endl;
							SOUND = i;
						}
					}
					for( int i = 5; i < 7; i++ )
					{
                        if (MouseButtonTrigger(ButtonClips[i]))
						{
							cout << "Music set to -> " << i << "..." << endl;
							MUSIC = i;
                            Audio.ToggleMusic();
						}
					}
					for( int i = 7; i < 8; i++ )
					{
                        if (MouseButtonTrigger(ButtonClips[i]))
						{
							cout << "Returning to main menu -> " << i << "..." << endl;
							gamestate.GameState.pop();
							gamestate.GameState.push(MENU_MAIN_STATE);
							_event.type = 0;
						}
					}
					for( int i = 0; i < 8; i++ )
					{
                        if (MouseButtonTrigger(ButtonClips[i]))
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
				{SDL_RenderCopy(renderer, srfSpaceshipTexture, NULL, &Ship.Position);
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
                    GamePad.HandleInput(_event);
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
                    GamePad.HandleInput(_event);
				} break;
			}
		} break;
		case SDL_QUIT:
		{
			Quit = true;
		} break;
        default:
        {
            //cout << "Unknown event please try again.." << endl;
        }
	}

	if(gamestate.GameState.top() == MENU_MAIN_STATE)
	{
        if (Audio.IsPlaying() == 0)
        {
            Audio.PlayMusic(3);
        }
        else if (Audio.IsPaused() == 1)
        {
            Audio.ResumeMusic();
        }

		for( int i = 0; i < 8; i++ )
		{
            if (MouseButtonTrigger(gamestate.MainMenuScreen->ButtonClips[i]))
			{
				cout << "Entering button " << i << "..." << endl;
			}
		}
		if (_event.type == SDL_MOUSEBUTTONUP )
		{
			// if mouse click within boundries of one of the buttons
			for( int i = 0; i < 8; i++ )
			{
                    if (MouseButtonTrigger(gamestate.MainMenuScreen->ButtonClips[i]))
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
						//cout << "Hit button..." << i << endl;
					}
			}
		}
	}
	else
	{
		return;
	}
*/
}

Gamestate::Gamestate()
{
    std::cout << "Creating Gamestate object..." << std::endl;
	//GameState.push(MENU_MAIN_STATE);
	Parallax = 0.0f;
	DeltaTime = 0.0f;
}

SDL_Rect srcRect;
SDL_Rect destRect;


void RunningScreen(int i)
{
    if (srcRect.x > 5200)
    srcRect.x = 0;
    srcRect.x += 1;
    srcRect.y = 0;
    srcRect.w = 600;
    srcRect.h = 800;



    SDL_RenderCopy(renderer, srfBackdrop_5200x1080, &srcRect, NULL);
    SDL_Delay(10);

	stringstream ss;
	std::string RenderedText;

    ss << i;
	RenderedText = "RunningScreen @ ";
	RenderedText.append(ss.str());

	RenderText(RenderedText,0,0);

    ss.clear();
    RenderedText = "";
    ss << i;
	RenderedText = "Score: ";
	RenderedText.append(ss.str());

	RenderText(RenderedText,0,500);

	ss.clear();
	RenderedText = "";
    ss << i;
	RenderedText = "Power: ";
	RenderedText.append(ss.str());

	RenderText(RenderedText,200,500);

	SDL_RenderCopy(renderer, srfSpaceshipTexture, NULL, &Engine.Ship.Position);

	if(laserFired)
	{
        SDL_RenderCopy(renderer, srfLaserBlueTexture, NULL, NULL);
    }

	//SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void MainScreen(int i)
{
	stringstream ss;
    ss << i;
	string str = "MainScreen @ ";
	str.append(ss.str());

	RenderText(str,0,0);

	SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_Rect r[10];

        r[0].x = 400;
        r[0].y = 137;
        r[0].w = 350;
        r[0].h = 30;

        r[1].x = 400;
        r[1].y = 193;
        r[1].w = 350;
        r[1].h = 30;

        r[2].x = 400;
        r[2].y = 249;
        r[2].w = 350;
        r[2].h = 30;

        r[3].x = 400;
        r[3].y = 305;
        r[3].w = 350;
        r[3].h = 30;

        r[4].x = 400;
        r[4].y = 362;
        r[4].w = 350;
        r[4].h = 30;

        r[5].x = 400;
        r[5].y = 471;
        r[5].w = 350;
        r[5].h = 30;

        r[6].x = 400;
        r[6].y = 527;
        r[6].w = 350;
        r[6].h = 30;

        r[7].x = 400;
        r[7].y = 527;
        r[7].w = 350;
        r[7].h = 30;

        r[8].x = 400;
        r[8].y = 527;
        r[8].w = 350;
        r[8].h = 30;

        r[9].x = 400;
        r[9].y = 527;
        r[9].w = 350;
        r[9].h = 30;

        for(int i = 0; i < 10; i++)
        {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            // Render our SDL_Rect
            // The top left pos of the rect will be at 50, 50
            // It will stretch 50 to the left and 50 towards the bottom
            SDL_RenderDrawRect( renderer, &r[i] );
        }

        for(int i = 0; i < 10; i++)
        {
            if((ObjMouse.XCoordinates > r[i].x) && (ObjMouse.XCoordinates < r[i].x + r[i].w))
            {
                // Resume game button
                if((ObjMouse.YCoordinates > r[0].y) && (ObjMouse.YCoordinates < r[0].y + r[0].h))
                {
                    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                    {
                        SDL_Log("Pressed the resume game button in main menu");
                        SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
                        SDL_RenderDrawRect( renderer, &r[0] );
                    }

                }

                // New game button
                if((ObjMouse.YCoordinates > r[1].y) && (ObjMouse.YCoordinates < r[1].y + r[1].h))
                {
                    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                    {
                        SDL_Log("Pressed the new game button in main menu");
                        SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
                        SDL_RenderDrawRect( renderer, &r[1] );
                        f_display = RunningScreen;
                    }
                }

                // Load game button
                if((ObjMouse.YCoordinates > r[2].y) && (ObjMouse.YCoordinates < r[2].y + r[2].h))
                {
                    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                    {
                        SDL_Log("Pressed the Load game button in main menu");
                        SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
                        SDL_RenderDrawRect( renderer, &r[2] );
                        f_display = LoadScreen;
                    }
                }

                // Save game button
                if((ObjMouse.YCoordinates > r[3].y) && (ObjMouse.YCoordinates < r[3].y + r[3].h))
                {
                    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                    {
                        SDL_Log("Pressed the save game button in main menu");
                        SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
                        SDL_RenderDrawRect( renderer, &r[3] );
                        f_display = SaveScreen;
                    }
                }

                // Options button
                if((ObjMouse.YCoordinates > r[4].y) && (ObjMouse.YCoordinates < r[4].y + r[4].h))
                {
                    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                    {
                        SDL_Log("Pressed the options button in main menu");
                        SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
                        SDL_RenderDrawRect( renderer, &r[4] );
                        f_display = OptionScreen;
                    }
                }

                // Credits button
                if((ObjMouse.YCoordinates > r[5].y) && (ObjMouse.YCoordinates < r[5].y + r[5].h))
                {
                    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                    {
                        SDL_Log("Pressed Credits button in main menu");
                        SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
                        SDL_RenderDrawRect( renderer, &r[5] );
                        f_display = CreditScreen;
                    }
                }

                // quit game button
                if((ObjMouse.YCoordinates > r[7].y) && (ObjMouse.YCoordinates < r[7].y + r[7].h))
                {
                    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                    {
                        SDL_Log("Pressed the quit button in main menu");
                        SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
                        SDL_RenderDrawRect( renderer, &r[7] );
                        SDL_Quit();
                    }
                }
            }
        }

        str = "RESUME GAME";
        RenderText(str,r[0].x+r[0].w / 3,r[0].y);
        str = "NEW GAME";
        RenderText(str,r[1].x+r[1].w / 3,r[1].y);
        str = "LOAD GAME";
        RenderText(str,r[2].x+r[2].w / 3,r[2].y);
        str = "SAVE GAME";
        RenderText(str,r[3].x+r[3].w / 3,r[3].y);
        str = "OPTIONS";
        RenderText(str,r[4].x+r[4].w / 3,r[4].y);
        str = "CREDITS";
        RenderText(str,r[5].x+r[5].w / 3,r[5].y);

        str = "QUIT";
        RenderText(str,r[7].x+r[6].w / 3,r[7].y);

}

void LoadScreen(int i)
{
	stringstream ss;
    ss << i;
	string str = "LoadScreen @";
	str.append(ss.str());
	//std::cout << str.c_str() << std::endl;

	RenderText(str,0,0);

    // easy option
    ButtonClips[0].h = 33;
    ButtonClips[0].w = 101;
    ButtonClips[0].x = 284;
    ButtonClips[0].y = 128;

    //medium option
    ButtonClips[1].h = 33;
    ButtonClips[1].w = 101;
    ButtonClips[1].x = 414;
    ButtonClips[1].y = 128;

    //hard option
    ButtonClips[2].h = 33;
    ButtonClips[2].w = 101;
    ButtonClips[2].x = 554;
    ButtonClips[2].y = 128;

    // sound on
    ButtonClips[3].h = 33;
    ButtonClips[3].w = 101;
    ButtonClips[3].x = 284;
    ButtonClips[3].y = 168;

    // sound off
    ButtonClips[4].h = 33;
    ButtonClips[4].w = 101;
    ButtonClips[4].x = 414;
    ButtonClips[4].y = 168;

    // music on
    ButtonClips[5].h = 33;
    ButtonClips[5].w = 101;
    ButtonClips[5].x = 284;
    ButtonClips[5].y = 218;

    // music off
    ButtonClips[6].h = 33;
    ButtonClips[6].w = 101;
    ButtonClips[6].x = 414;
    ButtonClips[6].y = 218;

    // back to main menu
    ButtonClips[7].h = 33;
    ButtonClips[7].w = 101;
    ButtonClips[7].x = 632;
    ButtonClips[7].y = 534;

    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

    SDL_RenderDrawRect( renderer, &ButtonClips[0] );
    SDL_RenderDrawRect( renderer, &ButtonClips[1] );
    SDL_RenderDrawRect( renderer, &ButtonClips[2] );
    SDL_RenderDrawRect( renderer, &ButtonClips[3] );
    SDL_RenderDrawRect( renderer, &ButtonClips[4] );
    SDL_RenderDrawRect( renderer, &ButtonClips[5] );
    SDL_RenderDrawRect( renderer, &ButtonClips[6] );
    SDL_RenderDrawRect( renderer, &ButtonClips[7] );

    RenderText("SAVE 0",ButtonClips[0].x,ButtonClips[0].y);
    RenderText("SAVE 1",ButtonClips[1].x,ButtonClips[1].y);
    RenderText("SAVE 2",ButtonClips[2].x,ButtonClips[2].y);
    RenderText("SAVE 3",ButtonClips[3].x,ButtonClips[3].y);
    RenderText("SAVE 4",ButtonClips[4].x,ButtonClips[4].y);
    RenderText("SAVE 5",ButtonClips[5].x,ButtonClips[5].y);
    RenderText("SAVE 6",ButtonClips[6].x,ButtonClips[6].y);
    RenderText("SAVE 7",ButtonClips[7].x,ButtonClips[7].y);

    if((ObjMouse.YCoordinates > ButtonClips[0].y) && (ObjMouse.YCoordinates < ButtonClips[0].y + ButtonClips[0].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[0].x) && (ObjMouse.XCoordinates < ButtonClips[0].x + ButtonClips[0].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                SDL_Log("Pressed buttonClips(0)");
                SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
                SDL_RenderFillRect( renderer, &ButtonClips[0] );
                int screenWidth;
                int screenHeight;
                SDL_GetWindowSize(window,&screenWidth,&screenHeight);
                RenderText("LOADING... @ 0", screenWidth - 200 , 0);
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[1].y) && (ObjMouse.YCoordinates < ButtonClips[1].y + ButtonClips[1].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[1].x) && (ObjMouse.XCoordinates < ButtonClips[1].x + ButtonClips[1].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[1] );
            int screenWidth;
            int screenHeight;
            SDL_GetWindowSize(window,&screenWidth,&screenHeight);
            RenderText("LOADING... @ 1", screenWidth - 200 , 0);
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[2].y) && (ObjMouse.YCoordinates < ButtonClips[2].y + ButtonClips[2].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[2].x) && (ObjMouse.XCoordinates < ButtonClips[2].x + ButtonClips[2].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[2] );
            int screenWidth;
            int screenHeight;
            SDL_GetWindowSize(window,&screenWidth,&screenHeight);
            RenderText("LOADING... @ 2", screenWidth - 200 , 0);
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[3].y) && (ObjMouse.YCoordinates < ButtonClips[3].y + ButtonClips[3].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[3].x) && (ObjMouse.XCoordinates < ButtonClips[3].x + ButtonClips[3].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[3] );
            int screenWidth;
            int screenHeight;
            SDL_GetWindowSize(window,&screenWidth,&screenHeight);
            RenderText("LOADING... @ 3", screenWidth - 200 , 0);
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[4].y) && (ObjMouse.YCoordinates < ButtonClips[4].y + ButtonClips[4].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[4].x) && (ObjMouse.XCoordinates < ButtonClips[4].x + ButtonClips[4].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[4] );
            int screenWidth;
            int screenHeight;
            SDL_GetWindowSize(window,&screenWidth,&screenHeight);
            RenderText("LOADING... @ 4", screenWidth - 200 , 0);
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[5].y) && (ObjMouse.YCoordinates < ButtonClips[5].y + ButtonClips[5].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[5].x) && (ObjMouse.XCoordinates < ButtonClips[5].x + ButtonClips[5].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[5] );
            int screenWidth;
            int screenHeight;
            SDL_GetWindowSize(window,&screenWidth,&screenHeight);
            RenderText("LOADING... @ 5", screenWidth - 200 , 0);
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[6].y) && (ObjMouse.YCoordinates < ButtonClips[6].y + ButtonClips[6].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[6].x) && (ObjMouse.XCoordinates < ButtonClips[6].x + ButtonClips[6].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[6] );
            int screenWidth;
            int screenHeight;
            SDL_GetWindowSize(window,&screenWidth,&screenHeight);
            RenderText("LOADING... @ 6", screenWidth - 200 , 0);
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[7].y) && (ObjMouse.YCoordinates < ButtonClips[7].y + ButtonClips[7].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[7].x) && (ObjMouse.XCoordinates < ButtonClips[7].x + ButtonClips[7].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[7] );
            int screenWidth;
            int screenHeight;
            SDL_GetWindowSize(window,&screenWidth,&screenHeight);
            RenderText("LOADING... @ 7", screenWidth - 200 , 0);
            f_display = MainScreen;
            }
        }
    }

    RenderVersion();
}

void SaveScreen(int i)
{
	stringstream ss;
    ss << i;
	string str = "SaveScreen @";
	str.append(ss.str());
	//std::cout << str.c_str() << std::endl;

	RenderText(str,0,0);

    // easy option
    ButtonClips[0].h = 33;
    ButtonClips[0].w = 101;
    ButtonClips[0].x = 284;
    ButtonClips[0].y = 128;

    //medium option
    ButtonClips[1].h = 33;
    ButtonClips[1].w = 101;
    ButtonClips[1].x = 414;
    ButtonClips[1].y = 128;

    //hard option
    ButtonClips[2].h = 33;
    ButtonClips[2].w = 101;
    ButtonClips[2].x = 554;
    ButtonClips[2].y = 128;

    // sound on
    ButtonClips[3].h = 33;
    ButtonClips[3].w = 101;
    ButtonClips[3].x = 284;
    ButtonClips[3].y = 168;

    // sound off
    ButtonClips[4].h = 33;
    ButtonClips[4].w = 101;
    ButtonClips[4].x = 414;
    ButtonClips[4].y = 168;

    // music on
    ButtonClips[5].h = 33;
    ButtonClips[5].w = 101;
    ButtonClips[5].x = 284;
    ButtonClips[5].y = 218;

    // music off
    ButtonClips[6].h = 33;
    ButtonClips[6].w = 101;
    ButtonClips[6].x = 414;
    ButtonClips[6].y = 218;

    // back to main menu
    ButtonClips[7].h = 33;
    ButtonClips[7].w = 101;
    ButtonClips[7].x = 632;
    ButtonClips[7].y = 534;

    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

    SDL_RenderDrawRect( renderer, &ButtonClips[0] );
    SDL_RenderDrawRect( renderer, &ButtonClips[1] );
    SDL_RenderDrawRect( renderer, &ButtonClips[2] );
    SDL_RenderDrawRect( renderer, &ButtonClips[3] );
    SDL_RenderDrawRect( renderer, &ButtonClips[4] );
    SDL_RenderDrawRect( renderer, &ButtonClips[5] );
    SDL_RenderDrawRect( renderer, &ButtonClips[6] );
    SDL_RenderDrawRect( renderer, &ButtonClips[7] );


    RenderText("SAVE 0",ButtonClips[0].x,ButtonClips[0].y);
    RenderText("SAVE 1",ButtonClips[1].x,ButtonClips[1].y);
    RenderText("SAVE 2",ButtonClips[2].x,ButtonClips[2].y);
    RenderText("SAVE 3",ButtonClips[3].x,ButtonClips[3].y);
    RenderText("SAVE 4",ButtonClips[4].x,ButtonClips[4].y);
    RenderText("SAVE 5",ButtonClips[5].x,ButtonClips[5].y);
    RenderText("SAVE 6",ButtonClips[6].x,ButtonClips[6].y);
    RenderText("SAVE 7",ButtonClips[7].x,ButtonClips[7].y);

    if((ObjMouse.YCoordinates > ButtonClips[0].y) && (ObjMouse.YCoordinates < ButtonClips[0].y + ButtonClips[0].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[0].x) && (ObjMouse.XCoordinates < ButtonClips[0].x + ButtonClips[0].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[0] );
            int screenWidth;
            int screenHeight;
            SDL_GetWindowSize(window,&screenWidth,&screenHeight);
            RenderText("SAVING... @ 0", screenWidth - 200 , 0);

            ofstream saveFile;
            saveFile.open ("./assets/save/save0.txt");
            saveFile << "Version" << std::endl;
            saveFile << "Difficulty" << std::endl;
            saveFile << "Music" << std::endl;
            saveFile << "Sound" << std::endl;
            saveFile.close();
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[1].y) && (ObjMouse.YCoordinates < ButtonClips[1].y + ButtonClips[1].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[1].x) && (ObjMouse.XCoordinates < ButtonClips[1].x + ButtonClips[1].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[1] );
            int screenWidth;
            int screenHeight;
            SDL_GetWindowSize(window,&screenWidth,&screenHeight);
            RenderText("SAVING... @ 1", screenWidth - 200 , 0);

            ofstream saveFile;
            saveFile.open ("./assets/save/save1.txt");
            saveFile << "Version" << std::endl;
            saveFile << "Difficulty" << std::endl;
            saveFile << "Music" << std::endl;
            saveFile << "Sound" << std::endl;
            saveFile.close();
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[2].y) && (ObjMouse.YCoordinates < ButtonClips[2].y + ButtonClips[2].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[2].x) && (ObjMouse.XCoordinates < ButtonClips[2].x + ButtonClips[2].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[2] );
            int screenWidth;
            int screenHeight;
            SDL_GetWindowSize(window,&screenWidth,&screenHeight);
            RenderText("SAVING... @ 2", screenWidth - 200 , 0);

            ofstream saveFile;
            saveFile.open ("./assets/save/save2.txt");
            saveFile << "Version" << std::endl;
            saveFile << "Difficulty" << std::endl;
            saveFile << "Music" << std::endl;
            saveFile << "Sound" << std::endl;
            saveFile.close();
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[3].y) && (ObjMouse.YCoordinates < ButtonClips[3].y + ButtonClips[3].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[3].x) && (ObjMouse.XCoordinates < ButtonClips[3].x + ButtonClips[3].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[3] );
            int screenWidth;
            int screenHeight;
            SDL_GetWindowSize(window,&screenWidth,&screenHeight);
            RenderText("SAVING... @ 3", screenWidth - 200 , 0);

            ofstream saveFile;
            saveFile.open ("./assets/save/save3.txt");
            saveFile << "Version" << std::endl;
            saveFile << "Difficulty" << std::endl;
            saveFile << "Music" << std::endl;
            saveFile << "Sound" << std::endl;
            saveFile.close();
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[4].y) && (ObjMouse.YCoordinates < ButtonClips[4].y + ButtonClips[4].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[4].x) && (ObjMouse.XCoordinates < ButtonClips[4].x + ButtonClips[4].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[4] );
            int screenWidth;
            int screenHeight;
            SDL_GetWindowSize(window,&screenWidth,&screenHeight);
            RenderText("SAVING... @ 4", screenWidth - 200 , 0);

            ofstream saveFile;
            saveFile.open ("./assets/save/save4.txt");
            saveFile << "Version" << std::endl;
            saveFile << "Difficulty" << std::endl;
            saveFile << "Music" << std::endl;
            saveFile << "Sound" << std::endl;
            saveFile.close();
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[5].y) && (ObjMouse.YCoordinates < ButtonClips[5].y + ButtonClips[5].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[5].x) && (ObjMouse.XCoordinates < ButtonClips[5].x + ButtonClips[5].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[5] );
            int screenWidth;
            int screenHeight;
            SDL_GetWindowSize(window,&screenWidth,&screenHeight);
            RenderText("SAVING... @ 5", screenWidth - 200 , 0);

            ofstream saveFile;
            saveFile.open ("./assets/save/save5.txt");
            saveFile << "Version" << std::endl;
            saveFile << "Difficulty" << std::endl;
            saveFile << "Music" << std::endl;
            saveFile << "Sound" << std::endl;
            saveFile.close();
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[6].y) && (ObjMouse.YCoordinates < ButtonClips[6].y + ButtonClips[6].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[6].x) && (ObjMouse.XCoordinates < ButtonClips[6].x + ButtonClips[6].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[6] );
            int screenWidth;
            int screenHeight;
            SDL_GetWindowSize(window,&screenWidth,&screenHeight);
            RenderText("SAVING... @ 6", screenWidth - 200 , 0);

            ofstream saveFile;
            saveFile.open ("./assets/save/save6.txt");
            saveFile << "Version" << std::endl;
            saveFile << "Difficulty" << std::endl;
            saveFile << "Music" << std::endl;
            saveFile << "Sound" << std::endl;
            saveFile.close();
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[7].y) && (ObjMouse.YCoordinates < ButtonClips[7].y + ButtonClips[7].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[7].x) && (ObjMouse.XCoordinates < ButtonClips[7].x + ButtonClips[7].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[7] );
            int screenWidth;
            int screenHeight;
            SDL_GetWindowSize(window,&screenWidth,&screenHeight);
            RenderText("SAVING... @ 7", screenWidth - 200 , 0);
            f_display = MainScreen;
            }
        }
    }

    RenderVersion();
}

void CreditScreen(int i)
{
	stringstream ss;
    ss << i;
	string str = "CreditScreen @";
	str.append(ss.str());

	RenderText(str,0,0);

    SDL_Rect r[10];

    r[0].x = 0;
    r[0].y = 0;
    r[0].w = 200;
    r[0].h = 200;

    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_RenderDrawRect( renderer, &r[0] );

    if((ObjMouse.YCoordinates > r[0].y) && (ObjMouse.YCoordinates < r[0].y + r[0].h))
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
        SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
        SDL_RenderDrawRect( renderer, &r[0] );
        f_display = MainScreen;
        }
    }

    RenderVersion();
}

void Gameover(int i)
{
	stringstream ss;
    ss << i;
	string str = "Gameover @";
	str.append(ss.str());
	//std::cout << str.c_str() << std::endl;

	RenderText(str,0,0);

    SDL_Rect r[10];

    r[0].x = 0;
    r[0].y = 0;
    r[0].w = 200;
    r[0].h = 200;

    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_RenderDrawRect( renderer, &r[0] );

    if((ObjMouse.XCoordinates > ButtonClips[0].x) && (ObjMouse.XCoordinates < ButtonClips[0].x + ButtonClips[0].w))
    {
        if((ObjMouse.YCoordinates > r[0].y) && (ObjMouse.YCoordinates < r[0].y + r[0].h))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
            SDL_RenderDrawRect( renderer, &r[0] );
            f_display = MainScreen;
            }
        }
    }
}



void OptionScreen(int i)
{
	stringstream ss;
    ss << i;
	string str = "OptionScreen @";
	str.append(ss.str());
	std::cout << str.c_str() << std::endl;

    // easy option
    ButtonClips[0].h = 33;
    ButtonClips[0].w = 101;
    ButtonClips[0].x = 284;
    ButtonClips[0].y = 128;

    //medium option
    ButtonClips[1].h = 33;
    ButtonClips[1].w = 101;
    ButtonClips[1].x = 414;
    ButtonClips[1].y = 128;

    //hard option
    ButtonClips[2].h = 33;
    ButtonClips[2].w = 101;
    ButtonClips[2].x = 554;
    ButtonClips[2].y = 128;

    // sound on
    ButtonClips[3].h = 33;
    ButtonClips[3].w = 101;
    ButtonClips[3].x = 284;
    ButtonClips[3].y = 168;

    // sound off
    ButtonClips[4].h = 33;
    ButtonClips[4].w = 101;
    ButtonClips[4].x = 414;
    ButtonClips[4].y = 168;

    // music on
    ButtonClips[5].h = 33;
    ButtonClips[5].w = 101;
    ButtonClips[5].x = 284;
    ButtonClips[5].y = 218;

    // music off
    ButtonClips[6].h = 33;
    ButtonClips[6].w = 101;
    ButtonClips[6].x = 414;
    ButtonClips[6].y = 218;

    // back to main menu
    ButtonClips[7].h = 33;
    ButtonClips[7].w = 101;
    ButtonClips[7].x = 632;
    ButtonClips[7].y = 534;

    //SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 0, 0));

    // Set color of renderer to black
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

    // Clear the window and make it all black
    SDL_RenderClear( renderer );

    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

    SDL_RenderDrawRect( renderer, &ButtonClips[0] );
    SDL_RenderDrawRect( renderer, &ButtonClips[1] );
    SDL_RenderDrawRect( renderer, &ButtonClips[2] );
    SDL_RenderDrawRect( renderer, &ButtonClips[3] );
    SDL_RenderDrawRect( renderer, &ButtonClips[4] );
    SDL_RenderDrawRect( renderer, &ButtonClips[5] );
    SDL_RenderDrawRect( renderer, &ButtonClips[6] );
    SDL_RenderDrawRect( renderer, &ButtonClips[7] );

    RenderText("DIFFICULTY",ButtonClips[0].x - 150, ButtonClips[0].y);

    RenderText("EASY",ButtonClips[0].x,ButtonClips[0].y);
    RenderText("MEDIUM",ButtonClips[1].x,ButtonClips[1].y);
    RenderText("HARD",ButtonClips[2].x,ButtonClips[2].y);


    RenderText("SOUND",ButtonClips[3].x - 150,ButtonClips[3].y);

    RenderText("ON",ButtonClips[3].x,ButtonClips[3].y);
    RenderText("OFF",ButtonClips[4].x,ButtonClips[4].y);

    RenderText("MUSIC",ButtonClips[5].x - 150,ButtonClips[5].y);

    RenderText("ON",ButtonClips[5].x,ButtonClips[5].y);
    RenderText("OFF",ButtonClips[6].x,ButtonClips[6].y);

    RenderText("MAIN MENU",ButtonClips[7].x,ButtonClips[7].y);

    if((ObjMouse.YCoordinates > ButtonClips[0].y) && (ObjMouse.YCoordinates < ButtonClips[0].y + ButtonClips[0].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[0].x) && (ObjMouse.XCoordinates < ButtonClips[0].x + ButtonClips[0].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[0] );
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[1].y) && (ObjMouse.YCoordinates < ButtonClips[1].y + ButtonClips[1].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[1].x) && (ObjMouse.XCoordinates < ButtonClips[1].x + ButtonClips[1].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[1] );
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[2].y) && (ObjMouse.YCoordinates < ButtonClips[2].y + ButtonClips[2].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[2].x) && (ObjMouse.XCoordinates < ButtonClips[2].x + ButtonClips[2].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[2] );
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[3].y) && (ObjMouse.YCoordinates < ButtonClips[3].y + ButtonClips[3].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[3].x) && (ObjMouse.XCoordinates < ButtonClips[3].x + ButtonClips[3].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[3] );
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[4].y) && (ObjMouse.YCoordinates < ButtonClips[4].y + ButtonClips[4].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[4].x) && (ObjMouse.XCoordinates < ButtonClips[4].x + ButtonClips[4].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[4] );
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[5].y) && (ObjMouse.YCoordinates < ButtonClips[5].y + ButtonClips[5].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[5].x) && (ObjMouse.XCoordinates < ButtonClips[5].x + ButtonClips[5].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[5] );
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[6].y) && (ObjMouse.YCoordinates < ButtonClips[6].y + ButtonClips[6].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[6].x) && (ObjMouse.XCoordinates < ButtonClips[6].x + ButtonClips[6].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[6] );
            }
        }
    }

    if((ObjMouse.YCoordinates > ButtonClips[7].y) && (ObjMouse.YCoordinates < ButtonClips[7].y + ButtonClips[7].h))
    {
        if((ObjMouse.XCoordinates > ButtonClips[7].x) && (ObjMouse.XCoordinates < ButtonClips[7].x + ButtonClips[7].w))
        {
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
            SDL_RenderFillRect( renderer, &ButtonClips[7] );
            f_display = MainScreen;
            }
        }
    }

    RenderVersion();

    SDL_Rect r[10];

    r[0].x = 0;
    r[0].y = 0;
    r[0].w = 200;
    r[0].h = 200;

    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_RenderDrawRect( renderer, &r[0] );

    if((ObjMouse.YCoordinates > r[0].y) && (ObjMouse.YCoordinates < r[0].y + r[0].h))
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
        SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
        SDL_RenderDrawRect( renderer, &r[0] );
        f_display = MainScreen;
        }
    }
}


void Game::LoadFiles(std::string inFromPath)
{
    std::string sFromPath = inFromPath;

    SDL_Surface * image = NULL;
    DIR *dir;
    struct dirent *dent;

    dir = opendir(sFromPath.c_str());
    if(dir!=NULL)
    {
        while((dent=readdir(dir))!=NULL)
        {
            string sPath = sFromPath.c_str();
            sPath.append(dent->d_name);

            image = IMG_Load(sPath.c_str());
            if( image == NULL )
            {
                std::cout << sPath.c_str() << std::endl;
                SDL_GetError();
            }
            else
            {
                std::cout << "Loading " << sPath.c_str() << std::endl;
                SDL_FreeSurface(image);
            }
        }
    }
    closedir(dir);
}

// ----------------------------------------------------------------------------
// Update() - Updates the whole game depending on which state it is in
// ----------------------------------------------------------------------------
void Game::Update( SDL_Event /*input*/, double iElapsedTime )
{
/*
    logger.write(__LINE__, __FUNCTION__);

	// Check game state
	switch( gamestate.GameState.top() )
	{
        case GAME_BOSS_STATE:
            break;
        case GAME_OUTRO_STATE:
            break;
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
                // Disables the mouse cursor when playing the game
                if( SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE)
                {
                    SDL_ShowCursor(SDL_DISABLE);
                }

                if (GameLevel.StageCleared)
                {
                    gamestate.StageCleared(iElapsedTime);
                    return;
                }

                // Not really sure???
                if ( PowerLevelSecond < 5 )
                {
                    PowerLevelSecond += 1;
                }

                gamestate.CreateAll();

                Gfx.DrawBackgroundBlack();

                //SDL_Surface *surface = SDL_CreateRGBSurface(0, 1920, 1080, 32, 0, 0, 0, 255);
                for (std::vector<SDL_Rect>::iterator it = starbackground_trigger.begin(); it != starbackground_trigger.end(); ++it)
                {
                    //SDL_FillRect(Gfx.BackBuffer, &(*it), SDL_MapRGBA(Gfx.BackBuffer->format, 255, 255, 255, rand() % 255));
                    //SDL_SetAlpha(surface, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
                    //SDL_BlitSurface(surface, NULL, Gfx.BackBuffer,NULL);
                }

                GameLevel.Update(iElapsedTime);
                //SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfBackdrop), &Scroller, Gfx.BackBuffer, 0);

                // Render Level Background
                //SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfLevel[GameLevel.GetCurrent()]), &GameLevel.GetBox(), Gfx.BackBuffer, 0);

                OctoBossman.Spawn(GameLevel.GetBox().x);
                if ( OctoBossman.isActive() )
                {
                    OctoBossman.Update();
                    OctoBossman.Draw();
                    if (OctoBossman.onCollision(Spaceship.GetCollisionBox()))
                    {
                        //OctoBossman.onDestruction();
                        Spaceship.Died();
                        Spaceship.Reset();
                    }
                }

                Gfx.srfText = TTF_RenderText_Blended(Gfx.TitleFont, std::to_string(RobotnicController.RobotnicArrayRef.size()).c_str(), Gfx.WhiteRGB);
                Gfx.apply_surface(Gfx.BackBuffer->w - 50, 100, Gfx.srfText, Gfx.BackBuffer);

                if (GameLevel.GetBox().x < 1000)
                {
                    Gfx.srfText = TTF_RenderText_Blended(Gfx.TitleFont, GameLevel.GetIntroText().c_str(), Gfx.WhiteRGB);
                    Gfx.apply_surface(Gfx.BackBuffer->w / 4, Gfx.BackBuffer->h / 2, Gfx.srfText, Gfx.BackBuffer);
                }

                Gfx.srfText = TTF_RenderText_Blended(Gfx.TitleFont, std::to_string(GameLevel.GetCurrent()).c_str(), Gfx.WhiteRGB);
                Gfx.apply_surface(Gfx.BackBuffer->w - 250, 100, Gfx.srfText, Gfx.BackBuffer);

                Gfx.srfText = TTF_RenderText_Blended(Gfx.TitleFont, std::to_string(GameLevel.GetLength()).c_str(), Gfx.WhiteRGB);
                Gfx.apply_surface(Gfx.BackBuffer->w - 450, 100, Gfx.srfText, Gfx.BackBuffer);

                Gfx.srfText = TTF_RenderText_Blended(Gfx.TitleFont, std::to_string(OctoBossman.hasHealth()).c_str(), Gfx.WhiteRGB);
                Gfx.apply_surface(Gfx.BackBuffer->w - 100, 0, Gfx.srfText, Gfx.BackBuffer);

				Gfx.DrawObjects();


                //SDL_Surface *surface = SDL_CreateRGBSurface(0, 1920, 1080, 32, 0, 0, 0, 255);

                if (RobotnicController.RobotnicArrayRef.size() > 0)
                    for (std::vector<Robotnic>::iterator iRobotnic = RobotnicController.RobotnicArrayRef.begin(); iRobotnic != RobotnicController.RobotnicArrayRef.end(); ++iRobotnic)
                        for (std::vector<SDL_Rect>::iterator it = (*iRobotnic).bullet_object.begin(); it != (*iRobotnic).bullet_object.end(); ++it)
                        {
                            SDL_FillRect(Gfx.BackBuffer, &(*it), SDL_MapRGBA(Gfx.BackBuffer->format, 255, 0, 0, rand() % 255));
                            //SDL_SetAlpha(surface, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
                            //SDL_BlitSurface(surface, NULL, Gfx.BackBuffer,NULL);
                        }

                // Collision controllers for objects and player spaceship
                CollisionController.ObjectCollider(BulletController.BulletArrayRef, PurpleShipController.PurpleShipArrayRef);
                CollisionController.ObjectCollider( BulletController.BulletArrayRef, RobotnicController.RobotnicArrayRef );
				CollisionController.ObjectCollider( BulletController.BulletArrayRef, BlueFishController.BlueFishArrayRef );
                if (OctoBossman.isActive())
                {
                    CollisionController.ObjectCollider(BulletController.BulletArrayRef, OctoBossman);
                    CollisionController.ObjectCollider(OctoBulletController.BulletArrayRef, Spaceship);
                }

                if ( OctoBossman.hasHealth() <= 0 )
                {
                    //OctoBoss died
                    if (OctoBossman.isActive())
                    {
                        OctoBossman.DeActivate();
                        gamestate.GameState.pop();
                        gamestate.GameState.push(GAME_CREDITS_STATE);
                    }
                }
                CollisionController.SpaceshipCollider(Spaceship, PurpleShipController.PurpleShipArrayRef);
                CollisionController.SpaceshipCollider( Spaceship, RobotnicController.RobotnicArrayRef );
				CollisionController.SpaceshipCollider( Spaceship,BlueFishController.BlueFishArrayRef );
                CollisionController.SpaceshipCollider( Spaceship,OctoBossman);

                CollisionController.SpaceshipCollider( Spaceship, PowerupController.PowerupArrayRef);

                Gfx.DrawScore(Gfx.BackBuffer->w / 2, 0, UpdateScore());

                Gfx.srfText = TTF_RenderText_Blended(Gfx.ScoreFont, std::to_string(UpdateScore()).c_str(), Gfx.WhiteRGB);
                Gfx.apply_surface(Gfx.BackBuffer->w / 2, 0, Gfx.srfText, Gfx.BackBuffer);

                Gfx.DrawScore(Gfx.BackBuffer->w / 2, 50, GameLevel.GetBox().x);

                Gfx.srfText = TTF_RenderText_Blended(Gfx.ScoreFont, std::to_string(GameLevel.GetBox().x).c_str(), Gfx.WhiteRGB);
                Gfx.apply_surface(Gfx.BackBuffer->w - 150, 0, Gfx.srfText, Gfx.BackBuffer);

                Gfx.DrawSprite();

                // Gui options
                SDL_Rect Powerlevel;
                Powerlevel.x = 200;
                Powerlevel.y = 0;
                Powerlevel.h = 20;
                Powerlevel.w = PowerLevel;
                SDL_FillRect(Gfx.BackBuffer, &Powerlevel, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 255, 0, 0));
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
*/
}

// ----------------------------------------------------------------------------
// MainScreen() - Draws the mainscreen, checks conditions. MenuScreen
// ----------------------------------------------------------------------------
void Gamestate::MainScreen(double iElapsedTime)
{
    SDL_Surface* backgroundSurface = NULL;
    SDL_FillRect(backgroundSurface,NULL,SDL_MapRGBA(backgroundSurface->format, 0, 0, 0, 0));
	stringstream ss;
    ss << iElapsedTime;
	string str = "MainScreen @ ";
	str.append(ss.str());

/*
    logger.write(__LINE__, __FUNCTION__);
    SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 0, 0));
    SDL_BlitSurface(&Gfx.m_SurfaceCollection["assets/gfx/backdrops/srfMooPie_1920x1080.png"], 0, Gfx.BackBuffer, 0);
	SDL_BlitSurface( &Gfx.m_SurfaceCollection["assets/gfx/backdrops/srfMainMenu_1920x1080.png"], 0, Gfx.BackBuffer, 0 );

	stringstream ss;
	//ss << (float)iElapsedTime / 1000000;
    ss << iElapsedTime;
	string str = "MainScreen @ ";
	str.append(ss.str());

    //Gfx.RenderText(str.c_str(), 0, 50);
    Gfx.RenderText("v 1.0", 150, 50);
*/
}

// ----------------------------------------------------------------------------
// LoadScreen() - Draws the credit screen
// ----------------------------------------------------------------------------
void Gamestate::LoadScreen(double iElapsedTime)
{
/*
    logger.write(__LINE__, __FUNCTION__);
    SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 0, 0));
    SDL_BlitSurface(&Gfx.m_SurfaceCollection["assets/gfx/backdrops/srfLoad_1920x1080.png"], 0, Gfx.BackBuffer, 0);

    //SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[0]);
    //SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[1]);
    //SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[2]);
    //SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[3]);
    //SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[4]);
    //SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[5]);
    //SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[6]);
    //SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[7]);

	stringstream ss;
	//ss << (float)iElapsedTime / 1000000;
    ss << iElapsedTime;
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
*/
}

// ----------------------------------------------------------------------------
// SaveScreen() - Draws the save screen
// ----------------------------------------------------------------------------
void Gamestate::SaveScreen(double iElapsedTime)
{
/*
    logger.write(__LINE__, __FUNCTION__);
    SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 0, 0));
    SDL_BlitSurface(&Gfx.m_SurfaceCollection["assets/gfx/backdrops/srfSave_1920x1080.png"], 0, Gfx.BackBuffer, 0);

    //SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[0]);
    //SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[1]);
    //SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[2]);
    //SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[3]);
    //SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[4]);
    //SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[5]);
    //SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[6]);
    //SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[7]);

	stringstream ss;
	//ss << (float)iElapsedTime / 1000000;
    ss << iElapsedTime;
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
*/
}

// ----------------------------------------------------------------------------
// Gameover() - Draws the gameover screen
// ----------------------------------------------------------------------------

void Gamestate::Gameover(double /*iElapsedTime*/)
{
/*
    OctoBossman.onDestruction();
    logger.write(__LINE__, __FUNCTION__);
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
*/
}

// ----------------------------------------------------------------------------
// CreditScreen() - Draws the credit screen
// ----------------------------------------------------------------------------
void Gamestate::CreditScreen(double iElapsedTime)
{
/*
    logger.write(__LINE__, __FUNCTION__);
    SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 0, 0));
    SDL_BlitSurface(&Gfx.m_SurfaceCollection["assets/gfx/backdrops/srfCredits_1920x1080.png"], 0, Gfx.BackBuffer, 0);

	stringstream ss;
	//ss << (float)iElapsedTime / 1000000;
    ss << iElapsedTime;
	string str = "CreditsScreen @";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.WhiteRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
*/
}

// ----------------------------------------------------------------------------
// OptionScreen() - Draws the option screen
// ----------------------------------------------------------------------------
void Gamestate::OptionScreen(double iElapsedTime)
{
/*
    logger.write(__LINE__, __FUNCTION__);
    SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 0, 0));
    SDL_BlitSurface(&Gfx.m_SurfaceCollection["assets/gfx/backdrops/srfOptions_1920x1080.png"], 0, Gfx.BackBuffer, 0);

	if( DIFFICULTY == 0 )
	{
			//SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 0 ]);
	}
	else
	if( DIFFICULTY == 1 )
	{
		//SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 1 ]);
	}
	else
	if( DIFFICULTY == 2 )
	{
		//SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 2 ]);
	}
	if( SOUND == 3 )
	{
		//SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 3 ]);
	}
	else
	if( SOUND == 4 )
	{
		//SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 4 ]);
	}
	if( Audio.State() == 0 )
	{
		//SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 5 ]);
		//Audio.PlayMusic( std::rand() % 3 );
	}
	else
	if( Audio.State() == 1 )
	{
		//SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 6 ]);
		Audio.PauseMusic();
	}

	//SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 7 ]);

	stringstream ss;
	//ss << (float)iElapsedTime / 1000000;
    ss << iElapsedTime;
	string str = "OptionsScreen @";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.WhiteRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
*/
}

// ----------------------------------------------------------------------------
// StageCleared() - Draws the StageCleared
// ----------------------------------------------------------------------------
void Gamestate::StageCleared(double iElapsedTime)
{
/*
    static bool Delayed = false;
    static int Delay;
    if (!Delayed)
    {
        Delay = 50000;
        Delayed = true;
    }

    if (Delay > 0)
    {
        Delay -= iElapsedTime;
    }
    else
    {
        GameLevel.StageCleared = 0;
        Delayed = false;
    }

    //logger.write(__LINE__, __FUNCTION__);
    SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 0, 0));
    //SDL_BlitSurface(&Gfx.m_SurfaceCollection["assets/gfx/backdrops/srfMooPie_1920x1080.png"], 0, Gfx.BackBuffer, 0);
    //SDL_BlitSurface(&Gfx.m_SurfaceCollection["assets/gfx/backdrops/srfMainMenu_1920x1080.png"], 0, Gfx.BackBuffer, 0);

    stringstream ss;
    ss << iElapsedTime;
    string str = "StageCleared @ ";
    str.append(ss.str());

    //Gfx.RenderText(str.c_str(), 0, 50);
    Gfx.RenderText("STAGE CLEARED", Gfx.screen->w / 3, Gfx.screen->h / 2,"Title");
    Gfx.RenderText(std::to_string(Engine.UpdateScore()).c_str(), Gfx.screen->w / 3, Gfx.screen->h / 2 - 150);
    Gfx.RenderText(std::to_string(Delay).c_str(), Gfx.screen->w / 3, 0);
*/

}

void Gamestate::RestartGame()
{
/*
    logger.write(__LINE__, __FUNCTION__);
    OctoBossman.onDestruction();
	Spaceship.Reset();

    PurpleShipController.Destroy();
    RobotnicController.Destroy();
	BlueFishController.BlueFishArrayRef.clear();

	_SCORE = 0;
	Spaceship._Lives = 3;
    Engine.Progressbar(0,1);
*/
}

void Gamestate::Reset()
{
/*
    logger.write(__LINE__, __FUNCTION__);
	Spaceship.Reset();

    PurpleShipController.Destroy();
    RobotnicController.Destroy();
	BlueFishController.BlueFishArrayRef.clear();
	*/
}

void Gamestate::Cleanup()
{
/*
    logger.write(__LINE__, __FUNCTION__);
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
    if (gamestate.GameOverScreen != NULL)
    {
        delete GameOverScreen;
    }
*/
}

void Game::Cleanup()
{
/*
    logger.write(__LINE__, __FUNCTION__);
    atexit(TTF_Quit); // Ensure TTF_Quit() is called when we exit
	SDL_Quit();
*/
}

// inits sdl, font and videomode
void Game::Init()
{
    //const SDL_VideoInfo* info = SDL_GetVideoInfo();
    //ScreenSize.w = info->current_w;
    //ScreenSize.h = info->current_h;
	//set up the screen
    //screen = SDL_SetVideoMode(ScreenSize.w, ScreenSize.h, 32, flags);

    // Get the current video hardware information
    //const SDL_VideoInfo* myPointer = SDL_GetVideoInfo();

    //screen = SDL_SetVideoMode(myPointer->current_w, myPointer->current_h, 32, flags);

    //Gfx.m_SurfaceCollection["Screen"] = *SDL_SetVideoMode(ScreenSize.w, ScreenSize.h, 32, flags);

    //Uint32 flags = SDL_SWSURFACE;
    //flags = screen->flags;
    //screen = SDL_SetVideoMode(0, 0, 0, screen->flags ^ SDL_FULLSCREEN);
    //if (screen == NULL) screen = SDL_SetVideoMode(0, 0, 0, flags);
    //if (screen == NULL) exit(1);


    //modes = SDL_ListModes(NULL, SDL_FULLSCREEN | SDL_HWSURFACE);


    //if (modes == (SDL_Rect**)0)
	//{
    //    cout << "No modes available!" << endl;
    //    exit(-1);
	//}


   //if (modes == (SDL_Rect**)-1)
   //{
   //    cout << "All resolutions available." << endl;
   //}
   //else
   //{

    //   cout << "Available Modes" << endl;
    //   for (i = 0; modes[i]; ++i)
    //   {
    //       cout << modes[i]->w << " x " << modes[i]->h << endl;
    //   }
   //}

	//set window caption
	//SDL_WM_SetCaption( " S-TYPE ", NULL);

	//Uint32 rmask, gmask, bmask, amask;


	//rmask = 0x00000000;
	//gmask = 0x00000000;
	//bmask = 0x00000000;
	//amask = 0x00000000;

	//Gfx.BackBuffer = SDL_CreateRGBSurface( SDL_HWSURFACE, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h, SDL_GetVideoSurface()->format->BitsPerPixel,
	//							   rmask, gmask, bmask, amask);

    //Gfx.BackBuffer = SDL_CreateRGBSurface(0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h, SDL_GetVideoSurface()->format->BitsPerPixel, 0, 0, 0, 0);
}

int Game::UpdateScore(int add_score)
{
    return add_score;
}

/*
int Game::Progressbar(int progress, int _reset)
{
    _Progress += progress;
    return _Progress;

    double dt = 1.0 / 60.0;
    if ( _reset == 1 )
    {
        _Progress = 0;
    }

    if ( progress == 0 )
    {
        return _Progress += dt * 20;
    }
    else
    {
        return _Progress += dt * 20;
    }
}
*/
void Gamestate::CreateAll()
{
/*
    logger.write(__LINE__, __FUNCTION__);
    PurpleShipController.CreatePurpleShip(Engine.Progressbar());
    RobotnicController.CreateRobotnic(Engine.Progressbar());
    BlueFishController.CreateBlueFish(Engine.Progressbar());
	EnemyController.Create_Enemies();
	ObjectController.CreateObjects();
	*/
}
