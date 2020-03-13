#include "GameScreenMenu.h"
#include <iostream>

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	startTextRect.x = startTextRect.y = 0;
	exitTextRect.x = exitTextRect.y = 0;
	copyrightTextRect.x = copyrightTextRect.y = 0;

	SetUpMenu();
}

GameScreenMenu::~GameScreenMenu()
{
	// OBJECTS
	delete mBlackBackground;
	mBlackBackground = NULL;

	delete mMarioLogo;
	mMarioLogo = NULL;

	// SOUNDS
	delete startSound;
	startSound = NULL;

	// FONTS
	delete fontVeryLarge;
	fontVeryLarge = NULL;

	delete fontLarge;
	fontLarge = NULL;

	delete fontMedium;
	fontMedium = NULL;

	delete fontSmall;
	fontSmall = NULL;

	SDL_DestroyTexture(startText);
	SDL_DestroyTexture(exitText);
	SDL_DestroyTexture(copyrightText);
}

void GameScreenMenu::Render()
{
	mBlackBackground->Render(Vector2D(), SDL_FLIP_NONE);
	mMarioLogo->Render(Vector2D(((SCREEN_WIDTH / 2) - (mMarioLogo->GetWidth() / 2)), 50), SDL_FLIP_NONE);

	startTextRect.x = (SCREEN_WIDTH / 2) - (startTextRect.w / 2);
	startTextRect.y = ((SCREEN_HEIGHT / 2) - (startTextRect.h / 2)) + 60;
	SDL_RenderCopy(mRenderer, startText, NULL, &startTextRect);

	exitTextRect.x = (SCREEN_WIDTH / 2) - (exitTextRect.w / 2);
	exitTextRect.y = ((SCREEN_HEIGHT / 2) - (exitTextRect.h / 2)) + 100;
	SDL_RenderCopy(mRenderer, exitText, NULL, &exitTextRect);

	copyrightTextRect.x = (SCREEN_WIDTH / 2) - (copyrightTextRect.w / 2);
	copyrightTextRect.y = ((SCREEN_HEIGHT / 2) - (copyrightTextRect.h / 2)) + 160;
	SDL_RenderCopy(mRenderer, copyrightText, NULL, &copyrightTextRect);
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{

}

bool GameScreenMenu::SetUpMenu()
{
	LoadAudio();
	LoadFont();

	Mix_PlayChannel(-1, startSound, 0);

	mBlackBackground = new Texture2D(mRenderer);
	if (!mBlackBackground->LoadFromFile("Images/Levels/Menu/Black_Bg_Small.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	mMarioLogo = new Texture2D(mRenderer);
	if (!mMarioLogo->LoadFromFile("Images/Levels/Menu/MarioLogo.png"))
	{
		cout << "Failed to load mario logo!";
		return false;
	}

	return true;
}

void GameScreenMenu::LoadAudio()
{
	startSound = Mix_LoadWAV("Music/WAV/TitleTheme.wav");
	if (startSound == NULL)
	{
		cout << "Failed to load start sound! Error: " << Mix_GetError() << endl;
	}
}

void GameScreenMenu::LoadFont()
{
	fontVeryLarge = TTF_OpenFont("Fonts/MarioFont.ttf", 72);
	fontLarge = TTF_OpenFont("Fonts/MarioFont.ttf", 36);
	fontMedium = TTF_OpenFont("Fonts/MarioFont.ttf", 24);
	fontSmall = TTF_OpenFont("Fonts/MarioFont.ttf", 18);

	colorFg = { 255, 255, 255, 255 };
	colorBg = { 0, 0, 0, 255 };
	colorYellow = {255, 156, 51, 255};

	// START
	startTextSurface = TTF_RenderText_Solid(fontMedium, "'ENTER' TO START", colorYellow);
	startText = SDL_CreateTextureFromSurface(mRenderer, startTextSurface);
	SDL_QueryTexture(startText, NULL, NULL, &startTextRect.w, &startTextRect.h);

	SDL_FreeSurface(startTextSurface);
	startTextSurface = nullptr;

	// EXIT
	exitTextSurface = TTF_RenderText_Solid(fontMedium, "'ESC' TO EXIT", colorYellow);
	exitText = SDL_CreateTextureFromSurface(mRenderer, exitTextSurface);
	SDL_QueryTexture(exitText, NULL, NULL, &exitTextRect.w, &exitTextRect.h);

	SDL_FreeSurface(exitTextSurface);
	exitTextSurface = nullptr;

	// COPYRIGHT
	copyrightTextSurface = TTF_RenderText_Solid(fontMedium, "©1983. ©1988. ©1999 NINTENDO", colorFg);
	copyrightText = SDL_CreateTextureFromSurface(mRenderer, copyrightTextSurface);
	SDL_QueryTexture(copyrightText, NULL, NULL, &copyrightTextRect.w, &copyrightTextRect.h);

	SDL_FreeSurface(copyrightTextSurface);
	copyrightTextSurface = nullptr;
}