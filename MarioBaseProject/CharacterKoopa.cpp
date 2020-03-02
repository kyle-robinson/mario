#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mPosition = startPosition;
	mInjured = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterKoopa::~CharacterKoopa()
{

}

void CharacterKoopa::Render()
{
	int left = mCurrentFrame * mSingleSpriteWidth;
	
	if (mInjured)
	{
		mCurrentFrame = 2;
		left = mCurrentFrame * mSingleSpriteWidth;
	}

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

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	if (!mInjured)
	{
		AnimateKoopa(deltaTime, e);
		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mMovingRight = true;
			mMovingLeft = false;
		}
	}
	else
	{
		mMovingRight = false;
		mMovingLeft = false;

		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0)
		{
			FlipRightWayUp();
		}
	}
}

void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;
		
		mJumping = true;
		mCanJump = false;
	}
}

void CharacterKoopa::FlipRightWayUp()
{
	if (mFacingDirection == 0)
	{
		mFacingDirection = FACING_RIGHT;
	}
	else
	{
		mFacingDirection = FACING_LEFT;
	}

	mInjured = false;
	Jump();
}

void CharacterKoopa::AnimateKoopa(float deltaTime, SDL_Event e)
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