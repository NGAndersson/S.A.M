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

int Collision::CheckCollisionEntity(vector<Entity*>* Entity_1, vector<Entity*>* Entity_2, HandlerIndex EntityType1, HandlerIndex EntityType2)
{
	int _returnScore = 0;
	for (auto i = 0; i < Entity_1->size(); i++)
	{
		for (auto j = 0; j < Entity_2->size(); j++)
		{

				if (CheckCollision((*Entity_1)[i]->GetBoundingBox(), (*Entity_2)[j]->GetBoundingBox()))
				{
					if (EntityType1 != BULLET5)
					{
						(*Entity_1)[i]->AddHealth(-1);
						if ((*Entity_1)[i]->GetHealth() <= 0)
							Entity_1 = RemoveEntity(i, Entity_1);

						(*Entity_2)[j]->AddHealth(-1000);		//Normal bullets do 100 damage
					}
					else
						(*Entity_2)[j]->AddHealth(-4);			//Laser does 1 damage (per-frame)

					if ((*Entity_2)[j]->GetHealth() <= 0 && EntityType2 != PLAYER)
					{
						_returnScore += (*Entity_2)[j]->GetScore();
						Entity_2 = RemoveEntity(j, Entity_2);
					}
					break;
				}
			
		}
	}
	return _returnScore;
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


