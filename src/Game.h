#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <windows.h>
using namespace std;

#include "Paralaxlayers.h"
#include "Objects.h"
#include "SDL_mixer.h"
#include "SpaceShip.h"
#include "Enemies.h"
#include "Global\Global.h"
#include "MainMenu.h"
#include "Credits.h"
#include "Options.h"
#include "Load.h"
#include "Save.h"
#include "GameOver.h"
#include "Collision.h"
#include "OutroFinish.h"
#include "GetInput.h"
#include "World\CWorld.h"


class Gamestate
{
public:
	Gamestate();
	~Gamestate(){ std::cout << "Destroying Gamestate object..." << endl; };
	
	std::stack<InGameStates> GameState;

	ParallaxBackground *ParallaxBG;

	float DeltaTime;
	float UpdateAnimationSpeed;
	float Parallax;

	StringInput * name;
	MainMenu * MainMenuScreen;
	Credits * CreditsScreen;
	Options * OptionsScreen;
	Load * LoadsScreen;
	Save * SavesScreen;
	GameOver * GameOverScreen;

	int m_srfBackdrop, 
		m_srfAsteroid,
		m_srfBlack,
		m_srfStart, 
		m_srfButtons,
		m_srfIntro, 
		m_srfPower, 
		m_srfOutro, 
		m_srfHealth,
		m_srfLaser,
		m_srfCredits,
		m_srfOptions,
		m_srfLoad,
		m_srfSave,
		m_srfCube,
		m_srfTriangle,
		m_srfButtonActive;

	std::map<string,int> m_SurfaceCollection;

	// Active menu
	int ActiveMenu;

	void ResumeGame(){};
	void NewGame(){};
	void LoadGame(){};
	void SaveGame(){};

	void MainScreen(int iElapsedTime);
	void CreditScreen(int iElapsedTime);
	void OptionScreen(int iElapsedTime);
	void LoadScreen(int iElapsedTime);
	void SaveScreen(int iElapsedTime);
	void GameoverScreen(int iElapsedTime);

	void Quit(){};


	void CreateAll();

	void EnterName();
	void setUpParallaxLayers();
	void load_files();

	// Key Mapping trial
	void KeyMapping(SDL_Event _event);

	void RestartGame();
	void Reset();
	void ResetEnemies();
	void ResetRest();
	void PlayOutro();
	void Cleanup();
	
private:
	SDL_Surface * m_surfaceList[ MAX_SURFACE ];
};

extern Gamestate gamestate;

class Game
{
public:
	Game();
	~Game(){ std::cout << "Destroying Game::Object..." << endl; };
	void Update( SDL_Event input, int iElapsedTime );
	bool Init( SDL_Surface * &screen );
	void HandleEvents( SDL_Event input );
	void Cleanup();
	int UpdateScore(){ return _SCORE++; };
	bool Quit;
	int MouseXCoordinates; // the last recorded x coordinate of the mouse
	int MouseYCoordinates; // the last recorded y coordinate of the mouse
	std::map <string, SDL_Rect> _Button;

	Uint16 SPAWN_POSITION_X;
	Uint16 SPAWN_POSITION_Y;

private:
	Gamestate _State;
	World _World;
};

extern Game Engine;
