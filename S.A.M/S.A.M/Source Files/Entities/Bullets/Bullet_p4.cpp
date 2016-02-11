#include "Entities/Bullets/Bullet_p4.h"

Bullet_p4::Bullet_p4()
{

}

Bullet_p4::Bullet_p4(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, XMFLOAT3 Color, int bulletIndex)
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
	m_scale = Scale;
	m_position = XMFLOAT3(Position.x, Position.y, Position.z + 2);
	m_health;
	if (bulletIndex == 0)
		m_move = XMFLOAT3(-40, 0, 55);
	else if (bulletIndex == 1)
		m_move = XMFLOAT3(0, 0, 100);
	else if (bulletIndex == 2)
		m_move = XMFLOAT3(40, 0, 55);
	m_light = new Light(XMFLOAT4(Position.x, Position.y, Position.z, 1.0f), XMFLOAT4(Color.x, Color.y, Color.z, 1.0f), XMFLOAT4(10, 1, 0, 0));
}

Bullet_p4::~Bullet_p4()
{
	if (m_light != nullptr)
		delete m_light;
}

void Bullet_p4::Update(double time)
{
	m_position = XMFLOAT3((m_move.x * time) + m_position.x, (m_move.y * time) + m_position.y, (m_move.z * time) + m_position.z);
	m_light->SetPos(XMFLOAT4(m_position.x, m_position.y, m_position.z, 1.0f));

	m_entityBox.Center = m_position;
}

void Bullet_p4::Destroyed(double time)
{
	m_delete = true;
}