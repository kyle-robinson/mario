#pragma once

#include "Commons.h"
#include "GameScreen.h"
#include "LevelMap.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "CharacterGoomba.h"
#include "CharacterPeach.h"
#include "GameScreenManager.h"

#include <Windows.h>

#include <vector>

class Texture2D;
class Character;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	Character* characterMario;
	Character* characterLuigi;
	CharacterPeach* characterPeach;

	void UpdatePOWBlock();

private:
	bool SetUpLevel();
	Texture2D* mBackgroundTexture;
	Texture2D* mLevelTexture;

	void SetLevelMap();
	LevelMap* mLevelMap;

	PowBlock* mPowBlock;

	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;
	
	void DoScreenShake();

	void WallWrapping(Character* character);

	HANDLE hConsole;
	int redFont, greenFont, pinkFont, whiteFont;

	GameScreenManager* gameScreenManager;

	// GAME OBJECTS
	void UpdatePeach(float deltaTime, SDL_Event e);
	void CreatePeach(Vector2D position, FACING direction);

	void UpdateCoin(float deltaTime, SDL_Event e);
	void CreateCoin(Vector2D position);
	vector<CharacterCoin*> mCoins;

	// ENEMIES
	void UpdateKoopas(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction);
	vector<CharacterKoopa*> mEnemyKoopa;

	void UpdateGoombas(float deltaTime, SDL_Event e);
	void CreateGoomba(Vector2D position, FACING direction);
	vector<CharacterGoomba*> mEnemyGoomba;

	float enemyTimer;
};