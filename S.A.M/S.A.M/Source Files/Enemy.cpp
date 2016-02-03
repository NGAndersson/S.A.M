#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position)
{
	m_soundManager = SoundManager;
	m_mapWidth = MapWidth;
	m_mapLength = MapLength;
	m_position = Position;
}

Enemy::~Enemy()
{

}

void Enemy::Update(double time)
{

}

void Enemy::Destroyed()
{

}

XMFLOAT3 Enemy::GetPosition()
{
	return m_position;
}

void Enemy::SetPosition(XMFLOAT3 newPos)
{
	m_position = newPos;
}

XMMATRIX Enemy::GetRotation()
{
	return m_rotation;
}

BoundingBox Enemy::GetBoundingBox()
{
	return m_entityBox;
}