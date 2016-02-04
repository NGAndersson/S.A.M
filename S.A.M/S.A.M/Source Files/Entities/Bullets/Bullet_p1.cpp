#include "Entities/Bullets/Bullet_p1.h"

Bullet_p1::Bullet_p1()
{

}

Bullet_p1::~Bullet_p1()
{

}

void Bullet_p1::Destroyed()
{
	m_delete = true;
}

void Bullet_p1::Update(double time)
{
	m_position.z += 0.5 * time;
}