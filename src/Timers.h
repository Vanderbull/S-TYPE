#pragma once

class Timer
{
public:
	Timer();

	bool IsPaused();
	bool IsStarted();
	bool Unpause();
	bool Pause();
	bool Stop();
	bool Start();
	void RestartTimers();
	int GetTicks();

	float AttackTimerSkeleton;
	float AttackTimerZombie;
	float AttackTimerHead;
	float TimerAttackBoss;
	float TimerBossAnim;
	float TimerBossHead;
	float TimerCoffinTimer;
	float TimerPowerUp;
	float TimerPowerUpRoll;
	float TimerMorphPics;
	float TimerHit;

private:
	//The clock time when the timer started
    int _StartTicks;
    
    //The ticks stored when the timer was paused
    int _PausedTicks;
    
    //The timer status
    bool _Paused;
    bool _Started;
};

extern Timer timer;