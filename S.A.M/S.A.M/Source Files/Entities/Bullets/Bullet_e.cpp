#include "Entities/Bullets/Bullet_e.h"

Bullet_e::Bullet_e()
{

}

Bullet_e::Bullet_e(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health)
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
	m_scale = Scale;
	m_position = Position;
	m_entityBox.Extents = XMFLOAT3(2, 0, 2);
	m_health = Health;
}

Bullet_e::~Bullet_e()
{

}

void Bullet_e::Update(double time)
{
	m_position.z -= 80 * time;
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotationValue += time;
	m_rotation = XMMatrixRotationAxis(_rotzAxis, XM_PI * m_rotationValue);


	m_entityBox.Center = m_position;
}

void Bullet_e::Destroyed(double time)
{
	m_delete = true;
}