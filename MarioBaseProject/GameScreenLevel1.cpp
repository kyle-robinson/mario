#include "GameScreenLevel1.h"
#include "Collisions.h"
#include "Texture2D.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "PowBlock.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	enemyTimer = ENEMY_TIMER;
	
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete mLevelTexture;
	mLevelTexture = NULL;

	delete characterMario;
	characterMario = NULL;

	delete characterLuigi;
	characterLuigi = NULL;

	delete characterPeach;
	characterPeach = NULL;

	mLevelMap = NULL;

	delete mPowBlock;
	mPowBlock = NULL;

	mEnemyKoopa.clear();
	mEnemyGoomba.clear();
	mCoins.clear();
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
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
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

	UpdatePeach(deltaTime, e);
	UpdatePOWBlock();

	// Update and spawn the enemy characters.
	enemyTimer -= 1.0f;
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
}

bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Level1/Overworld_Bg_Small.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	mLevelTexture = new Texture2D(mRenderer);
	if (!mLevelTexture->LoadFromFile("Images/Level1/Level_1.png"))
	{
		cout << "Failed to load level map texture!";
		return false;
	}

	characterMario = new CharacterMario(mRenderer, "Images/MarioWalk.png", Vector2D(64, 330), mLevelMap);
	characterLuigi = new CharacterLuigi(mRenderer, "Images/LuigiWalk.png", Vector2D(414, 330), mLevelMap);

	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	mScreenshake = false;
	mBackgroundYPos = 0.0f;

	CreatePeach(Vector2D(32, 20), FACING_RIGHT);
	CreateKoopa(Vector2D(64, 32), FACING_RIGHT);
	CreateGoomba(Vector2D(414, 32), FACING_LEFT);

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
										{1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
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
	if (Collisions::Instance()->Box(characterMario->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			if (characterMario->IsJumping())
			{
				DoScreenShake();
				mPowBlock->TakeAHit();
				characterMario->CancelJump();
				cout << endl << "Mario hit the POW block." << endl;
			}
		}
	}
	else if (Collisions::Instance()->Box(characterLuigi->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			if (characterLuigi->IsJumping())
			{
				DoScreenShake();
				mPowBlock->TakeAHit();
				characterLuigi->CancelJump();
				cout << endl << "Luigi hit the POW block." << endl;
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
			characterPeach->isRescued = true;
			characterMario->mScore += 50;
			cout << endl <<  "Mario saved Princess Peach." << endl;
			cout << "Mario's score: " << characterMario->mScore << endl;
		}
		else if (Collisions::Instance()->Circle(characterPeach, characterLuigi))
		{
			characterPeach->isRescued = true;
			characterLuigi->mScore += 50;
			cout << endl << "Luigi saved Princess Peach." << endl;
			cout << "Luigi's score: " << characterLuigi->mScore << endl;
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
						mEnemyKoopa[i]->SetAlive(false);
						characterMario->mScore += 20;
						cout << endl << "Mario killed a Koopa." << endl;
						cout << "Mario's score: " << characterMario->mScore << endl;
					}
					else
					{
						characterMario->SetAlive(false);
						characterMario->SetPosition(Vector2D(500, 1000));
						cout << endl << "A Koopa killed Mario." << endl;
					}
				}
				else if (Collisions::Instance()->Circle(mEnemyKoopa[i], characterLuigi))
				{
					if (mEnemyKoopa[i]->GetInjured())
					{
						mEnemyKoopa[i]->SetAlive(false);
						characterLuigi->mScore += 20;
						cout << endl << "Luigi killed a koopa." << endl;
						cout << "Luigi's score: " << characterLuigi->mScore << endl;
					}
					else
					{
						characterLuigi->SetAlive(false);
						characterLuigi->SetPosition(Vector2D(500, 1000));
						cout << endl << "A Koopa killed Luigi." << endl;
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
						mEnemyGoomba[i]->SetAlive(false);
						characterMario->mScore += 20;
						cout << endl << "Mario killed a Goomba." << endl;
						cout << "Mario's score: " << characterMario->mScore << endl;
					}
					else
					{
						characterMario->SetAlive(false);
						characterMario->SetPosition(Vector2D(500, 1000));
						cout << endl << "A Goomba killed Mario." << endl;
					}
				}
				else if (Collisions::Instance()->Circle(mEnemyGoomba[i], characterLuigi))
				{
					if (mEnemyGoomba[i]->GetInjured())
					{
						mEnemyGoomba[i]->SetAlive(false);
						characterLuigi->mScore += 20;
						cout << endl << "Luigi killed a Goomba." << endl;
						cout << "Luigi's score: " << characterLuigi->mScore << endl;
					}
					else
					{
						characterLuigi->SetAlive(false);
						characterLuigi->SetPosition(Vector2D(500, 1000));
						cout << endl << "A Goomba killed Luigi." << endl;
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
				mCoins[i]->SetAlive(false);
				
				characterMario->mScore += 10;
				cout << endl << "Mario collected a coin." << endl;
				cout << "Mario's Score: " << characterMario->mScore << endl;
			}
			if (Collisions::Instance()->Circle(mCoins[i], characterLuigi))
			{
				mCoins[i]->SetAlive(false);

				characterLuigi->mScore += 10;
				cout << endl << "Luigi collected a coin." << endl;
				cout << "Luigi's Score: " << characterLuigi->mScore << endl;
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
	characterPeach = new CharacterPeach(mRenderer, "Images/Peach.png", mLevelMap, position, direction);
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction)
{
	CharacterKoopa* characterKoopa = new CharacterKoopa(mRenderer, "Images/Koopa.png", mLevelMap, position, direction);
	mEnemyKoopa.push_back(characterKoopa);
}

void GameScreenLevel1::CreateGoomba(Vector2D position, FACING direction)
{
	CharacterGoomba* characterGoomba = new CharacterGoomba(mRenderer, "Images/GoombaNPC.png", mLevelMap, position, direction);
	mEnemyGoomba.push_back(characterGoomba);
}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
	CharacterCoin* characterCoin = new CharacterCoin(mRenderer, "Images/Coin.png", mLevelMap, position);
	mCoins.push_back(characterCoin);
}