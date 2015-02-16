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
#include <stack>
#include <windows.h>
using namespace std;

#include "Global\Global.h"
#include "Objects/Objects.h"
#include "SDL_mixer.h"
#include "Objects/SpaceShip.h"
#include "Enemies.h"
#include "Screens/MainMenu.h"
#include "Screens/Credits.h"
#include "Screens/Options.h"
#include "Screens/Load.h"
#include "Screens/GameOver.h"
#include "Save/Save.h"
#include "Collision/Collision.h"
#include "OutroFinish.h"
#include "GetInput.h"
#include "GameController\GameController.h"
#include "ParticleController\Particle.h"
#include "Enemies\OctoBoss.h"
class Gamestate
{
public:
	Gamestate();
	~Gamestate(){ std::cout << "Destroying Gamestate object..." << endl; };
	
	std::stack<InGameStates> GameState;

	double DeltaTime;
	double UpdateAnimationSpeed;
	double Parallax;

	StringInput * name;
	MainMenu * MainMenuScreen;
	Credits * CreditsScreen;
	Options * OptionsScreen;
	Load * LoadsScreen;
	Save * SavesScreen;
    GameOver * GameOverScreen;

    Sint16 m_srfGameover,
        m_srfPurpleShip,
        m_srfRobotnic,
        m_srfBlueFish,
        m_srfBackdrop, 
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
		m_srfButtonActive,
        m_srfInk;

    Sint16 m_srfLevel[10];

    Sint16 m_srfExplosion[15];

    // Powerup image index
    int m_srfRedPowerup;
    int m_srfGreenPowerup;
    int m_srfBluePowerup;

    // Boss image index
    int m_srfOctoBoss;

	std::map<string,int> m_SurfaceCollection;

	// Active menu
	int ActiveMenu;

	void ResumeGame(){};
	void NewGame(){};
	void LoadGame(){};
	void SaveGame(){};

	void MainScreen(double iElapsedTime);
    void CreditScreen(double iElapsedTime);
    void OptionScreen(double iElapsedTime);
    void LoadScreen(double iElapsedTime);
    void SaveScreen(double iElapsedTime);
    void Gameover(double iElapsedTime);
    void StageCleared(double iElapsedTime);

	void Quit(){};


	void CreateAll();

	void load_files();

	// Key Mapping trial
	void KeyMapping(SDL_Event _event);

	void RestartGame();
	void Reset();
	void Cleanup();

    Particle p;
	
private:
	SDL_Surface * m_surfaceList[ MAX_SURFACE ];
};

extern Gamestate gamestate;

class Game
{
public:
	Game();
	~Game(){ std::cout << "Destroying Game::Object..." << endl; };
	void Update( SDL_Event input, double iElapsedTime );
	bool Init( SDL_Surface * &screen );
	void HandleEvents( SDL_Event input );
	void Cleanup();
	int UpdateScore(int score = 0);
    int Progressbar(int progress = 0, int _reset = 0);


	bool Quit;
	int MouseXCoordinates; // the last recorded x coordinate of the mouse
	int MouseYCoordinates; // the last recorded y coordinate of the mouse
	std::map <string, SDL_Rect> _Button;

	Uint16 SPAWN_POSITION_X;
	Uint16 SPAWN_POSITION_Y;

    //GameController *GamePad;
    GameController GamePad;

    int MouseButtonTrigger(SDL_Rect TriggerArea);


private:
	Gamestate _State;
    double _Progress;
};

extern Game Engine;
