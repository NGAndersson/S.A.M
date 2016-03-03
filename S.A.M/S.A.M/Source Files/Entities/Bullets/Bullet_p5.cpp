#include "Entities/Bullets/Bullet_p5.h"

Bullet_p5::Bullet_p5()
{
	
}

Bullet_p5::Bullet_p5(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int rotation, XMFLOAT3 Offset)
{
	XMVECTOR _rotzAxis{ 0,1,0,0 }, _rotzAxis2{ 0,0,1,0 };
	if (rotation == 0)
	{
		m_rotation = XMMatrixRotationAxis(_rotzAxis, XM_PI / 2);
	}
	else if (rotation == 1)
	{
		m_rotation = XMMatrixRotationAxis(_rotzAxis, XM_PI / 2) * XMMatrixRotationAxis(_rotzAxis2, XM_PI);
	}
	m_scale = Scale;
	m_position = XMFLOAT3(Position.x + Offset.x, Position.y + Offset.y, Position.z + Offset.z);
	m_entityBox.Extents = XMFLOAT3(Scale.x, 0, Scale.z);
	m_health = 1;
	m_speed = 0;
	m_offset = Offset;
}

Bullet_p5::~Bullet_p5()
{

}

void Bullet_p5::Update(double time)
{
	m_timeToLive -= time;
	if (m_timeToLive < 0)
	{
		m_delete = true;
	}
	m_position = XMFLOAT3(m_position.x + m_offset.x, m_position.y + m_offset.y, m_position.z + m_offset.z);
	m_entityBox.Center = m_position;

}

void Bullet_p5::Destroyed(double time)
{
	m_delete = true;
}