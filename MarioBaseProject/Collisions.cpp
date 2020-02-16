#include "Collisions.h"

Collisions* Collisions::mInstance = NULL;

Collisions::Collisions()
{
	
}

Collisions::~Collisions()
{
	mInstance = NULL;
}

Collisions* Collisions::Instance()
{
	if (!mInstance)
	{
		mInstance = new Collisions;
	}
	return mInstance;
}

bool Collisions::Circle(Character* character1, Character* character2)
{
	Vector2D vec = Vector2D((character1->GetPosition().x - character2->GetPosition().x),
							(character1->GetPosition().y - character2->GetPosition().y));
	double distance = sqrt((vec.x*vec.x)+(vec.y*vec.y));
	double combinedDistance(character1->GetCollisionRadius() + character2->GetCollisionRadius());
	return distance < combinedDistance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if (rect1.x + (rect1.width/2) > rect2.x &&
		rect1.x + (rect1.width/2) < rect2.x + rect2.width &&
		rect1.y + (rect1.height/2) > rect2.y &&
		rect1.y + (rect1.height/2) < rect2.y + rect2.height) 
	{
		return true;
	}
	return false;
}