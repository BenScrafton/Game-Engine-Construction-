#pragma once
#include <HAPI_lib.h>
// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;


class Renderer
{
private:
	Renderer() {};

	BYTE* screen = nullptr;

	int screenWidth{ 1024 };
	int screenHeight{ 768 };

	void iClearScreen(int screenPixelNum);
	void iBlit(BYTE* texture, int spriteWidth, int spriteHeight, int posX, int posY, int textureOffsetX, int textureOffsetY, int textureWidth, int textureHeight);
	void iBlitAlpha(BYTE* texture, int spriteWidth, int spriteHeight, int posX, int posY, int textureOffsetX, int textureOffsetY, int textureWidth, int textureHeight);
	void iBlitAlphaClipped(BYTE* texture, int spriteWidth, int spriteHeight, int posX, int posY, int textureOffsetX, int textureOffsetY, int textureWidth, int textureHeight, bool inverted);

public:
	Renderer(const Renderer&) = delete;

	static Renderer& Get()
	{
		static Renderer renderer_Instance;

		renderer_Instance.screen =  HAPI.GetScreenPointer();
		return renderer_Instance;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------
	static void ClearScreen(int screenPixelNum) 
	{ 
		 Get().iClearScreen(screenPixelNum); 
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------
	static void Blit(BYTE* texture, int spriteWidth, int spriteHeight, int posX, int posY, int textureOffsetX, int textureOffsetY, int textureWidth, int textureHeight)
	{
		Get().iBlit(texture, spriteWidth, spriteHeight, posX, posY, textureOffsetX, textureOffsetY, textureWidth, textureHeight);
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------
	static void BlitAlpha(BYTE* texture, int spriteWidth, int spriteHeight, int posX, int posY, int textureOffsetX, int textureOffsetY, int textureWidth, int textureHeight)
	{
		Get().iBlitAlpha(texture, spriteWidth, spriteHeight, posX, posY, textureOffsetX, textureOffsetY, textureWidth, textureHeight);
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------
	static void BlitAlphaClipped(BYTE* texture, int spriteWidth, int spriteHeight, int posX, int posY, int textureOffsetX, int textureOffsetY, int textureWidth, int textureHeight, bool inverted)
	{
		Get().iBlitAlphaClipped(texture, spriteWidth, spriteHeight, posX, posY, textureOffsetX, textureOffsetY, textureWidth, textureHeight, inverted);
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------
};


