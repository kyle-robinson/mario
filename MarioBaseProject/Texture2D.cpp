#include "Texture2D.h"
#include <SDL_Image.h>
#include <iostream>

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}

Texture2D::~Texture2D()
{
	Free();
	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(string path)
{
	// Remove the memory used for a previous texture.
	Free();

	// Load the image.
	SDL_Surface* mSurface = IMG_Load(path.c_str());
	if (mSurface != NULL)
	{
		// Colour key the image - The colour to be transparent.
		SDL_SetColorKey(mSurface, SDL_TRUE, SDL_MapRGB(mSurface->format, 0, 0xFF, 0xFF));

		// Create the texture from the pixels on the surface.
		mTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		else
		{
			mWidth = mSurface->w;
			mHeight = mSurface->h;
		}
		SDL_FreeSurface(mSurface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError() << endl;
	}

	return mTexture != NULL;
}

/*bool Texture2D::LoadFromRenderedText(string textureText, SDL_Color textColor)
{
	Free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: &s\n", SDL_GetError());
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}	
		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
}*/

void Texture2D::Free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };

	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, flip);
}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}