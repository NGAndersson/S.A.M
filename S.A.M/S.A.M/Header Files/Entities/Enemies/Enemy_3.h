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
	Enemy_3(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, vector<XMFLOAT3> MovPattern) : Enemy(SoundManager, MapWidth, MapLength, Position, Scale, Health, MovPattern)
	{
		m_score = m_health;
	}
	~Enemy_3();
	void Update(double time);
	void Destroyed(double time);

	//Attributes
private:
protected:
public:

};

#endif