#include "../../../Header Files/Entities/Bullets/BulletExplosion.h"


BulletExplosion::BulletExplosion()
{

}

BulletExplosion::BulletExplosion(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, XMFLOAT3 Color)
{
	m_sphere.Center = Position;
	m_sphere.Radius = 2;
	m_health = 360;
}

BulletExplosion::~BulletExplosion()
{

}

void BulletExplosion::Update(double time)
{
	m_sphere.Radius += time;

	if (m_sphere.Radius > 10)
		m_sphere.Radius = 10.0f;

	m_health -= time;
}

void BulletExplosion::Destroyed(double time)
{

}

