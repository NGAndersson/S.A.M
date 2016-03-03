#ifndef ENEMY_2_H
#define ENEMY_2_H
#include "Entities\Enemies\Enemy.h"

class Enemy_2 : public Enemy
{
	//Functions
private:
protected:
public:
	Enemy_2();
	Enemy_2(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, vector<XMFLOAT3> MovPattern) : Enemy(SoundManager, MapWidth, MapLength, Position, Scale, Health, MovPattern)
	{
		m_score = 1000;
	}
	~Enemy_2();
	void Update(double time);

	//Attributes
private:
protected:
public:

};

#endif