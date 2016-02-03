#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position)
{
	m_soundManager = SoundManager;
	m_mapLength = MapLength;
	m_mapWidth = MapWidth;
	m_position = Position;
}

Bullet::~Bullet()
{

}

void Bullet::Update(double time)
{

}

void Bullet::Destroyed()
{

}

XMFLOAT3 Bullet::GetPosition()
{
	return m_position;
}

void Bullet::SetPosition(XMFLOAT3 newPos)
{
	m_position = newPos;
}

BoundingBox Bullet::GetBoundingBox()
{
	return m_entityBox;
}