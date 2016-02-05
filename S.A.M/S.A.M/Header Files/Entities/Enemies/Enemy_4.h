#ifndef ENEMY_4_H
#define ENEMY_4_H
#include "Enemy.h"

class Enemy_4 : public Enemy
{
	//Functions
private:
protected:
public:
	Enemy_4();
	Enemy_4(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale) : Enemy(SoundManager, MapWidth, MapLength, Position, Scale) {}
	~Enemy_4();
	void Update(double time);
	void Destroyed();

	//Attributes
private:
protected:
public:

};

#endif