#pragma once

#include "Character.h"

class CharacterPeach : public Character
{
public:
	CharacterPeach(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing);
	~CharacterPeach();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	bool isRescued;

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	float mFrameDelay;
	int mCurrentFrame;
	void AnimatePeach(float deltaTime, SDL_Event e);
};