#include "GameScreenLevel1.h"
#include "Collisions.h"
#include "Texture2D.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "PowBlock.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	bool circleCollision = false;
	bool boxCollision = false;
	bool powCollision = false;
	
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

	mLevelMap = NULL;

	delete mPowBlock;
	mPowBlock = NULL;

	mEnemies.clear();
}

void GameScreenLevel1::Render()
{	
	// Draw the background.
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

	// Draw the level map.
	mLevelTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	// Render the player.
	characterMario->Render();
	characterLuigi->Render();

	// Render the POW block.
	mPowBlock->Render();

	// Render the enemies.
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	// Do the screen shake if required
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
	
	// Check for collisions.
	if (Collisions::Instance()->Circle(characterMario, characterLuigi))
	{
		if (circleCollision == false)
		{
			cout << "Character Circle Collision" << endl;
		}
		circleCollision = true;
	}
	
	if (Collisions::Instance()->Box(characterMario->GetCollisionBox(), characterLuigi->GetCollisionBox()))
	{
		if (boxCollision == false)
		{
			cout << "Character Box Collision" << endl;
		}
		boxCollision = true;
	}
	
	// Update the players.
	characterMario->Update(deltaTime, e);
	characterLuigi->Update(deltaTime, e);

	// Update POW block for each player.
	UpdatePOWBlock(characterMario);
	UpdatePOWBlock(characterLuigi);

	// Update the enemy characters.
	UpdateEnemies(deltaTime, e);
}

bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();
	
	// Load the background texture.
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/background.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	// Load the level map texture.
	mLevelTexture = new Texture2D(mRenderer);
	if (!mLevelTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		cout << "Failed to load level map texture!";
		return false;
	}

	// Set up the player character.
	characterMario = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	characterLuigi = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(414, 330), mLevelMap);

	// Set up the POW block.
	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	mScreenshake = false;
	mBackgroundYPos = 0.0f;

	// Set up the Koopa enemies.
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
										{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
										{1, 1, 1, 1, 1, 1 ,0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

	// Clear up any old map.
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	// Set the new one.
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel1::UpdatePOWBlock(Character* character)
{
	if (Collisions::Instance()->Box(character->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			// Collided whilst jumping.
			if (character->IsJumping())
			{
				DoScreenShake();
				mPowBlock->TakeAHit();
				character->CancelJump();
				cout << "POW Block Collision" << endl;
			}
		}
	}
}

void GameScreenLevel1::DoScreenShake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
	
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	// Update the Enemies.
	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			// Check if enemy is on the bottom row of tiles.
			if (mEnemies[i]->GetPosition().y > 300.0f)
			{
				// Is the enemy off screen to the left / right?
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
				{
					mEnemies[i]->SetAlive(false);;
				}
			}

			// Now do the update.
			mEnemies[i]->Update(deltaTime, e);

			// Check to see if the enemy collides with the player.
			if (mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f && (mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				// Ignore the collisions if the enemy is behind a pipe?
			}
			else
			{
				if (Collisions::Instance()->Circle(mEnemies[i], characterMario))
				{
					if (mEnemies[i]->GetInjured())
					{
						mEnemies[i]->SetAlive(false);
					}
					else
					{
						// Kill Mario.
						characterMario->SetAlive(false);
						cout << "Mario is dead." << endl;
					}
				}

				if (Collisions::Instance()->Circle(mEnemies[i], characterLuigi))
				{
					if (mEnemies[i]->GetInjured())
					{
						mEnemies[i]->SetAlive(false);
					}
					else
					{
						// Kill Luigi.
						characterLuigi->SetAlive(false);
						cout << "Luigi is dead." << endl;
					}
				}
			}

			// If the enemy is no longer alive, then schedule it for deletion.
			if (!mEnemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		// Remove dead enemies - 1 each update.
		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* characterKoopa = new CharacterKoopa(mRenderer, "Images/Koopa.png", mLevelMap, position, direction, speed);
	mEnemies.push_back(characterKoopa);
}