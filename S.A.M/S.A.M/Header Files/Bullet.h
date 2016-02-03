#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"

class Bullet : public Entity
{
	//Functions
private:
protected:
public:
	Bullet();
	Bullet(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position) : Entity(SoundManager, MapWidth, MapLength, Position) {}
	~Bullet();
	void Update(double time);
	void Destroyed();

	//Attributes
private:
protected:
public:

};

#endif