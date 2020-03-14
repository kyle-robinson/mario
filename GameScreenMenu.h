#pragma once

#include "Commons.h"
#include "GameScreen.h"
#include "Texture2D.h"

#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

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