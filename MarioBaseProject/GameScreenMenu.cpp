#include "GameScreenMenu.h"
#include <iostream>

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
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
	delete gOverworld;
	gOverworld = NULL;

	delete gUnderworld;
	gUnderworld = NULL;

	delete gameStartSound;
	gameStartSound = NULL;

	delete coinSound;
	coinSound = NULL;

	delete dieSound;
	dieSound = NULL;

	delete flagpoleSound;
	flagpoleSound = NULL;

	delete gameOverSound;
	gameOverSound = NULL;

	delete kickSound;
	kickSound = NULL;

	delete pauseSound;
	pauseSound = NULL;

	delete pipeSound;
	pipeSound = NULL;

	delete startSound;
	startSound = NULL;

	delete thwompSound;
	thwompSound = NULL;

	delete victorySound;
	victorySound = NULL;

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
	SDL_DestroyTexture(copyrightText);
	SDL_DestroyTexture(start1Text);
	SDL_DestroyTexture(start2Text);
	SDL_DestroyTexture(pauseText);
	SDL_DestroyTexture(titleText);
	SDL_DestroyTexture(multiplyText);
	SDL_DestroyTexture(marioText);
	SDL_DestroyTexture(marioScoreText);
	SDL_DestroyTexture(marioFinalScoreText);
	SDL_DestroyTexture(marioWinText);
	SDL_DestroyTexture(luigiText);
	SDL_DestroyTexture(luigiScoreText);
	SDL_DestroyTexture(luigiFinalScoreText);
	SDL_DestroyTexture(luigiWinText);
	SDL_DestroyTexture(peachText);
	SDL_DestroyTexture(gameOverText);
	SDL_DestroyTexture(nextLevelText);
	SDL_DestroyTexture(escapeText);
	SDL_DestroyTexture(exitText);
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

	Mix_PlayChannel(-1, gameStartSound, 0);

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