#include "Character.h"
#include "Texture2D.h"
#include "Collisions.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map)
{
    mRenderer = renderer;
    mPosition = startPosition;
    mTexture = new Texture2D(mRenderer);
    mTexture->LoadFromFile(imagePath);

    mFacingDirection = FACING_RIGHT;
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
    mTexture->Render(GetPosition(), SDL_FLIP_NONE);

    // Change character direction.
    if (mFacingDirection == FACING_RIGHT)
    {
        mTexture->Render(mPosition, SDL_FLIP_NONE);
    }
    else
    {
        mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
    }
}

void Character::Update(float deltaTime, SDL_Event e)
{
	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

	// Deal with gravity.
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		// Collided with ground so we can jump again.
		mCanJump = true;
	}
	
	// Deal with Jumping first
    if (mJumping)
    {
        // Adjust the position.
        mPosition.y -= mJumpForce * deltaTime;

        // Reduce the jump force.
        mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

        // Has the jump force reduced to zero?
        if (mJumpForce <= 0.0f)
        {
            mJumping = false;
        }
    }
    
    // Character Direction and Movement
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
	mFacingDirection = FACING_LEFT;
	mPosition.x -= MOVEMENT_SPEED;
}

void Character::MoveRight(float deltaTime)
{
	mFacingDirection = FACING_RIGHT;
	mPosition.x += MOVEMENT_SPEED;
}

void Character::AddGravity(float deltaTime)
{
    mPosition.y += PLAYER_GRAVITY * deltaTime;
}

void Character::Jump()
{
    if (!mJumping)
    {
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
	mJumpForce = 0;
}