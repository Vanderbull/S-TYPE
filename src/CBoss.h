#pragma once

#include <SDL.h>
#include <SDL_image.h>

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
	void Update();
	void SetClips();
	void SetSurface(int iSurface);

private:
	enum{ BOSS_IDLE, BOSS_ATTACK, BOSS_DIE };
	int xPos_, yPos_;
	int Width_, Height_;
	int Surface_;

};

extern CBoss gBoss;



