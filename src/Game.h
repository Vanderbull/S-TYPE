#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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
#include "Intro.h"
#include "FirstScreen.h"
#include "Collision.h"
#include "OutroFinish.h"
#include "GetInput.h"
#include "HighScore.h"
#include "DancingDragon.h"

enum{ GS_INTRO, GS_LEVEL1, GS_LEVEL1BOSS, GS_OUTRO, 
	  GS_LOADING, GS_INTROSTORY, GS_MORPH, GS_DEAD, GS_ENTERNAME };
enum{ BOSS_IDLE, BOSS_ATTACK, BOSS_DIE };
enum{ HEAD_GO, HEAD_DOWN, HEAD_CRASH };
enum{ BUTTON_NEW_GAME, BUTTON_OPTIONS, BUTTON_QUIT };
enum{ MAIN_MENU, OPTIONS_MENU, CREDITS_MENU };

const int MAX_SURFACE = 128;
const int ANIMPACE = 150;
const int ANIMPACESLOWER = 300;
const int ANIMPACEENEMY = 50;
const int ANIMPACEBOSSHEAD = 5;

const int DEMONHEIGHT = 100;
const int DEMONWIDTH = 130;
const int DEMONWIDTHREAL = 25;
const int DEMONHEIGHTREAL = 25;

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
	
	ParallaxBackground *Parallax;

	int CurrentFrame, PreviousFrame;	
	int GameCondition;

	float dt;
	float UpdateAnimationSpeed;
	float m_parallax;

	bool GameOK;
	bool BossStart;
	bool IntroDone;

	char Text[ 256 ];
	string ScoreString;

	SDL_Rect MorphingPics[ 5 ];

	//TTF_Font * font;

	//Boss * pBoss;
	IntroTalk * Intro;
	Outro * outro;
	StringInput * name;
	FillHighScore * ListHighScore;
	DancingDragon * Dragon;
	FirstScreen * TitleScreen;

	int m_srfCity, m_srfSky, m_srfFence, m_srfClouds, m_srfTree, m_srfEnemyZombie,
		m_srfSkeleton, m_srfCrow, m_srfCoffin, m_srfTrees, m_srfBlack, m_srfBoss, 
		m_srfDemonLife, m_srfDemonHealthAndFire, m_srfDragon, m_srfStart, m_srfButtons,
		m_srfIntro, m_srfPower, m_srfMorphing, m_srfReaper, m_srfOutro, m_srfButton, m_srfHealth;

	//SDL_Surface * srfText;
	//SDL_Surface * textIntro;
	//SDL_Surface * DeathSurface[ 2 ];
	//SDL_Surface * TypeName;

	// Level progress counter
	//int LevelProgress;

	// Player name
	std::string PlayerName;

	// Active menu
	int ActiveMenu;

	//int Load_imageAlpha( std::string filename, int r, int g, int b );

	//SDL_Surface * screen;
	//SDL_Surface * BackBuffer;

	void CreateAll();
	void AddTick();
	//void drawParallaxLayers();

	void Loading();
	void DrawAllText();
	void DoIntroTalk();
	void MorphMyDude();
	void EndAll();
	
	void MainScreen();
	void EnterName();
	//void DrawSprite();
	//void DrawObjects();
	//void DrawBoss();
	//void DrawBackgroundBlack();
	void CreateNewThings();
	void setUpParallaxLayers();
	void load_files();

	// Key Mapping trial
	void KeyMapping(SDL_Event _event);

	//void FLIP();
	//SDL_Surface * GetSurface( int WhichSurface );

	//void stretchBlit( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect );
	//void PasteScreenToAnother( SDL_Rect srcRect, SDL_Rect destRect );
	//void stretchPicToBackBuffer( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect  );
	//void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );

	void PlayerDied();
	void RestartGame();
	void ResetBoss();
	void ResetEnemies();
	void ResetObjects();
	void ResetPlayer();
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
	void Audiotonic();
	void Update( SDL_Event input );
	bool Init( SDL_Surface * &screen );
	void HandleEvents( SDL_Event input );
	void Cleanup();

	bool Quit;
private:
	Gamestate _State;
};

