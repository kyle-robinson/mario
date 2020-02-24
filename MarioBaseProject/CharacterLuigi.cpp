#include "CharacterLuigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = FACING_LEFT;
}

CharacterLuigi::~CharacterLuigi()
{

}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
	Keyboard(deltaTime, e);
}

void CharacterLuigi::Keyboard(float deltaTime, SDL_Event e)
{
	// Deal with keyboard input.
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