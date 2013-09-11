#include "ControlGfx.h"
#include "Game.h"
#include "Animals.h"
#include "Bullets.h"
#include "CBoss.h"

ControlGfx Gfx;

ControlGfx::ControlGfx()
{
	if (TTF_Init() == -1) 
	{
		printf("Unable to initialize SDL_ttf: %s \n", TTF_GetError());
	}
	else
	{
		 printf("initialize SDL_ttf: %s \n", TTF_GetError());
	}

	DefaultFont = TTF_OpenFont("cour.ttf", 14);
	if (Gfx.DefaultFont == NULL){
      printf("Unable to load font: %s %s \n", "cour.ttf", TTF_GetError());
      // Handl	e the error here.
    }

	WhiteRGB.r = 255;
	WhiteRGB.g = 255;
	WhiteRGB.b = 255;
	BlackRGB.r = 0;
	BlackRGB.g = 0;
	BlackRGB.b = 0;
}

// loads image with chosen value to not show
int ControlGfx::Load_imageAlpha( std::string filename, int r, int g, int b )
{
	//temp storage for the image loaded
	SDL_Surface * loadedimage = NULL;

	//optimized image for storage and flipping
	SDL_Surface * optimizedImage = NULL;

	//load image 
	loadedimage = IMG_Load( filename.c_str() );
	int index = findAvailableIndex();
	//if something went wrong
	if( loadedimage != NULL )
	{
		//create an optimized image 
		optimizedImage = SDL_DisplayFormatAlpha( loadedimage );
		
		if( index == -1 )
		{
			return -1;
		}

		m_surfaceList[ index ] =optimizedImage;
		//free old image
		SDL_FreeSurface( loadedimage );
	}
	else
	{
		MessageBox(NULL,filename.c_str(),"Failed Loading",MB_OK);
	}

	//if(optimizedImage != NULL)
	//{
	//	SDL_SetColorKey(optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, r, g, b ) );
	//}
	

	return index;
}

void ControlGfx::stretchPicToBackBuffer( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect )	
{			

	int srcWidth = srcRect.w - srcRect.x;
	int srcHeight = srcRect.h - srcRect.y,
		DestWidth = destRect.w - destRect.x,
		DestHeight = destRect.h - destRect.y;

	SDL_LockSurface( Gfx.BackBuffer );
	SDL_LockSurface( m_surfaceList[ layer->m_surface ] );

	int dstPitch = Gfx.BackBuffer->pitch;
	int pitch = m_surfaceList[ layer->m_surface ]->pitch;

	DWORD * dst = ( DWORD * )Gfx.BackBuffer->pixels;

	DWORD * src = ( DWORD * )m_surfaceList[ layer->m_surface ]->pixels;

	float scaleWidth = srcWidth / ( float )DestWidth;
	float scaleHeight = srcHeight / ( float )DestHeight; 


	float fSrcX = srcRect.x,
		  fSrcY = srcRect.y;

	for(int y = destRect.y;  y < destRect.y + destRect.h; y++ )
	{
		fSrcX = 0;

		for(int x = destRect.x ;  x < destRect.x + destRect.w ; x++)
		{
			dst[ ( y * dstPitch / 4) + ( x ) ] = src[ int( ( fSrcY ) * ( pitch / 4 ) + int( fSrcX ) )];

			fSrcX += scaleWidth;
		}

		fSrcY += scaleHeight;	
	}

	SDL_UnlockSurface( Gfx.BackBuffer );
	SDL_UnlockSurface( m_surfaceList[ layer->m_surface ] );

}

// --------------------------------------------------------------------------------------
// blit() - blits offscreen surface to (xpos,ypos) on backbuffer
// --------------------------------------------------------------------------------------
void ControlGfx::blit( int index, int xpos, int ypos, bool transparent )
{
	// Calc rects
	SDL_Rect srcRect = { 0, 0, m_surfaceList[ index ]->w, m_surfaceList[ index ]->h };
	SDL_Rect destRect = { xpos, ypos, xpos+m_surfaceList[ index ]->w, ypos+m_surfaceList[ index ]->h };


	// Blit!
	if( transparent )
		SDL_BlitSurface(m_surfaceList[index], &destRect, Gfx.screen, &srcRect );
		/*m_lpddsBackbuffer->Blt( &destRect, m_surfaceList[index], &srcRect, DDBLT_WAIT|DDBLT_KEYSRC, 0 );*/
	else
		SDL_BlitSurface(m_surfaceList[index], &destRect, Gfx.screen, &srcRect );

}

// ----------------------------------------------------------------------------
// findAvailableIndex() - find free slot in surface list and return its index
// ----------------------------------------------------------------------------
int ControlGfx::findAvailableIndex()
{
	for( int i = 0; i < MAX_SURFACES; i++ )
	{
		if( !m_surfaceList[i] )
		{
			return i;
		}
	}

	// None available
	return -1;
}

SDL_Surface* ControlGfx::GetSurface(int index)
{
	return m_surfaceList[index];
}

void ControlGfx::PasteScreenToAnother( SDL_Rect srcRect, SDL_Rect destRect )
{
	SDL_LockSurface( Gfx.screen );
	SDL_LockSurface( Gfx.BackBuffer );

	int dstPitch = Gfx.screen->pitch;
	int pitch = Gfx.BackBuffer->pitch;

	DWORD * dst = ( DWORD * )Gfx.screen->pixels;
	DWORD * src = ( DWORD * )Gfx.BackBuffer->pixels;

	float scaleWidth = Gfx.BackBuffer->w / ( float )destRect.w;
	float scaleHeight = Gfx.BackBuffer->h / ( float )destRect.h; 


	float fSrcX = 0.0f,
		  fSrcY = 0.0f;

	for(int y = destRect.y;  y < destRect.y + destRect.h; y++ )
	{
		fSrcX = 0.0f;

		for(int x = destRect.x ;  x < destRect.x + destRect.w ; x++)
		{
			dst[ (y * dstPitch / 4) + (x) ] = src[ int(fSrcY) * (pitch / 4) + int(fSrcX) ];

			fSrcX += scaleWidth;
		}

		fSrcY += scaleHeight;	
	}

	SDL_UnlockSurface( Gfx.screen );
	SDL_UnlockSurface( Gfx.BackBuffer );
}

// ----------------------------------------------------------------------------
// GetSurface() - gives backbuffer to destination buffer streches and all
// ----------------------------------------------------------------------------
bool ControlGfx::FLIP()
{
	SDL_Rect srcRect = { 0, 0, Gfx.BackBuffer->w, Gfx.BackBuffer->h };
	SDL_Rect destRect = { 0, 0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h };
					
	//gamestate.PasteScreenToAnother( srcRect, destRect );
	Gfx.PasteScreenToAnother( srcRect, destRect);
	//flips screen
	if( SDL_Flip( Gfx.screen ) == -1)
	{
		//gamestate.GameOK = false;
		return false;
	}
	return true;
}

void ControlGfx::stretchBlit( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect )	
{			
	SDL_LockSurface( Gfx.BackBuffer );
	SDL_LockSurface( m_surfaceList[ layer->m_surface ] );

	int dstPitch = Gfx.BackBuffer->pitch;
	int pitch = m_surfaceList[ layer->m_surface ]->pitch;

	DWORD * dst = ( DWORD * )Gfx.BackBuffer->pixels;

	DWORD * src = ( DWORD * )m_surfaceList[ layer->m_surface ]->pixels;

	float scaleWidth = srcRect.w / ( float )destRect.w;
	float scaleHeight = srcRect.h / ( float )destRect.h; 


	float fSrcX = srcRect.x,
		  fSrcY = srcRect.y;

	for(int y = destRect.y;  y < destRect.y + destRect.h; y++ )
	{
		fSrcX = srcRect.x;

		for(int x = destRect.x ;  x < destRect.x + destRect.w ; x++)
		{
			dst[ (y * dstPitch / 4) + (x) ] = src[ int((fSrcY) * (pitch / 4) + int(fSrcX) )];

			fSrcX += scaleWidth;
		}
		fSrcY += scaleHeight;	
	}

	SDL_UnlockSurface( Gfx.BackBuffer );
	SDL_UnlockSurface( m_surfaceList[ layer->m_surface ] );

}

void ControlGfx::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

void ControlGfx::DrawParallaxLayers()
{
	if( gamestate.State != GAME_BOSS_STATE && gamestate.State != GAME_OUTRO_STATE )
	{
		/*
		if( BCPlayer.xVel >= STARTSCROLLING - 50 )
		{
			// Updating the background to scroll when character is moving
			if( BCPlayer.isMovingRight )
			{
				gamestate.m_paralax += 20;
			}
			else if( BCPlayer.isMovingLeft )
			{
				gamestate.m_paralax -= 20;
			}
		}
		*/
		gamestate.CreateAll();
	}
	else
	{
		//if( !BossStart )
		//{
		//	//BCPlayer.demonHunter = true;
		//	//BCPlayer.SmallHunter = false;
		//	gamestate.pBoss = gamestate.CreateBoss( SDL_GetVideoSurface()->w - 180, GROUND_Y - 210, m_srfBoss );
		//	BossStart = true;
		//}
	}

		//// Draw parallax layers
		ParallaxLayer  * MyParaBackGround;
		MyParaBackGround = gamestate.ParallaxBG->getLayer( 0 );

		SDL_Rect scRect = { 0, 0,	MyParaBackGround->m_width, 
									MyParaBackGround->m_height };

		SDL_Rect dtRect = {	0, 0, MyParaBackGround->DW, MyParaBackGround->DH };
												
		SDL_BlitSurface( Gfx.GetSurface(MyParaBackGround->m_surface), &scRect, Gfx.BackBuffer, &dtRect );
		//SDL_BlitSurface( m_surfaceList[ MyParaBackGround->m_surface ], &scRect, gamestate.BackBuffer, &dtRect ); 

		//gamestate.stretchPicToBackBuffer( MyParaBackGround, scRect, dtRect );

		int x = 0;
		for( int i = 1; i < gamestate.ParallaxBG->getLayerCount(); ++i )
		{		
			// Calc rects
			MyParaBackGround = gamestate.ParallaxBG->getLayer( i );
			if( MyParaBackGround->m_surface == gamestate.m_srfClouds )
			{
				MyParaBackGround->AnimClouds += 100.0f * gamestate.DeltaTime;

				//////// Calc parallax position
				x = (int)( MyParaBackGround->m_parallax * (float)( +MyParaBackGround->AnimClouds ) );  
				if( x < 0 )	// neg -> pos
				{
					x *= -1;	// invert sign, because % only works with positive integers
					x = MyParaBackGround->m_width - (x % MyParaBackGround->m_width);
				}
				else
				{
					x %= MyParaBackGround->m_width;
				}

				x -= MyParaBackGround->m_width;	// move one back
			}
			else
			{

				//////// Calc parallax position
				x = (int)( MyParaBackGround->m_parallax * (float)( +gamestate.Parallax ) );  
				if( x < 0 )	// neg -> pos
				{
					x *= -1;	// invert sign, because % only works with positive integers
					x = MyParaBackGround->m_width - (x % MyParaBackGround->m_width);
				}
				else
				{
					x %= MyParaBackGround->m_width;
				}

				x -= MyParaBackGround->m_width;	// move one back
			}

			for( int i = 0; i < 2; i++ )
			{
				SDL_Rect sourceRect = { 0 + x, MyParaBackGround->m_surfaceYOffset,
										MyParaBackGround->m_width, MyParaBackGround->m_height };

				SDL_Rect destinationRect = {	MyParaBackGround->DX, MyParaBackGround->DY, 
												MyParaBackGround->DW, MyParaBackGround->DH };

				SDL_BlitSurface( Gfx.GetSurface( MyParaBackGround->m_surface ), &sourceRect, Gfx.BackBuffer, &destinationRect );

				//SDL_BlitSurface( m_surfaceList[ MyParaBackGround->m_surface ], &sourceRect, gamestate.BackBuffer, &destinationRect ); 
				
				
				x += MyParaBackGround->m_width;
			}
			MyParaBackGround->HowFarGone = MyParaBackGround->Xpos - MyParaBackGround->m_width;

		}
						
		//Scrolling the map
		gamestate.Parallax += 0.0001f * gamestate.DeltaTime;
		if( gamestate.Parallax > Gfx.GetSurface( gamestate.m_srfCity )->w );
		//gamestate.State = GAME_OUTRO_STATE;
}

void ControlGfx::DrawSprite()
{
		BCPlayer.Update();

		//Gfx.SetAlpha( demon.Surface, 255 );

		//Gfx.SetAlpha( demon.Surface, 255 );
		SDL_BlitSurface(	Gfx.GetSurface( BCPlayer._Surface ), 
			&BCPlayer.AnimationArrays[ BCPlayer.GetState() ][ BCPlayer.Animate() ],
			Gfx.BackBuffer, &BCPlayer.GetPosition() );

		//gamestate.PreviousFrame = gamestate.CurrentFrame;
}
// ----------------------------------------------------------------------------
// DrawObjects() - Draws all objects, coffins, health etc.
// ----------------------------------------------------------------------------
void ControlGfx::DrawObjects()
{
	if( gamestate.State == GAME_BOSS_STATE )
	{
		ObjectController.DrawObjects();
	}
	else
	{						  
		BCPlayer.Update();
		AnimalController.Draw_Animals();
		BulletController.Draw_Bullets();
		EnemyController.Update();
		EnemyController.Draw_Enemies();
		ObjectController.DrawObjects();
	}	
}

// ----------------------------------------------------------------------------
// DrawBoss() - hmmm.
// ----------------------------------------------------------------------------
void ControlGfx::DrawBoss()
{
	//SDL_Rect srcRect = { 0, 0, 150, 300 };
	//gamestate.pBoss->UpdateFrame();
	//				SDL_BlitSurface( Gfx.GetSurface( gamestate.pBoss->Surface ), 
	//				&gamestate.pBoss->GetClips( gamestate.pBoss->GetFrame() ),
	//							gamestate.BackBuffer, &srcRect );
	//Sleep(100);
	//gamestate.pBoss->UpdateBoss();
	gBoss.Update();
}

// ----------------------------------------------------------------------------
// DrawBackgroundBlack - draws a background black with the size of screen
// ----------------------------------------------------------------------------
void ControlGfx::DrawBackgroundBlack()
{
	if( gamestate.State == GAME_OUTRO_STATE )
	{
		SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0,0,0,0));
		/*
		ParallaxLayer  * MyParaBackGround;
		MyParaBackGround = gamestate.Paralax->getLayer( gamestate.m_srfBlack );

		SDL_Rect scRect = { 0, 0,	100, 70 };
									
		SDL_Rect dtRect = {	600, 530, 100, 50 };

		SDL_BlitSurface( gamestate.GetSurface( gamestate.m_srfBlack ), &scRect, gamestate.BackBuffer, &dtRect ); 
		*/
	}
	else
	{
		SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0,0,0,0));
		/*
		ParallaxLayer  * MyParaBackGround;
		MyParaBackGround = gamestate.Paralax->getLayer( gamestate.m_srfBlack );

		SDL_Rect scRect = { 0, 0,	MyParaBackGround->m_width, 
									600 };

		SDL_Rect dtRect = {	0, 0, MyParaBackGround->m_width, 600 };

		SDL_BlitSurface( gamestate.GetSurface( gamestate.m_srfBlack ), &scRect, gamestate.BackBuffer, &dtRect );
		*/
	}
}

void ControlGfx::DrawScore()
{
	TTF_Font * ScoreTTF;
	SDL_Rect offset;
	SDL_Surface * SrfScore;
	static int iScore = 0;
	SrfScore = TTF_RenderText_Solid( Gfx.DefaultFont, std::to_string(iScore++).c_str(), Gfx.WhiteRGB );
	Gfx.apply_surface( 300, 0, SrfScore, Gfx.BackBuffer );
}

void ControlGfx::SetAlpha( int _SurfaceIndex, int _Opacity )
{
	SDL_SetAlpha( Gfx.GetSurface( _SurfaceIndex ), SDL_SRCALPHA | SDL_RLEACCEL, _Opacity );
}