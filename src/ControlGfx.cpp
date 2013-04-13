#include "ControlGfx.h"
#include "Game.h"

ControlGfx Gfx;

ControlGfx::ControlGfx()
{
	WhiteRGB.r = 255;
	WhiteRGB.g = 255;
	WhiteRGB.b = 255;
	BlackRGB.r = 255;
	BlackRGB.g = 255;
	BlackRGB.b = 255;
	return;
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

	//if something went wrong
	if( loadedimage != NULL )
	{
		//create an optimized image 
		optimizedImage = SDL_DisplayFormat( loadedimage );

		//free old image
		SDL_FreeSurface( loadedimage );
	}

	if(optimizedImage != NULL)
	{
		SDL_SetColorKey(optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, r, g, b ) );
	}
	
	int index = findAvailableIndex();
	if( index == -1 )
	{
		return -1;
	}

	m_surfaceList[ index ] = optimizedImage;
	return index;
}

void ControlGfx::stretchPicToBackBuffer( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect )	
{			

	int srcWidth = srcRect.w - srcRect.x;
	int srcHeight = srcRect.h - srcRect.y,
		DestWidth = destRect.w - destRect.x,
		DestHeight = destRect.h - destRect.y;

	SDL_LockSurface( gamestate.BackBuffer );
	SDL_LockSurface( m_surfaceList[ layer->m_surface ] );

	int dstPitch = gamestate.BackBuffer->pitch;
	int pitch = m_surfaceList[ layer->m_surface ]->pitch;

	DWORD * dst = ( DWORD * )gamestate.BackBuffer->pixels;

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

	SDL_UnlockSurface( gamestate.BackBuffer );
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
		SDL_BlitSurface(m_surfaceList[index], &destRect, gamestate.screen, &srcRect );
		/*m_lpddsBackbuffer->Blt( &destRect, m_surfaceList[index], &srcRect, DDBLT_WAIT|DDBLT_KEYSRC, 0 );*/
	else
		SDL_BlitSurface(m_surfaceList[index], &destRect, gamestate.screen, &srcRect );

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
	SDL_LockSurface( gamestate.screen );
	SDL_LockSurface( gamestate.BackBuffer );

	int dstPitch = gamestate.screen->pitch;
	int pitch = gamestate.BackBuffer->pitch;

	DWORD * dst = ( DWORD * )gamestate.screen->pixels;
	DWORD * src = ( DWORD * )gamestate.BackBuffer->pixels;

	float scaleWidth = gamestate.BackBuffer->w / ( float )destRect.w;
	float scaleHeight = gamestate.BackBuffer->h / ( float )destRect.h; 


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

	SDL_UnlockSurface( gamestate.screen );
	SDL_UnlockSurface( gamestate.BackBuffer );
}

// ----------------------------------------------------------------------------
// GetSurface() - gives backbuffer to destination buffer streches and all
// ----------------------------------------------------------------------------
void ControlGfx::FLIP()
{
	SDL_Rect srcRect = { 0, 0, gamestate.BackBuffer->w, gamestate.BackBuffer->h };
	SDL_Rect destRect = { 0, 0, gamestate.SCREEN_WIDTH, gamestate.SCREEN_HEIGHT };
					
	//gamestate.PasteScreenToAnother( srcRect, destRect );
	Gfx.PasteScreenToAnother( srcRect, destRect);
	//flips screen
	if( SDL_Flip( gamestate.screen ) == -1)
	{
		gamestate.GameOK = false;
	}
}

void ControlGfx::stretchBlit( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect )	
{			
	SDL_LockSurface( gamestate.BackBuffer );
	SDL_LockSurface( m_surfaceList[ layer->m_surface ] );

	int dstPitch = gamestate.BackBuffer->pitch;
	int pitch = m_surfaceList[ layer->m_surface ]->pitch;

	DWORD * dst = ( DWORD * )gamestate.BackBuffer->pixels;

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

	SDL_UnlockSurface( gamestate.BackBuffer );
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

