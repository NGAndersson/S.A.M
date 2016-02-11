#include "Entities/Bullets/Bullet_e.h"

Bullet_e::Bullet_e()
{

}

Bullet_e::Bullet_e(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, XMFLOAT3 Color)
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
	m_scale = Scale;
	m_position = Position;
	m_entityBox.Extents = XMFLOAT3(2, 0, 2);
	m_health = Health;
	m_speed = -28;
	m_light = new Light(XMFLOAT4(Position.x, Position.y, Position.z, 1.0f), XMFLOAT4(Color.x, Color.y, Color.z, 1.0f), XMFLOAT4(10, 1, 0, 0));
}

Bullet_e::~Bullet_e()
{

}

void Bullet_e::Update(double time)
{
	m_position.z += m_speed * time;
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotationValue += time;
	m_rotation = XMMatrixRotationAxis(_rotzAxis, XM_PI * m_rotationValue);
	m_light->SetPos(XMFLOAT4(m_position.x, m_position.y, m_position.z, 1.0f));


	m_entityBox.Center = m_position;
}

void Bullet_e::Destroyed(double time)
{
	m_delete = true;
}