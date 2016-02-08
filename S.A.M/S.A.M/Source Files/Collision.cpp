#include "Collision.h"

Collision::Collision()
{

}

Collision::~Collision()
{

}

bool Collision::CheckCollision(BoundingBox Entitiy1, BoundingBox Entity2)
{
	if (Entitiy1.Intersects(Entity2))
		return true;
	
	return false;
}



