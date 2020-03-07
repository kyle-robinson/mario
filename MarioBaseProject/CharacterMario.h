#pragma once

#include "Character.h"
//#include "SoundEffect.h"
#include <SDL_mixer.h>

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();

protected:
	void Render();
	void Update(float deltaTime, SDL_Event e);
	void Keyboard(float deltaTime, SDL_Event e);

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	
	float mFrameDelay;
	int mCurrentFrame;
	
	//Mix_Chunk* gJump;
	//string audioPath;

	void AnimateMario(float deltaTime, SDL_Event e);
};