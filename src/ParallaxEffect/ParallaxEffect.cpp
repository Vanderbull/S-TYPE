#include "ParallaxEffect.h"

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

namespace ParallaxEffect
{

    Layer::Layer()
    {

    }

    int Set()
    {
        return 0;
    }

    Layer::~Layer()
    {

    }


    int Controller::getLayerCount()
    {
        // Notice the data type for the subscript, vector<double>::size_type.As with strings, class vector<type> provides a size_type to 
        // represent positions and sizes.It is always recommended that you use this data type when dealing with vectors
        // Example:
        // for (vector<double>::size_type i = 0; i < 20; i++)
        // {
        //     cout << "Enter marks for student #" << i + 1
        //         << ": " << flush;
        //     cin >> student_marks[i];
        // }
       return mParallaxLayerVector.size();
    }
    Layer Controller::getLayer(int index)
    {
        Layer tempLayer;
        return tempLayer;
    }

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
    Xpos = 0;
}



// ------------------------------------------------------------
// set() - set members
// ------------------------------------------------------------
void ParallaxLayer::set(float p, Uint16 s, Uint16 sy, Uint16 w, Uint16 h, Uint16 DestX, Uint16 DestY, Uint16 DestW, Uint16 DestH)
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
    m_demons = NULL;
}



// ------------------------------------------------------------
// ~ParallaxBackground() - cleans up
// ------------------------------------------------------------
ParallaxBackground::~ParallaxBackground()
{
    if (m_demons)
    {
        delete[] m_demons;
    }
}



// ------------------------------------------------------------
// createLayers() - Create new Parallax layers
// ------------------------------------------------------------
void ParallaxBackground::createLayers(int count)
{
    ParallaxLayer temp_background;
    for (int layers = 0; layers < count; layers++)
        m_ParallaxBackground.push_back(temp_background);
    m_layerCount = count;
    m_demons = new ParallaxLayer[m_layerCount];
}



// ------------------------------------------------------------
// setLayer() - sets internal data for a layer
// ------------------------------------------------------------
void ParallaxBackground::setLayer(int index, float p, Uint16 s, Uint16 sy, Uint16 w, Uint16 h, Uint16 DestX, Uint16 DestY, Uint16 DestW, Uint16 DestH)
{
    // Sanity check
    if ((index < 0) || (index >= getLayerCount()))
        return;

    // Set it!
    m_demons[index].set(p, s, sy, w, h, DestX, DestY, DestW, DestH);

    // new setit
    m_ParallaxBackground.at(index).set(p, s, sy, w, h, DestX, DestY, DestW, DestH);
}



// ------------------------------------------------------------
// getLayer() - returns layer
// ------------------------------------------------------------
ParallaxLayer *ParallaxBackground::getLayer(int index)
{
    // Sanity check
    if ((index < 0) || (index >= getLayerCount()))
    {
        return 0;
    }

    // Return it!
    return &m_demons[index];
}

} 