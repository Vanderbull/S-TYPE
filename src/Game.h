#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map>
#include <string>
#include <sstream>
#include <windows.h>
#include "Paralaxlayers.h"
#include <iostream>
#include "Objects.h"
#include "SDL_mixer.h"
#include "characters.h"
#include <list>
#include "Enemies.h"
#include <fstream>
#include "Global\Global.h"
#include "MainMenu.h"
#include "Credits.h"
#include "Options.h"
#include "Collision.h"
#include "OutroFinish.h"
#include "GetInput.h"
#include "HighScore.h"
#include "DancingDragon.h"
#include "World\CWorld.h"

using namespace std;

class Gamestate
{
public:
	Gamestate();
	~Gamestate(){ std::cout << "Destroying Gamestate object..." << endl; };
	
	std::stack<InGameStates> GameState;

	ParallaxBackground *ParallaxBG;

	int State;

	float DeltaTime;
	float UpdateAnimationSpeed;
	float Parallax;

	StringInput * name;
	MainMenu * MainMenuScreen;
	Credits * CreditsScreen;
	Options * OptionsScreen;

	int m_srfCity, 
		m_srfSky, 
		m_srfFence, 
		m_srfClouds, 
		m_srfEnemyZombie,
		m_srfCrow,
		m_srfBlack, 
		m_srfBoss, 
		m_srfdemonLife, 
		m_srfdemonHealthAndFire, 
		m_srfDragon, 
		m_srfStart, 
		m_srfButtons,
		m_srfIntro, 
		m_srfPower, 
		m_srfMorphing, 
		m_srfOutro, 
		m_srfButton, 
		m_srfHealth,
		m_srfLaser,
		m_srfCredits,
		m_srfOptions;

	// Active menu
	int ActiveMenu;

	void ResumeGame(){};
	void NewGame(){};
	void LoadGame(){};
	void SaveGame(){};
	void CreditScreen(int iElapsedTime);
	void OptionScreen(int iElapsedTime);
	void Quit(){};


	void CreateAll();
	void AddTick();

	void Loading();
	void DrawAllText();
	void EndAll();
	
	void MainScreen(int iElapsedTime);
	void EnterName();
	void setUpParallaxLayers();
	void load_files();

	// Key Mapping trial
	void KeyMapping(SDL_Event _event);

	void RestartGame();
	void ResetBoss();
	void ResetEnemies();
	void ResetObjects();
	void ResetRest();
	void PlayOutro();

	Boss * CreateBoss( int xPos, int yPos, int surface );
	
private:
	SDL_Surface * m_surfaceList[ MAX_SURFACE ];
	int _Score;

};

extern Gamestate gamestate;

class Game
{
public:
	Game();
	~Game(){ std::cout << "Destroying Game::Object..." << endl; };
	void Audiotonic();
	void Update( SDL_Event input, int iElapsedTime );
	bool Init( SDL_Surface * &screen );
	void HandleEvents( SDL_Event input );
	void Cleanup();

	bool Quit;
	int LevelProgress;
	int MouseXCoordinates; // the last recorded x coordinate of the mouse
	int MouseYCoordinates; // the last recorded y coordinate of the mouse
	std::map <string, SDL_Rect> _Button;

private:
	Gamestate _State;
	World _World;
};

