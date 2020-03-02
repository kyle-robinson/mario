#pragma once

#include "Character.h"

class Character;

class Collisions
{
public:
	~Collisions();

	static Collisions* Instance();
	bool Circle(Character* character1, Character* character2);
	bool Box(Rect2D rect1, Rect2D rect2);
private:
	Collisions();
	static Collisions* mInstance;
};