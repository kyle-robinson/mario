#include "GameScreenScore.h"
#include <iostream>

GameScreenScore::GameScreenScore(SDL_Renderer* renderer) : GameScreen(renderer)
{
	titleTextRect.x = titleTextRect.y = 0;
	marioTextRect.x = marioTextRect.y = 0;
	marioScoreTextRect.x = marioScoreTextRect.y = 0;
	luigiTextRect.x = luigiTextRect.y = 0;
	luigiScoreTextRect.x = luigiScoreTextRect.y = 0;
	peachTextRect.x = peachTextRect.y = 0;
	winTextRect.x = winTextRect.y = 0;
	exitTextRect.x = exitTextRect.y = 0;

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

	// FONTS
	delete fontVeryLarge;
	fontVeryLarge = NULL;

	delete fontLarge;
	fontLarge = NULL;

	delete fontMedium;
	fontMedium = NULL;

	delete fontSmall;
	fontSmall = NULL;

	SDL_DestroyTexture(titleText);
	SDL_DestroyTexture(marioText);
	SDL_DestroyTexture(marioScoreText);
	SDL_DestroyTexture(luigiText);
	SDL_DestroyTexture(luigiScoreText);
	SDL_DestroyTexture(peachText);
	SDL_DestroyTexture(winText);
	SDL_DestroyTexture(exitText);

	// SOUNDS
	delete coinSound;
	coinSound = NULL;

	delete victorySound;
	victorySound = NULL;
}

void GameScreenScore::Render()
{
	mBlackBackground->Render(Vector2D(), SDL_FLIP_NONE);
	
	titleTextRect.x = (SCREEN_WIDTH / 2) - (titleTextRect.w / 2);
	titleTextRect.y = 20;
	SDL_RenderCopy(mRenderer, titleText, NULL, &titleTextRect);

	characterMario->Render(Vector2D(100, 110), SDL_FLIP_NONE);
	characterLuigi->Render(Vector2D(100, 220), SDL_FLIP_NONE);
	characterPeach->Render(Vector2D(), SDL_FLIP_NONE);

	winTextRect.x = (SCREEN_WIDTH / 2) - (winTextRect.w / 2);
	winTextRect.y = SCREEN_HEIGHT - 100;
	SDL_RenderCopy(mRenderer, winText, NULL, &winTextRect);

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
	LoadFont();

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

	return true;
}

void GameScreenScore::LoadFont()
{
	fontVeryLarge = TTF_OpenFont("Fonts/MarioFont.ttf", 72);
	fontLarge = TTF_OpenFont("Fonts/MarioFont.ttf", 36);
	fontMedium = TTF_OpenFont("Fonts/MarioFont.ttf", 24);
	fontSmall = TTF_OpenFont("Fonts/MarioFont.ttf", 18);

	colorFg = { 255, 255, 255, 255 };
	colorBg = { 0, 0, 0, 255 };
	colorRed = { 240, 102, 102, 255 };
	colorGreen = { 102, 240, 102, 255 };
	colorPink = { 255, 153, 255, 255 };

	// TITLE
	titleTextSurface = TTF_RenderText_Solid(fontLarge, "PLAYER SCORES", colorFg);
	titleText = SDL_CreateTextureFromSurface(mRenderer, titleTextSurface);
	SDL_QueryTexture(titleText, NULL, NULL, &titleTextRect.w, &titleTextRect.h);

	SDL_FreeSurface(titleTextSurface);
	titleTextSurface = nullptr;

	// MARIO
	marioTextSurface = TTF_RenderText_Solid(fontMedium, "MARIO", colorRed);
	marioText = SDL_CreateTextureFromSurface(mRenderer, marioTextSurface);
	SDL_QueryTexture(marioText, NULL, NULL, &marioTextRect.w, &marioTextRect.h);

	SDL_FreeSurface(marioTextSurface);
	marioTextSurface = nullptr;

	// MARIO SCORE
	marioScoreTextSurface = TTF_RenderText_Solid(fontMedium, "MARIO SCORE", colorFg);
	marioScoreText = SDL_CreateTextureFromSurface(mRenderer, marioScoreTextSurface);
	SDL_QueryTexture(marioScoreText, NULL, NULL, &marioScoreTextRect.w, &marioScoreTextRect.h);

	SDL_FreeSurface(marioScoreTextSurface);
	marioScoreTextSurface = nullptr;

	// LUIGI
	luigiTextSurface = TTF_RenderText_Solid(fontMedium, "LUIGI", colorGreen);
	luigiText = SDL_CreateTextureFromSurface(mRenderer, luigiTextSurface);
	SDL_QueryTexture(luigiText, NULL, NULL, &luigiTextRect.w, &luigiTextRect.h);

	SDL_FreeSurface(luigiTextSurface);
	luigiTextSurface = nullptr;

	// LUIGI SCORE
	luigiScoreTextSurface = TTF_RenderText_Solid(fontMedium, "LUIGI SCORE", colorFg);
	luigiScoreText = SDL_CreateTextureFromSurface(mRenderer, luigiScoreTextSurface);
	SDL_QueryTexture(luigiScoreText, NULL, NULL, &luigiScoreTextRect.w, &luigiScoreTextRect.h);

	SDL_FreeSurface(luigiScoreTextSurface);
	luigiScoreTextSurface = nullptr;

	// PEACH
	peachTextSurface = TTF_RenderText_Solid(fontMedium, "PEACH", colorPink);
	peachText = SDL_CreateTextureFromSurface(mRenderer, peachTextSurface);
	SDL_QueryTexture(peachText, NULL, NULL, &peachTextRect.w, &peachTextRect.h);

	SDL_FreeSurface(peachTextSurface);
	peachTextSurface = nullptr;

	// WIN
	winTextSurface = TTF_RenderText_Solid(fontMedium, "PLAYER 'X' WINS!", colorFg);
	winText = SDL_CreateTextureFromSurface(mRenderer, winTextSurface);
	SDL_QueryTexture(winText, NULL, NULL, &winTextRect.w, &winTextRect.h);

	SDL_FreeSurface(winTextSurface);
	winTextSurface = nullptr;

	// EXIT
	exitTextSurface = TTF_RenderText_Solid(fontMedium, "PRESS 'ESC' TO EXIT", colorFg);
	exitText = SDL_CreateTextureFromSurface(mRenderer, exitTextSurface);
	SDL_QueryTexture(exitText, NULL, NULL, &exitTextRect.w, &exitTextRect.h);

	SDL_FreeSurface(exitTextSurface);
	exitTextSurface = nullptr;
}

void GameScreenScore::LoadAudio()
{
	coinSound = Mix_LoadWAV("Music/WAV/1up.wav");
	if (coinSound == NULL)
	{
		cout << "Failed to load coin sound! Error: " << Mix_GetError() << endl;
	}

	victorySound = Mix_LoadWAV("Music/WAV/Respawn.wav");
	if (victorySound == NULL)
	{
		cout << "Failed to load victory sound! Error: " << Mix_GetError() << endl;
	}
}