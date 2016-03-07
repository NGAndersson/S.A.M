#include "Entities/Bullets/BulletBoundingSphere.h"


BulletBoundingSphere::BulletBoundingSphere()
{

}

BulletBoundingSphere::BulletBoundingSphere(XMFLOAT3 Position, XMFLOAT3 Scale, int Health, float size)
{
	m_scale = Scale;
	m_position = XMFLOAT3(Position.x, Position.y, Position.z);
	m_health = 1;
	m_sphere.Center = m_position;
	m_sphere.Radius = size / 2;
	m_speed = Health;
}

BulletBoundingSphere::~BulletBoundingSphere()
{
	
}

void BulletBoundingSphere::Destroyed(double time)
{
	m_delete = true;
}

void BulletBoundingSphere::Update(double time)
{
	m_position.z += (m_speed * 5) * time;
	m_sphere.Center.z = m_sphere.Center.z - (m_speed * 5) * time;
	m_sphere.Radius = m_sphere.Radius + (0.4 * (m_speed * 5) * time);
	if (m_timeToLive < 0)
	{
		m_delete = true;
	}
	m_timeToLive -= time;
}