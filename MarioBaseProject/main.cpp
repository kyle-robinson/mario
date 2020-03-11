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
Mix_Music* gMusic = nullptr;

bool InitSDL();
void CloseSDL();
bool Update();
void Render();
void LoadMusic(string path);

int main(int argc, char* args[])
{
	cout << "Mario Bros. Stats Window" << endl;
	
	if (InitSDL())
	{
		LoadMusic("Music/OGG/Mario_Overworld.ogg");
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(gMusic, -1);
		}
	}

	// Set up the game screen manager - Start with Level1
	gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);
	gOldTime = SDL_GetTicks();
	
	bool quit = false;
	while (!quit)
	{
		Render();
		quit = Update();
	}

	gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL2);

	Mix_HaltMusic();
	gMusic = nullptr;

	LoadMusic("Music/OGG/Mario_Underworld.ogg");
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(gMusic, -1);
	}

	quit = false;
	while (!quit)
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
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	delete gameScreenManager;
	gameScreenManager = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

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
			return true;
		break;

		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
				case SDLK_q:
					return true;
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

void LoadMusic(string path)
{
	gMusic = Mix_LoadMUS(path.c_str());
	if (gMusic == NULL)
	{
		cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
	}
}