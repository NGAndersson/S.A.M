#include "Entities/Enemies/Enemy_3.h"

Enemy_3::Enemy_3()
{
	
}

Enemy_3::~Enemy_3()
{

}

void Enemy_3::Update(double time)
{
	m_age += time / 2;
	if (m_age > 1.0f)
	{
		m_age = 0;
		m_spline->SetCurrPathNode(m_spline->GetCurrPathNode() + 1);
	}
	m_position = m_spline->GetPathPosition(m_age);
	m_entityBox.Center = m_position;
	m_entityBox.Extents = XMFLOAT3(m_scale.x, 0, m_scale.z);
}
