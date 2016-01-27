#include "Entity.h"

int Entity::GetPosition()
{
	return mPosition;
}

void Entity::SetPosition(int NewPos)
{
	mPosition = NewPos;
}

BoundingBox Entity::GetBoundingBox()
{
	return mBoundingBox;
}
