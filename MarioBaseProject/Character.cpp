#include "Character.h"
#include "Texture2D.h"
#include "Collisions.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition)
{
    mRenderer = renderer;
    mPosition = startPosition;
    mTexture = new Texture2D(mRenderer);
    mTexture->LoadFromFile(imagePath);

    mFacingDirection = FACING_RIGHT;
    mMovingLeft = false;
    mMovingRight = false;

    mCollisionRadius = 15.0f;
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

    if (mPosition.y == SCREEN_HEIGHT)
    {
        // Collided with ground so we can jump again.
        mCanJump = true;
    }
    else
    {
        // Add Gravity to the Character
        AddGravity(deltaTime);
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

    // Stop the player from moving off screen.
    if (mPosition.y >= SCREEN_HEIGHT - mTexture->GetHeight())
    {
        mPosition.y -= 1;
    }
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