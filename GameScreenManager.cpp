#include "GameScreen.h"
#include "GameScreenMenu.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenScore.h"
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

	GameScreenMenu* tempScreenMenu;
	GameScreenLevel1* tempScreenLevel1;
	GameScreenLevel2* tempScreenLevel2;
	GameScreenScore* tempScreenScore;
	switch (newScreen)
	{
	//case SCREEN_INTRO:
	//	tempScreen1 = new GameScreenLevel1(mRenderer);
	//	mCurrentScreen = (GameScreen*)tempScreen1;
	//	tempScreen1 = NULL;
	//	break;
	case SCREEN_MENU:
		tempScreenMenu = new GameScreenMenu(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreenMenu;
		tempScreenMenu = NULL;
		break;
	case SCREEN_LEVEL1:
		tempScreenLevel1 = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreenLevel1;
		tempScreenLevel1 = NULL;
		break;
	case SCREEN_LEVEL2:
		tempScreenLevel2 = new GameScreenLevel2(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreenLevel2;
		tempScreenLevel2 = NULL;
		break;
	//case SCREEN_GAMEOVER:
	//	tempScreen1 = new GameScreenLevel1(mRenderer);
	//	mCurrentScreen = (GameScreen*)tempScreen1;
	//	tempScreen1 = NULL;
	//	break;
	case SCREEN_HIGHSCORES:
		tempScreenScore = new GameScreenScore(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreenScore;
		tempScreenScore = NULL;
		break;
	default:
		cout << "Was not able to load any of the game screens!" << endl;
		break;
	}
}