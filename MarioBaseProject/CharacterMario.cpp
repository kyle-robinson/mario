#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition) : Character(renderer, imagePath, startPosition)
{
	
}

CharacterMario::~CharacterMario()
{

}

void CharacterMario::Update(float deltaTime, SDL_Event e)
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
	Character::Update(deltaTime, e);
}