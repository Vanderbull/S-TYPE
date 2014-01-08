#include "Paralaxlayers.h"

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

// struct ParallaxLayer
// ************************************************************

// ------------------------------------------------------------
// ParallaxLayer() - inits members
// ------------------------------------------------------------
ParallaxLayer::ParallaxLayer()
{
	m_parallax = 0;
	m_surface = m_surfaceYOffset = 0;
	m_width = m_height = 0;
	DX = 0;
	DY = 0;
	DW = 0;
	DH = 0;
	HowFarGone = 0;
	AnimClouds = 0;
}



// ------------------------------------------------------------
// set() - set members
// ------------------------------------------------------------
void ParallaxLayer::set( float p, Uint16 s, Uint16 sy, Uint16 w, Uint16 h, Uint16 DestX, Uint16 DestY, Uint16 DestW, Uint16 DestH  )
{
	m_parallax = p; 
	m_surface = s; 
	m_surfaceYOffset = sy; 
	m_width = w; 
	m_height = h; 
	DX = DestX;
	DY = DestY;
	DW = DestW;
	DH = DestH;
	Xpos = 0;
}





// class ParallaxBackground
// ************************************************************
// ------------------------------------------------------------
// ParallaxBackground() - inits members
// ------------------------------------------------------------
ParallaxBackground::ParallaxBackground()
{
	m_layerCount = 0;
	m_demons = 0;
}



// ------------------------------------------------------------
// ~ParallaxBackground() - cleans up
// ------------------------------------------------------------
ParallaxBackground::~ParallaxBackground()
{
	if( m_demons ) 
	{
		delete [] m_demons; 
	}
}



// ------------------------------------------------------------
// createLayers() - kills old layers and creates new ones
// ------------------------------------------------------------
void ParallaxBackground::createLayers( int count )
{
	// Kill old layers
	if( m_demons ) 
	{
		delete [] m_demons; 
	}


	// Create new layers
	m_layerCount = count;
	m_demons = new ParallaxLayer[ count ];
}



// ------------------------------------------------------------
// setLayer() - sets internal data for a layer
// ------------------------------------------------------------
void ParallaxBackground::setLayer(	int index, float p, Uint16 s, Uint16 sy, Uint16 w, Uint16 h, Uint16 DestX, Uint16 DestY, Uint16 DestW, Uint16 DestH )
{
	// Sanity check
	if( ( index < 0 ) || ( index >= m_layerCount ) )
		return;

	// Set it!
	m_demons[ index ].set( p, s, sy, w, h, DestX, DestY, DestW, DestH );
}



// ------------------------------------------------------------
// getLayer() - returns layer
// ------------------------------------------------------------
ParallaxLayer *ParallaxBackground::getLayer( int index )
{
	// Sanity check
	if( ( index < 0 ) || ( index >= m_layerCount ) )
	{
		return 0;
	}

	// Return it!
	return &m_demons[ index ];
}
