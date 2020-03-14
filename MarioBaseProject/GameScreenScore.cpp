#include "GameScreenScore.h"
#include <iostream>

GameScreenScore::GameScreenScore(SDL_Renderer* renderer) : GameScreen(renderer)
{
	titleTextRect.x = titleTextRect.y = 0;
	multiplyTextRect.x = multiplyTextRect.y = 0;
	marioScoreTextRect.x = marioScoreTextRect.y = 0;
	luigiScoreTextRect.x = luigiScoreTextRect.y = 0;
	peachTextRect.x = peachTextRect.y = 0;
	marioWinTextRect.x = marioWinTextRect.y = 0;
	luigiWinTextRect.x = luigiWinTextRect.y = 0;
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

	delete coinTexture;
	coinTexture = NULL;

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
	SDL_DestroyTexture(multiplyText);
	SDL_DestroyTexture(marioScoreText);
	SDL_DestroyTexture(luigiScoreText);
	SDL_DestroyTexture(peachText);
	SDL_DestroyTexture(marioWinText);
	SDL_DestroyTexture(luigiWinText);
	SDL_DestroyTexture(exitText);

	// SOUNDS
	delete victorySound;
	victorySound = NULL;
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

	marioScoreTextRect.x = 210;
	marioScoreTextRect.y = 117;
	SDL_RenderCopy(mRenderer, marioScoreText, NULL, &marioScoreTextRect);

	if (level1_mario_peach || level2_mario_peach)
	{
		multiplyTextRect.x = 300;
		multiplyTextRect.y = 121;
		SDL_RenderCopy(mRenderer, multiplyText, NULL, &multiplyTextRect);
	}

	if (level1_mario_peach && !level1_mario_peach)
	{
		characterPeach->Render(Vector2D(330, 110), SDL_FLIP_NONE);
	}
	else if (!level1_mario_peach && level1_mario_peach)
	{
		characterPeach->Render(Vector2D(330, 110), SDL_FLIP_NONE);
	}
	else if (level1_mario_peach && level1_mario_peach)
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

	luigiScoreTextRect.x = 210;
	luigiScoreTextRect.y = 227;
	SDL_RenderCopy(mRenderer, luigiScoreText, NULL, &luigiScoreTextRect);

	if (level1_luigi_peach || level2_luigi_peach)
	{
		multiplyTextRect.x = 300;
		multiplyTextRect.y = 231;
		SDL_RenderCopy(mRenderer, multiplyText, NULL, &multiplyTextRect);
	}

	if (level1_luigi_peach && !level1_luigi_peach)
	{
		characterPeach->Render(Vector2D(330, 220), SDL_FLIP_NONE);
	}
	else if (!level1_luigi_peach && level1_luigi_peach)
	{
		characterPeach->Render(Vector2D(330, 220), SDL_FLIP_NONE);
	}
	else if (level1_luigi_peach && level1_luigi_peach)
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
	LoadFont();
	LoadScores();

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

	// MULTIPLY
	multiplyTextSurface = TTF_RenderText_Solid(fontMedium, "x", colorFg);
	multiplyText = SDL_CreateTextureFromSurface(mRenderer, multiplyTextSurface);
	SDL_QueryTexture(multiplyText, NULL, NULL, &multiplyTextRect.w, &multiplyTextRect.h);

	SDL_FreeSurface(multiplyTextSurface);
	multiplyTextSurface = nullptr;

	// PEACH
	peachTextSurface = TTF_RenderText_Solid(fontMedium, "PEACH", colorPink);
	peachText = SDL_CreateTextureFromSurface(mRenderer, peachTextSurface);
	SDL_QueryTexture(peachText, NULL, NULL, &peachTextRect.w, &peachTextRect.h);

	SDL_FreeSurface(peachTextSurface);
	peachTextSurface = nullptr;

	// WIN
	marioWinTextSurface = TTF_RenderText_Solid(fontMedium, "PLAYER 'MARIO' WINS!", colorRed);
	marioWinText = SDL_CreateTextureFromSurface(mRenderer, marioWinTextSurface);
	SDL_QueryTexture(marioWinText, NULL, NULL, &marioWinTextRect.w, &marioWinTextRect.h);

	SDL_FreeSurface(marioWinTextSurface);
	marioWinTextSurface = nullptr;

	luigiWinTextSurface = TTF_RenderText_Solid(fontMedium, "PLAYER 'LUIGI' WINS!", colorGreen);
	luigiWinText = SDL_CreateTextureFromSurface(mRenderer, luigiWinTextSurface);
	SDL_QueryTexture(luigiWinText, NULL, NULL, &luigiWinTextRect.w, &luigiWinTextRect.h);

	SDL_FreeSurface(luigiWinTextSurface);
	luigiWinTextSurface = nullptr;

	// EXIT
	exitTextSurface = TTF_RenderText_Solid(fontMedium, "PRESS 'ESC' TO EXIT", colorFg);
	exitText = SDL_CreateTextureFromSurface(mRenderer, exitTextSurface);
	SDL_QueryTexture(exitText, NULL, NULL, &exitTextRect.w, &exitTextRect.h);

	SDL_FreeSurface(exitTextSurface);
	exitTextSurface = nullptr;
}

void GameScreenScore::LoadAudio()
{
	victorySound = Mix_LoadWAV("Music/WAV/Respawn.wav");
	if (victorySound == NULL)
	{
		cout << "Failed to load victory sound! Error: " << Mix_GetError() << endl;
	}
}

void GameScreenScore::LoadScores()
{
	// MARIO SCORE
	marioScoreString = to_string(marioScore);
	marioScoreTextSurface = TTF_RenderText_Solid(fontMedium, marioScoreString.c_str(), colorFg);
	marioScoreText = SDL_CreateTextureFromSurface(mRenderer, marioScoreTextSurface);
	SDL_QueryTexture(marioScoreText, NULL, NULL, &marioScoreTextRect.w, &marioScoreTextRect.h);

	SDL_FreeSurface(marioScoreTextSurface);
	marioScoreTextSurface = nullptr;

	// LUIGI SCORE
	luigiScoreString = to_string(luigiScore);
	luigiScoreTextSurface = TTF_RenderText_Solid(fontMedium, luigiScoreString.c_str(), colorFg);
	luigiScoreText = SDL_CreateTextureFromSurface(mRenderer, luigiScoreTextSurface);
	SDL_QueryTexture(luigiScoreText, NULL, NULL, &luigiScoreTextRect.w, &luigiScoreTextRect.h);

	SDL_FreeSurface(luigiScoreTextSurface);
	luigiScoreTextSurface = nullptr;
}