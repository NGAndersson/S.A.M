#include "Entities/Bullets/Bullet_p4.h"

Bullet_p4::Bullet_p4()
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
}

Bullet_p4::Bullet_p4(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale)
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
}

Bullet_p4::~Bullet_p4()
{

}

void Bullet_p4::Update(double time)
{

}

void Bullet_p4::Destroyed()
{

}