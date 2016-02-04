#ifndef BULLET_P4_H
#define BULLET_P4_H
#include "Bullet.h"

class Bullet_p4 : public Bullet
{
	//Functions
private:
protected:
public:
	Bullet_p4();
	Bullet_p4(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale) : Bullet(SoundManager, MapWidth, MapLength, Position, Scale) {}
	~Bullet_p4();
	void Update(double time);
	void Destroyed();

	//Variables
private:
protected:
public:

};

#endif