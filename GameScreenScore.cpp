#include "GameScreenScore.h"
#include <iostream>

GameScreenScore::GameScreenScore(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpScreen();
}

GameScreenScore::~GameScreenScore()
{
	// OBJECTS
	delete mBlackBackground;
	mBlackBackground = NULL;

	delete characterMario;
	characterMario = NULL;

	delete characterLuigi;
	characterLuigi = NULL;

	delete characterPeach;
	characterPeach = NULL;

	delete coinTexture;
	coinTexture = NULL;

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

void GameScreenScore::Render()
{
	mBlackBackground->Render(Vector2D(), SDL_FLIP_NONE);
	
	titleTextRect.x = (SCREEN_WIDTH / 2) - (titleTextRect.w / 2);
	titleTextRect.y = 20;
	SDL_RenderCopy(mRenderer, titleText, NULL, &titleTextRect);

	// MARIO SCORE
	characterMario->Render(Vector2D(100, 110), SDL_FLIP_NONE);
	
	multiplyTextRect.x = 150;
	multiplyTextRect.y = 121;
	SDL_RenderCopy(mRenderer, multiplyText, NULL, &multiplyTextRect);

	coinTexture->Render(Vector2D(170, 119), SDL_FLIP_NONE);

	marioFinalScoreTextRect.x = 210;
	marioFinalScoreTextRect.y = 117;
	SDL_RenderCopy(mRenderer, marioFinalScoreText, NULL, &marioFinalScoreTextRect);

	if (marioSavedPeach >= 1)
	{
		multiplyTextRect.x = 300;
		multiplyTextRect.y = 121;
		SDL_RenderCopy(mRenderer, multiplyText, NULL, &multiplyTextRect);
	}

	if (marioSavedPeach == 1)
	{
		characterPeach->Render(Vector2D(330, 110), SDL_FLIP_NONE);
	}
	else if (marioSavedPeach == 2)
	{
		characterPeach->Render(Vector2D(330, 110), SDL_FLIP_NONE);
		characterPeach->Render(Vector2D(370, 110), SDL_FLIP_NONE);
	}

	// LUIGI SCORE
	characterLuigi->Render(Vector2D(100, 220), SDL_FLIP_NONE);

	multiplyTextRect.x = 150;
	multiplyTextRect.y = 231;
	SDL_RenderCopy(mRenderer, multiplyText, NULL, &multiplyTextRect);

	coinTexture->Render(Vector2D(170, 229), SDL_FLIP_NONE);

	luigiFinalScoreTextRect.x = 210;
	luigiFinalScoreTextRect.y = 227;
	SDL_RenderCopy(mRenderer, luigiFinalScoreText, NULL, &luigiFinalScoreTextRect);

	if (luigiSavedPeach >= 1)
	{
		multiplyTextRect.x = 300;
		multiplyTextRect.y = 231;
		SDL_RenderCopy(mRenderer, multiplyText, NULL, &multiplyTextRect);
	}

	if (luigiSavedPeach == 1)
	{
		characterPeach->Render(Vector2D(330, 220), SDL_FLIP_NONE);
	}
	else if (luigiSavedPeach == 2)
	{
		characterPeach->Render(Vector2D(330, 220), SDL_FLIP_NONE);
		characterPeach->Render(Vector2D(370, 220), SDL_FLIP_NONE);
	}

	// WINNER
	if (marioScore > luigiScore)
	{
		marioWinTextRect.x = (SCREEN_WIDTH / 2) - (marioWinTextRect.w / 2);
		marioWinTextRect.y = SCREEN_HEIGHT - 100;
		SDL_RenderCopy(mRenderer, marioWinText, NULL, &marioWinTextRect);
	}
	else if (luigiScore > marioScore)
	{
		luigiWinTextRect.x = (SCREEN_WIDTH / 2) - (luigiWinTextRect.w / 2);
		luigiWinTextRect.y = SCREEN_HEIGHT - 100;
		SDL_RenderCopy(mRenderer, luigiWinText, NULL, &luigiWinTextRect);
	}

	// EXIT
	exitTextRect.x = (SCREEN_WIDTH / 2) - (exitTextRect.w / 2);
	exitTextRect.y = SCREEN_HEIGHT - 50;
	SDL_RenderCopy(mRenderer, exitText, NULL, &exitTextRect);
}

void GameScreenScore::Update(float deltaTime, SDL_Event e)
{

}

bool GameScreenScore::SetUpScreen()
{
	LoadAudio();
	
	OpenInFiles();
	LoadFont();
	LoadPlayerScores();

	Mix_PlayChannel(-1, victorySound, 0);

	mBlackBackground = new Texture2D(mRenderer);
	if (!mBlackBackground->LoadFromFile("Images/Levels/Menu/Black_Bg_Small.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	characterMario = new Texture2D(mRenderer);
	if (!characterMario->LoadFromFile("Images/Characters/Mario.png"))
	{
		cout << "Failed to load mario texture!";
		return false;
	}

	characterLuigi = new Texture2D(mRenderer);
	if (!characterLuigi->LoadFromFile("Images/Characters/Luigi.png"))
	{
		cout << "Failed to load luigi texture!";
		return false;
	}

	characterPeach = new Texture2D(mRenderer);
	if (!characterPeach->LoadFromFile("Images/Characters/Peach.png"))
	{
		cout << "Failed to load peach texture!";
		return false;
	}

	coinTexture = new Texture2D(mRenderer);
	if (!coinTexture->LoadFromFile("Images/Objects/CoinTexture.png"))
	{
		cout << "Failed to load coin texture!";
		return false;
	}

	return true;
}