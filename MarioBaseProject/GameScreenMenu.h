#pragma once

#include "GameScreen.h"
#include "Texture2D.h"

class Texture2D;

class GameScreenMenu : GameScreen
{
public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	bool SetUpMenu();
	Texture2D* mBlackBackground;
	Texture2D* mMarioLogo;
};