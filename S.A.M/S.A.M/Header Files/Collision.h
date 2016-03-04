#ifndef _COLLISION_
#define _COLLISION_ //Pointless class but hey cool name :)

#include <stdio.h>
#include <DirectXCollision.h>
#include <DirectXMath.h>
#include <vector>
#include "Entities\Entity.h"
#include "Graphics\LightHandler.h"
#include "Graphics\ExplosionPart.h"

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
	int CheckCollisionEntity(vector<Entity*>* Entity_1, vector<Entity*>* Entity_2, HandlerIndex EntityType1, HandlerIndex EntityType2, vector<ExplosionPart*>* Explosion, ID3D11Device* device, ID3D11DeviceContext* deviceContext, float time);
private:
public:



};
#endif // !_COLLISION_
