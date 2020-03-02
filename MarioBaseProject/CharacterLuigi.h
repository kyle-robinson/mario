#pragma once

#include "Character.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterLuigi();

protected:
	void Render();
	void Update(float deltaTime, SDL_Event e);
	void Keyboard(float deltaTime, SDL_Event e);

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	float mFrameDelay;
	int mCurrentFrame;

	void AnimateLuigi(float deltaTime, SDL_Event e);
};