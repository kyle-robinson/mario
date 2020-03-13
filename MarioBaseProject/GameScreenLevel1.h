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
#include <string>

using namespace std;

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

	int marioScore;
	int luigiScore;
	bool playersDead;

	void UpdatePOWBlock();

private:
	bool SetUpLevel();
	Texture2D* mBackgroundTexture;
	Texture2D* mLevelTexture;
	Texture2D* mTransparency;

	void SetLevelMap();
	LevelMap* mLevelMap;
	
	void CheckPaused(SDL_Event e);
	bool paused;

	PowBlock* mPowBlock;

	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;
	
	void DoScreenShake();

	void WallWrapping(Character* character);

	HANDLE hConsole;
	int redFont, greenFont, pinkFont, whiteFont;

	// FONTS
	void LoadFont();
	void LoadPlayerScores();

	TTF_Font* fontVeryLarge;
	TTF_Font* fontLarge;
	TTF_Font* fontMedium;
	TTF_Font* fontSmall;
	
	SDL_Color colorFg;
	SDL_Color colorBg;
	SDL_Color colorRed;
	SDL_Color colorGreen;
	SDL_Color colorPink;

	SDL_Surface* pauseTextSurface;
	SDL_Texture* pauseText;
	SDL_Rect pauseTextRect;

	SDL_Surface* marioTextSurface;
	SDL_Texture* marioText;
	SDL_Rect marioTextRect;

	SDL_Surface* marioScoreTextSurface;
	SDL_Texture* marioScoreText;
	SDL_Rect marioScoreTextRect;
	string marioScoreString;

	SDL_Surface* luigiTextSurface;
	SDL_Texture* luigiText;
	SDL_Rect luigiTextRect;

	SDL_Surface* luigiScoreTextSurface;
	SDL_Texture* luigiScoreText;
	SDL_Rect luigiScoreTextRect;
	string luigiScoreString;

	SDL_Surface* peachTextSurface;
	SDL_Texture* peachText;
	SDL_Rect peachTextRect;

	SDL_Surface* gameOverTextSurface;
	SDL_Texture* gameOverText;
	SDL_Rect gameOverTextRect;

	SDL_Surface* nextLevelTextSurface;
	SDL_Texture* nextLevelText;
	SDL_Rect nextLevelTextRect;

	// SOUNDS
	void LoadAudio();

	Mix_Music* gMusic;
	bool startTimer;
	float pauseMusic;

	Mix_Chunk* coinSound;
	Mix_Chunk* dieSound;
	Mix_Chunk* flagpoleSound;
	Mix_Chunk* gameOverSound;
	Mix_Chunk* kickSound;
	Mix_Chunk* pauseSound;
	Mix_Chunk* pipeSound;
	Mix_Chunk* thwompSound;

	// GAME OBJECTS
	CharacterPeach* characterPeach;
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