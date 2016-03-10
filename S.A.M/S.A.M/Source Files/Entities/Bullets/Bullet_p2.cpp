#include "Entities/Bullets/Bullet_p2.h"

Bullet_p2::Bullet_p2()
{
	
}

Bullet_p2::Bullet_p2(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, int rocketOffset)
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, XM_PI / 2);
	XMVECTOR _rotzAxis2{ 0,1,0,0 };
	m_rotation = m_rotation * XMMatrixRotationAxis(_rotzAxis2, XM_PI / 2);
	m_scale = Scale;
	if (rocketOffset == 0)
	{
		m_position = XMFLOAT3(Position.x - 1.3, Position.y, Position.z);
	}
	else
	{
		m_position = XMFLOAT3(Position.x + 1.3, Position.y, Position.z);
	}
	m_health = Health;
	m_speed = 100;
	m_entityBox.Extents = XMFLOAT3(0.5f, 0.0f, 1.5f);
}

Bullet_p2::~Bullet_p2()
{

}

void Bullet_p2::Update(double time)
{
	m_position.z += m_speed * time;

	m_entityBox.Center = m_position;
}

void Bullet_p2::Destroyed(double time)
{
	m_delete = true;
}