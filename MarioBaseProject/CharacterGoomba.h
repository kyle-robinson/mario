#pragma once

#include "Character.h"

class CharacterGoomba : public Character
{
public:
	CharacterGoomba(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing);
	~CharacterGoomba();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	// Enemy Movement
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

	// Animation variables
	float mFrameDelay;
	int mCurrentFrame;
	void AnimateGoomba(float deltaTime, SDL_Event e);

	// Enemy Movement
	void FlipRightWayUp();
	float mMovementSpeed;
};