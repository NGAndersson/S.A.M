#include "Collision.h"

XMFLOAT3 CNormalizeFloat3(XMFLOAT3 pos)
{
	float _divider = sqrt((pos.x * pos.x) + (pos.y * pos.y) + (pos.z * pos.z));
	XMFLOAT3 _normalized = XMFLOAT3(pos.x / _divider, pos.y / _divider, pos.z / _divider);

	return _normalized;
}

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
bool Collision::CheckCollision2(BoundingSphere Entitiy1, BoundingBox Entity2)
{
	if (Entitiy1.Intersects(Entity2))
		return true;

	return false;
}

int Collision::CheckCollisionEntity(vector<Entity*>* Entity_1, vector<Entity*>* Entity_2, HandlerIndex EntityType1, HandlerIndex EntityType2, vector<ExplosionPart*>* Explosion, ID3D11Device* device, ID3D11DeviceContext* deviceContext, float time, std::vector<Entity*>* bulletSphere)
{
	int _returnScore = 0;
	for (auto i = 0; i < Entity_1->size(); i++)
	{
		for (auto j = 0; j < Entity_2->size(); j++)
		{
				if (EntityType1 != SPHERE && CheckCollision((*Entity_1)[i]->GetBoundingBox(), (*Entity_2)[j]->GetBoundingBox()))
				{
					if (EntityType1 == BULLET2)
					{
						(*Entity_1)[i]->AddHealth(-1);
						bulletSphere->push_back(new BulletBoundingSphere((*Entity_1)[i]->GetPosition(), (*Entity_1)[i]->GetScale(), 5, 2));
						Explosion->push_back(new ExplosionPart(2, 1.0f));
						(*Explosion)[Explosion->size() - 1]->AddPartSys(Entity_1[i], XMFLOAT4((*Entity_1)[i]->GetPosition().x, (*Entity_1)[i]->GetPosition().y, (*Entity_1)[i]->GetPosition().z - (1 * (*Entity_1)[i]->GetScale().z), 0));
						wstring _texName = L"Resources\\Models\\star.jpg";
						(*Explosion)[Explosion->size() - 1]->CreateBuffer(device, deviceContext, _texName);
					}
					else if (EntityType1 != BULLET5)
					{
						(*Entity_1)[i]->AddHealth(-1);
						(*Entity_2)[j]->AddHealth(-1000);		//Normal bullets do 100 damage
					}
					else
						(*Entity_2)[j]->AddHealth(-500 * time);			//Laser does 100 damage (per-bullet if full hit)

					if ((*Entity_2)[j]->GetHealth() <= 0 && EntityType2 != PLAYER)
					{
						_returnScore += (*Entity_2)[j]->GetScore();
						Explosion->push_back(new ExplosionPart((((*Entity_2)[j]->GetSize().x + (*Entity_2)[j]->GetSize().z) / 2), 1.0f));
						if (EntityType1 != BULLET5)
						{
							XMFLOAT3 _directVec = CNormalizeFloat3(XMFLOAT3((*Entity_1)[i]->GetPosition().x - (*Entity_2)[j]->GetPosition().x, (*Entity_1)[i]->GetPosition().y - (*Entity_2)[j]->GetPosition().y, (*Entity_1)[i]->GetPosition().z - (*Entity_2)[j]->GetPosition().z));
							if ((*Entity_1)[i]->GetHealth() <= 0)
								Entity_1 = RemoveEntity(i, Entity_1);
							(*Explosion)[Explosion->size() - 1]->AddPartSys(Entity_2[j], XMFLOAT4((*Entity_2)[j]->GetPosition().x + _directVec.x, (*Entity_2)[j]->GetPosition().y + _directVec.y, (*Entity_2)[j]->GetPosition().z + _directVec.z, 0));
						}
						else
						{
							(*Explosion)[Explosion->size() - 1]->AddPartSys(Entity_2[j], XMFLOAT4((*Entity_2)[j]->GetPosition().x, (*Entity_2)[j]->GetPosition().y, (*Entity_2)[j]->GetPosition().z - (1 * (*Entity_2)[j]->GetScale().z), 0));
						}
						wstring _texName = L"Resources\\Models\\star.jpg";
						(*Explosion)[Explosion->size() - 1]->CreateBuffer(device, deviceContext, _texName);
						Entity_2 = RemoveEntity(j, Entity_2);
						j--;
						i--;
					}
					else
					{
						if ((*Entity_1)[i]->GetHealth() <= 0)
						{
							Entity_1 = RemoveEntity(i, Entity_1);
							i--;
						}
					}
					break;
				}
			else if (EntityType1 == SPHERE && CheckCollision2((*Entity_1)[i]->GetBoundingSphere(), (*Entity_2)[j]->GetBoundingBox()))
			{
				(*Entity_2)[j]->AddHealth(-1000 * time);
				if ((*Entity_2)[j]->GetHealth() <= 0 && EntityType2 != PLAYER)
				{
					_returnScore += (*Entity_2)[j]->GetScore();
					Explosion->push_back(new ExplosionPart((((*Entity_2)[j]->GetSize().x + (*Entity_2)[j]->GetSize().z) / 2), 1.0f));
					XMFLOAT3 _directVec = CNormalizeFloat3(XMFLOAT3((*Entity_1)[i]->GetPosition().x - (*Entity_2)[j]->GetPosition().x, (*Entity_1)[i]->GetPosition().y - (*Entity_2)[j]->GetPosition().y, (*Entity_1)[i]->GetPosition().z - (*Entity_2)[j]->GetPosition().z));
					(*Explosion)[Explosion->size() - 1]->AddPartSys(Entity_2[j], XMFLOAT4((*Entity_2)[j]->GetPosition().x + _directVec.x, (*Entity_2)[j]->GetPosition().y + _directVec.y, (*Entity_2)[j]->GetPosition().z + _directVec.z, 0));
					wstring _texName = L"Resources\\Models\\star.jpg";
					(*Explosion)[Explosion->size() - 1]->CreateBuffer(device, deviceContext, _texName);
					Entity_2 = RemoveEntity(j, Entity_2);
					j--;
				}
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


