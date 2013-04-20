#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <list>
using namespace std;
#include "Objects.h"
#include "Enemies\MovingThings.h"
#include "Enemies\CSkeleton.h"
#include "Enemies\CZombie.h"
#include "Enemies\CHeads.h"

class BossInterface
 {
public:

	 virtual void Update()=0;
	 virtual void SetClips()=0;
};

class CBoss : public BossInterface
{
public:
	CBoss();
	CHeads * CBoss::CreateBossHeads( int xPos, int yPos, int surface, int lengthOfTravel );
	void Update();
	void UpdateFrame();
	int GetFrame();
	void SetClips();
	void SetSurface(int iSurface);

	float xPos, yPos;
	int Frame;
	int Radius;
	int Width, Height;
	float Speed;
	
	int Surface;
	SDL_Rect Clips[ 16 ];
	int radius_Second;

	int BossWidth, BossHeight;
	int BossLife;
	bool BossDead;

	bool HeadsComing;
	bool HeadAnimation;

	float AnimPaceBoss;
	float HeadTimer;
	float SizeHeads;
	
	int Timer;

	std::list< CHeads* > _BossHeads;

	int State;

private:
	enum{ BOSS_IDLE, BOSS_ATTACK, BOSS_DIE };
	int xPos_, yPos_;
	int Width_, Height_;
	int Surface_;

};

extern CBoss gBoss;



