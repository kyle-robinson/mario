#include "CharacterLuigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = FACING_LEFT;

	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterLuigi::~CharacterLuigi()
{

}

void CharacterLuigi::Render()
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

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
	Keyboard(deltaTime, e);
	if (mMovingRight || mMovingLeft)
	{
		AnimateLuigi(deltaTime, e);
	}
}

void CharacterLuigi::Keyboard(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = false;
			break;

		case SDLK_RIGHT:
			mMovingRight = false;
			break;

		default:
			break;
		}
		break;

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			Character::Jump();
			break;

		case SDLK_DOWN:
			break;

		case SDLK_LEFT:
			mMovingRight = false;
			mMovingLeft = true;
			break;

		case SDLK_RIGHT:
			mMovingLeft = false;
			mMovingRight = true;
			break;

		default:
			break;
		}
		break;
	}
}

void CharacterLuigi::AnimateLuigi(float deltaTime, SDL_Event e)
{
	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f)
	{
		mFrameDelay = ANIMATION_DELAY;
		mCurrentFrame++;

		if (mCurrentFrame > 2)
		{
			mCurrentFrame = 0;
		}
	}
}