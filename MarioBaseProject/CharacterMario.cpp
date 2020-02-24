#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = FACING_RIGHT;
}

CharacterMario::~CharacterMario()
{

}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
	Keyboard(deltaTime, e);
}

void CharacterMario::Keyboard(float deltaTime, SDL_Event e)
{
	// Deal with keyboard input.
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