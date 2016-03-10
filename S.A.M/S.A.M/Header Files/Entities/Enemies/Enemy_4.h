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
		m_size = XMFLOAT3(m_scale.x, m_scale.y, m_scale.z);	//used to set size of explosion
		m_entityBox.Extents = XMFLOAT3(m_scale.x, 0, m_scale.z);
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