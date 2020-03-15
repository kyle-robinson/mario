#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "PowBlock.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	playersDead = false;
	
	paused = false;
	startTimer = false;
	pauseMusic = MUSIC_TIMER;
	enemyTimer = ENEMY_TIMER;
	startGameTimer = START_TIMER;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	redFont = 12;
	greenFont = 10;
	pinkFont = 13;
	whiteFont = 15;

	hitPowBlock = false;
	hitTimer = 0.0f;

	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	// OBJECTS
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete mLevelTexture;
	mLevelTexture = NULL;

	delete mTransparency;
	mTransparency = NULL;

	delete mBlackBackground;
	mBlackBackground = NULL;

	delete characterMario;
	characterMario = NULL;

	delete characterLuigi;
	characterLuigi = NULL;

	delete characterPeach;
	characterPeach = NULL;

	delete mPowBlock;
	mPowBlock = NULL;

	mLevelMap = NULL;

	// FILE HANDLING
	if (marioFileOut.is_open())
	{
		marioFileOut.close();
	}
	if (luigiFileOut.is_open())
	{
		luigiFileOut.close();
	}

	if (marioFileIn.is_open())
	{
		marioFileIn.close();
	}
	if (luigiFileIn.is_open())
	{
		luigiFileIn.close();
	}

	// ENEMIES
	mEnemyKoopa.clear();
	mEnemyGoomba.clear();
	mCoins.clear();

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

void GameScreenLevel1::Render()
{	
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
	mLevelTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	characterMario->Render();
	characterLuigi->Render();

	characterPeach->Render();
	mPowBlock->Render();

	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}
	for (unsigned int i = 0; i < mEnemyKoopa.size(); i++)
	{
		mEnemyKoopa[i]->Render();
	}
	for (unsigned int i = 0; i < mEnemyGoomba.size(); i++)
	{
		mEnemyGoomba[i]->Render();
	}
	
	// Render Mario Score
	marioTextRect.x = 75;
	marioTextRect.y = 5;
	SDL_RenderCopy(mRenderer, marioText, NULL, &marioTextRect);
	marioScoreTextRect.x = 187;
	marioScoreTextRect.y = 6;
	SDL_RenderCopy(mRenderer, marioScoreText, NULL, &marioScoreTextRect);
	
	// Render Luigi Score
	luigiTextRect.x = 321;
	luigiTextRect.y = 5;
	SDL_RenderCopy(mRenderer, luigiText, NULL, &luigiTextRect);
	luigiScoreTextRect.x = 425;
	luigiScoreTextRect.y = 6;
	SDL_RenderCopy(mRenderer, luigiScoreText, NULL, &luigiScoreTextRect);

	if (paused)
	{
		mTransparency->Render(Vector2D(), SDL_FLIP_NONE);

		pauseTextRect.x = (SCREEN_WIDTH / 2) - (pauseTextRect.w / 2);
		pauseTextRect.y = (SCREEN_HEIGHT / 2) - (pauseTextRect.h / 2);
		SDL_RenderCopy(mRenderer, pauseText, NULL, &pauseTextRect);
	}
	else
	{
		if (startGameTimer >= 0.0f)
		{
			mTransparency->Render(Vector2D(), SDL_FLIP_NONE);

			start1TextRect.x = (SCREEN_WIDTH / 2) - (start1TextRect.w / 2);
			start1TextRect.y = (SCREEN_HEIGHT / 2) - (start1TextRect.h / 2);
			SDL_RenderCopy(mRenderer, start1Text, NULL, &start1TextRect);
		}
		
		if (characterPeach->isRescued)
		{
			mBlackBackground->Render(Vector2D(), SDL_FLIP_NONE);

			peachTextRect.x = (SCREEN_WIDTH / 2) - (peachTextRect.w / 2);
			peachTextRect.y = (SCREEN_HEIGHT / 2) - (peachTextRect.h / 2);
			SDL_RenderCopy(mRenderer, peachText, NULL, &peachTextRect);

			nextLevelTextRect.x = (SCREEN_WIDTH / 2) - (nextLevelTextRect.w / 2);
			nextLevelTextRect.y = ((SCREEN_HEIGHT / 2) - (nextLevelTextRect.h / 2)) + 40;
			SDL_RenderCopy(mRenderer, nextLevelText, NULL, &nextLevelTextRect);
		}

		if (characterMario->GetAlive() == false && characterLuigi->GetAlive() == false && !characterPeach->isRescued)
		{
			mBlackBackground->Render(Vector2D(), SDL_FLIP_NONE);

			gameOverTextRect.x = (SCREEN_WIDTH / 2) - (gameOverTextRect.w / 2);
			gameOverTextRect.y = (SCREEN_HEIGHT / 2) - (gameOverTextRect.h / 2);
			SDL_RenderCopy(mRenderer, gameOverText, NULL, &gameOverTextRect);

			nextLevelTextRect.x = (SCREEN_WIDTH / 2) - (nextLevelTextRect.w / 2);
			nextLevelTextRect.y = ((SCREEN_HEIGHT / 2) - (nextLevelTextRect.h / 2)) + 40;
			SDL_RenderCopy(mRenderer, nextLevelText, NULL, &nextLevelTextRect);
		}
	}
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	startGameTimer -= 1.0f;

	if (startGameTimer <= 0.0f)
	{
		CheckPaused(e);
	}

	if (startGameTimer == 1000.0f)
	{
		Mix_PlayMusic(gOverworld, -1);
	}
	
	if (!paused && !characterPeach->isRescued && startGameTimer <= 0.0f)
	{
		if (pauseMusic == MUSIC_TIMER)
		{
			Mix_ResumeMusic();
		}
		
		if (mScreenshake)
		{
			mScreenshakeTime -= deltaTime;
			mWobble++;
			mBackgroundYPos = sin(mWobble);
			mBackgroundYPos *= 3.0f;

			// End the shake after the duration.
			if (mScreenshakeTime <= 0.0f)
			{
				mScreenshake = false;
				mBackgroundYPos = 0.0f;
			}
		}

		characterMario->Update(deltaTime, e);
		WallWrapping(characterMario);

		characterLuigi->Update(deltaTime, e);
		WallWrapping(characterLuigi);

		CharacterCollisions(characterMario, characterLuigi);

		UpdatePeach(deltaTime, e);
		UpdatePOWBlock();

		// Update and spawn the enemy characters.
		enemyTimer -= 0.25f;
		switch ((int)enemyTimer)
		{
		case 15000:
			CreateKoopa(Vector2D(64, 32), FACING_RIGHT);
			break;
		case 10000:
			CreateGoomba(Vector2D(414, 32), FACING_LEFT);
			break;
		case 5000:
			CreateGoomba(Vector2D(64, 32), FACING_RIGHT);
			break;
		case 0:
			enemyTimer = ENEMY_TIMER;
			CreateKoopa(Vector2D(414, 32), FACING_LEFT);
			break;
		default:
			break;
		}
		
		UpdateKoopas(deltaTime, e);
		UpdateGoombas(deltaTime, e);
		UpdateCoin(deltaTime, e);

		if (characterMario->GetAlive() == false && characterLuigi->GetAlive() == false && playersDead == false)
		{
			Mix_HaltMusic();
			Mix_HaltChannel(-1);
			Mix_PlayChannel(-1, gameOverSound, 0);
			playersDead = true;
		}
	}
	else
	{
		Mix_PauseMusic();
	}
}

bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();
	
	LoadAudio();
	LoadFont();
	
	OpenOutFiles();

	Mix_PlayChannel(-1, startSound, 0);

	mBlackBackground = new Texture2D(mRenderer);
	if (!mBlackBackground->LoadFromFile("Images/Levels/Level1/Black_Bg_Small.png"))
	{
		cout << "Failed to load black background texture!";
		return false;
	}

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Levels/Level1/Overworld_Bg_Small.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	mLevelTexture = new Texture2D(mRenderer);
	if (!mLevelTexture->LoadFromFile("Images/Levels/Level1/Level1_New.png"))
	{
		cout << "Failed to load level map texture!";
		return false;
	}

	mTransparency = new Texture2D(mRenderer);
	if (!mTransparency->LoadFromFile("Images/Transparency.png"))
	{
		cout << "Failed to load transparency image!";
		return false;
	}

	characterMario = new CharacterMario(mRenderer, "Images/Characters/MarioWalk.png", Vector2D(64, 342), mLevelMap);
	characterLuigi = new CharacterLuigi(mRenderer, "Images//Characters/LuigiWalk.png", Vector2D(414, 342), mLevelMap);

	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	mScreenshake = false;
	mBackgroundYPos = 0.0f;

	CreatePeach(Vector2D(32, 20), FACING_RIGHT);
	CreateKoopa(Vector2D(64, 34), FACING_RIGHT);
	CreateGoomba(Vector2D(414, 34), FACING_LEFT);

	// Create and set coin positions.
	{
		// Bottom-left platform
		CreateCoin(Vector2D(25, 266));
		CreateCoin(Vector2D(89, 266));
		CreateCoin(Vector2D(153, 266));

		// Bottom-right platform
		CreateCoin(Vector2D(345, 266));
		CreateCoin(Vector2D(409, 266));
		CreateCoin(Vector2D(471, 266));

		// Middle-left platform
		CreateCoin(Vector2D(25, 170));

		// Middle platform
		CreateCoin(Vector2D(153, 138));
		CreateCoin(Vector2D(217, 138));
		CreateCoin(Vector2D(281, 138));
		CreateCoin(Vector2D(345, 138));

		// Middle-right platform
		CreateCoin(Vector2D(471, 170));
	}

	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
										{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
										{1, 1, 1, 1, 1, 1 ,1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

	// Clear up any old map.
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	// Set the new one.
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (hitPowBlock)
	{
		hitTimer -= 1.0f;
	}
	if (hitTimer == 0.0f)
	{
		hitPowBlock = false;
	}

	if (Collisions::Instance()->Box(characterMario->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			if (characterMario->IsJumping() && !hitPowBlock)
			{
				Mix_PlayChannel(-1, thwompSound, 0);
				DoScreenShake();

				mPowBlock->TakeAHit();
				hitTimer = POWBLOCK_HIT_TIMER;
				hitPowBlock = true;

				characterMario->CancelJump();

				SetConsoleTextAttribute(hConsole, redFont);
				cout << endl << "Mario";
				SetConsoleTextAttribute(hConsole, whiteFont);
				cout << " hit the POW block." << endl;
			}
		}
	}
	else if (Collisions::Instance()->Box(characterLuigi->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable() && !hitPowBlock)
		{
			if (characterLuigi->IsJumping())
			{
				Mix_PlayChannel(-1, thwompSound, 0);
				DoScreenShake();

				mPowBlock->TakeAHit();
				hitTimer = POWBLOCK_HIT_TIMER;
				hitPowBlock = true;

				characterLuigi->CancelJump();

				SetConsoleTextAttribute(hConsole, greenFont);
				cout << endl << "Luigi";
				SetConsoleTextAttribute(hConsole, whiteFont);
				cout << " hit the POW block." << endl;
			}
		}
	}
}

void GameScreenLevel1::DoScreenShake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
	
	for (unsigned int i = 0; i < mEnemyKoopa.size(); i++)
	{
		mEnemyKoopa[i]->TakeDamage();
	}

	for (unsigned int i = 0; i < mEnemyGoomba.size(); i++)
	{
		mEnemyGoomba[i]->TakeDamage();
	}
}

void GameScreenLevel1::WallWrapping(Character* character)
{
	// Right wall collision - wrap left
	if (character->GetPosition().x >= SCREEN_WIDTH - character->GetCollisionBox().width / 3)
	{
		character->SetPosition(Vector2D(0, character->GetPosition().y));
	}

	// Left wall collision - wrap right
	if (character->GetPosition().x < 0)
	{
		character->SetPosition(Vector2D(SCREEN_WIDTH - character->GetCollisionBox().width / 3, character->GetPosition().y));
	}
}

void GameScreenLevel1::UpdatePeach(float deltaTime, SDL_Event e)
{
	characterPeach->Update(deltaTime, e);

	if (!characterPeach->isRescued)
	{
		if (Collisions::Instance()->Circle(characterPeach, characterMario))
		{
			Mix_HaltMusic();
			Mix_PlayChannel(-1, flagpoleSound, 0);
			
			characterPeach->isRescued = true;
			
			marioSavedPeach += 1;
			marioScore += 50;
			WriteToFiles();
			LoadPlayerScores();

			SetConsoleTextAttribute(hConsole, redFont);
			cout << endl << "Mario";
			SetConsoleTextAttribute(hConsole, whiteFont);
			cout << " saved ";
			SetConsoleTextAttribute(hConsole, pinkFont);
			cout << "Princess Peach." << endl;

			SetConsoleTextAttribute(hConsole, redFont);
			cout << "Mario";
			SetConsoleTextAttribute(hConsole, whiteFont);
			cout << "'s score: " << marioScore << endl;
		}
		else if (Collisions::Instance()->Circle(characterPeach, characterLuigi))
		{
			Mix_HaltMusic();
			Mix_PlayChannel(-1, flagpoleSound, 0);
			
			characterPeach->isRescued = true;
			
			luigiSavedPeach += 1;
			luigiScore += 50;
			WriteToFiles();
			LoadPlayerScores();

			SetConsoleTextAttribute(hConsole, greenFont);
			cout << endl << "Luigi";
			SetConsoleTextAttribute(hConsole, whiteFont);
			cout << " saved ";
			SetConsoleTextAttribute(hConsole, pinkFont);
			cout << "Princess Peach." << endl;
			
			SetConsoleTextAttribute(hConsole, greenFont);
			cout << "Luigi";
			SetConsoleTextAttribute(hConsole, whiteFont);
			cout << "'s score: " << luigiScore << endl;
		}
	}
}

void GameScreenLevel1::UpdateKoopas(float deltaTime, SDL_Event e)
{
	if (!mEnemyKoopa.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemyKoopa.size(); i++)
		{
			// Check if enemy is on the bottom row of tiles.
			if (mEnemyKoopa[i]->GetPosition().y > 300.0f)
			{
				// Is the enemy off screen to the left / right?
				if (mEnemyKoopa[i]->GetPosition().x < (float)(-mEnemyKoopa[i]->GetCollisionBox().width * 0.5f) || mEnemyKoopa[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemyKoopa[i]->GetCollisionBox().width * 0.5f))
				{
					mEnemyKoopa[i]->SetAlive(false);

				}
			}

			mEnemyKoopa[i]->Update(deltaTime, e);

			// Check to see if the enemy collides with the player.
			if (mEnemyKoopa[i]->GetPosition().y > 300.0f || mEnemyKoopa[i]->GetPosition().y <= 64.0f && (mEnemyKoopa[i]->GetPosition().x < 64.0f || mEnemyKoopa[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				// Ignore the collisions if the enemy is behind a pipe?
			}
			else
			{
				if (Collisions::Instance()->Circle(mEnemyKoopa[i], characterMario))
				{
					if (mEnemyKoopa[i]->GetInjured())
					{
						Mix_PlayChannel(-1, kickSound, 0);
						mEnemyKoopa[i]->SetAlive(false);

						marioScore += 20;
						WriteToFiles();
						LoadPlayerScores();

						SetConsoleTextAttribute(hConsole, redFont);
						cout << endl << "Mario";
						SetConsoleTextAttribute(hConsole, whiteFont);
						cout << " killed a Koopa." << endl;

						SetConsoleTextAttribute(hConsole, redFont);
						cout << "Mario";
						SetConsoleTextAttribute(hConsole, whiteFont);
						cout << " 's score: " << marioScore << endl;
					}
					else
					{
						Mix_PauseMusic();
						startTimer = true;
						Mix_PlayChannel(-1, dieSound, 0);
						
						characterMario->SetAlive(false);
						characterMario->SetPosition(Vector2D(500, 1000));

						cout << endl << "A Koopa killed ";
						SetConsoleTextAttribute(hConsole, redFont);
						cout << "Mario." << endl;
						SetConsoleTextAttribute(hConsole, whiteFont);
					}
				}
				else if (Collisions::Instance()->Circle(mEnemyKoopa[i], characterLuigi))
				{
					if (mEnemyKoopa[i]->GetInjured())
					{
						Mix_PlayChannel(-1, kickSound, 0);
						mEnemyKoopa[i]->SetAlive(false);
						
						luigiScore += 20;
						WriteToFiles();
						LoadPlayerScores();
						
						SetConsoleTextAttribute(hConsole, greenFont);
						cout << endl << "Luigi";
						SetConsoleTextAttribute(hConsole, whiteFont);
						cout << " killed a koopa." << endl;
						
						SetConsoleTextAttribute(hConsole, greenFont);
						cout << "Luigi";
						SetConsoleTextAttribute(hConsole, whiteFont);
						cout << " 's score: " << luigiScore << endl;
					}
					else
					{
						Mix_PauseMusic();
						startTimer = true;
						Mix_PlayChannel(-1, dieSound, 0);
						
						characterLuigi->SetAlive(false);
						characterLuigi->SetPosition(Vector2D(500, 1000));
						
						cout << endl << "A Koopa killed ";
						SetConsoleTextAttribute(hConsole, greenFont);
						cout << "Luigi." << endl;
						SetConsoleTextAttribute(hConsole, whiteFont);
					}
				}
			}

			if (!mEnemyKoopa[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		if (enemyIndexToDelete != -1)
		{
			mEnemyKoopa.erase(mEnemyKoopa.begin() + enemyIndexToDelete);
		}
	}

	if (startTimer == true)
	{
		pauseMusic -= 1.0f;
	}

	if (pauseMusic == 0.0f)
	{
		pauseMusic = MUSIC_TIMER;
		startTimer = false;
		Mix_ResumeMusic();
	}
}

void GameScreenLevel1::UpdateGoombas(float deltaTime, SDL_Event e)
{
	if (!mEnemyGoomba.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemyGoomba.size(); i++)
		{
			// Check if enemy is on the bottom row of tiles.
			if (mEnemyGoomba[i]->GetPosition().y > 300.0f)
			{
				// Is the enemy off screen to the left / right?
				if (mEnemyGoomba[i]->GetPosition().x < (float)(-mEnemyGoomba[i]->GetCollisionBox().width * 0.5f) || mEnemyGoomba[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemyGoomba[i]->GetCollisionBox().width * 0.5f))
				{
					mEnemyGoomba[i]->SetAlive(false);;
				}
			}

			mEnemyGoomba[i]->Update(deltaTime, e);

			// Check to see if the enemy collides with the player.
			if (mEnemyGoomba[i]->GetPosition().y > 300.0f || mEnemyGoomba[i]->GetPosition().y <= 64.0f && (mEnemyGoomba[i]->GetPosition().x < 64.0f || mEnemyGoomba[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				// Ignore the collisions if the enemy is behind a pipe?
			}
			else
			{
				if (Collisions::Instance()->Circle(mEnemyGoomba[i], characterMario))
				{
					if (mEnemyGoomba[i]->GetInjured())
					{
						Mix_PlayChannel(-1, kickSound, 0);
						mEnemyGoomba[i]->SetAlive(false);
						
						marioScore += 20;
						WriteToFiles();
						LoadPlayerScores();

						SetConsoleTextAttribute(hConsole, redFont);
						cout << endl << "Mario";
						SetConsoleTextAttribute(hConsole, whiteFont);
						cout << " killed a Goomba." << endl;

						SetConsoleTextAttribute(hConsole, redFont);
						cout << "Mario";
						SetConsoleTextAttribute(hConsole, whiteFont);
						cout << " 's score: " << marioScore << endl;
					}
					else
					{
						Mix_PauseMusic();
						startTimer = true;
						Mix_PlayChannel(-1, dieSound, 0);
						
						characterMario->SetAlive(false);
						characterMario->SetPosition(Vector2D(500, 1000));

						cout << endl << "A Goomba killed ";
						SetConsoleTextAttribute(hConsole, redFont);
						cout << "Mario." << endl;
						SetConsoleTextAttribute(hConsole, whiteFont);
					}
				}
				else if (Collisions::Instance()->Circle(mEnemyGoomba[i], characterLuigi))
				{
					if (mEnemyGoomba[i]->GetInjured())
					{
						Mix_PlayChannel(-1, kickSound, 0);
						mEnemyGoomba[i]->SetAlive(false);
						
						luigiScore += 20;
						WriteToFiles();
						LoadPlayerScores();

						SetConsoleTextAttribute(hConsole, greenFont);
						cout << endl << "Luigi";
						SetConsoleTextAttribute(hConsole, whiteFont);
						cout << " killed a Goomba." << endl;
						
						SetConsoleTextAttribute(hConsole, greenFont);
						cout << "Luigi";
						SetConsoleTextAttribute(hConsole, whiteFont);
						cout << "'s score: " << luigiScore << endl;
					}
					else
					{
						Mix_PauseMusic();
						startTimer = true;
						Mix_PlayChannel(-1, dieSound, 0);
						
						characterLuigi->SetAlive(false);
						characterLuigi->SetPosition(Vector2D(500, 1000));

						cout << endl << "A Goomba killed ";
						SetConsoleTextAttribute(hConsole, greenFont);
						cout << "Luigi." << endl;
						SetConsoleTextAttribute(hConsole, whiteFont);
					}
				}
			}

			if (!mEnemyGoomba[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		if (enemyIndexToDelete != -1)
		{
			mEnemyGoomba.erase(mEnemyGoomba.begin() + enemyIndexToDelete);
		}
	}

	if (startTimer == true)
	{
		pauseMusic -= 1.0f;
	}

	if (pauseMusic == 0.0f)
	{
		pauseMusic = MUSIC_TIMER;
		startTimer = false;
		Mix_ResumeMusic();
	}
}

void GameScreenLevel1::UpdateCoin(float deltaTime, SDL_Event e)
{
	if (!mCoins.empty())
	{
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < mCoins.size(); i++)
		{
			mCoins[i]->Update(deltaTime, e);

			if (Collisions::Instance()->Circle(mCoins[i], characterMario))
			{
				Mix_PlayChannel(-1, coinSound, 0);
				mCoins[i]->SetAlive(false);

				marioScore += 10;
				WriteToFiles();
				LoadPlayerScores();
				
				SetConsoleTextAttribute(hConsole, redFont);
				cout << endl << "Mario";
				SetConsoleTextAttribute(hConsole, whiteFont);
				cout << " collected a coin." << endl;
				
				SetConsoleTextAttribute(hConsole, redFont);
				cout << "Mario";
				SetConsoleTextAttribute(hConsole, whiteFont);
				cout << "'s Score: " << marioScore << endl;
			}
			if (Collisions::Instance()->Circle(mCoins[i], characterLuigi))
			{
				Mix_PlayChannel(-1, coinSound, 0);
				mCoins[i]->SetAlive(false);
				
				luigiScore += 10;
				WriteToFiles();
				LoadPlayerScores();

				SetConsoleTextAttribute(hConsole, greenFont);
				cout << endl << "Luigi";
				SetConsoleTextAttribute(hConsole, whiteFont);
				cout << " collected a coin." << endl;
				
				SetConsoleTextAttribute(hConsole, greenFont);
				cout << "Luigi";
				SetConsoleTextAttribute(hConsole, whiteFont);
				cout << "'s Score: " << luigiScore << endl;
			}

			if (!mCoins[i]->GetAlive())
			{
				coinIndexToDelete = i;
			}
		}

		if (coinIndexToDelete != -1)
		{
			mCoins.erase(mCoins.begin() + coinIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreatePeach(Vector2D position, FACING direction)
{
	characterPeach = new CharacterPeach(mRenderer, "Images/Objects/Peach.png", mLevelMap, position, direction);
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction)
{
	CharacterKoopa* characterKoopa = new CharacterKoopa(mRenderer, "Images/Enemies/Koopa.png", mLevelMap, position, direction);
	mEnemyKoopa.push_back(characterKoopa);
}

void GameScreenLevel1::CreateGoomba(Vector2D position, FACING direction)
{
	CharacterGoomba* characterGoomba = new CharacterGoomba(mRenderer, "Images/Enemies/GoombaNPC.png", mLevelMap, position, direction);
	mEnemyGoomba.push_back(characterGoomba);
}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
	CharacterCoin* characterCoin = new CharacterCoin(mRenderer, "Images/Objects/Coin.png", mLevelMap, position);
	mCoins.push_back(characterCoin);
}