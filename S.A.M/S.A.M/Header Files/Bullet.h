#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"

enum BulletType
{
	PLAYER_1,	//basic shot (finger snapping)
	PLAYER_2,	//slowing shot (electro drumkick)
	PLAYER_3,	//shot 3
	PLAYER_4,	//shot 4
	PLAYER_5,	//shot 5
	ENEMY_1		//enemy's shot
};

class Bullet : Entity
{
	//Functions
private:
protected:
public:
	Bullet();
	Bullet(SoundManager* SoundManager, int MapWidth, int MapLength, XMFLOAT3 Position);
	~Bullet();
	void Update(double time);
	void Destroyed();
	XMFLOAT3 GetPosition();
	void SetPosition(XMFLOAT3 newPos);
	BoundingBox GetBoundingBox();

	//Attributes
private:
protected:
public:

};

#endif