#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"

enum EnemyType
{
	ENEMY_1,	//Normal
	ENEMY_2,	//Swarmer?
	ENEMY_3,	//Slow tank?
	ENEMY_4		//Quick, swirvy assault?
	//Other ideas?
};

class Enemy : Entity
{
	//Functions
private:
protected:
public:
	Enemy();
	Enemy(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position);
	~Enemy();
	void Update(double time);
	void Destroyed();
	XMFLOAT3 GetPosition();
	void SetPosition(XMFLOAT3 newPos);
	XMMATRIX GetRotation();
	BoundingBox GetBoundingBox();

	//Attributes
private:
protected:
public:

};

#endif