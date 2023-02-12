#pragma once
#include <HAPI_lib.h>
#include <assert.h>
using namespace HAPISPACE;

struct SpriteSheet
{
	std::string id = "NULL";
	BYTE* spriteSheet = nullptr;

	int spriteSheetWidth;
	int spriteSheetHeight;

	int spriteWidth;
	int spriteHeight;

	int numFrames;

	void CleanMemory()
	{
		delete spriteSheet;
	}
};

class SpriteManager
{
private:
	std::vector<SpriteSheet*> spriteSheets;

	SpriteManager()
	{
		LoadAllSprites();
	}
	
	void CreateSpriteSheet(std::string name, std::string filePath, int spriteWidth, int spriteHeight, int numFrames);
	void LoadAllSprites();

	SpriteSheet* iGetSprite(std::string id);
	void iCleanMemory();
public:
	SpriteManager(const SpriteManager&) = delete;

	static SpriteSheet* GetSprite(std::string id)
	{
		return Get().iGetSprite(id);
	}

	static SpriteManager& Get()
	{
		static SpriteManager spriteManager_Instance;
		return spriteManager_Instance;
	}

	static void CleanMemory()
	{
		Get().iCleanMemory();
	}
};

