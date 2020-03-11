#pragma once

#include <SDL.h>
#include <string>
//#include <SDL_ttf.h>
//#include <stdio.h>
//#include <cmath>
#include "Commons.h"

using namespace::std;

class Texture2D
{
public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();
	
	bool LoadFromFile(string path);
	bool LoadFromRenderedText(string textureText, SDL_Color textColor);
	void Free();
	
	void Render(Vector2D newPosition, SDL_RendererFlip flip, double angle = 0.0f);
	void Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle = 0.0f);
	
	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }

	//TTF_Font* gFont;

private:
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
	
	int	mWidth;
	int	mHeight;
};