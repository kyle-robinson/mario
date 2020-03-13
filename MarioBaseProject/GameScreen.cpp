#include "GameScreen.h"
#include <iostream>

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	paused = false;
}

GameScreen::~GameScreen()
{
	mRenderer = NULL;

	// FONTS
	delete fontVeryLarge;
	fontVeryLarge = NULL;

	delete fontLarge;
	fontLarge = NULL;

	delete fontMedium;
	fontMedium = NULL;

	delete fontSmall;
	fontSmall = NULL;

	SDL_DestroyTexture(start1Text);
	SDL_DestroyTexture(start2Text);
	SDL_DestroyTexture(pauseText);
	SDL_DestroyTexture(marioText);
	SDL_DestroyTexture(marioScoreText);
	SDL_DestroyTexture(luigiText);
	SDL_DestroyTexture(luigiScoreText);
	SDL_DestroyTexture(peachText);
	SDL_DestroyTexture(gameOverText);
	SDL_DestroyTexture(nextLevelText);
	SDL_DestroyTexture(escapeText);

	// SOUNDS
	delete gOverworld;
	gOverworld = NULL;

	delete gUnderworld;
	gUnderworld = NULL;

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
}

void GameScreen::Render()
{

}

void GameScreen::Update(float deltaTime, SDL_Event e)
{

}

void GameScreen::CheckPaused(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_p:
			Mix_PlayChannel(-1, pauseSound, 0);
			paused = !paused;
			break;
		}
		break;
	}
}

bool GameScreen::LoadAudio()
{
	gOverworld = Mix_LoadMUS("Music/OGG/Mario_Overworld.ogg");
	if (gOverworld == NULL)
	{
		cout << "Failed to load overworld theme! Error: " << Mix_GetError() << endl;
		return false;
	}

	gUnderworld = Mix_LoadMUS("Music/OGG/Mario_Underworld.ogg");
	if (gUnderworld == NULL)
	{
		cout << "Failed to load underworld theme! Error: " << Mix_GetError() << endl;
		return false;
	}

	coinSound = Mix_LoadWAV("Music/WAV/Coin.wav");
	if (coinSound == NULL)
	{
		cout << "Failed to load coin sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	dieSound = Mix_LoadWAV("Music/WAV/Die.wav");
	if (dieSound == NULL)
	{
		cout << "Failed to load die sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	flagpoleSound = Mix_LoadWAV("Music/WAV/Flagpole.wav");
	if (flagpoleSound == NULL)
	{
		cout << "Failed to load flagpole sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	gameOverSound = Mix_LoadWAV("Music/WAV/GameOver.wav");
	if (gameOverSound == NULL)
	{
		cout << "Failed to load game over sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	kickSound = Mix_LoadWAV("Music/WAV/Kick.wav");
	if (kickSound == NULL)
	{
		cout << "Failed to load kick sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	pauseSound = Mix_LoadWAV("Music/WAV/Pause.wav");
	if (pauseSound == NULL)
	{
		cout << "Failed to load pause sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	pipeSound = Mix_LoadWAV("Music/WAV/Pipe.wav");
	if (pipeSound == NULL)
	{
		cout << "Failed to load pipe sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	startSound = Mix_LoadWAV("Music/WAV/LevelStart.wav");
	if (startSound == NULL)
	{
		cout << "Failed to load start sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	thwompSound = Mix_LoadWAV("Music/WAV/Thwomp.wav");
	if (thwompSound == NULL)
	{
		cout << "Failed to load thwomp sound! Error: " << Mix_GetError() << endl;
		return false;
	}

	return true;
}

void GameScreen::LoadFont()
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

	// LEVEL 1 - START
	start1TextSurface = TTF_RenderText_Solid(fontLarge, "LEVEL 1 START", colorFg);
	start1Text = SDL_CreateTextureFromSurface(mRenderer, start1TextSurface);
	SDL_QueryTexture(start1Text, NULL, NULL, &start1TextRect.w, &start1TextRect.h);

	SDL_FreeSurface(start1TextSurface);
	start1TextSurface = nullptr;

	// LEVEL 2 - START
	start2TextSurface = TTF_RenderText_Solid(fontLarge, "LEVEL 2 START", colorFg);
	start2Text = SDL_CreateTextureFromSurface(mRenderer, start2TextSurface);
	SDL_QueryTexture(start2Text, NULL, NULL, &start2TextRect.w, &start2TextRect.h);

	SDL_FreeSurface(start2TextSurface);
	start2TextSurface = nullptr;

	// PAUSE
	pauseTextSurface = TTF_RenderText_Solid(fontVeryLarge, "paused", colorFg);
	pauseText = SDL_CreateTextureFromSurface(mRenderer, pauseTextSurface);
	SDL_QueryTexture(pauseText, NULL, NULL, &pauseTextRect.w, &pauseTextRect.h);

	SDL_FreeSurface(pauseTextSurface);
	pauseTextSurface = nullptr;

	// MARIO
	marioTextSurface = TTF_RenderText_Solid(fontMedium, "mario score:", colorRed);
	marioText = SDL_CreateTextureFromSurface(mRenderer, marioTextSurface);
	SDL_QueryTexture(marioText, NULL, NULL, &marioTextRect.w, &marioTextRect.h);

	SDL_FreeSurface(marioTextSurface);
	marioTextSurface = nullptr;

	// MARIO SCORE
	marioScoreString = to_string(marioScore);
	marioScoreTextSurface = TTF_RenderText_Solid(fontSmall, marioScoreString.c_str(), colorFg);
	marioScoreText = SDL_CreateTextureFromSurface(mRenderer, marioScoreTextSurface);
	SDL_QueryTexture(marioScoreText, NULL, NULL, &marioScoreTextRect.w, &marioScoreTextRect.h);

	SDL_FreeSurface(marioScoreTextSurface);
	marioScoreTextSurface = nullptr;

	// LUIGI
	luigiTextSurface = TTF_RenderText_Solid(fontMedium, "luigi score:", colorGreen);
	luigiText = SDL_CreateTextureFromSurface(mRenderer, luigiTextSurface);
	SDL_QueryTexture(luigiText, NULL, NULL, &luigiTextRect.w, &luigiTextRect.h);

	SDL_FreeSurface(luigiTextSurface);
	luigiTextSurface = nullptr;

	// LUIGI SCORE
	luigiScoreString = to_string(luigiScore);
	luigiScoreTextSurface = TTF_RenderText_Solid(fontSmall, luigiScoreString.c_str(), colorFg);
	luigiScoreText = SDL_CreateTextureFromSurface(mRenderer, luigiScoreTextSurface);
	SDL_QueryTexture(luigiScoreText, NULL, NULL, &luigiScoreTextRect.w, &luigiScoreTextRect.h);

	SDL_FreeSurface(luigiScoreTextSurface);
	luigiScoreTextSurface = nullptr;

	// PEACH
	peachTextSurface = TTF_RenderText_Solid(fontLarge, "princess peach has been rescued", colorPink);
	peachText = SDL_CreateTextureFromSurface(mRenderer, peachTextSurface);
	SDL_QueryTexture(peachText, NULL, NULL, &peachTextRect.w, &peachTextRect.h);

	SDL_FreeSurface(peachTextSurface);
	peachTextSurface = nullptr;

	// GAME OVER
	gameOverTextSurface = TTF_RenderText_Solid(fontLarge, "game over", colorFg);
	gameOverText = SDL_CreateTextureFromSurface(mRenderer, gameOverTextSurface);
	SDL_QueryTexture(gameOverText, NULL, NULL, &gameOverTextRect.w, &gameOverTextRect.h);

	SDL_FreeSurface(gameOverTextSurface);
	gameOverTextSurface = nullptr;

	// NEXT LEVEL
	nextLevelTextSurface = TTF_RenderText_Solid(fontSmall, "'ENTER' - LEVEL 2 || 'ESC' - EXIT", colorFg);
	nextLevelText = SDL_CreateTextureFromSurface(mRenderer, nextLevelTextSurface);
	SDL_QueryTexture(nextLevelText, NULL, NULL, &nextLevelTextRect.w, &nextLevelTextRect.h);

	SDL_FreeSurface(nextLevelTextSurface);
	nextLevelTextSurface = nullptr;

	// ESCAPE
	escapeTextSurface = TTF_RenderText_Solid(fontSmall, "'ESC' - EXIT", colorFg);
	escapeText = SDL_CreateTextureFromSurface(mRenderer, escapeTextSurface);
	SDL_QueryTexture(escapeText, NULL, NULL, &escapeTextRect.w, &escapeTextRect.h);

	SDL_FreeSurface(escapeTextSurface);
	escapeTextSurface = nullptr;
}

void GameScreen::LoadPlayerScores()
{
	// MARIO SCORE
	marioScoreString = to_string(marioScore);
	marioScoreTextSurface = TTF_RenderText_Solid(fontSmall, marioScoreString.c_str(), colorFg);
	marioScoreText = SDL_CreateTextureFromSurface(mRenderer, marioScoreTextSurface);
	SDL_QueryTexture(marioScoreText, NULL, NULL, &marioScoreTextRect.w, &marioScoreTextRect.h);

	SDL_FreeSurface(marioScoreTextSurface);
	marioScoreTextSurface = nullptr;

	// LUIGI SCORE
	luigiScoreString = to_string(luigiScore);
	luigiScoreTextSurface = TTF_RenderText_Solid(fontSmall, luigiScoreString.c_str(), colorFg);
	luigiScoreText = SDL_CreateTextureFromSurface(mRenderer, luigiScoreTextSurface);
	SDL_QueryTexture(luigiScoreText, NULL, NULL, &luigiScoreTextRect.w, &luigiScoreTextRect.h);

	SDL_FreeSurface(luigiScoreTextSurface);
	luigiScoreTextSurface = nullptr;
}