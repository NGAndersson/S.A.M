#include "Entities/Bullets/Bullet_e.h"

Bullet_e::Bullet_e()
{
	m_rotationValue = 0.0f;
}

Bullet_e::Bullet_e(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, XMFLOAT3 Color, XMFLOAT3 TravelVec)
{
	XMVECTOR _rotzAxis{ TravelVec.x, TravelVec.y, TravelVec.z, 0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
	m_rotationValue = 0.0f;
	m_scale = Scale;
	m_position = Position;
	m_entityBox.Extents = XMFLOAT3(1, 0, 1);
	m_health = Health;
	m_speed = 28;
	m_travelVec = TravelVec;
	m_light = new Light(XMFLOAT4(Position.x, Position.y, Position.z, 1.0f), XMFLOAT4(Color.x, Color.y, Color.z, 1.0f), XMFLOAT4(2, 1, 0, 0));
}

Bullet_e::~Bullet_e()
{
	delete m_light;
}

void Bullet_e::Update(double time)
{
	m_position.x += m_travelVec.x * m_speed * time;
	m_position.y += m_travelVec.y * m_speed * time;
	m_position.z += m_travelVec.z * m_speed * time;
	XMVECTOR _rotzAxis{ m_travelVec.x, m_travelVec.y, m_travelVec.z,0 };
	m_rotationValue += time;
	m_rotation = XMMatrixRotationAxis(_rotzAxis, XM_PI * m_rotationValue);
	m_light->SetPos(XMFLOAT4(m_position.x, m_position.y, m_position.z, 1.0f));


	m_entityBox.Center = m_position;
}

void Bullet_e::Destroyed(double time)
{
	m_delete = true;
}