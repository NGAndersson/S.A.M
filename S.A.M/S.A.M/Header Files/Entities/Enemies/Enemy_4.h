#ifndef ENEMY_4_H
#define ENEMY_4_H
#include "Entities\Enemies\Enemy.h"

class Enemy_4 : public Enemy
{
	//Functions
private:
protected:
public:
	Enemy_4();
	Enemy_4(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, vector<XMFLOAT3> MovPattern) : Enemy(SoundManager, MapWidth, MapLength, Position, Scale, Health, MovPattern)
	{
		m_score = m_health;
	}
	~Enemy_4();
	void Update(double time);
	void Destroyed(double time);

	//Attributes
private:
protected:
public:

};

#endif