#include "Intro.h"
#include <SDL.h>
#include "Game.h"

// @date 2012-08-07
/*
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
}

void DancingDragon::SetClips()
{
	for( int index = 0; index < 23; index++ )
	{
		DancingDragon::Clips[ index ].x = index * DancingDragon::Width;
		DancingDragon::Clips[ index ].y = 0;
		DancingDragon::Clips[ index ].h = DancingDragon::Height;
		DancingDragon::Clips[ index ].w = DancingDragon::Width;
	}
}

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
}
*/
// sets up the intro where the dudes talk
IntroTalk::IntroTalk( int Surface )
{
	xPos = 100;
	yPos = 200;
	Height = 210;
	Width = 100;
	surface = Surface;
	Frame = 0;
	for( int i = 0; i < 3; i++ )
	{
		srcClips[ i ].x = i * Width;
		srcClips[ i ].y = 0;
		srcClips[ i ].w = Width;
		srcClips[ i ].h = Height;
	}

	CenturionTalks[ 0 ] = "Please all mighty gods help me revenge my family and get my sister back.";
	CenturionTalks[ 1 ] = "I will do anything you ask as long as I get my belowed sister back from those demons.";
	ZeusTalks[ 0 ]		= "My son, I hear your prayers. I will fullfill your wishes, but just so you know your humanity will be lost in the process.";
	CenturionTalks[ 2 ] = "My humanity was lost the minute my family was butchered.";
	CenturionTalks[ 1 ] = "OK, Centurion you will get the powers of an ancient god, the possibility to transform into beasts";
	ZeusTalks[ 2 ]		= "This is however nothing you control and you might turn into the beast at any time along your journey.";
	ZeusTalks[ 3 ]		= "Now go Centurion and rescue your sister before your humanity is totally lost and you no longer care.";
	CenturionTalks[ 3 ] = "I swear to return and claim my humantiy back.";

	CounterWords = 0;
	CounterNextTalker = 0;
	Counter = 0;

	Centurion = true;
	Zeus = false;
	MyDude_Demon = false;
	FirstLine = true;
	SecondLine = false;
	ThirdLine = false;
	Fifth = false;
	Sixth = false;
	Seventh = false;

	Letter = 0;
	LetterHeight = 30;
	LetterWidth = 0;
	y = 20;
	Line = 0;
}

// draws a black background
void IntroTalk::DrawBackground()
{
	SDL_FillRect(gamestate.BackBuffer, NULL, SDL_MapRGB(gamestate.BackBuffer->format, 0,0,0));
	/*
	ParallaxLayer  * MyParaBackGround;
	MyParaBackGround = gamestate.Paralax->getLayer( gamestate.m_srfBlack );

	SDL_Rect scRect = { 0, 0,	MyParaBackGround->m_width, 600 };

	SDL_Rect dtRect = {	0, 0, MyParaBackGround->m_width, 600 };

	SDL_BlitSurface( gamestate.GetSurface( gamestate.m_srfBlack ), &scRect, gamestate.BackBuffer, &dtRect ); 
	*/
}

// all the talking
void IntroTalk::DoTalk()
{
	int IntroState = 0;

	//The color of the font
	SDL_Color textColor = { 255, 255, 255 };
	SDL_Event input;
	
	while( IntroState < 4 )
	{
		DrawBackground();

		if( Centurion )
		{
			
			SDL_Rect destRect = { 0, 0, Width, Height };
			SDL_BlitSurface(	gamestate.GetSurface( surface ), &srcClips[ CENTURION ], 
								gamestate.BackBuffer, &destRect );
								
		}
		if( MyDude_Demon )
		{
			
			SDL_Rect destRect = { 620, 0, Width, Height };
			SDL_BlitSurface(	gamestate.GetSurface( surface ), &srcClips[ MYDUDE_DEMON ], 
								gamestate.BackBuffer, &destRect );
								
		}

		if( Zeus )
		{
			
			SDL_Rect destRect = { 550, 300, Width, Height };
			SDL_BlitSurface(	gamestate.GetSurface( surface ), &srcClips[ ZEUS ], 
								gamestate.BackBuffer, &destRect );
								
		}


		SDL_PollEvent( &input );
		if( input.type == SDL_KEYDOWN )
		{
			switch( input.key.keysym.sym )
			{
			case SDLK_SPACE:
				IntroState = 5;
				break;
			}
		}

		int SpeedOfWords = 25;//500.0f * ( gamestate.dt / 1000 ) ;
		Counter += SpeedOfWords;
		
		//DrawBackground();
		gamestate.DrawAllText();

		if( Counter > 400 )
		{
			Counter = 0;
			switch( IntroState )
			{
			case 0:
				{
					/*
					if( FirstLine )
					{
						
						if( Letter < CenturionTalks[ 0 ].length() )
						{
							++Letter;
						}
						else
						{
							Letter = 0;
							Line = 0;	
							LetterWidth = 0;
							FirstLine = false;
							SecondLine = true;
						}
						
					}
					else
					{
						
						if( Letter < CenturionTalks[ 1 ].length() )
						{
							Letter++;
						}
						else
						{
							IntroState = 1;
							Letter = 0;
							Line = 0;	
							LetterWidth = 0;
							SecondLine = false;
							ThirdLine = true;
							Zeus = true;
						}
						
					}
					*/
					
					if( FirstLine )
					{
						CenturionTalksSlow[ Line ] += CenturionTalks[ 0 ][ Letter ];
						for( int i = 0; i < 5; i++ )
						{
							IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, CenturionTalksSlow[ i ].c_str(), textColor );
							gamestate.apply_surface( 200, i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer );
						}
						if( Letter < CenturionTalks[ 0 ].length() )
						{
							Letter++;
						}
						else
						{
							Letter = 0;
							Line = 0;	
							LetterWidth = 0;
							FirstLine = false;
							SecondLine = true;
						}
					}
					else
					{
						CenturionTalksSlow2[ Line ] += CenturionTalks[ 1 ][ Letter ];
						for( int i = 0; i < 5; i++ )
						{
							IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, CenturionTalksSlow2[ i ].c_str(), textColor );
							gamestate.apply_surface( 200, i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer );
						}
						if( Letter < CenturionTalks[ 1 ].length() )
						{
							Letter++;
						}
						else
						{
							IntroState = 1;
							Letter = 0;
							Line = 0;	
							LetterWidth = 0;
							SecondLine = false;
							ThirdLine = true;
							Zeus = true;
						}
					}

					LetterWidth++;
			
					break;

		
				}
			case 1:
				{
					/*
					if( ThirdLine )
					{
						if( Letter < ZeusTalks[ 0 ].length() )
						{
							Letter++;
						}
						else
						{
							
							Letter = 0;
							Line = 0;	
							LetterWidth = 0;
							ThirdLine = false;
							FourthLine = true;
						}
					}
					else
					{
						if( Letter <CenturionTalks[ 2 ].length() )
						{
							Letter++;
						}
						else
						{
							Letter = 0;
							Line = 0;	
							FourthLine = false;
							LetterWidth = 0;
							Fifth = true;
							IntroState = 2;
						}
					}
					*/
					if( ThirdLine )
					{
						ZeusTalksSlow[ Line ] += ZeusTalks[ 0 ][ Letter ];
						for( int i = 0; i < 5; i++ )
						{
							IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, ZeusTalksSlow[ i ].c_str(), textColor );
							gamestate.apply_surface( 100, 250 + i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer );
						}
						if( Letter < ZeusTalks[ 0 ].length() )
						{
							Letter++;
						}
						else
						{
							
							Letter = 0;
							Line = 0;	
							LetterWidth = 0;
							ThirdLine = false;
							FourthLine = true;
						}
					}
					else
					{
						CenturionTalksSlow3[ Line ] += CenturionTalks[ 2 ][ Letter ];
						for( int i = 0; i < 5; i++ )
						{
							IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, CenturionTalksSlow3[ i ].c_str(), textColor );
							gamestate.apply_surface( 200, i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer );
						}
						if( Letter <CenturionTalks[ 2 ].length() )
						{
							Letter++;
						}
						else
						{
							Letter = 0;
							Line = 0;	
							FourthLine = false;
							LetterWidth = 0;
							Fifth = true;
							IntroState = 2;
						}
					}

					LetterWidth++;
			
					break;

				}
			case 2:
				{
					/*
					if( Fifth )
					{
						if( Letter < ZeusTalks[ 1 ].length() )
						{
							Letter++;
						}
						else
						{
							MyDude_Demon = true;
							Letter = 0;
							Line = 0;	
							LetterWidth = 0;
							Fifth = false;
							Sixth = true;
						}
					}
					else
					{
						if( Letter < ZeusTalks[ 2 ].length() )
						{
							Letter++;
						}
						else
						{
							Letter = 0;
							Line = 0;	
						
							LetterWidth = 0;
							Sixth = false;
							Seventh = true;
							IntroState = 3;
						}
					}
					*/
					if( Fifth )
					{
						ZeusTalksSlow2[ Line ] +=ZeusTalks[ 1 ][ Letter ];
						for( int i = 0; i < 5; i++ )
						{
							IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, ZeusTalksSlow2[ i ].c_str(), textColor );
							gamestate.apply_surface( 100, 250 + i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer );
						}
						if( Letter < ZeusTalks[ 1 ].length() )
						{
							Letter++;
						}
						else
						{
							MyDude_Demon = true;
							Letter = 0;
							Line = 0;	
							LetterWidth = 0;
							Fifth = false;
							Sixth = true;
						}
					}
					else
					{
						ZeusTalksSlow3[ Line ] += ZeusTalks[ 2 ][ Letter ];
						for( int i = 0; i < 5; i++ )
						{
							IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, ZeusTalksSlow3[ i ].c_str(), textColor );
							gamestate.apply_surface( 100, 250 + i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer );
						}
						if( Letter < ZeusTalks[ 2 ].length() )
						{
							Letter++;
						}
						else
						{
							Letter = 0;
							Line = 0;	
						
							LetterWidth = 0;
							Sixth = false;
							Seventh = true;
							IntroState = 3;
						}
					}

					LetterWidth++;
			
					break;



				}
			case 3:
				{
					/*
					if( Seventh )
					{
						if( Letter < ZeusTalks[ 3 ].length() )
						{
							Letter++;
						}
						else
						{
							Letter = 0;
							Line = 0;	
							LetterWidth = 0;
							Seventh = false;
							Eight = true;
						}
					}
					else
					{
						if( Letter < CenturionTalks[ 3 ].length() )
						{
							Letter++;
						}
						else
						{
							Letter = 0;
							Line = 0;	
						
							LetterWidth = 0;
							IntroState = 5;
							
								
						}
					}
					*/
					if( Seventh )
					{
						ZeusTalksSlow4[ Line ] += ZeusTalks[ 3 ][ Letter ];
						for( int i = 0; i < 5; i++ )
						{
							IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, ZeusTalksSlow4[ i ].c_str(), textColor );
							gamestate.apply_surface( 100, 250 + i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer );
						}
						if( Letter < ZeusTalks[ 3 ].length() )
						{
							Letter++;
						}
						else
						{
							Letter = 0;
							Line = 0;	
							LetterWidth = 0;
							Seventh = false;
							Eight = true;
						}
					}
					else
					{
						CenturionTalksSlow4[ Line ] += CenturionTalks[ 3 ][ Letter ];
						for( int i = 0; i < 5; i++ )
						{
							IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, CenturionTalksSlow4[ i ].c_str(), textColor );
							gamestate.apply_surface( 200, i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer );
						}
						if( Letter < CenturionTalks[ 3 ].length() )
						{
							Letter++;
						}
						else
						{
							Letter = 0;
							Line = 0;	
						
							LetterWidth = 0;
							IntroState = 5;		
						}
					}

					LetterWidth++;
			
					
					break;



				}
			}

			if( LetterWidth > 27 )
			{
				y += 100;
				LetterWidth = 0;
				Line++;
			}
		}
		else
		{
			if( FirstLine )
			{
				for( int i = 0; i < 5; i++ )
				{
					IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, CenturionTalksSlow[ i ].c_str(), textColor );
					gamestate.apply_surface( 200, i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer ); 
				}
			}
			else if( SecondLine )
			{
				for( int i = 0; i < 5; i++ )
				{
					IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, CenturionTalksSlow2[ i ].c_str(), textColor );
					gamestate.apply_surface( 200, i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer ); 
				}
			}
			else if( ThirdLine )
			{
				for( int i = 0; i < 5; i++ )
				{
					IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, ZeusTalksSlow[ i ].c_str(), textColor );
					gamestate.apply_surface( 100, 250 + i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer ); 
				}
			}
			else if( FourthLine )
			{
				for( int i = 0; i < 5; i++ )
				{
					IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, CenturionTalksSlow3[ i ].c_str(), textColor );
					gamestate.apply_surface( 200, i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer ); 
				}

			}
			else if( Fifth )
			{
				for( int i = 0; i < 5; i++ )
				{
					IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, ZeusTalksSlow2[ i ].c_str(), textColor );
					gamestate.apply_surface( 100, 250 + i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer ); 
				}
			}
			else if( Sixth )
			{
				for( int i = 0; i < 5; i++ )
				{
					IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, ZeusTalksSlow3[ i ].c_str(), textColor );
					gamestate.apply_surface( 100, 250 + i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer ); 
				}
			}
			else if( Seventh )
			{
				for( int i = 0; i < 5; i++ )
				{
					IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, ZeusTalksSlow4[ i ].c_str(), textColor );
					gamestate.apply_surface( 100, 250 + i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer ); 
				}
			}
			else if( Eight )
			{
				for( int i = 0; i < 5; i++ )
				{
					IntroSurfaces[ 0 ] = TTF_RenderText_Solid( gamestate.font, CenturionTalksSlow4[ i ].c_str(), textColor );
					gamestate.apply_surface( 200, i * 40, IntroSurfaces[ 0 ], gamestate.BackBuffer ); 
				}
			}

	
		}

		gamestate.FLIP();
	}

	gamestate.GameCondition = GS_LEVEL1;
}
	

	

