#pragma once
#ifndef BULLETBOUNDINGSPHERE_H
#define BULLETBOUNDINGSPHERE_H
#include "Entities\Bullets\Bullet.h"

class BulletBoundingSphere : public Bullet
{
	//Functions
private:
protected:
public:
	BulletBoundingSphere();
	BulletBoundingSphere(XMFLOAT3 Position, XMFLOAT3 Scale, int Health, float size);
	~BulletBoundingSphere();
	void Update(double time);
	void Destroyed(double time);

	//Variables
private:
	float m_timeToLive = 0.5f;
protected:
public:

};

#endif