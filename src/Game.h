#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <stack>

#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>

#ifdef _WIN32
    #include <windows.h>
#endif

using namespace std;

//#include "../src/Global/Global.h"
//#include "Objects/Objects.h"
//#include "SDL_mixer.h"
//#include "Objects/Objects.h"
//#include "Objects/Spaceship.h"
//#include "Objects/SpaceShip.h"
//#include "Enemies.h"
//#include "Screens/MainMenu.h"
//#include "Screens/Credits.h"
//#include "Screens/Options.h"
//#include "Screens/Load.h"
//#include "Screens/GameOver.h"
//#include "Save/Save.h"
//#include "Collision/Collision.h"
//#include "OutroFinish.h"
//#include "GetInput.h"
//#include "GameController/GameController.h"
//#include "ParticleController/Particle.h"
//#include "Enemies/OctoBoss.h"

class Life
{
public:
    Life(){ std::cout << "Constructing a Life..." << std::endl; m_Life = 6; };
    ~Life(){ std:cout << "Destroying a Life..." << std::endl; };
    int GetLife(){ return m_Life; };
    void Add()
    {
        if(m_Life < 6)
        {
            m_Life++;
        }
    };
    void Substract()
    {
        if(m_Life > 0)
        {
            m_Life--;
        }
    };

    int m_Life;
};

class Beam
{
public:
    Beam(){ std::cout << "Constructing a Beam..." << std::endl; m_Power = 0; };
    ~Beam(){ std:cout << "Destroying a Beam..." << std::endl; };
    int GetPower(){ return m_Power; };
    void Charge()
    {
        if(m_Power < 100)
        {
            m_Power++;
        }
    };
    void Discharge()
    {
        m_Power = 0;
    };

    int m_Power;
};

class Spaceship
{
public:
        Spaceship(){ std::cout << "Building spaceship" << std::endl; Position.x=0; Position.y=0; Position.w=100; Position.h=32; };
        ~Spaceship(){ std::cout << "Dismantling spaceship" << std::endl; };

        SDL_Rect Position;
};

class Gamestate
{
public:
	Gamestate();
	~Gamestate(){ std::cout << "Destroying Gamestate object..." << endl; };

	double DeltaTime;
	double UpdateAnimationSpeed;
	double Parallax;

	//StringInput * name;
	//MainMenu * MainMenuScreen;
	//Credits * CreditsScreen;
	//Options * OptionsScreen;
	//Load * LoadsScreen;
	//Save * SavesScreen;
    //GameOver * GameOverScreen;

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

    //Particle p;

private:
	SDL_Surface * m_surfaceList[ 128 ];
};

//extern Gamestate gamestate;

class Game
{
public:
	Game();
	~Game(){ std::cout << "Game object destroyed..." << std::endl; };
	void Update( SDL_Event input, double iElapsedTime );
	void Init();
	void HandleEvents( SDL_Event input );
	void Cleanup();
	int UpdateScore(int score = 0);
    //int Progressbar(int progress = 0, int _reset = 0);

	std::map <string, SDL_Rect> _Button;

    //GameController *GamePad;
    //GameController GamePad;

    int MouseButtonTrigger(SDL_Rect TriggerArea);
    void LoadFiles(std::string inFromPath);

    std::stack<Gamestate> aState;
    Spaceship Ship;
    Beam BeamIndicator;
    Life LifeIndicator;

private:

	Gamestate _State;
    double _Progress;
    bool Quit;
   	int MouseXCoordinates; // the last recorded x coordinate of the mouse
	int MouseYCoordinates; // the last recorded y coordinate of the mouse
    Uint16 SPAWN_POSITION_X;
	Uint16 SPAWN_POSITION_Y;

};

//extern Game Engine;
