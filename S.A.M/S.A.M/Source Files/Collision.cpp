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

void Collision::CheckCollisionEntity(vector<Entity*>* Entity_1, vector<Entity*>* Entity_2, HandlerIndex BulletType)
{

	for (auto i = 0; i < Entity_1->size(); i++)
	{
		for (auto j = 0; j < Entity_2->size(); j++)
		{
			if (CheckCollision((*Entity_1)[i]->GetBoundingBox(), (*Entity_2)[j]->GetBoundingBox()))
			{
				if (BulletType != BULLET5)
					Entity_1 = RemoveEntity(i, Entity_1);

				Entity_2 = RemoveEntity(j, Entity_2);
				break;
			}
		}
	}
}


vector<Entity*>* Collision::RemoveEntity(int RemoveId, vector<Entity*>* RemoveType)
{
	vector<Entity*>* _tempVec = RemoveType;

	//Play DeathSound?

	//
	delete (*_tempVec)[RemoveId];
	_tempVec->erase(_tempVec->begin() + RemoveId);

	return _tempVec;
}


