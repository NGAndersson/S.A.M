#include "Entities/Enemies/Enemy_4.h"

Enemy_4::Enemy_4()
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
}

Enemy_4::~Enemy_4()
{

}

void Enemy_4::Update(double time)
{

}

void Enemy_4::Destroyed()
{

}