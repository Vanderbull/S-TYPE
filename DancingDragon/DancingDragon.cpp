#include <windows.h>
using namespace std;

#include "DancingDragon.h"

void DancingDragon::SetFrame()
{
	if( Frame == 21 )
	{
		DancingDragon::Frame = 0;
	}
	else
	{
		DancingDragon::Frame++;
	}
};

void DancingDragon::SetClips()
{
	for( int index = 0; index < 23; index++ )
	{
		DancingDragon::Clips[ index ].x = index * DancingDragon::Width;
		DancingDragon::Clips[ index ].y = 0;
		DancingDragon::Clips[ index ].h = DancingDragon::Height;
		DancingDragon::Clips[ index ].w = DancingDragon::Width;
	}
};

DancingDragon::DancingDragon( int Surface )
{
	DancingDragon::Frame = 0;
	DancingDragon::PrevFrame = 0;
	DancingDragon::StateCounter = 0;
	DancingDragon::xPos = 0;
	DancingDragon::yPos = 0;
	DancingDragon::surface = Surface;
	DancingDragon::Width = 64;
	DancingDragon::Height = 64;
	DancingDragon::SetClips();
	DancingDragon::AnimationTimestamp = GetTickCount();
};
