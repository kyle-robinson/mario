#pragma once

#include "Character.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed);
	~CharacterKoopa();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	// Enemy movement.
	void TakeDamage();
	void Jump();

	bool GetInjured() { return mInjured; }

private:
	// Get sprite dimensions.
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	// Check for when enemy is injured.
	bool mInjured;
	float mInjuredTime;

	// Enemy movement.
	void FlipRightWayUp();
	float mMovementSpeed;
};