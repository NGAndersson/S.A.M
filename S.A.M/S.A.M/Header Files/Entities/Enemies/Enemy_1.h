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
		m_size = XMFLOAT3(m_scale.x / 2.0, m_scale.y, m_scale.z / 2.0);	//used to set size of explosion
		m_entityBox.Extents = XMFLOAT3(m_scale.x, 0, m_scale.z);
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