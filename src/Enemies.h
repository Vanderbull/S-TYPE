#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <list>
#include "Objects.h"
#include "Enemies\MovingThings.h"

#include "Enemies\CWave1.h"


// Set_Clips enum
enum{ ENEMY_WAVE1 };


enum{ WAVE1 };

// holds info for all the enemies

class CEnemy : public MovingThings
{
public:
	
	CEnemy();
	void Set_Clips( int WhichTypeOfEnemy ); // Should be replaced by objects SetClips
	void SetFrame();
	
	// New update functionality
	SDL_Rect GetPosition()
	{
		return CEnemy::_Position;
	}
	void Update()
	{
		CEnemy::_Position.w = CEnemy::Width;
		CEnemy::_Position.h = CEnemy::Height;
	}

	int PrevFrame, Frame, Radius, AnimCounter;

	std::list<SDL_Rect> Clips;

private:
};

// controls the enemies and creates the enemies
class Control_Enemies
{
public:
	Control_Enemies();
	void Update();
	void Draw_Enemies();
	void Create_Enemies();
	std::list<CWave1*> _Wave1;
	std::list< CEnemy* > Enemies;
	CEnemy * CreateEnemy( Sint16 xPos, Sint16 yPos, int surface );	
private:

	int SpawnTimer;
	bool Collide;
	bool CollideFire;
	bool Attack;
};

extern Control_Enemies EnemyController;


