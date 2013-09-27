#include "Timers.h"
#include <SDL.h>
Timer timer;

Timer::Timer()
{
	AttackTimerSkeleton = 0.0f;
	AttackTimerZombie = 0.0f;
	AttackTimerHead = 0.0f;

	AttackBoss = 0.0f;
	BossAnim = 0.0f;
	BossHead = 0.0f;

	CoffinTimer = 0.0f;
	PowerUpRoll = 0.0f;
	MorphPics = 0.0f;

	Hit = 0.0f;

	_StartTicks = 0;
    _PausedTicks = 0;
    _Paused = false;
    _Started = false;
}

bool Timer::IsPaused()
{
	return _Paused;
}

bool Timer::IsStarted()
{
	return _Started;
}

int Timer::GetTicks()
{
    //If the timer is running
    if( _Started == true )
    {
        //If the timer is paused
        if( _Paused == true )
        {
            //Return the number of ticks when the the timer was paused
            return _PausedTicks;
        }
        else
        {
            //Return the current time minus the start time
			return SDL_GetTicks() - _StartTicks;
        }    
    }
    
    //If the timer isn't running
    return 0;  
};
bool Timer::Unpause()
{
    //If the timer is paused
    if( _Paused == true )
    {
        //Unpause the timer
        _Paused = false;
    
        //Reset the starting ticks
        _StartTicks = SDL_GetTicks() - _PausedTicks;
        
        //Reset the paused ticks
        _PausedTicks = 0;
    }
	return _Paused;
};
bool Timer::Pause()
{
    //If the timer is running and isn't already paused
    if( ( _Started == true ) && ( _Paused == false ) )
    {
        //Pause the timer
        _Paused = true;
    
        //Calculate the paused ticks
        _PausedTicks = SDL_GetTicks() - _StartTicks;
    }
	return _Paused;
};
bool Timer::Stop()
{
	if( IsStarted() )
	{
		_Started = false;
		_Paused = false;
		return true;
	}
	else
	{
		return false;
	}
    //Stop the timer
    //started = false;
    
    //Unpause the timer
    //paused = false;    

	//return false;
};
bool Timer::Start()
{
	if( IsStarted() )
	{
		_Paused = false;
		return true;
	}
	else
	{
	    //Get the current clock time
	    _StartTicks = SDL_GetTicks();    

		_Paused = true;
		return false;
	}

    //Start the timer
    //started = true;
    
    //Unpause the timer
    //paused = false;
    
    //Get the current clock time
    //startTicks = SDL_GetTicks();    

	//return false;
};
void Timer::RestartTimers()
{
	AttackTimerSkeleton = 0.0f;
	AttackTimerZombie = 0.0f;
	AttackTimerHead = 0.0f;

	AttackBoss = 0.0f;
	BossAnim = 0.0f;
	BossHead = 0.0f;

	CoffinTimer = 0.0f;
	PowerUpRoll = 0.0f;
	MorphPics = 0.0f;

	Hit = 0.0f;

	_StartTicks = 0;
	_PausedTicks = 0;
    _Paused = false;
    _Started = false;
};
