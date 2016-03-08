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
		m_score = m_health;
		m_size = XMFLOAT3(m_scale.x * 1.5, m_scale.y * 1.5, m_scale.z * 1.5);	//used to set size of explosion
		m_entityBox.Extents = XMFLOAT3(m_scale.x * 4, 0.0f, m_scale.z * 4);
	}
	~Enemy_2();
	void Update(double time);
	void Destroyed(double time);

	//Attributes
private:
protected:
public:

};

#endif