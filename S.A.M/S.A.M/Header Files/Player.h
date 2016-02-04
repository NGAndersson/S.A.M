#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Input.h"
#include "Audio/SoundManager.h"
#include <math.h>

class Player : public Entity
{
	//----------------------------Functions----------------------------------------
public:
	Player();
	~Player();
	Player(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, Input* input);
	void Update(double time);
	void Destroyed();
	//----------------------------Attributes----------------------------------------
private:
	Input* m_input;
	float m_rotAngle = 0;
};

#endif // ! PLAYER_H
