#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition) : Character(renderer, imagePath, startPosition, map)
{
	mPosition = startPosition;
	mCollected = false;

	mCurrentFrame = 0;
	mFrameDelay = ANIMATION_DELAY;

	mSingleSpriteWidth = mTexture->GetWidth() / 3;	// 3 sprites on this spritesheet in 1 row.
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterCoin::~CharacterCoin()
{

}

void CharacterCoin::Render()
{
	int left = mCurrentFrame * mSingleSpriteWidth;

	// Get the portion of the spritesheet you want to draw.
	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	
	// Determine where you want it drawn.
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };
	
	mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
}

void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	// Change frame?
	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f)
	{
		// Reset frame delay count.
		mFrameDelay = ANIMATION_DELAY;

		// Move frame on.
		mCurrentFrame++;

		// Loop frame around if it goes beyond the number of frames.
		if (mCurrentFrame > 2)
		{
			mCurrentFrame = 0;
		}
	}
}