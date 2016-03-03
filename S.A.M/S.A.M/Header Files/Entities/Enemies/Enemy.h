#ifndef ENEMY_H
#define ENEMY_H
#include "Entities/Entity.h"
#include "../../Gamelogic/Spline.h"

enum EnemyMovementPattern { MOVEMENT_1,MOVEMENT_2,MOVEMENT_3,MOVEMENT_4,MOVEMENT_5};

class Enemy : public Entity
{
	//Functions
private:
protected:
public:
	Enemy() {}
	Enemy(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position, XMFLOAT3 Scale, int Health, vector<XMFLOAT3> MovPattern) : Entity(SoundManager, MapWidth, MapLength, Position, Scale, Health) {
		XMVECTOR _rotyAxis{ 0,1,0,0 };
		m_rotation = XMMatrixRotationAxis(_rotyAxis, XM_PI);
		m_spline = new Spline(MovPattern);

		
		/*if (MovementPattern == MOVEMENT_1)
			m_spline = new Spline(g_movementPattern1);

		else if (MovementPattern == MOVEMENT_2)
			m_spline = new Spline(g_movementPattern2);

		else if (MovementPattern == MOVEMENT_3)
			m_spline = new Spline(g_movementPattern3);
		*/

	}
	virtual ~Enemy(){}
	virtual void Update(double time) = 0;
	virtual void Destroyed(double time) = 0;
	void SetEnemyPatterm(EnemyMovementPattern NewPattern) {
		//Swap movementpattern here
	}

	//Attributes
private:
protected:
	Spline* m_spline = nullptr;
	float m_age = 0;
public:
};

#endif