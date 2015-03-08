#include "ControlGfx.h"
#include "../Game.h"
#include "../Enemies/PurpleShip.h"
#include "../Enemies/Robotnic.h"
#include "../Enemies/Powerup.h"
#include "../Enemies/BlueFish.h"
#include "../Objects/Bullets.h"
#include "../ParticleController/Particle.h"
#include "../fps/fps.h"

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
    logger.write(__LINE__, __FUNCTION__);

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
    TitleFont = TTF_OpenFont("assets/fonts/Mecha.ttf", 60);
    if (Gfx.TitleFont == NULL){
        printf("Unable to load font: %s %s \n", "assets/fonts/Mecha.ttf", TTF_GetError());
    }
    GameoverFont = TTF_OpenFont("assets/fonts/Mecha.ttf", 240);
    if (Gfx.GameoverFont == NULL){
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
    logger.write(__LINE__, __FUNCTION__);

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
        loadedimage = NULL;
	}
	else
	{
		MessageBox(NULL,filename.c_str(),"Failed Loading",MB_OK);
	}

	if(optimizedImage != NULL)
	{
		SDL_SetColorKey(optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, r, g, b ) );
	}
	
	return index;
}

// ----------------------------------------------------------------------------
// findAvailableIndex() - find free slot in surface list and return its index
// ----------------------------------------------------------------------------
int ControlGfx::findAvailableIndex()
{
    logger.write(__LINE__, __FUNCTION__);

	for( int i = 0; i < MAX_SURFACES; i++ )
	{
		if( !m_surfaceList[i] )
		{
			return i;
		}
	}

	// No index available
	return -1;
}

SDL_Surface* ControlGfx::GetSurface(int index)
{
    logger.write(__LINE__, __FUNCTION__);

	return m_surfaceList[index];
}

void ControlGfx::PasteScreenToAnother( SDL_Rect srcRect, SDL_Rect destRect )
{
    //logger.write(__LINE__, __FUNCTION__);

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
    //logger.write(__LINE__, __FUNCTION__);

    stringstream ss;
    ss << framespersecond;
    string str = "FPS: ";
    str.append(ss.str());


    SDL_Surface * SrfText;
    SrfText = TTF_RenderText_Solid(Gfx.DefaultFont, str.c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(0, 0, SrfText, Gfx.BackBuffer);

	SDL_Rect srcRect = { 0, 0, (Uint16)Gfx.BackBuffer->w, (Uint16)Gfx.BackBuffer->h };
	SDL_Rect destRect = { 0, 0, (Uint16)SDL_GetVideoSurface()->w, (Uint16)SDL_GetVideoSurface()->h };
					
	Gfx.PasteScreenToAnother( srcRect, destRect);

	if( SDL_Flip( Gfx.screen ) == -1)
	{
		return false;
	}
    else
    { 
	    return true;
    }
}

void ControlGfx::apply_surface( Sint16 x, Sint16 y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    logger.write(__LINE__, __FUNCTION__);

    SDL_Rect offset;
    
    offset.x = x;
    offset.y = y;
    
    // Applies the image from source upon the destination source
    SDL_BlitSurface( source, clip, destination, &offset );
    SDL_FreeSurface(source);
    source = NULL;
}

// Draws the spaceship
void ControlGfx::DrawSprite()
{
    logger.write(__LINE__, __FUNCTION__);

    Spaceship.Update();
    Spaceship.SetCollisionBox(Spaceship.GetPosition().x, Spaceship.GetPosition().y, 64, 64);

    
    SDL_BlitSurface(Gfx.GetSurface(Spaceship._SurfaceID),
        &Spaceship.AnimationArrays[0][Spaceship.Animate()],
        Gfx.BackBuffer, &Spaceship.GetPosition());
    

    stringstream ss;
    ss << Spaceship._SpawnTimer;
    string str = "";
    str.append(ss.str());


    SDL_Surface * SrfText;
    SrfText = TTF_RenderText_Solid(Gfx.DefaultFont, str.c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(100, 100, SrfText, Gfx.BackBuffer);
}

// ----------------------------------------------------------------------------
// DrawObjects() - Draws all objects
// ----------------------------------------------------------------------------
void ControlGfx::DrawObjects()
{
    logger.write(__LINE__, __FUNCTION__);

    PurpleShipController.DrawPurpleShip();
    RobotnicController.DrawRobotnic();
	BlueFishController.DrawBlueFish();
	BulletController.Draw_Bullets();
    OctoBulletController.DrawOctoBullets();
	ObjectController.DrawObjects();
	PowerupController.DrawPowerup();
    Spaceship.Update();
}

// ----------------------------------------------------------------------------
// DrawBackgroundBlack - draws a background black with the size of screen
// ----------------------------------------------------------------------------
void ControlGfx::DrawBackgroundBlack()
{
    logger.write(__LINE__, __FUNCTION__);

 	SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0,0,0,0));
}

void ControlGfx::DrawScore(unsigned int /*xCoord*/,unsigned int /*yCoord*/,int /*iScore*/)
{
    logger.write(__LINE__, __FUNCTION__);

   /* p.checkEdges(1520,880);
    p.Update();
    p.applyForce(Vector3D(2 * (double)rand() / (double)RAND_MAX - 1, 2 * (double)rand() / (double)RAND_MAX - 1, 0));
    p.Display(); */
    /*
	SDL_Surface * SrfScore;

    SrfScore = TTF_RenderText_Solid(Gfx.DefaultFont, "POWER LEVEL: ", Gfx.WhiteRGB);
    Gfx.apply_surface(0, 120, SrfScore, Gfx.BackBuffer);
    SrfScore = TTF_RenderText_Solid(Gfx.DefaultFont, std::to_string(PowerLevel).c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(100, 120, SrfScore, Gfx.BackBuffer);

    SrfScore = TTF_RenderText_Solid(Gfx.DefaultFont, "POWER LEVEL(NEW): ", Gfx.WhiteRGB);
    Gfx.apply_surface(0, 140, SrfScore, Gfx.BackBuffer);
    SrfScore = TTF_RenderText_Solid(Gfx.DefaultFont, std::to_string(Spaceship.GetPowerLevel()).c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(100, 140, SrfScore, Gfx.BackBuffer);
    */
    /*
    SrfScore = TTF_RenderText_Solid(Gfx.DefaultFont, "PARTICLE(X): ", Gfx.WhiteRGB);
    Gfx.apply_surface(0, 160, SrfScore, Gfx.BackBuffer);
    SrfScore = TTF_RenderText_Solid(Gfx.DefaultFont, std::to_string(p.GetX()).c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(p.GetX(), p.GetY(), SrfScore, Gfx.BackBuffer);

    SrfScore = TTF_RenderText_Solid(Gfx.DefaultFont, "PARTICLE(Y): ", Gfx.WhiteRGB);
    Gfx.apply_surface(0, 180, SrfScore, Gfx.BackBuffer);
    SrfScore = TTF_RenderText_Solid(Gfx.DefaultFont, std::to_string(p.GetY()).c_str(), Gfx.WhiteRGB);
    Gfx.apply_surface(100, 180, SrfScore, Gfx.BackBuffer);
	*/
    //SDL_FreeSurface(SrfScore);
    //SrfScore = NULL;
}

void ControlGfx::SetAlpha( int _SurfaceIndex, int _Opacity )
{
    logger.write(__LINE__, __FUNCTION__);

	SDL_SetAlpha( Gfx.GetSurface( _SurfaceIndex ), SDL_SRCALPHA | SDL_RLEACCEL, (Uint8)_Opacity );
}

void ControlGfx::RenderText(std::string _Text, int _x, int _y,std::string _FontName)
{
    //logger.write(__LINE__, __FUNCTION__);

    int w = 0;
    int h = 0;

    if (_FontName == "Default")
        if ((TTF_SizeText(Gfx.DefaultFont, _Text.c_str(), &w, &h) != -1))
        {
        // Setting the width and height of the text
        }
        else
        {
            // Error...
        }
    else
    if (_FontName == "Title")
        if ((TTF_SizeText(Gfx.TitleFont, _Text.c_str(), &w, &h) != -1))
        {
        // Setting the width and height of the text
        }
        else
        {
            // Error...
        }


    //if ((TTF_SizeText(Gfx.TitleFont, _Text.c_str(), &w, &h) != -1))
    //{
        // Setting the width and height of the text
    //}
    //else 
    //{
        // Error...
    //}

    SDL_Surface * SrfText;
    if (_FontName == "Default")
        SrfText = TTF_RenderText_Solid(Gfx.DefaultFont, _Text.c_str(), Gfx.WhiteRGB);
    if (_FontName == "Title")
        SrfText = TTF_RenderText_Solid(Gfx.TitleFont, _Text.c_str(), Gfx.WhiteRGB);

    if ( (_x == 0) && (_y == 0) )
    {
        Gfx.apply_surface( (Gfx.BackBuffer->w - w) / 2, (Gfx.BackBuffer->h - h) - _y, SrfText, Gfx.BackBuffer);
    }
    else
    {
        Gfx.apply_surface((Gfx.BackBuffer->w - w) - _x, (Gfx.BackBuffer->h - h) - _y, SrfText, Gfx.BackBuffer);
    }
}