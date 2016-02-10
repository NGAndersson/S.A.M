#include "Entities/Enemies/Enemy_1.h"

Enemy_1::Enemy_1(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health) : Enemy(SoundManager, MapWidth, MapLength, Position, Scale, Health)
{
	m_score = 1000;
	vector<XMFLOAT3> _tempPathPos;
	_tempPathPos.push_back(XMFLOAT3(50, 0, 110));
	_tempPathPos.push_back(XMFLOAT3(50, 0, 105));
	_tempPathPos.push_back(XMFLOAT3(50, 0, 80));
	_tempPathPos.push_back(XMFLOAT3(80, 0, 60));
	_tempPathPos.push_back(XMFLOAT3(30, 0, 80));
	_tempPathPos.push_back(XMFLOAT3(80, 0, 30));
	_tempPathPos.push_back(XMFLOAT3(50, 0, -30));
	m_spline = new Spline(_tempPathPos);
	
	_tempPathPos.clear();
}

Enemy_1::~Enemy_1()
{
	delete m_spline;
}

void Enemy_1::Update(double time)
{
	m_age += time;
	if (m_age > 1.0f)
	{
		m_age = 0;
		m_spline->SetCurrPathNode(m_spline->GetCurrPathNode() + 1);
	}
	m_position = m_spline->GetPathPosition(m_age);
	//m_position.z -= MOVEMENTSPEEDZ/6*(time*1500);
	m_entityBox.Center = m_position;
}

void Enemy_1::Destroyed(double time)
{
	//PlaySound of DEATH


}