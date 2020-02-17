#pragma once

#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

#include <iostream>
#include "Constants.h"
#include "Texture2D.h"
#include "LevelMap.h"

using namespace std;

class Texture2D;

class Character
{
public:
	// Main Functions
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	// Render Characters - Change Directions
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	// Set Character Positions
	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	// Character Direction
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;

	// Handle Collisions
	float GetCollisionRadius();
	Rect2D GetCollisionBox() { return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight()); }

	// Character Jumping
	bool IsJumping();
	void CancelJump();

private:
	LevelMap* mCurrentLevelMap;
protected:
	// Character Creation
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	// Character Movement
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void AddGravity(float deltaTime);
	virtual void Jump();

	// Character Jumping
	bool mJumping;
	bool mCanJump;
	float mJumpForce;

	// Collision Variables
	float mCollisionRadius;
};

#endif //_TEXTURE2D_H