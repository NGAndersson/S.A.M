#ifndef BULLET_E_H
#define BULLET_E_H
#include "Entities\Bullets\Bullet.h"

class Bullet_e : public Bullet
{
	//Functions
private:
protected:
public:
	Bullet_e();
	Bullet_e(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health);
	~Bullet_e();
	void Update(double time);
	void Destroyed();

	//Variables
private:
	float m_rotationValue;
protected:
public:

};

#endif