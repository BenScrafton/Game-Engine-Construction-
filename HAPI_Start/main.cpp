#include <HAPI_lib.h>
#include "Time.h"
#include "World.h"

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down

std::vector<GameObject*> gameObjects;

void HAPI_Main()
{
	int width{1024};
	int height{768};
	int screenPixelNum = width * height * 4;

	if (!HAPI.Initialise(width, height))
		return;

	BYTE* screen{ HAPI.GetScreenPointer() };

	World* world = new World();

	Time::Init();

	while(HAPI.Update())
	{	
		//Render-----------------------------------------------------------------------------------
		Renderer::ClearScreen(screenPixelNum);
		world->Update();

		//Timer------------------------------------------------------------------------------------
		Time::Update();
	}

	//Memory CleanUp-------------------------------------------------------------------------------
	
	SpriteManager::CleanMemory();
	world->MemoryClean();

	delete world;
}

