#ifndef BULLET_P5_H
#define BULLET_P5_H
#include "Entities\Bullets\Bullet.h"

class Bullet_p5 : public Bullet
{
	//Functions
private:
protected:
public:
	Bullet_p5();
	Bullet_p5(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health);
	~Bullet_p5();
	void Update(double time);
	void Destroyed();

	//Variables
private:
	float m_timeToLive = 0.2;
protected:
public:

};

#endif