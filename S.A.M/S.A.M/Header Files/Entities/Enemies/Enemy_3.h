#ifndef ENEMY_3_H
#define ENEMY_3_H
#include "Entities\Enemies\Enemy.h"

class Enemy_3 : public Enemy
{
	//Functions
private:
protected:
public:
	Enemy_3();
	Enemy_3(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale) : Enemy(SoundManager, MapWidth, MapLength, Position, Scale) {}
	~Enemy_3();
	void Update(double time);
	void Destroyed();

	//Attributes
private:
protected:
public:

};

#endif