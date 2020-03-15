#include "GameScreen.h"
#include <iostream>

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}

GameScreen::~GameScreen()
{
	mRenderer = NULL;
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

	gameStartSound = Mix_LoadWAV("Music/WAV/TitleTheme.wav");
	if (gameStartSound == NULL)
	{
		cout << "Failed to load game start sound! Error: " << Mix_GetError() << endl;
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

	victorySound = Mix_LoadWAV("Music/WAV/Respawn.wav");
	if (victorySound == NULL)
	{
		cout << "Failed to load victory sound! Error: " << Mix_GetError() << endl;
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
	colorYellow = { 255, 156, 51, 255 };

	// START
	startTextSurface = TTF_RenderText_Solid(fontMedium, "'ENTER' TO START", colorYellow);
	startText = SDL_CreateTextureFromSurface(mRenderer, startTextSurface);
	SDL_QueryTexture(startText, NULL, NULL, &startTextRect.w, &startTextRect.h);

	SDL_FreeSurface(startTextSurface);
	startTextSurface = nullptr;

	// COPYRIGHT
	copyrightTextSurface = TTF_RenderText_Solid(fontMedium, "©1983. ©1988. ©1999 NINTENDO", colorFg);
	copyrightText = SDL_CreateTextureFromSurface(mRenderer, copyrightTextSurface);
	SDL_QueryTexture(copyrightText, NULL, NULL, &copyrightTextRect.w, &copyrightTextRect.h);

	SDL_FreeSurface(copyrightTextSurface);
	copyrightTextSurface = nullptr;

	// TITLE
	titleTextSurface = TTF_RenderText_Solid(fontLarge, "PLAYER SCORES", colorFg);
	titleText = SDL_CreateTextureFromSurface(mRenderer, titleTextSurface);
	SDL_QueryTexture(titleText, NULL, NULL, &titleTextRect.w, &titleTextRect.h);

	SDL_FreeSurface(titleTextSurface);
	titleTextSurface = nullptr;

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

	// MULTIPLY
	multiplyTextSurface = TTF_RenderText_Solid(fontMedium, "x", colorFg);
	multiplyText = SDL_CreateTextureFromSurface(mRenderer, multiplyTextSurface);
	SDL_QueryTexture(multiplyText, NULL, NULL, &multiplyTextRect.w, &multiplyTextRect.h);

	SDL_FreeSurface(multiplyTextSurface);
	multiplyTextSurface = nullptr;

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

	// MARIO FINAL SCORE
	marioFinalScoreString = to_string(marioScore);
	marioFinalScoreTextSurface = TTF_RenderText_Solid(fontMedium, marioFinalScoreString.c_str(), colorFg);
	marioFinalScoreText = SDL_CreateTextureFromSurface(mRenderer, marioFinalScoreTextSurface);
	SDL_QueryTexture(marioFinalScoreText, NULL, NULL, &marioFinalScoreTextRect.w, &marioFinalScoreTextRect.h);

	SDL_FreeSurface(marioFinalScoreTextSurface);
	marioFinalScoreTextSurface = nullptr;

	// MARIO WIN
	marioWinTextSurface = TTF_RenderText_Solid(fontMedium, "PLAYER 'MARIO' WINS!", colorRed);
	marioWinText = SDL_CreateTextureFromSurface(mRenderer, marioWinTextSurface);
	SDL_QueryTexture(marioWinText, NULL, NULL, &marioWinTextRect.w, &marioWinTextRect.h);

	SDL_FreeSurface(marioWinTextSurface);
	marioWinTextSurface = nullptr;

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

	// LUIGI FINAL SCORE
	luigiFinalScoreString = to_string(luigiScore);
	luigiFinalScoreTextSurface = TTF_RenderText_Solid(fontMedium, luigiFinalScoreString.c_str(), colorFg);
	luigiFinalScoreText = SDL_CreateTextureFromSurface(mRenderer, luigiFinalScoreTextSurface);
	SDL_QueryTexture(luigiFinalScoreText, NULL, NULL, &luigiFinalScoreTextRect.w, &luigiFinalScoreTextRect.h);

	SDL_FreeSurface(luigiFinalScoreTextSurface);
	luigiFinalScoreTextSurface = nullptr;

	// LUIGI WIN
	luigiWinTextSurface = TTF_RenderText_Solid(fontMedium, "PLAYER 'LUIGI' WINS!", colorGreen);
	luigiWinText = SDL_CreateTextureFromSurface(mRenderer, luigiWinTextSurface);
	SDL_QueryTexture(luigiWinText, NULL, NULL, &luigiWinTextRect.w, &luigiWinTextRect.h);

	SDL_FreeSurface(luigiWinTextSurface);
	luigiWinTextSurface = nullptr;

	// PEACH
	peachTextSurface = TTF_RenderText_Solid(fontLarge, "princess peach has been rescued", colorFg);
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
	nextLevelTextSurface = TTF_RenderText_Solid(fontSmall, "'ENTER' - LEVEL 2 || 'ESC' - EXIT", colorYellow);
	nextLevelText = SDL_CreateTextureFromSurface(mRenderer, nextLevelTextSurface);
	SDL_QueryTexture(nextLevelText, NULL, NULL, &nextLevelTextRect.w, &nextLevelTextRect.h);

	SDL_FreeSurface(nextLevelTextSurface);
	nextLevelTextSurface = nullptr;

	// ESCAPE
	escapeTextSurface = TTF_RenderText_Solid(fontSmall, "'ENTER' - VIEW SCORES || 'ESC' - EXIT", colorYellow);
	escapeText = SDL_CreateTextureFromSurface(mRenderer, escapeTextSurface);
	SDL_QueryTexture(escapeText, NULL, NULL, &escapeTextRect.w, &escapeTextRect.h);

	SDL_FreeSurface(escapeTextSurface);
	escapeTextSurface = nullptr;

	// EXIT
	exitTextSurface = TTF_RenderText_Solid(fontMedium, "PRESS 'ESC' TO EXIT", colorYellow);
	exitText = SDL_CreateTextureFromSurface(mRenderer, exitTextSurface);
	SDL_QueryTexture(exitText, NULL, NULL, &exitTextRect.w, &exitTextRect.h);

	SDL_FreeSurface(exitTextSurface);
	exitTextSurface = nullptr;
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

bool GameScreen::OpenOutFiles()
{
	// MARIO FILES
	marioFileOut.open("Score/MarioScore.txt", ostream::trunc);
	if (!marioFileOut)
	{
		cout << endl << "Failed to open MarioScore file for writing." << endl;
		return false;
	}
	else
	{
		cout << endl << "Opened MarioScore file for writing." << endl;
		marioFileOut << "0";
	}
	marioFileOut.close();

	marioFileOut.open("Score/MarioPeach.txt", ostream::trunc);
	if (!marioFileOut)
	{
		cout << endl << "Failed to open MarioPeach file for writing." << endl;
		return false;
	}
	else
	{
		cout << endl << "Opened MarioPeach file for writing." << endl;
		marioFileOut << "0";
	}
	marioFileOut.close();

	// LUIGI FILES
	luigiFileOut.open("Score/LuigiScore.txt", ostream::trunc);
	if (!luigiFileOut)
	{
		cout << endl << "Failed to open LuigiScore file for writing." << endl;
		return false;
	}
	else
	{
		cout << endl << "Opened LuigiScore file for writing." << endl;
		luigiFileOut << "0";
	}
	luigiFileOut.close();

	luigiFileOut.open("Score/LuigiPeach.txt", ostream::trunc);
	if (!luigiFileOut)
	{
		cout << endl << "Failed to open LuigiPeach file for writing." << endl;
		return false;
	}
	else
	{
		cout << endl << "Opened LuigiPeach file for writing." << endl;
		luigiFileOut << "0";
	}
	luigiFileOut.close();

	return true;
}

void GameScreen::WriteToFiles()
{
	marioFileOut.open("Score/MarioScore.txt", ostream::trunc);
	marioFileOut << marioScore;
	marioFileOut.close();

	marioFileOut.open("Score/MarioPeach.txt");
	marioFileOut << marioSavedPeach;
	marioFileOut.close();

	luigiFileOut.open("Score/LuigiScore.txt", ostream::trunc);
	luigiFileOut << luigiScore;
	luigiFileOut.close();

	luigiFileOut.open("Score/LuigiPeach.txt");
	luigiFileOut << luigiSavedPeach;
	luigiFileOut.close();
}

bool GameScreen::OpenInFiles()
{
	// MARIO FILES
	marioFileIn.open("Score/MarioScore.txt");
	if (!marioFileIn)
	{
		cout << endl << "Failed to open MarioScore file for reading." << endl;
		return false;
	}
	else
	{
		cout << endl << "Opened MarioScore file for reading." << endl;
		marioFileIn >> marioScore;
	}
	marioFileIn.close();

	marioFileIn.open("Score/MarioPeach.txt");
	if (!marioFileIn)
	{
		cout << endl << "Failed to open MarioPeach file for reading." << endl;
		return false;
	}
	else
	{
		cout << endl << "Opened MarioPeach file for reading." << endl;
		marioFileIn >> marioSavedPeach;
	}
	marioFileIn.close();

	// LUIGI FILES
	luigiFileIn.open("Score/LuigiScore.txt");
	if (!luigiFileIn)
	{
		cout << endl << "Failed to open LuigiScore file for reading." << endl;
		return false;
	}
	else
	{
		cout << endl << "Opened LuigiScore file for reading." << endl;
		luigiFileIn >> luigiScore;
	}
	luigiFileIn.close();

	luigiFileIn.open("Score/LuigiPeach.txt");
	if (!luigiFileIn)
	{
		cout << endl << "Failed to open LuigiPeach file for reading." << endl;
		return false;
	}
	else
	{
		cout << endl << "Opened LuigiPeach file for reading." << endl;
		luigiFileIn >> luigiSavedPeach;
	}
	luigiFileIn.close();

	return true;
}

void GameScreen::CharacterCollisions(Character* character1, Character* character2)
{
	if (Collisions::Instance()->Circle(character1, character2))
	{
		int tempPosition;
		int newPosition;

		// Both players moving.
		if (character1->mMovingRight && character2->mMovingLeft)
		{
			tempPosition = character1->GetPosition().x;
			newPosition = tempPosition -= COLLISION_FORCE;
			character1->SetPosition(Vector2D(newPosition, character1->GetPosition().y));

			tempPosition = character2->GetPosition().x;
			newPosition = tempPosition += COLLISION_FORCE;
			character2->SetPosition(Vector2D(newPosition, character2->GetPosition().y));
		}
		else if (character1->mMovingLeft && character2->mMovingRight)
		{
			tempPosition = character1->GetPosition().x;
			newPosition = tempPosition += COLLISION_FORCE;
			character1->SetPosition(Vector2D(newPosition, character1->GetPosition().y));

			tempPosition = character2->GetPosition().x;
			newPosition = tempPosition -= COLLISION_FORCE;
			character2->SetPosition(Vector2D(newPosition, character2->GetPosition().y));
		}// Only player 1 moving.
		else if (character1->mMovingRight)
		{
			tempPosition = character1->GetPosition().x;
			newPosition = tempPosition -= COLLISION_FORCE;
			character1->SetPosition(Vector2D(newPosition, character1->GetPosition().y));
		}
		else if (character1->mMovingLeft)
		{
			tempPosition = character1->GetPosition().x;
			newPosition = tempPosition += COLLISION_FORCE;
			character1->SetPosition(Vector2D(newPosition, character1->GetPosition().y));
		}// Only player 2 moving.
		else if (character2->mMovingRight)
		{
			tempPosition = character2->GetPosition().x;
			newPosition = tempPosition -= COLLISION_FORCE;
			character2->SetPosition(Vector2D(newPosition, character2->GetPosition().y));
		}
		else if (character2->mMovingLeft)
		{
			tempPosition = character2->GetPosition().x;
			newPosition = tempPosition += COLLISION_FORCE;
			character2->SetPosition(Vector2D(newPosition, character2->GetPosition().y));
		}// Both moving the same direction.
		else if ((character1->mMovingRight && character2->mMovingRight) || (character1->mMovingLeft && character2->mMovingLeft))
		{
			// Don't do anything.
		}
	}
}