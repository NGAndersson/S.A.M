#ifndef _COLLISION_
#define _COLLISION_ //Pointless class but hey cool name :)

#include <stdio.h>
#include <DirectXCollision.h>
#include <DirectXMath.h>
#include <vector>
#include "Entities\Entity.h"

using namespace DirectX;
using namespace std;
class Collision
{
private:
	bool CheckCollision(BoundingBox Object_1, BoundingBox Object_2);
	vector<Entity*>* RemoveEntity(int RemoveId, vector<Entity*>* RemoveType);
public:
	Collision();
	~Collision();
	void CheckCollisionEntity(vector<Entity*>* Entity_1, vector<Entity*>* Entity_2, HandlerIndex EntityType1, HandlerIndex EntityType2);
private:
public:



};
#endif // !_COLLISION_
