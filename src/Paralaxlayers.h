// Parallax.h
#pragma once
#include <SDL.h>
#include <vector>

// struct declarations
struct ParallaxLayer
{
	ParallaxLayer();
	void set(	float p, Uint16 s, Uint16 sy, Uint16 w, Uint16 h, Uint16 DestX, Uint16 DestY, Uint16 DestW, Uint16 DestH  );


	float m_parallax;
	Uint16 m_surface, m_surfaceYOffset;
	Uint16 m_width, m_height;
	Uint16 DX, DY, DW, DH;
	int Xpos;
	int HowFarGone;
	float AnimClouds;
};



// ParallaxBackground - container for ParallaxLayer
// ------------------------------------------------
class ParallaxBackground
{
	public:	
		ParallaxBackground();
		~ParallaxBackground();

		// Creation
		void createLayers( int count );

		// Get/Set
		int getLayerCount() { return m_layerCount; }
		ParallaxLayer *getLayer( int index );
		void setLayer(	int index, float p, Uint16 s, Uint16 sy, Uint16 w, Uint16 h, Uint16 DestX, Uint16 DestY, Uint16 DestW, Uint16 DestH );


	private:
		int m_layerCount;
		ParallaxLayer *m_demons;
		std::vector<ParallaxLayer> m_ParallaxBackground;
};
