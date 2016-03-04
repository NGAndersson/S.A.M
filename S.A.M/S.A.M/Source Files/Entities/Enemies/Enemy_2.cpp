#include "Entities/Enemies/Enemy_2.h"

Enemy_2::Enemy_2()
{
	
}

Enemy_2::~Enemy_2()
{
	delete m_spline;
}

void Enemy_2::Update(double time)
{
	m_age += time / 2;
	if (m_age > 1.0f)
	{
		m_age = 0;
		m_spline->SetCurrPathNode(m_spline->GetCurrPathNode() + 1);
	}
	m_position = m_spline->GetPathPosition(m_age);
	m_entityBox.Center = m_position;
	m_size = XMFLOAT3(m_scale.x * 2, m_scale.y * 2, m_scale.z * 2);	//used to set size of explosion
	m_entityBox.Extents = XMFLOAT3(m_scale.x * 4, 0.0f, m_scale.z * 4);
}

void Enemy_2::Destroyed(double time)
{

}