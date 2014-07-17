#include "CWorld.h"
#include <SDL.h>
#include "../game.h"
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

ControlWorlds WorldController;

WorldState::WorldState()
{
};

WorldState::~WorldState()
{
};

void World::Update()
{
}

void World::Draw()
{
}

World::World()
{
};

ControlWorlds::ControlWorlds()
{
};

ControlWorlds::~ControlWorlds()
{
};

void ControlWorlds::DrawWorlds()
{
};

void ControlWorlds::CreateWorlds()
{
};

World * ControlWorlds::CreateWorld()
{
	cout << "Creating the world as we know it...";
	World * temp = new World;
	return temp;
};