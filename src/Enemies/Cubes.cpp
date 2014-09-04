#include "Cubes.h"
#include <SDL.h>
#include "../Game.h"
#include "../ControlGfx.h"

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

ControlCubes CubeController;

const float CubeSpeed = 0.0001f;
const int Frames = 16;

Cube::Cube()
{
    logger.write(__LINE__, __FILE__);
    PrevFrame = 0;
    Frame = 0;
    Height = 64;
    Width = 64;

    for (int CurrentFrame = 0; CurrentFrame < Frames; CurrentFrame++)
    {
        Clips[CurrentFrame].x = CurrentFrame * Width;
        Clips[CurrentFrame].y = 0;
        Clips[CurrentFrame].h = Height;
        Clips[CurrentFrame].w = Width;
    }
}

SDL_Rect Cube::UpdateCollisionBox(SDL_Rect Box)
{
    logger.write(__LINE__, __FILE__);
	CollisionBox = Box;
	return CollisionBox;
}

void Cube::Update()
{
    logger.write(__LINE__, __FILE__);

    double _freq = 50;
    int _sTime = 5, _amp = 100;

    double full = (2 * 3.14159) * 50.f;
    static double _x = 0;
    int _y = (sin(xPos / _freq)*_amp) + 300;
    if (_x >= full)
        _x -= full;
    _x++;
	xPos -= CubeSpeed * gamestate.DeltaTime;
	Destination.h = Height;
	Destination.w = Width;
	Destination.x = xPos;
    Destination.y = _y;

	PrevFrame = Frame++;
	if( Frame >= CUBE_MAX_FRAMES )
	{
		Frame = 0;
	}
    Frame = 0;
	UpdateCollisionBox(Destination);
}

void Cube::Draw()
{
    logger.write(__LINE__, __FILE__);
	#ifdef _DEBUG 
	SDL_FillRect(Gfx.BackBuffer, &CollisionBox,0xffffff );
	#endif
	
	SDL_BlitSurface( 
		Gfx.GetSurface( SurfaceID ),
		&Clips[ PrevFrame ], 
		Gfx.BackBuffer, 
		&GetDestination() 
	);
}

SDL_Rect Cube::GetDestination()
{
    logger.write(__LINE__, __FILE__);
	return Destination;
}

// ControlCubes begins here
void ControlCubes::LoadSpawnPoints()
{
    logger.write(__LINE__, __FILE__);

    ifstream ifile;
    ifile.open("./assets/cfg/cube_spawn_points.txt", ios::in);

    if (!ifile.is_open()) {
        cerr << "There was an error opening the input file!\n";
        exit(0);
    }
    else
    {
        cout << "Opened cube_spawn_points.txt for reading" << endl;
    }
    int temp = 0;

    while (ifile >> temp)
    {
        cube_spawn_points.push(temp);
    }
}

void ControlCubes::DrawCubes()
{
    logger.write(__LINE__, __FILE__);
	if( CubeArrayRef.size() < 1 )
		return;
	vector< Cube >::iterator i;

	i = CubeArrayRef.begin();

	while(i != CubeArrayRef.end() )
	{
		i->Update();
		i->Draw();
		
		if( i->xPos <= 0.0f - SpriteWidth )
		{
			i = CubeArrayRef.erase(i);
		}
		else
		{
			++i;
		}
	}
}

void ControlCubes::CreateCubes(int iProgress )
{
    logger.write(__LINE__, __FILE__);
    int temp = cube_spawn_points.top();
    if (iProgress == cube_spawn_points.top())
    {
        CubeArrayRef.push_back(CreateCubeByReference(SDL_GetVideoSurface()->w, std::rand() % Gfx.BackBuffer->h - 64, gamestate.m_srfCube));
        cube_spawn_points.pop();
    }
}

Cube ControlCubes::CreateCubeByReference( int xPos, int yPos, int surface )
{
    logger.write(__LINE__, __FILE__);
	static int old_y_pos = 0;
	static int old_x_pos = 0;

	while( xPos > old_x_pos && xPos < old_x_pos + 64 )
	{
		xPos = std::rand() % Gfx.BackBuffer->w - 64;
	}
	if( xPos < 64 )
		xPos = 64;
	
	while( yPos > old_y_pos && yPos < old_y_pos + 64 )
	{
		yPos = std::rand() % Gfx.BackBuffer->h - 64;
	}
	if( yPos < 64 )
		yPos = 64;

	Cube temp;
	temp.SurfaceID = surface;
	temp.xPos = xPos;
	temp.yPos = yPos;

	old_y_pos = yPos;

	return temp;
}
ControlCubes::ControlCubes()
{
    logger.write(__LINE__, __FILE__);
}

ControlCubes::~ControlCubes()
{
    logger.write(__LINE__, __FILE__);
}