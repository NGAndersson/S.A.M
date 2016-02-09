#include "Entities/Bullets/Bullet_p3.h"

Bullet_p3::Bullet_p3()
{
	
}

Bullet_p3::Bullet_p3(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health)
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotationValue = 0;
	m_rotation = XMMatrixRotationAxis(_rotzAxis, XM_PI * m_rotationValue);
	m_scale = Scale;
	m_position = Position;
	m_health = Health;
}

Bullet_p3::~Bullet_p3()
{

}

void Bullet_p3::Update(double time)
{
	m_position.z += 100 * time;
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotationValue += time;
	m_rotation = XMMatrixRotationAxis(_rotzAxis, XM_PI * m_rotationValue);


	m_entityBox.Center = m_position;
}

void Bullet_p3::Destroyed()
{
	m_delete = true;
}