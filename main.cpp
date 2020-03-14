#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>

#include "Texture2D.h"
#include "GameScreenManager.h"
#include "Constants.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
GameScreenManager* gameScreenManager;
Uint32 gOldTime;

bool InitSDL();
void CloseSDL();
bool Update();
void Render();

bool closeGame = false;

int main(int argc, char* args[])
{
	cout << "Mario Bros. Stats Window" << endl;
	
	InitSDL();

	gameScreenManager = new GameScreenManager(gRenderer, SCREEN_MENU);
	gOldTime = SDL_GetTicks();
	bool quit = false;
	while (!quit && !closeGame)
	{
		Render();
		quit = Update();
	}
	
	gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);
	quit = false;
	while (!quit && !closeGame)
	{
		Render();
		quit = Update();
	}
	
	gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL2);
	quit = false;
	while (!quit && !closeGame)
	{
		Render();
		quit = Update();
	}

	gameScreenManager = new GameScreenManager(gRenderer, SCREEN_HIGHSCORES);
	quit = false;
	while (!quit && !closeGame)
	{
		Render();
		quit = Update();
	}

	CloseSDL();

	return 0;
}	

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Games Engine Creation - Super Mario Bros.",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			cout << "Window was not created. Error: " << SDL_GetError();
		}

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

			// Initialise SDL_ttf
			if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialise! SDL_ttf Error: %s\n", TTF_GetError());
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

		if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048) < 0)
		{
			cout << "Mixer could not initialise. Error: " << Mix_GetError();
			return false;
		}
	}
	return true;
}

void CloseSDL()
{
	delete gameScreenManager;
	gameScreenManager = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Update()
{
	// Get the new time.
	Uint32 newTime = SDL_GetTicks();

	SDL_Event e;
	SDL_PollEvent(&e);

	switch (e.type)
	{
		case SDL_QUIT:
			closeGame = true;
			return true;
		break;

		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
				case SDLK_RETURN:
					Mix_HaltMusic();
					Mix_HaltChannel(-1);
					return true;
				break;
				case SDLK_ESCAPE:
					closeGame = true;
				break;
			}
		break;

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
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	gameScreenManager->Render();

	SDL_RenderPresent(gRenderer);
}