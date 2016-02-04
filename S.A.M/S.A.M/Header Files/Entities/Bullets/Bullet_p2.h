#ifndef BULLET_P2_H
#define BULLET_P2_H
#include "Bullet.h"

class Bullet_p2 : public Bullet
{
	//Functions
private:
protected:
public:
	Bullet_p2();
	Bullet_p2(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale) : Bullet(SoundManager, MapWidth, MapLength, Position, Scale) {}
	~Bullet_p2();
	void Update(double time);
	void Destroyed();

	//Variables
private:
protected:
public:

};

#endif