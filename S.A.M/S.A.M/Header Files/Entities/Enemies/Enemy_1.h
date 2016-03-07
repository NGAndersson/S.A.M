#ifndef ENEMY_1_H
#define ENEMY_1_H
#include "Entities\Enemies\Enemy.h"

class Enemy_1 : public Enemy
{
	//Functions
private:
protected:
public:
	Enemy_1();
	Enemy_1(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, vector<XMFLOAT3> MovPattern) : Enemy(SoundManager, MapWidth, MapLength, Position, Scale, Health, MovPattern)
	{
		m_score = m_health;
	}

	~Enemy_1();
	void Update(double time);
	void Destroyed(double time);
	//Attributes
private:
protected:
public:

};

#endif