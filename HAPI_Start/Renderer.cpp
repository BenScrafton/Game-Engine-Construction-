#include "Renderer.h"

void Renderer::iClearScreen(int screenPixelNum)
{
	for (size_t i = 0; i < screenPixelNum; i++)
	{
		screen[i] = 00;
	}
}

void Renderer::iBlit(BYTE* texture, int spriteWidth, int spriteHeight, int posX, int posY, int textureOffsetX, int textureOffsetY, int textureWidth, int textureHeight)
{
	BYTE* tempTexture{ texture };
	BYTE* tempScreen{ screen + (posX + (posY * screenWidth)) * 4 };

	tempTexture += (textureOffsetX * 4) + ((textureOffsetY * 4) * (textureWidth * 4));

	for (size_t y = 0; y < spriteHeight; y++)
	{
		memcpy(tempScreen, tempTexture, (size_t) (spriteWidth * 4.0f));
		tempTexture += (textureWidth * 4);
		tempScreen += screenWidth * 4;
	}
}

void Renderer::iBlitAlpha(BYTE* texture, int spriteWidth, int spriteHeight, int posX, int posY, int textureOffsetX, int textureOffsetY, int textureWidth, int textureHeight)
{
	int endOfLineScreenOffset = (screenWidth * 4) - (spriteWidth * 4);

	BYTE* tempTexture{ texture };
	BYTE* tempScreen{ screen + (posX + (posY * screenWidth)) * 4 };

	tempTexture += (textureOffsetX * 4) + ((textureOffsetY * 4) * (textureWidth * 4));

	for (size_t y = 0; y < spriteHeight; y++)
	{
		for (size_t x = 0; x < spriteWidth; x++)
		{
	
			if (tempTexture[3] == 255)
			{
				memcpy(tempScreen, tempTexture, 4);
			}
			else if (tempTexture[3] != 0)
			{
				float alpha = (tempTexture[3] / 255.0f);
				int r = (int)((tempTexture[0] * alpha) + (tempScreen[0] * (1 - alpha)));
				int	g = (int)((tempTexture[1] * alpha) + (tempScreen[1] * (1 - alpha)));
				int b = (int)((tempTexture[2] * alpha) + (tempScreen[2] * (1 - alpha)));

				tempScreen[0] = r;
				tempScreen[1] = g;
				tempScreen[2] = b;
			}
			
			tempTexture += 4;
			tempScreen += 4;
		}
		tempScreen += endOfLineScreenOffset;
		tempTexture += (textureWidth * 4) - (spriteWidth * 4);
	}
}

void Renderer::iBlitAlphaClipped(BYTE* texture, int spriteWidth, int spriteHeight, int posX, int posY, int textureOffsetX, int textureOffsetY, int textureWidth, int textureHeight, bool inverted)
{
	BYTE* tempTexture{ texture };
	BYTE* tempScreen{ screen + ((posX < 0 ? 0 : std::min(screenWidth, posX)) + (posY < 0 ? 0 : posY) * screenWidth) * 4 };

	int endOfLineScreenOffset = (screenWidth * 4) - (spriteWidth * 4);
	int yStart = 0;
	int xStart = 0;
	int yEnd = spriteHeight;
	int xEnd = spriteWidth;

	if (posY < 0)
	{
		yStart = abs(posY);
		tempTexture += ((textureWidth * yStart) * 4);
	}

	if (posX < 0)
	{
		xStart = abs(posX);
		tempTexture += (xStart * 4);
	}

	if (posX + spriteWidth > screenWidth)
	{
		int offset = (posX + spriteWidth) - screenWidth;
		xEnd -= offset;
	}

	if (posY + spriteHeight > screenHeight)
	{
		int offset = (posY + spriteHeight) - screenHeight;
		yEnd -= offset;
	}

	if(!inverted)
	{
		tempTexture += (textureOffsetX * 4) + ((textureOffsetY) * (textureWidth * 4));
	}
	else
	{
		tempTexture += (textureOffsetX * 4) + ((textureOffsetY) * (textureWidth * 4)) + ((spriteWidth-1) * 4) - (2*(xStart * 4));
	}

	if (!(yStart > yEnd || xStart > xEnd))
	{
		for (size_t y = yStart; y < yEnd; y++)
		{
			for (size_t x = xStart; x < xEnd; x++)
			{
				if (tempTexture[3] == 255)
				{
					memcpy(tempScreen, tempTexture, 4);
				}
				else if (tempTexture[3] != 0)
				{
					float alpha = (tempTexture[3] / 255.0f);

					int r = (int)((tempTexture[0] * alpha) + (tempScreen[0] * (1 - alpha)));
					int	g = (int)((tempTexture[1] * alpha) + (tempScreen[1] * (1 - alpha)));
					int b = (int)((tempTexture[2] * alpha) + (tempScreen[2] * (1 - alpha)));

					tempScreen[0] = r;
					tempScreen[1] = g;
					tempScreen[2] = b;
				}
				if (!inverted)
				{
					tempTexture += 4;
				}
				else
				{
					tempTexture -= 4;
				}
				
				tempScreen += 4;
			}

			if(!inverted)
			{
				tempTexture += (xStart * 4) + ((textureWidth - xEnd) * 4);
			}
			else
			{
				tempTexture += (xStart * 4) + ((textureWidth - xEnd) * 4) + (((xEnd * 4) - (xStart * 4))*2);
			}

			tempScreen += endOfLineScreenOffset + (xStart * 4) + ((spriteWidth - xEnd) * 4);
		}
	}
}




