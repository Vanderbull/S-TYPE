#include "ControlGfx.h"
#include "Game.h"
#include "Enemies\BlueShip.h"
#include "Enemies\Cubes.h"
#include "Enemies\Powerup.h"
#include "Enemies\BlueFish.h"
#include "Bullets.h"
#include "ParticleController\Particle.h"

// 1. this should go into every .cpp , after all header inclusions
#ifdef _WIN32
#ifdef _DEBUG
   #include <crtdbg.h>
   #undef THIS_FILE
   static char THIS_FILE[] = __FILE__;
   #define new       new( _NORMAL_BLOCK, __FILE__, __LINE__)
   #define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif

ControlGfx Gfx;

ControlGfx::ControlGfx()
{
    Particle p(Vector3D(1920 / 2, 1080 / 2, 0.0f));

	if (TTF_Init() == -1) 
	{
		printf("Unable to initialize SDL_ttf: %s \n", TTF_GetError());
	}
	else
	{
		 printf("initialize SDL_ttf: %s \n", TTF_GetError());
	}

	// Loading fonts
    DefaultFont = TTF_OpenFont("assets/fonts/Mecha.ttf", 14);
	if (Gfx.DefaultFont == NULL){
      printf("Unable to load font: %s %s \n", "assets/fonts/Mecha.ttf", TTF_GetError());
    }
    ScoreFont = TTF_OpenFont("assets/fonts/Mecha.ttf", 30);
    if (Gfx.ScoreFont == NULL){
        printf("Unable to load font: %s %s \n", "assets/fonts/Mecha.ttf", TTF_GetError());
    }

    const SDL_version *linked_version = TTF_Linked_Version();
    SDL_version compiled_version;
    SDL_TTF_VERSION(&compiled_version);

    std::cout << "Linked version:\n"
        << linked_version->major << "." << linked_version->minor << "." << linked_version->patch;

    std::cout << "Compiled version:\n"
        << compiled_version.major << "." << compiled_version.minor << "." << compiled_version.patch << std::endl << std::endl;

	WhiteRGB.r = 255;
	WhiteRGB.g = 255;
	WhiteRGB.b = 255;
	BlackRGB.r = 0;
	BlackRGB.g = 0;
	BlackRGB.b = 0;

	m_SurfaceCollection["Screen"];
	m_SurfaceCollection["BackBuffer"];
	m_SurfaceCollection["srfText"];
}

// loads image with chosen value to not show
int ControlGfx::Load_imageAlpha( std::string filename, int r = 0, int g = 0, int b = 0 )
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
		m_SurfaceCollection[filename] = *optimizedImage;
		//free old image
		SDL_FreeSurface( loadedimage );
	}
	else
	{
		//MessageBox(NULL,filename.c_str(),"Failed Loading",MB_OK);
	}

	if(optimizedImage != NULL)
	{
		SDL_SetColorKey(optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, r, g, b ) );
	}
	

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
	SDL_Rect srcRect = { 0, 0, (Uint16)Gfx.BackBuffer->w, (Uint16)Gfx.BackBuffer->h };
	SDL_Rect destRect = { 0, 0, (Uint16)SDL_GetVideoSurface()->w, (Uint16)SDL_GetVideoSurface()->h };
					
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

void ControlGfx::apply_surface( Sint16 x, Sint16 y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
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
	if( gamestate.GameState.top() != GAME_BOSS_STATE || gamestate.GameState.top() != GAME_OUTRO_STATE )
	{
		gamestate.CreateAll();
	}

	//// Draw parallax layers
		ParallaxLayer  * MyParaBackGround;
		MyParaBackGround = gamestate.ParallaxBG->getLayer( 0 );

		SDL_Rect scRect = { 0, 0,	MyParaBackGround->m_width, 
									MyParaBackGround->m_height };

		SDL_Rect dtRect = {	0, 0, MyParaBackGround->DW, MyParaBackGround->DH };
												
		//SDL_BlitSurface( Gfx.GetSurface(MyParaBackGround->m_surface), &scRect, Gfx.BackBuffer, &dtRect );
        SDL_BlitSurface(Gfx.GetSurface(MyParaBackGround->m_surface), 0, Gfx.BackBuffer, 0);
		//SDL_BlitSurface( m_surfaceList[ MyParaBackGround->m_surface ], &scRect, gamestate.BackBuffer, &dtRect ); 

		//gamestate.stretchPicToBackBuffer( MyParaBackGround, scRect, dtRect );

		int x = 0;
		for( int i = 1; i < gamestate.ParallaxBG->getLayerCount(); ++i )
		{		
			// Calc rects
			MyParaBackGround = gamestate.ParallaxBG->getLayer( i );
			if( MyParaBackGround->m_surface == gamestate.m_srfBackdrop )
			{
				MyParaBackGround->AnimClouds += 0.0003f * gamestate.DeltaTime;

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
                SDL_BlitSurface(Gfx.GetSurface(MyParaBackGround->m_surface), &sourceRect, Gfx.BackBuffer, &destinationRect);

				//SDL_BlitSurface( m_surfaceList[ MyParaBackGround->m_surface ], &sourceRect, gamestate.BackBuffer, &destinationRect ); 
				
				
				x += MyParaBackGround->m_width;
			}
			MyParaBackGround->HowFarGone = MyParaBackGround->Xpos - MyParaBackGround->m_width;

		}
						
		//Scrolling the map
		gamestate.Parallax += SpaceScrollingSpeed * gamestate.DeltaTime;
}

// Draws the spaceship
void ControlGfx::DrawSprite()
{
    Spaceship.Update();
    Spaceship.SetCollisionBox(Spaceship.GetPosition().x, Spaceship.GetPosition().y, 64, 64);

    SDL_BlitSurface(Gfx.GetSurface(Spaceship._SurfaceID),
        &Spaceship.AnimationArrays[0][Spaceship.Animate()],
        Gfx.BackBuffer, &Spaceship.GetPosition());
}

// ----------------------------------------------------------------------------
// DrawObjects() - Draws all objects
// ----------------------------------------------------------------------------
void ControlGfx::DrawObjects()
{
    BlueShipController.DrawBlueShip();
	//CubeController.DrawCubes();
	BlueFishController.DrawBlueFish();
	BulletController.Draw_Bullets();
	ObjectController.DrawObjects();
	PowerupController.DrawPowerup();
    Spaceship.Update();
}

// ----------------------------------------------------------------------------
// DrawBackgroundBlack - draws a background black with the size of screen
// ----------------------------------------------------------------------------
void ControlGfx::DrawBackgroundBlack()
{
 	SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0,0,0,0));
}

void ControlGfx::DrawScore(unsigned int xCoord,unsigned int yCoord,int iScore)
{
    p.checkEdges(1520,880);
    p.Update();
    p.applyForce(Vector3D(2 * (double)rand() / (double)RAND_MAX - 1, 2 * (double)rand() / (double)RAND_MAX - 1, 0));
    p.Display();
	SDL_Surface * SrfScore;

    SrfScore = TTF_RenderText_Solid(Gfx.DefaultFont, "POWER LEVEL: ", Gfx.WhiteRGB);
    Gfx.apply_surface(0, 120, SrfScore, Gfx.BackBuffer);
    SrfScore = TTF_RenderText_Solid(Gfx.DefaultFont, std::to_string(PowerLevel).c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(100, 120, SrfScore, Gfx.BackBuffer);

    SrfScore = TTF_RenderText_Solid(Gfx.DefaultFont, "POWER LEVEL(NEW): ", Gfx.WhiteRGB);
    Gfx.apply_surface(0, 140, SrfScore, Gfx.BackBuffer);
    SrfScore = TTF_RenderText_Solid(Gfx.DefaultFont, std::to_string(Spaceship.GetPowerLevel()).c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(100, 140, SrfScore, Gfx.BackBuffer);

    SrfScore = TTF_RenderText_Solid(Gfx.DefaultFont, "PARTICLE(X): ", Gfx.WhiteRGB);
    Gfx.apply_surface(0, 160, SrfScore, Gfx.BackBuffer);
    SrfScore = TTF_RenderText_Solid(Gfx.DefaultFont, std::to_string(p.GetX()).c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(p.GetX(), p.GetY(), SrfScore, Gfx.BackBuffer);

    SrfScore = TTF_RenderText_Solid(Gfx.DefaultFont, "PARTICLE(Y): ", Gfx.WhiteRGB);
    Gfx.apply_surface(0, 180, SrfScore, Gfx.BackBuffer);
    SrfScore = TTF_RenderText_Solid(Gfx.DefaultFont, std::to_string(p.GetY()).c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(100, 180, SrfScore, Gfx.BackBuffer);
	SDL_FreeSurface(SrfScore);
}

void ControlGfx::SetAlpha( int _SurfaceIndex, int _Opacity )
{
	SDL_SetAlpha( Gfx.GetSurface( _SurfaceIndex ), SDL_SRCALPHA | SDL_RLEACCEL, (Uint8)_Opacity );
}

void ControlGfx::RenderText(std::string _Text, int _x , int _y )
{
    int w = 0;
    int h = 0;

    if ((TTF_SizeText(Gfx.DefaultFont, _Text.c_str(), &w, &h) != -1))
    {
        // Print out the width and height of the string if I render it with myFont
        std::cout << "Width : " << w << "\nHeight: " << h << std::endl;
    }
    else {
        // Error...
    }

    if ((TTF_SizeText(Gfx.DefaultFont, "Version 1.0 Beta", &w, &h) != -1))
    {
        // Print out the width and height of the string if I render it with myFont
        std::cout << "Width : " << w << "\nHeight: " << h << std::endl;
    }
    else {
        // Error...
    }
    Gfx.apply_surface(Gfx.BackBuffer->w - w, Gfx.BackBuffer->h - h, TTF_RenderText_Solid(Gfx.DefaultFont, "Version 1.0 Beta", Gfx.WhiteRGB), Gfx.BackBuffer);


    SDL_Surface * SrfText;
    SrfText = TTF_RenderText_Solid(Gfx.DefaultFont, _Text.c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface( (Gfx.BackBuffer->w - w) / 2, (Gfx.BackBuffer->h - h) - _y, SrfText, Gfx.BackBuffer);
    SDL_FreeSurface(SrfText);
}

void ControlGfx::RenderPowerupText(std::string _Text, int _x, int _y)
{
    int w = 0;
    int h = 0;

    if ((TTF_SizeText(Gfx.DefaultFont, _Text.c_str(), &w, &h) != -1))
    {
    }
    else {
        // Error...
    }

    SDL_Surface * SrfText;
    SrfText = TTF_RenderText_Solid(Gfx.DefaultFont, _Text.c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface( _x - w, _y - h, SrfText, Gfx.BackBuffer);
    SDL_FreeSurface(SrfText);
}