#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include <iostream>
#include "Texture2D.h"
#include "GameScreenManager.h"

// Globals
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
GameScreenManager* gameScreenManager;
Uint32 gOldTime;
//Texture2D* gTexture = NULL;

// Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();

int main(int argc, char* args[])
{
	// Check if SDL was set up correctly.
	if (InitSDL())
	{
		// Pause for a few seconds.
		//SDL_Delay(5000);
	}

	// Set up the game screen manager - Start with Level1
	gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);
	gOldTime = SDL_GetTicks();

	// Flag to check if we wish to quit.
	bool quit = false;

	// Game Loop.
	while (!quit)
	{
		//gTexture->Render(Vector2D(), SDL_FLIP_NONE);
		Render();
		quit = Update();
	}

	// Close Window and free resources.
	CloseSDL();

	return 0;
}	

bool InitSDL()
{
	// Setup SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		// All good, so attempt to create the window.
		gWindow = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		// Did the window get created?
		if (gWindow == NULL)
		{
			// The window did not get created.
			cout << "Window was not created. Error: " << SDL_GetError();
		}

		// Setup the renderer.
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		if (gRenderer != NULL)
		{
			// Initialise PNG loading.
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}
	}
	return true;
}

void CloseSDL()
{
	// Destroy the game screen manager.
	delete gameScreenManager;
	gameScreenManager = NULL;

	// Release the renderer.
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	
	// Release the window.
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL subsystems.
	IMG_Quit();
	SDL_Quit();
}

bool Update()
{
	// Get the new time.
	Uint32 newTime = SDL_GetTicks();
	
	// Event Handler.
	SDL_Event e;

	// Get the events.
	SDL_PollEvent(&e);

	// Handle any events.
	switch (e.type)
	{
		// Click 'X' to quit.
		case SDL_QUIT:
			return true;
		break;
		
		// Click 'Q' to quit.
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
				case SDLK_q:
					return true;
				break;
			}
		break;

		// Click 'Right Mouse' to quit.
		case SDL_MOUSEBUTTONDOWN:
			return true;
		break;
	}

	gameScreenManager->Update((float)(newTime-gOldTime)/1000.0f, e);

	// Set the current time to be the old time.
	gOldTime = newTime;

	return false;
}

void Render()
{
	// Clear the screen.
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	//gTexture->Render(Vector2D(), SDL_FLIP_NONE, 0.0f);
	gameScreenManager->Render();

	// Update the screen.
	SDL_RenderPresent(gRenderer);
}