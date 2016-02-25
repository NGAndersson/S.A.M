#include "Entities/Bullets/Bullet_p1.h"


Bullet_p1::Bullet_p1()
{

}

Bullet_p1::Bullet_p1(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, XMFLOAT3 Color)
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
	m_scale = Scale;
	m_position = Position;
	m_health = Health;
	m_speed = 100;
	m_light = new Light(XMFLOAT4(Position.x, Position.y, Position.z, 1.0f), XMFLOAT4(Color.x, Color.y, Color.z, 1.0f), XMFLOAT4(10, 1, 0, 0));
	m_entityBox.Extents = XMFLOAT3(0.5f, 0.0f, 0.5f);
}

Bullet_p1::~Bullet_p1()
{
	if(m_light != nullptr)
	delete m_light;
}

void Bullet_p1::Destroyed(double time)
{
	m_delete = true;
}

void Bullet_p1::Update(double time)
{
	m_position.z += m_speed * time;
	m_light->SetPos(XMFLOAT4(m_position.x, m_position.y, m_position.z, 1.0f));
	m_entityBox.Center = m_position;	
}