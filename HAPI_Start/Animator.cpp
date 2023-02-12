#pragma once
#include "Animator.h"
#include "GameObject.h"

void Animator::FlipHorizontal(bool flipState)
{
	inverted = flipState;
}

void Animator::CreateNewAnim(std::string spriteSheetID, float animDuration)
{
	animation newAnim;

	newAnim.spriteSheetID = spriteSheetID;
	newAnim.animDuration = animDuration;

	animations.push_back(newAnim);
}

void Animator::Render(int posX, int posY, int animIndex)
{
	SpriteSheet* currentSpriteSheet = SpriteManager::GetSprite(animations[animIndex].spriteSheetID); //Get the sprite sheet using the anim index

	time += Time::GetDeltaTime();
	animations[animIndex].currentTimer += Time::GetDeltaTime(); //incrament the timer for the current animation

	int curFrame = 0;

	if (animations[animIndex].currentTimer > animations[animIndex].animDuration) //calculate current frame
	{
		animations[animIndex].currentFrame = 0;
		animations[animIndex].currentTimer = 0;
		curFrame = animations[animIndex].defaultFrame;
	}
	else
	{
		curFrame = (int)((animations[animIndex].currentTimer / animations[animIndex].animDuration) * currentSpriteSheet->numFrames);
		animations[animIndex].currentFrame = curFrame;
	}


	//-------------Calculate the texture offsets for the current frame on the sprite sheet------------------------------------
	int numSpritesPerRow = (currentSpriteSheet->spriteSheetWidth / currentSpriteSheet->spriteWidth);

	int rowNum = curFrame / numSpritesPerRow;
	int columnNum = curFrame % numSpritesPerRow;

	int textureOffsetX = columnNum * currentSpriteSheet->spriteWidth;
	int textureOffsetY = rowNum * currentSpriteSheet->spriteHeight;
	//------------------------------------------------------------------------------------------------------------------------


	Renderer::BlitAlphaClipped(currentSpriteSheet->spriteSheet, currentSpriteSheet->spriteWidth, 
							   currentSpriteSheet->spriteHeight, posX, posY, textureOffsetX, textureOffsetY, 
							   currentSpriteSheet->spriteSheetWidth, currentSpriteSheet->spriteHeight, inverted); //Render the frame using the Renderer
}

void Animator::SetCurFrame(int curFrameIndex)
{
	animations[currentAnimIndex].currentFrame = curFrameIndex;
}

void Animator::SetDefaultFrame(int defaultFrameIndex)
{
	animations[currentAnimIndex].defaultFrame = defaultFrameIndex;
}

void Animator::SetAnimIndex(int index)
{
	currentAnimIndex = index;
}

bool Animator::GetInverted()
{
	return inverted;
}

void Animator::Process()
{
	Render((int)m_gameObject->pos.x, (int)m_gameObject->pos.y, currentAnimIndex);
}


