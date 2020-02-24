#pragma once

#include "Character.h"

class CharacterCoin : public Character
{
public:
	CharacterCoin(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition);
	~CharacterCoin();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	// Collect coin functions.
	bool GetCollected() { return mCollected; }

private:
	// Get sprite dimensions.
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	// Animation variables.
	float mFrameDelay;
	int mCurrentFrame;

	// Check to see if a character has collected a coin.
	bool mCollected;
};