#pragma once
#include <SDL.h>
#include <string>

// @date 2012-08-07

using namespace std;

enum{ CENTURION, MYDUDE_DEMON, ZEUS };

/*
class DancingDragon
{
public:
	DancingDragon( int Surface );
	int xPos, yPos;
	int Height, Width;
	int Frame, PrevFrame;
	int surface;
	int StateCounter;
	void SetFrame();
	void SetClips();
	SDL_Rect Clips[ 23 ];
	int AnimationTimestamp;
};
*/

class IntroTalk
{
public:
	IntroTalk( int Surface );

	int xPos, yPos;
	int Height, Width;
	int surface;
	int LetterHeight, LetterWidth, y;
	int Letter;

	int CounterWords, CounterNextTalker, Counter;
	SDL_Rect srcClips[ 3 ];
	SDL_Rect DestClips[ 3 ];
	int Frame;
	int Line;

	string CenturionTalks[ 8 ];
	string ZeusTalks[ 8 ];

	void DrawBackground();

	string CenturionTalksSlow[ 5 ];
	string CenturionTalksSlow2[ 5 ];
	string CenturionTalksSlow3[ 5 ];
	string CenturionTalksSlow4[ 5 ];

	string ZeusTalksSlow[ 5 ];
	string ZeusTalksSlow2[ 5 ];
	string ZeusTalksSlow3[ 5 ];
	string ZeusTalksSlow4[ 5 ];

	void DoTalk();

	bool Centurion, Zeus, MyDude_Demon, FirstLine, SecondLine, ThirdLine, FourthLine, Fifth,
		Sixth, Seventh, Eight;

	SDL_Surface * IntroSurfaces[ 1 ];
};