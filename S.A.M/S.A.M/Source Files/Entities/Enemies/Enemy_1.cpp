#include "Entities/Enemies/Enemy_1.h"

Enemy_1::Enemy_1()
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
}

Enemy_1::~Enemy_1()
{

}

void Enemy_1::Update(double time)
{

}

void Enemy_1::Destroyed()
{
	//PlaySound of DEATH
}