#ifndef BULLET_P4_H
#define BULLET_P4_H
#include "Entities\Bullets\Bullet.h"

class Bullet_p4 : public Bullet
{
	//Functions
private:
protected:
public:
	Bullet_p4();
	Bullet_p4(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, XMFLOAT3 Color, int bulletIndex);
	~Bullet_p4();
	void Update(double time);
	void Destroyed(double time);

	//Variables
private:
	XMFLOAT3 m_move;
protected:
public:

};

#endif