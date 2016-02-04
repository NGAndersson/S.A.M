#include "Entities/Bullets/Bullet_p2.h"

Bullet_p2::Bullet_p2()
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
}

Bullet_p2::Bullet_p2(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale)
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
}

Bullet_p2::~Bullet_p2()
{

}

void Bullet_p2::Update(double time)
{

}

void Bullet_p2::Destroyed()
{

}