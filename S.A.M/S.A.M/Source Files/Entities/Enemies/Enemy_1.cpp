#include "Entities/Enemies/Enemy_1.h"

Enemy_1::Enemy_1()
{
}

Enemy_1::~Enemy_1()
{

}

void Enemy_1::Update(double time)
{
	m_position.z -= MOVEMENTSPEEDZ/6;

	m_entityBox.Center = m_position;
}

void Enemy_1::Destroyed()
{
	//PlaySound of DEATH
}