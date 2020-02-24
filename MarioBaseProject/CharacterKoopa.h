#pragma once

#include "Character.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed);
	~CharacterKoopa();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void TakeDamage();
	void Jump();

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	bool mInjured;
	float mInjuredTime;

	void FlipRightWayUp();

	float mMovementSpeed;
};