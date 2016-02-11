#include "Entities/Bullets/Bullet_p3.h"

Bullet_p3::Bullet_p3()
{
	
}

Bullet_p3::Bullet_p3(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, XMFLOAT3 Color)
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotationValue = 0;
	m_rotation = XMMatrixRotationAxis(_rotzAxis, XM_PI * m_rotationValue);
	m_scale = Scale;
	m_position = Position;
	m_health = Health;
	m_speed = 100;
	m_light = new Light(XMFLOAT4(Position.x, Position.y, Position.z, 1.0f), XMFLOAT4(Color.x, Color.y, Color.z, 1.0f), XMFLOAT4(10, 1, 0, 0));
}

Bullet_p3::~Bullet_p3()
{
	if (m_light != nullptr)
		delete m_light;
}

void Bullet_p3::Update(double time)
{
	m_position.z += m_speed * time;
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotationValue += time;
	m_rotation = XMMatrixRotationAxis(_rotzAxis, XM_PI * m_rotationValue);
	m_light->SetPos(XMFLOAT4(m_position.x, m_position.y, m_position.z, 1.0f));

	m_entityBox.Center = m_position;
}

void Bullet_p3::Destroyed(double time)
{
	m_delete = true;
}