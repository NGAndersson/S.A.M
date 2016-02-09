#include "Entities/Bullets/Bullet_p5.h"

Bullet_p5::Bullet_p5()
{
	
}

Bullet_p5::Bullet_p5(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health)
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
	m_scale = Scale;
	m_position = Position;
	m_entityBox.Extents = XMFLOAT3(5, 0, 100);
	m_health = Health;
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

	m_entityBox.Center = m_position;

}

void Bullet_p5::Destroyed()
{
	m_delete = true;
}