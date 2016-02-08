#ifndef _COLLISION_
#define _COLLISION_

#include <stdio.h>
#include <DirectXCollision.h>
#include <DirectXMath.h>

using namespace DirectX;

class Collision
{
private:
public:
	Collision();
	~Collision();
	bool CheckCollision(BoundingBox Entitiy1, BoundingBox Entity2);


private:
public:



};
#endif // !_COLLISION_
