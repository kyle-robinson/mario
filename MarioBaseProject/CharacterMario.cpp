#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = FACING_RIGHT;
	
	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterMario::~CharacterMario()
{

}

void CharacterMario::Render()
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

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
	Keyboard(deltaTime, e);
	if (mMovingRight || mMovingLeft)
	{
		AnimateMario(deltaTime, e);
	}
}

void CharacterMario::Keyboard(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = false;
			break;

		case SDLK_d:
			mMovingRight = false;
			break;

		default:
			break;
		}
		break;

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			Character::Jump();
			break;

		case SDLK_s:
			break;

		case SDLK_a:
			mMovingRight = false;
			mMovingLeft = true;
			break;

		case SDLK_d:
			mMovingLeft = false;
			mMovingRight = true;
			break;

		default:
			break;
		}
		break;
	}
}

void CharacterMario::AnimateMario(float deltaTime, SDL_Event e)
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