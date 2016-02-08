#ifndef BULLET_H
#define BULLET_H
#include "Entities\Entity.h"

class Bullet : public Entity
{
	//Functions
private:
protected:
public:
	Bullet(){}
	Bullet(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale) : Entity(SoundManager, MapWidth, MapLength, Position, Scale) {}
	//~Bullet();
	virtual void Update(double time) = 0;
	virtual void Destroyed() = 0;

	//Attributes
private:
protected:
public:

};

#endif