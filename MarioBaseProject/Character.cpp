#include "Character.h"
#include "Collisions.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map)
{
    mRenderer = renderer;
    mPosition = startPosition;
    mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);
	LoadAudio();

    mMovingLeft = false;
    mMovingRight = false;

    mCollisionRadius = 15.0f;

	mCurrentLevelMap = map;
}

Character::~Character()
{
    mRenderer = NULL;
}

void Character::Render()
{

}

void Character::Update(float deltaTime, SDL_Event e)
{
	int headPosition = (int)(mPosition.y + mTexture->GetHeight() - 32) / TILE_HEIGHT;
	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

	// Deal with Jumping first
	if (mJumping)
	{
		mPosition.y -= mJumpForce * deltaTime;
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f && mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 1)
		{
			mJumping = false;
		}
	}

	// Deal with gravity.
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		mCanJump = true;
	}

	if (mCurrentLevelMap->GetTileAt(headPosition, centralXPosition) == 1)
	{
		mJumpForce = 0.0f;
		mCanJump = false;
	}

	if (mMovingLeft)
    {
        MoveLeft(deltaTime);
    }
    else if (mMovingRight)
    {
        MoveRight(deltaTime);
    }
}

void Character::SetPosition(Vector2D newPosition)
{
    mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
    return mPosition;
}

void Character::MoveLeft(float deltaTime)
{
	mMovementSpeedRight = 0.0f;
	mFacingDirection = FACING_LEFT;

	mPosition.x -= mMovementSpeedLeft * deltaTime;
	mMovementSpeedLeft -= MOVEMENT_SPEED_INCREASE_LEFT * deltaTime;

	if (mMovementSpeedLeft > MAX_MOVEMENT_SPEED)
	{
		mMovementSpeedLeft = MAX_MOVEMENT_SPEED;
	}
}

void Character::MoveRight(float deltaTime)
{
	mMovementSpeedLeft = 0.0f;
	mFacingDirection = FACING_RIGHT;

	mPosition.x += mMovementSpeedRight * deltaTime;
	mMovementSpeedRight += MOVEMENT_SPEED_INCREASE_RIGHT * deltaTime;

	if (mMovementSpeedRight > MAX_MOVEMENT_SPEED)
	{
		mMovementSpeedRight = MAX_MOVEMENT_SPEED;
	}
}

void Character::AddGravity(float deltaTime)
{
    mPosition.y += PLAYER_GRAVITY * deltaTime;
}

void Character::Jump()
{
    if (!mJumping)
    {
		Mix_PlayChannel(-1, jumpSound, 0);
        mJumpForce = INITIAL_JUMP_FORCE;
        mJumping = true;
        mCanJump = false;
    }
}

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

bool Character::IsJumping()
{
	return mJumping;
}

void Character::CancelJump()
{
	mJumpForce = -mJumpForce;
}

void Character::SetAlive(bool isAlive)
{
	alive = isAlive;
}

bool Character::LoadAudio()
{
	jumpSound = Mix_LoadWAV("Music/WAV/Jump.wav");
	if (jumpSound == NULL)
	{
		cout << "Failed to load jump sound! Error: " << Mix_GetError() << endl;
		return false;
	}
	return true;
}