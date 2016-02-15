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
		XMVECTOR _rotzAxis{ 0,0,1,0 };
		m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
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
	const vector<XMFLOAT3> g_movementPattern1{
	XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth / 2, 0, Entity::m_mapLength + 30),
	XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth / 2, 0, Entity::m_mapLength),
	XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth / 6, 0, Entity::m_mapLength - 30),
	XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth * 3 / 5, 0, Entity::m_mapLength - Entity::m_mapLength / 3),
	XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth / 6, 0, Entity::m_mapLength - Entity::m_mapLength * 5 / 7),
	XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth * 4 / 5, 0, Entity::m_mapLength / 9),
	XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth / 2, 0, Entity::m_mapLength - (Entity::m_mapLength + 20))
	};

	const vector<XMFLOAT3> g_movementPattern2{
		XMFLOAT3(Entity::m_mapWidth - 10, 0, Entity::m_mapLength - Entity::m_mapLength/4),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth-5, 0, Entity::m_mapLength - Entity::m_mapLength / 4),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth/2, 0, Entity::m_mapLength - Entity::m_mapLength/8),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth/8, 0, Entity::m_mapLength - Entity::m_mapLength/4),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth/2, 0, Entity::m_mapLength - Entity::m_mapLength*3/8),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth*3/4, 0, Entity::m_mapLength - Entity::m_mapLength*3/4),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth/2, 0, Entity::m_mapLength/4),
		XMFLOAT3(Entity::m_mapWidth+30, 0, Entity::m_mapLength/2)
	};

	const vector<XMFLOAT3> g_movementPattern3{
		XMFLOAT3(Entity::m_mapWidth/4, 0, Entity::m_mapLength*3/4),
		XMFLOAT3(Entity::m_mapWidth/4, 0, Entity::m_mapLength/2),
		XMFLOAT3(Entity::m_mapWidth*3/4, 0,Entity::m_mapLength*3/4),
		XMFLOAT3(Entity::m_mapWidth*3/4, 0,Entity::m_mapLength/2)
	};

	const vector<XMFLOAT3> g_movementPattern4{
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth, 0, Entity::m_mapLength - Entity::m_mapLength),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth, 0, Entity::m_mapLength - Entity::m_mapLength),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth, 0, Entity::m_mapLength - Entity::m_mapLength),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth, 0, Entity::m_mapLength - Entity::m_mapLength),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth, 0, Entity::m_mapLength - Entity::m_mapLength),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth, 0, Entity::m_mapLength - Entity::m_mapLength),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth, 0, Entity::m_mapLength - Entity::m_mapLength)
	};


	const vector<XMFLOAT3> g_movementPattern5{
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth, 0, Entity::m_mapLength - Entity::m_mapLength),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth, 0, Entity::m_mapLength - Entity::m_mapLength),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth, 0, Entity::m_mapLength - Entity::m_mapLength),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth, 0, Entity::m_mapLength - Entity::m_mapLength),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth, 0, Entity::m_mapLength - Entity::m_mapLength),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth, 0, Entity::m_mapLength - Entity::m_mapLength),
		XMFLOAT3(Entity::m_mapWidth - Entity::m_mapWidth, 0, Entity::m_mapLength - Entity::m_mapLength)
	};

protected:
	Spline* m_spline;
	float m_age;
public:
};

#endif