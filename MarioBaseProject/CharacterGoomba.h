#pragma once

#include "Character.h"

class CharacterGoomba : public Character
{
public:
	CharacterGoomba(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing);
	~CharacterGoomba();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void TakeDamage();
	void Jump();

	bool GetInjured() { return mInjured; }

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	bool mInjured;
	float mInjuredTime;

	float mFrameDelay;
	int mCurrentFrame;
	void AnimateGoomba(float deltaTime, SDL_Event e);

	void FlipRightWayUp();
};