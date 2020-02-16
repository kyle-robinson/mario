#pragma once

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initX, float initY)
	{
		x = initX;
		y = initY;
	}
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;

	Rect2D()
	{
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
	}

	Rect2D(float initX, float initY, float initWidth, float initHeight)
	{
		x = initX;
		y = initY;
		width = initWidth;
		height = initHeight;
	}
};

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};