#include "Entities/Bullets/Bullet_p3.h"

Bullet_p3::Bullet_p3()
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
}

Bullet_p3::Bullet_p3(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale)
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
}

Bullet_p3::~Bullet_p3()
{

}

void Bullet_p3::Update(double time)
{

}

void Bullet_p3::Destroyed()
{

}