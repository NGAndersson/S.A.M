#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Input.h"
#include "SoundManager.h"
#include <math.h>

class Player : Entity
{
	//----------------------------Functions----------------------------------------
public:
	Player();
	~Player();

	void Update(double time);
	void Initialize(SoundManager* SoundManager, int MapWidth, int MapLenght,Input* input);
	void Destroyed();
	//----------------------------Attributes----------------------------------------
private:
	Input* m_input;

};

#endif // ! PLAYER_H
