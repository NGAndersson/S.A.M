#include "Entities/Enemies/Enemy_4.h"

Enemy_4::Enemy_4()
{
	m_score = m_health;
}

Enemy_4::~Enemy_4()
{

}

void Enemy_4::Update(double time)
{
	m_age += time / 2;
	if (m_age > 1.0f)
	{
		m_age = 0;
		m_spline->SetCurrPathNode(m_spline->GetCurrPathNode() + 1);
	}
	m_position = m_spline->GetPathPosition(m_age);
	m_entityBox.Center = m_position;
	m_entityBox.Extents = XMFLOAT3(m_scale.x * 6, 0, m_scale.z * 5);
	XMVECTOR _rotzAxis{ 0,1,0,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0);
	m_score = m_health;
	m_size = XMFLOAT3(m_scale.x, m_scale.y, m_scale.z);	//used to set size of explosion
}

void Enemy_4::Destroyed(double time)
{

}