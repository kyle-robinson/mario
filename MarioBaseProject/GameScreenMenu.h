#pragma once

#include "Commons.h"
#include "GameScreen.h"
#include "Texture2D.h"

#include <SDL_ttf.h>
#include <SDL_mixer.h>
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

	// FONTS
	void LoadFont();

	TTF_Font* fontVeryLarge;
	TTF_Font* fontLarge;
	TTF_Font* fontMedium;
	TTF_Font* fontSmall;

	SDL_Color colorFg;
	SDL_Color colorBg;
	SDL_Color colorYellow;

	SDL_Surface* startTextSurface;
	SDL_Texture* startText;
	SDL_Rect startTextRect;

	SDL_Surface* exitTextSurface;
	SDL_Texture* exitText;
	SDL_Rect exitTextRect;

	SDL_Surface* copyrightTextSurface;
	SDL_Texture* copyrightText;
	SDL_Rect copyrightTextRect;

	// SOUNDS
	void LoadAudio();

	Mix_Chunk* startSound;
};