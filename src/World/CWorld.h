#pragma once
#include <list>
#include <stack>
#include <SDL.h>

/// <summary>Keeps the state of any world</summary>
class WorldState
{
public:
	WorldState();
	~WorldState();
};

/// <summary>Used to create a World entity</summary>
class World : public WorldState
{

public:
	World();
	~World(){};
	
	void Update();
	void Draw();

private:
};

/// <summary>A class the controls the worlds</summary> 
class ControlWorlds
{
public:
	ControlWorlds();
	~ControlWorlds();
	void DrawWorlds();
	void CreateWorlds();

	World * CreateWorld();

	
private:
	std::list< World* > _Worlds;
};

extern ControlWorlds WorldController;