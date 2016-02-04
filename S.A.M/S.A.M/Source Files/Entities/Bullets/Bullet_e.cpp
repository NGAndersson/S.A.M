#include "Entities/Bullets/Bullet_e.h"

Bullet_e::Bullet_e()
{

}

Bullet_e::Bullet_e(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale)
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
}

Bullet_e::~Bullet_e()
{

}

void Bullet_e::Update(double time)
{

}

void Bullet_e::Destroyed()
{

}