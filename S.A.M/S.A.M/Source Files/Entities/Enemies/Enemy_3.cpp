#include "Entities/Enemies/Enemy_3.h"

Enemy_3::Enemy_3()
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
}

Enemy_3::~Enemy_3()
{

}

void Enemy_3::Update(double time)
{

}

void Enemy_3::Destroyed(double time)
{

}