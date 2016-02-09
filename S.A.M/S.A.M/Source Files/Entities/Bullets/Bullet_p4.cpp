#include "Entities/Bullets/Bullet_p4.h"

Bullet_p4::Bullet_p4()
{

}

Bullet_p4::Bullet_p4(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health)
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
	m_scale = Scale;
	m_position = Position;
	m_health;
}

Bullet_p4::~Bullet_p4()
{

}

void Bullet_p4::Update(double time)
{
	m_position.z += 100 * time;


	m_entityBox.Center = m_position;
}

void Bullet_p4::Destroyed(double time)
{
	m_delete = true;
}