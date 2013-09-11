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
//#include "Intro.h"
#include "MainMenu.h"
#include "Collision.h"
#include "OutroFinish.h"
#include "GetInput.h"
#include "HighScore.h"
#include "DancingDragon.h"
#include "World\CWorld.h"

enum
{
	MENU_MAIN_STATE,
	MENU_SUB_STATE,
	GAME_RUNNING_STATE,
	GAME_INTRO_STATE,
	GAME_OUTRO_STATE,
	GAME_PAUSED_STATE,
	GAME_STORY_STATE,
	GAME_LOADING_STATE,
	GAME_BOSS_STATE,
	GAME_PLAYER_DIED_STATE
};

enum{ BOSS_IDLE, BOSS_ATTACK, BOSS_DIE };
enum{ HEAD_GO, HEAD_DOWN, HEAD_CRASH };
enum{ BUTTON_NEW_GAME, BUTTON_OPTIONS, BUTTON_QUIT };
enum{ MAIN_MENU, OPTIONS_MENU, CREDITS_MENU };

const int MAX_SURFACE = 128;
const int ANIMPACE = 150;
const int ANIMPACESLOWER = 300;
const int ANIMPACEENEMY = 50;
const int ANIMPACEBOSSHEAD = 5;

const int demonHEIGHT = 100;
const int demonWIDTH = 130;
const int demonWIDTHREAL = 25;
const int demonHEIGHTREAL = 25;

const int GROUND_Y = 500;
const int GROUND_X = 400;
const int STARTSCROLLING = 400;
const int BOSS_ATTACK_START = 150;

using namespace std;

class Gamestate
{
public:
	Gamestate();
	~Gamestate(){};
	
	ParallaxBackground *ParallaxBG;

	int State;

	float DeltaTime;
	float UpdateAnimationSpeed;
	float Parallax;

	SDL_Rect MorphingPics[ 5 ];

	Outro * outro;
	StringInput * name;
	FillHighScore * ListHighScore;
	DancingDragon * Dragon;
	MainMenu * TitleScreen;

	int m_srfCity, 
		m_srfSky, 
		m_srfFence, 
		m_srfClouds, 
		//m_srfTree, 
		m_srfEnemyZombie,
		//m_srfSkeleton, 
		m_srfCrow, 
		m_srfCoffin,
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
		//m_srfReaper, 
		m_srfOutro, 
		m_srfButton, 
		m_srfHealth,
		m_srfLaser;

	// demon name
	string demonName;

	// Active menu
	int ActiveMenu;

	void CreateAll();
	void AddTick();

	void Loading();
	void DrawAllText();
	void DoIntroTalk();
	void EndAll();
	
	void MainScreen(int iElapsedTime);
	void EnterName();
	void CreateNewThings();
	void setUpParallaxLayers();
	void load_files();

	// Key Mapping trial
	void KeyMapping(SDL_Event _event);

	void demonDied();
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

