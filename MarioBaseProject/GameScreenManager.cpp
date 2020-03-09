#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenManager.h"

#include <iostream>

using namespace std;

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = NULL;

	// Ensure the first screen is set up.
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;

	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	// Clearup the old screen.
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreenLevel1* tempScreen1;
	GameScreenLevel2* tempScreen2;
	switch (newScreen)
	{
	case SCREEN_INTRO:
		tempScreen1 = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen1;
		tempScreen1 = NULL;
		break;
	case SCREEN_MENU:
		tempScreen1 = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen1;
		tempScreen1 = NULL;
		break;
	case SCREEN_LEVEL1:
		tempScreen1 = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen1;
		tempScreen1 = NULL;
		break;
	case SCREEN_LEVEL2:
		tempScreen2 = new GameScreenLevel2(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen2;
		tempScreen2 = NULL;
		break;
	case SCREEN_GAMEOVER:
		tempScreen1 = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen1;
		tempScreen1 = NULL;
		break;
	case SCREEN_HIGHSCORES:
		tempScreen1 = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen1;
		tempScreen1 = NULL;
		break;
	default:
		cout << "Was not able to load any of the game screens!" << endl;
		break;
	}
}