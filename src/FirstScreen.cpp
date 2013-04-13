#include "FirstScreen.h" 
#include <SDL.h>

// @date 2012-08-07

FirstScreen::FirstScreen( int ButtonX, int Surface, int SurfaceButtons )							
{
	//xPos = 0;
	//yPos = 0;
	//Width = 800;
	//Height = 600;

	//TitleScreen surface
	surface = Surface;

	SurfaceButt = SurfaceButtons;

	//ButtonXpos = ButtonX;
	//Button_Width = 250;
	//Button_Height = 70;
	//Button_Small_Width = 200;
	//Button_Small_Height = 50;

	ButtonOptions = false;
	ButtonBack = false; 
	ButtonSound = false;
	ButtonCredits = false;
	ButtonHighScore = false;

	ButtonNewgame = false;

	int ArraySize = sizeof(ButtonClips) / sizeof(ButtonClips[0]);
	for( int i = 0; i < ArraySize; i++ )
	{
		ButtonClips[ i ].x = 0;
		ButtonClips[ i ].y = 0;
		ButtonClips[ i ].w = 0;
		ButtonClips[ i ].h = 0;
	}
/*
	for( int i = 0; i < ArraySize; i++ )
	{
		ButtonClips[ i ].x = 0;
		ButtonClips[ i ].y = i * Button_Height + 25;
		ButtonClips[ i ].w = Button_Width;
		ButtonClips[ i ].h = Button_Height;
	}
*/
	ArraySize = sizeof(DestClips) / sizeof(DestClips[0]);
	for( int i = 0; i < ArraySize; i++ )
	{
		DestClips[ i ].x = 0;
		DestClips[ i ].y = 0;
		DestClips[ i ].w = 0;
		DestClips[ i ].h = 0;
	}
/*
	for( int i = 0; i < ArraySize; i++ )
	{
		DestClips[ i ].x = 0;
		DestClips[ i ].y = i * Button_Height + 25;
		DestClips[ i ].w = Button_Width;
		DestClips[ i ].h = Button_Height;
	}
*/
		//ButtonClips[ 0 ].y = 10;
		//ButtonClips[ 0 ].h = Button_Height-10;

		//ButtonClips[ 3 ].x = 0;
		//ButtonClips[ 3 ].y = 200;
		//ButtonClips[ 3 ].w = 390;
		//ButtonClips[ 3 ].h = 150;
	/*
	int j = 0;
	for( int i = 4; i < 8; i++, j++)
	{
		ButtonClips[ i ].x = 410;
		ButtonClips[ i ].y = j * 50;
		ButtonClips[ i ].w = Button_Small_Width;
		ButtonClips[ i ].h = Button_Small_Height;
	}

		ButtonClips[ 8 ].x = 410;
		ButtonClips[ 8 ].y = 55;
		ButtonClips[ 8 ].w = Button_Small_Width;
		ButtonClips[ 8 ].h = Button_Small_Height - 5;

	for( int i = 0; i < 3; i++ )
	{
		DestClips[ i ].x = ButtonXpos * i;
		DestClips[ i ].y = 515;
		DestClips[ i ].w = Button_Width;
		DestClips[ i ].h = Button_Height;

	}

		DestClips[ 3 ].x = 0;
		DestClips[ 3 ].y = 0;
		DestClips[ 3 ].w = 390;
		DestClips[ 3 ].h = 130;

	for( int i = 4; i < 8; i++ )
	{
		DestClips[ i ].x = 470;
		DestClips[ i ].y = 80 + i * 60;
		DestClips[ i ].w = Button_Small_Width;
		DestClips[ i ].h = Button_Small_Height;
	}

	DestClips[ 8 ].x = 40;
	DestClips[ 8 ].y = 20;
	DestClips[ 8 ].w = Button_Small_Width;
	DestClips[ 8 ].h = Button_Small_Height;

	DestClips[ 9 ].x = 40;
	DestClips[ 9 ].y = 20;
	DestClips[ 9 ].w = Button_Small_Width;
	DestClips[ 9 ].h = Button_Small_Height;
	*/

	/*
	0:gamestate.TitleScreen->Button_Newgame = true;
	1:gamestate.TitleScreen->Button_Options = true;
	2:gamestate.TitleScreen->Button_Quit = true;
	3:
	4:gamestate.TitleScreen->Button_HighScore = true
	5:gamestate.TitleScreen->Button_Credits = true;
	6:gamestate.TitleScreen->Button_Sound = true;
	7:gamestate.TitleScreen->Button_Back = true;
	8:
	9:
	*/
	ButtonClips[ 0 ].x = 0;
	ButtonClips[ 0 ].y = 0;
	ButtonClips[ 0 ].w = 325;
	ButtonClips[ 0 ].h = 70;

	ButtonClips[ 1 ].x = 0;
	ButtonClips[ 1 ].y = 70;
	ButtonClips[ 1 ].w = 325;
	ButtonClips[ 1 ].h = 70;

	ButtonClips[ 2 ].x = 0;
	ButtonClips[ 2 ].y = 140;
	ButtonClips[ 2 ].w = 325;
	ButtonClips[ 2 ].h = 70;

	ButtonClips[ 3 ].x = 0;
	ButtonClips[ 3 ].y = 0;
	ButtonClips[ 3 ].w = 0;
	ButtonClips[ 3 ].h = 0;

	ButtonClips[ 4 ].x = 325;
	ButtonClips[ 4 ].y = 0;
	ButtonClips[ 4 ].w = 325;
	ButtonClips[ 4 ].h = 70;

	ButtonClips[ 5 ].x = 325;
	ButtonClips[ 5 ].y = 70;
	ButtonClips[ 5 ].w = 325;
	ButtonClips[ 5 ].h = 70;

	ButtonClips[ 6 ].x = 325;
	ButtonClips[ 6 ].y = 70;
	ButtonClips[ 6 ].w = 325;
	ButtonClips[ 6 ].h = 70;

	ButtonClips[ 7 ].x = 325;
	ButtonClips[ 7 ].y = 140;
	ButtonClips[ 7 ].w = 325;
	ButtonClips[ 7 ].h = 70;

	ButtonClips[ 8 ].x = 0;
	ButtonClips[ 8 ].y = 0;
	ButtonClips[ 8 ].w = 0;
	ButtonClips[ 8 ].h = 0;

	ButtonClips[ 9 ].x = 0;
	ButtonClips[ 9 ].y = 0;
	ButtonClips[ 9 ].w = 0;
	ButtonClips[ 9 ].h = 0;

	DestClips[ 0 ].x = 0;
	DestClips[ 0 ].y = 200;
	DestClips[ 0 ].w = 325;
	DestClips[ 0 ].h = 70;

	DestClips[ 1 ].x = 0;
	DestClips[ 1 ].y = 270;
	DestClips[ 1 ].w = 325;
	DestClips[ 1 ].h = 70;

	DestClips[ 2 ].x = 0;
	DestClips[ 2 ].y = 340;
	DestClips[ 2 ].w = 325;
	DestClips[ 2 ].h = 70;

	DestClips[ 3 ].x = 0;
	DestClips[ 3 ].y = 0;
	DestClips[ 3 ].w = 0;
	DestClips[ 3 ].h = 0;

	DestClips[ 4 ].x = 325;
	DestClips[ 4 ].y = 200;
	DestClips[ 4 ].w = 325;
	DestClips[ 4 ].h = 70;

	DestClips[ 5 ].x = 325;
	DestClips[ 5 ].y = 270;
	DestClips[ 5 ].w = 325;
	DestClips[ 5 ].h = 70;

	DestClips[ 6 ].x = 325;
	DestClips[ 6 ].y = 270;
	DestClips[ 6 ].w = 325;
	DestClips[ 6 ].h = 70;

	DestClips[ 7 ].x = 800-325;
	DestClips[ 7 ].y = 600-140;
	DestClips[ 7 ].w = 325;
	DestClips[ 7 ].h = 70;

	DestClips[ 8 ].x = 0;
	DestClips[ 8 ].y = 0;
	DestClips[ 8 ].w = 0;
	DestClips[ 8 ].h = 0;

	DestClips[ 9 ].x = 0;
	DestClips[ 9 ].y = 0;
	DestClips[ 9 ].w = 0;
	DestClips[ 9 ].h = 0;
}


								