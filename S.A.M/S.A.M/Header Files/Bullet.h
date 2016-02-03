#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"

class Bullet : Entity
{
	//Functions
private:
protected:
public:
	Bullet();
	Bullet(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position);
	~Bullet();
	void Update(double time);
	void Destroyed();
	XMFLOAT3 GetPosition();
	void SetPosition(XMFLOAT3 newPos);
	BoundingBox GetBoundingBox();

	//Attributes
private:
protected:
public:

};

#endif