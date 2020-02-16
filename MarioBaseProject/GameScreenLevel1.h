#pragma once

#include "Commons.h"
#include "GameScreen.h"

class Texture2D;
class Character;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	// Character pointers
	Character* characterMario;
	Character* characterLuigi;
private:
	bool SetUpLevel();
	Texture2D* mBackgroundTexture;
};