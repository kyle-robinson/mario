#pragma once

#include "Commons.h"
#include "GameScreen.h"
#include "LevelMap.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "CharacterGoomba.h"
#include "CharacterPeach.h"
#include <Windows.h>

#include <vector>

class Texture2D;
class Character;
class PowBlock;

class GameScreenLevel2 : GameScreen
{
public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	Character* characterMario;
	Character* characterLuigi;

private:
	bool SetUpLevel();
	Texture2D* mBackgroundTexture;
	Texture2D* mLevelTexture;

	void SetLevelMap();
	LevelMap* mLevelMap;

	float mBackgroundYPos;

	void WallCollisions(Character* character);

	HANDLE hConsole;
	int redFont, greenFont, pinkFont, whiteFont;

	// GAME OBJECTS
	void UpdatePeach(float deltaTime, SDL_Event e);
	void CreatePeach(Vector2D position, FACING direction);
	CharacterPeach* characterPeach;

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