#pragma once

#include "Character.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition);
	~CharacterMario();
protected:
	void Update(float deltaTime, SDL_Event e);
};