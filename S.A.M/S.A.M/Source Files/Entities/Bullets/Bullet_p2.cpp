#include "Entities/Bullets/Bullet_p2.h"

Bullet_p2::Bullet_p2()
{
	
}

Bullet_p2::Bullet_p2(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health)
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
	m_scale = Scale;
	m_position = Position;
	m_health = Health;
	m_speed = 100;
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