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
	Enemy_1(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health) : Enemy(SoundManager, MapWidth, MapLength, Position, Scale, Health) {
		m_score = 1000;
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