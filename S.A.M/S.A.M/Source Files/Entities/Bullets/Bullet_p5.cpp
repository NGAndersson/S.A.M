#include "Entities/Bullets/Bullet_p5.h"

Bullet_p5::Bullet_p5()
{
	
}

Bullet_p5::Bullet_p5(SoundManager * SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale)
{
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
	m_scale = Scale;
	m_position = Position;
}

Bullet_p5::~Bullet_p5()
{

}

void Bullet_p5::Update(double time)
{
	m_position.z += 100 * time;
}

void Bullet_p5::Destroyed()
{
	m_delete = true;
}