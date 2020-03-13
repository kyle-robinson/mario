#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	int marioScore;
	int luigiScore;

	void CheckPaused(SDL_Event e);
	bool paused;

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

	SDL_Surface* start1TextSurface;
	SDL_Texture* start1Text;
	SDL_Rect start1TextRect;

	SDL_Surface* start2TextSurface;
	SDL_Texture* start2Text;
	SDL_Rect start2TextRect;

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
	
	SDL_Surface* escapeTextSurface;
	SDL_Texture* escapeText;
	SDL_Rect escapeTextRect;

	// SOUNDS
	bool LoadAudio();

	Mix_Music* gOverworld;
	Mix_Music* gUnderworld;
	bool startTimer;
	float pauseMusic;
	float startGameTimer;

	Mix_Chunk* coinSound;
	Mix_Chunk* dieSound;
	Mix_Chunk* flagpoleSound;
	Mix_Chunk* gameOverSound;
	Mix_Chunk* kickSound;
	Mix_Chunk* pauseSound;
	Mix_Chunk* pipeSound;
	Mix_Chunk* startSound;
	Mix_Chunk* thwompSound;

private:

protected:
	SDL_Renderer* mRenderer;
};