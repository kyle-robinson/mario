#pragma once

#include "Character.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing);
	~CharacterKoopa();

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
	void AnimateKoopa(float deltaTime, SDL_Event e);

	void FlipRightWayUp();
};