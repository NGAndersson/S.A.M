#include "Entities/Enemies/Enemy_2.h"

Enemy_2::Enemy_2()
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
}

Enemy_2::~Enemy_2()
{

}

void Enemy_2::Update(double time)
{

}

void Enemy_2::Destroyed(double time)
{

}