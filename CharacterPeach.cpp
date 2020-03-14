#include "CharacterPeach.h"

CharacterPeach::CharacterPeach(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mPosition = startPosition;
	isRescued = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterPeach::~CharacterPeach()
{

}

void CharacterPeach::Render()
{
	int left = mCurrentFrame * mSingleSpriteWidth;

	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterPeach::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
	AnimatePeach(deltaTime, e);
}

void CharacterPeach::AnimatePeach(float deltaTime, SDL_Event e)
{
	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f)
	{
		mFrameDelay = ANIMATION_DELAY;
		mCurrentFrame++;

		if (mCurrentFrame > 1)
		{
			mCurrentFrame = 0;
		}
	}
}