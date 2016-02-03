#ifndef BULLET_P3_H
#define BULLET_P3_H
#include "Bullet.h"

class Bullet_p3 : public Bullet
{
	//Functions
private:
protected:
public:
	Bullet_p3();
	Bullet_p3(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position) : Bullet(SoundManager, MapWidth, MapLength, Position) {}
	~Bullet_p3();
	void Update(double time);
	void Destroyed();

	//Variables
private:
protected:
public:

};

#endif