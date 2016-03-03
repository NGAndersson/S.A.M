#ifndef _BULLETEXPLOSION_H
#define _BULLETEXPLOSION_H
#include <iostream>
#include <stdio.h>
#include "../Entity.h"


class BulletExplosion : public Entity
{

public:
	BulletExplosion();
	BulletExplosion(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, XMFLOAT3 Color);
	~BulletExplosion();
	void Update(double time);
	void Destroyed(double time);
private:


};


#endif
