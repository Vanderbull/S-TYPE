#include "CWorld.h"
#include <SDL.h>
#include "../game.h"
#include "../ControlGfx.h"

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