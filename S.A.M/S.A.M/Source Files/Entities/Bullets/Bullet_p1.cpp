#include "Entities/Bullets/Bullet_p1.h"

Bullet_p1::Bullet_p1()
{

}

Bullet_p1::Bullet_p1(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale)
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
	m_scale = Scale;
	m_position = Position;
}

Bullet_p1::~Bullet_p1()
{

}

void Bullet_p1::Destroyed()
{
	m_delete = true;
}

void Bullet_p1::Update(double time)
{
	m_position.z += 100 * time;

	m_entityBox.Center = m_position;
}