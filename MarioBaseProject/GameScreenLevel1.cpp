#include "GameScreenLevel1.h"
#include "Collisions.h"
#include "Texture2D.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete characterMario;
	characterMario = NULL;

	delete characterLuigi;
	characterLuigi = NULL;
}

void GameScreenLevel1::Render()
{
	// Draw the background.
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

	// Render the player.
	characterMario->Render();
	characterLuigi->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	// Check for collisions.
	if (Collisions::Instance()->Circle(characterMario, characterLuigi))
	{
		cout << "Circle Collision" << endl;
	}
	
	if (Collisions::Instance()->Box(characterMario->GetCollisionBox(), characterLuigi->GetCollisionBox()))
	{
		cout << "Box Collision" << endl;
	}
	
	// Update the players.
	characterMario->Update(deltaTime, e);
	characterLuigi->Update(deltaTime, e);
}

bool GameScreenLevel1::SetUpLevel()
{
	// Load the background texture.
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/test.bmp"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	// Set up the player character.
	characterMario = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330));
	characterLuigi = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(124, 330));

	return true;
}