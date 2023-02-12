#include "SpriteManager.h"

void SpriteManager::CreateSpriteSheet(std::string name, std::string filePath, int numFrames, int spriteWidth = 0 , int spriteHeight = 0)
{
	//Creates a new sprite sheet with all the relevant data and pushes it onto the spriteSheets list

	BYTE* spriteSheet{ nullptr };
	int spriteSheetWidth{ NULL };
	int spriteSheetHeight{ NULL };

	if (!HAPI.LoadTexture(filePath, &spriteSheet, spriteSheetWidth, spriteSheetHeight))
	{
		HAPI.UserMessage("Missing Texture", "Error");
		return;
	}

	if (spriteWidth == 0 || spriteHeight == 0)
	{
		spriteWidth = spriteSheetWidth;
		spriteHeight = spriteSheetHeight;
	}

	SpriteSheet* newSpriteSheet = new SpriteSheet();

	newSpriteSheet->id = name;
	newSpriteSheet->spriteSheet = spriteSheet;
	newSpriteSheet->spriteSheetWidth = spriteSheetWidth;
	newSpriteSheet->spriteSheetHeight = spriteSheetHeight;
	newSpriteSheet->spriteWidth = spriteWidth;
	newSpriteSheet->spriteHeight = spriteHeight;
	newSpriteSheet->numFrames = numFrames;

	spriteSheets.push_back(newSpriteSheet);
}

void SpriteManager::LoadAllSprites()
{
	//Loads all sprite sheets in the game

	CreateSpriteSheet("Player_Run_Anim", "Data\\Player_RunSS.png", 3, 64, 68);
	CreateSpriteSheet("Player_Idle_Anim", "Data\\Player_Idle_Anim.png", 4, 64, 68);
	CreateSpriteSheet("Player_Death_Anim", "Data\\Player_Death_Anim.png", 11, 64, 68);
	CreateSpriteSheet("Enemy_Run_Anim", "Data\\Enemy_Run.png", 4, 64, 68);
	CreateSpriteSheet("Enemy_Idle_Anim", "Data\\Enemy_Idle_Anim.png", 2, 64, 68);
	CreateSpriteSheet("Enemy_Death_Anim", "Data\\Enemy_Death_Anim.png", 11, 64, 68);
	CreateSpriteSheet("Sky_Static", "Data\\sky.png", 1);
	CreateSpriteSheet("Tile_Grass_Static", "Data\\TileSet7.png", 21, 64, 64);
	CreateSpriteSheet("Bullet_Static", "Data\\Bullet.png", 1);
	CreateSpriteSheet("PalmTree1_Static", "Data\\PalmTree1.png", 1);
	CreateSpriteSheet("Mountains_Static", "Data\\MidGround.png", 1);
	CreateSpriteSheet("Trees1_Static", "Data\\Trees1.png", 1);
	CreateSpriteSheet("Trees2_Static", "Data\\Trees2.png", 1);
	CreateSpriteSheet("Trees3_Static", "Data\\Trees3.png", 1);

	CreateSpriteSheet("Plunger_Static", "Data\\PlungerStatic.png", 1);
	CreateSpriteSheet("Plunger_Anim", "Data\\PlungerAnim.png", 20, 64, 64);
	CreateSpriteSheet("Explosion_Anim", "Data\\Explosion.png", 8, 1600, 1600);
	CreateSpriteSheet("Explosion2_Anim", "Data\\Explosion2.png", 6, 1600, 1600);
	CreateSpriteSheet("Explosion_Static", "Data\\ExplosionWipe2.png", 1);

	CreateSpriteSheet("Heart_Static", "Data\\Heart.png", 1);
	CreateSpriteSheet("GameOver_Static", "Data\\GameOver.png", 1);
	CreateSpriteSheet("GameWin_Static", "Data\\YouWin.png", 1);
}

SpriteSheet* SpriteManager::iGetSprite(std::string id)
{
	//returns a sprite with relevant id

	bool foundSpriteSheet = false;
	for(SpriteSheet* spriteSheet : spriteSheets)
	{
		if(spriteSheet->id == id)
		{
			foundSpriteSheet = true;
			return spriteSheet;
		}		
	}
	assert(foundSpriteSheet != true);
	return nullptr;
}

void SpriteManager::iCleanMemory()
{
	for(SpriteSheet* ss : spriteSheets)
	{
		ss->CleanMemory();
		delete ss;
	}
}
