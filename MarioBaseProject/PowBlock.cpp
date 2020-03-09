#include "PowBlock.h"
#include <string>
#include <iostream>

using namespace std;

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
{
	string imagePath = "Images/Objects/PowBlock.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Falied to load texture: " << imagePath << endl;
		return;
	}

	mLevelMap = map;

	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = Vector2D((SCREEN_WIDTH * 0.5f) - mSingleSpriteWidth * 0.5f, 260);
}

PowBlock::~PowBlock()
{
	mRenderer = NULL;
	
	delete mTexture;
	mTexture = NULL;

	mLevelMap = NULL;
}

void PowBlock::TakeAHit()
{
	mNumberOfHitsLeft--;
	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;

		mLevelMap->ChangeTileAt(8, 7, 0);
		mLevelMap->ChangeTileAt(8, 8, 0);
	}
}

void PowBlock::Render()
{
	if (mNumberOfHitsLeft > 0)
	{
		int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);

		SDL_Rect portionOfSpritesheet = {left, 0, mSingleSpriteWidth, mSingleSpriteHeight};
		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight};

		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
}