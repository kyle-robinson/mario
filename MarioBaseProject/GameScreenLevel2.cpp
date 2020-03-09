#include "GameScreenLevel2.h"
#include "Collisions.h"
#include "Texture2D.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	enemyTimer = ENEMY_TIMER;
	mBackgroundYPos = 0.0f;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	redFont = 12;
	greenFont = 10;
	pinkFont = 13;
	whiteFont = 15;

	SetUpLevel();
}

GameScreenLevel2::~GameScreenLevel2()
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

	mEnemyKoopa.clear();
	mEnemyGoomba.clear();
	mCoins.clear();
}

void GameScreenLevel2::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
	mLevelTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	characterMario->Render();
	characterLuigi->Render();

	characterPeach->Render();

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

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	characterMario->Update(deltaTime, e);
	WallCollisions(characterMario);

	characterLuigi->Update(deltaTime, e);
	WallCollisions(characterLuigi);

	UpdatePeach(deltaTime, e);

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

bool GameScreenLevel2::SetUpLevel()
{
	SetLevelMap();

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Levels/Level2/Black_Bg_Small.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	mLevelTexture = new Texture2D(mRenderer);
	if (!mLevelTexture->LoadFromFile("Images/Levels/Level2/Level2.png"))
	{
		cout << "Failed to load level map texture!";
		return false;
	}

	characterMario = new CharacterMario(mRenderer, "Images/Characters/MarioWalk.png", Vector2D(64, 330), mLevelMap);
	characterLuigi = new CharacterLuigi(mRenderer, "Images/Characters/LuigiWalk.png", Vector2D(414, 330), mLevelMap);

	CreatePeach(Vector2D(240, 20), FACING_RIGHT);
	CreateKoopa(Vector2D(64, 32), FACING_RIGHT);
	CreateGoomba(Vector2D(414, 32), FACING_LEFT);

	// Create and set coin positions.
	{
		// Bottom-left platform
		CreateCoin(Vector2D(25, 201));

		// Bottom-right platform
		CreateCoin(Vector2D(471, 201));

		// Bottom-middle platform
		CreateCoin(Vector2D(208, 267));
		CreateCoin(Vector2D(248, 267));
		CreateCoin(Vector2D(288, 267));

		// Top-left platform
		CreateCoin(Vector2D(145, 109));
		CreateCoin(Vector2D(185, 109));

		// Top-right platform
		CreateCoin(Vector2D(310, 109));
		CreateCoin(Vector2D(350, 109));
	}

	return true;
}

void GameScreenLevel2::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
										{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
										{0, 1, 1, 0, 0, 0 ,0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1} };

	// Clear up any old map.
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	// Set the new one.
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel2::WallCollisions(Character* character)
{
	// Right wall collision - wrap left.
	if (character->GetPosition().x >= SCREEN_WIDTH - character->GetCollisionBox().width / 3)
	{
		character->SetPosition(Vector2D(0, character->GetPosition().y));
	}

	// Left wall collision - wrap right.
	if (character->GetPosition().x < 0)
	{
		character->SetPosition(Vector2D(SCREEN_WIDTH - character->GetCollisionBox().width / 3, character->GetPosition().y));
	}

	// Characters fall out of the map - bottom wall collision.
	if (character->GetPosition().y > SCREEN_HEIGHT)
	{
		if (character == characterMario && character->GetAlive() == true)
		{
			character->SetAlive(false);
			characterMario->SetPosition(Vector2D(500, 1000));

			SetConsoleTextAttribute(hConsole, redFont);
			cout << endl << "Mario";
			SetConsoleTextAttribute(hConsole, whiteFont);
			cout << " fell out of the map." << endl;
		}
		else if (character == characterLuigi && character->GetAlive() == true)
		{
			character->SetAlive(false);
			characterLuigi->SetPosition(Vector2D(500, 1000));

			SetConsoleTextAttribute(hConsole, greenFont);
			cout << endl << "Luigi";
			SetConsoleTextAttribute(hConsole, whiteFont);
			cout << " fell out of the map." << endl;
		}
	}
}

void GameScreenLevel2::UpdatePeach(float deltaTime, SDL_Event e)
{
	characterPeach->Update(deltaTime, e);

	if (!characterPeach->isRescued)
	{
		if (Collisions::Instance()->Circle(characterPeach, characterMario))
		{
			characterPeach->isRescued = true;

			SetConsoleTextAttribute(hConsole, greenFont);
			cout << endl << "Mario";
			SetConsoleTextAttribute(hConsole, whiteFont);
			cout << " saved ";
			SetConsoleTextAttribute(hConsole, pinkFont);
			cout << "Princess Peach!" << endl;

			characterMario->mScore += 50;

			SetConsoleTextAttribute(hConsole, redFont);
			cout << "Mario";
			SetConsoleTextAttribute(hConsole, whiteFont);
			cout << "'s score: " << characterMario->mScore << endl;
		}
		else if (Collisions::Instance()->Circle(characterPeach, characterLuigi))
		{
			characterPeach->isRescued = true;

			SetConsoleTextAttribute(hConsole, greenFont);
			cout << endl << "Luigi";
			SetConsoleTextAttribute(hConsole, whiteFont);
			cout << " saved ";
			SetConsoleTextAttribute(hConsole, pinkFont);
			cout << "Princess Peach!" << endl;

			characterLuigi->mScore += 50;
			SetConsoleTextAttribute(hConsole, greenFont);
			cout << "Luigi";
			SetConsoleTextAttribute(hConsole, whiteFont);
			cout << "'s score: " << characterLuigi->mScore << endl;
		}
	}
}

void GameScreenLevel2::UpdateKoopas(float deltaTime, SDL_Event e)
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

						SetConsoleTextAttribute(hConsole, redFont);
						cout << endl << "Mario";
						SetConsoleTextAttribute(hConsole, whiteFont);
						cout << " killed a Koopa." << endl;

						characterMario->mScore += 20;

						SetConsoleTextAttribute(hConsole, redFont);
						cout << "Mario";
						SetConsoleTextAttribute(hConsole, whiteFont);
						cout << " 's score: " << characterMario->mScore << endl;
					}
					else
					{
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
						mEnemyKoopa[i]->SetAlive(false);

						SetConsoleTextAttribute(hConsole, greenFont);
						cout << endl << "Luigi";
						SetConsoleTextAttribute(hConsole, whiteFont);
						cout << " killed a koopa." << endl;

						characterLuigi->mScore += 20;

						SetConsoleTextAttribute(hConsole, greenFont);
						cout << "Luigi";
						SetConsoleTextAttribute(hConsole, whiteFont);
						cout << " 's score: " << characterLuigi->mScore << endl;
					}
					else
					{
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
}

void GameScreenLevel2::UpdateGoombas(float deltaTime, SDL_Event e)
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

						SetConsoleTextAttribute(hConsole, redFont);
						cout << endl << "Mario";
						SetConsoleTextAttribute(hConsole, whiteFont);
						cout << " killed a Goomba." << endl;

						characterMario->mScore += 20;

						SetConsoleTextAttribute(hConsole, redFont);
						cout << "Mario";
						SetConsoleTextAttribute(hConsole, whiteFont);
						cout << " 's score: " << characterMario->mScore << endl;
					}
					else
					{
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
						mEnemyGoomba[i]->SetAlive(false);

						SetConsoleTextAttribute(hConsole, greenFont);
						cout << endl << "Luigi";
						SetConsoleTextAttribute(hConsole, whiteFont);
						cout << " killed a Goomba." << endl;

						characterLuigi->mScore += 20;

						SetConsoleTextAttribute(hConsole, greenFont);
						cout << "Luigi";
						SetConsoleTextAttribute(hConsole, whiteFont);
						cout << "'s score: " << characterLuigi->mScore << endl;
					}
					else
					{
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
}

void GameScreenLevel2::UpdateCoin(float deltaTime, SDL_Event e)
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

				SetConsoleTextAttribute(hConsole, redFont);
				cout << endl << "Mario";
				SetConsoleTextAttribute(hConsole, whiteFont);
				cout << " collected a coin." << endl;

				characterMario->mScore += 10;

				SetConsoleTextAttribute(hConsole, redFont);
				cout << "Mario";
				SetConsoleTextAttribute(hConsole, whiteFont);
				cout << "'s Score: " << characterMario->mScore << endl;
			}
			if (Collisions::Instance()->Circle(mCoins[i], characterLuigi))
			{
				mCoins[i]->SetAlive(false);

				SetConsoleTextAttribute(hConsole, greenFont);
				cout << endl << "Luigi";
				SetConsoleTextAttribute(hConsole, whiteFont);
				cout << " collected a coin." << endl;

				characterLuigi->mScore += 10;

				SetConsoleTextAttribute(hConsole, greenFont);
				cout << "Luigi";
				SetConsoleTextAttribute(hConsole, whiteFont);
				cout << "'s Score: " << characterLuigi->mScore << endl;
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

void GameScreenLevel2::CreatePeach(Vector2D position, FACING direction)
{
	characterPeach = new CharacterPeach(mRenderer, "Images/Objects/Peach.png", mLevelMap, position, direction);
}

void GameScreenLevel2::CreateKoopa(Vector2D position, FACING direction)
{
	CharacterKoopa* characterKoopa = new CharacterKoopa(mRenderer, "Images/Enemies/Koopa.png", mLevelMap, position, direction);
	mEnemyKoopa.push_back(characterKoopa);
}

void GameScreenLevel2::CreateGoomba(Vector2D position, FACING direction)
{
	CharacterGoomba* characterGoomba = new CharacterGoomba(mRenderer, "Images/Enemies/GoombaNPC.png", mLevelMap, position, direction);
	mEnemyGoomba.push_back(characterGoomba);
}

void GameScreenLevel2::CreateCoin(Vector2D position)
{
	CharacterCoin* characterCoin = new CharacterCoin(mRenderer, "Images/Objects/Coin.png", mLevelMap, position);
	mCoins.push_back(characterCoin);
}