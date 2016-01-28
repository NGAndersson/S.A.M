#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Renderer.h"

enum HandlerIndex { PLAYER, BULLET1, BULLET2, BULLET3, BULLET4, ENEMY1, ENEMY2, ENEMY3, ENEMY4};
class EntityManager
{
private:
	void SpawnEntity(HandlerIndex type);

	//Collision functions needed
public:
	void Initialize();
	void Render();
	void Update(double time);

private:
	ModelHandler* m_modelHandlers[9];
	std::vector<Entity*> m_bullet1;
	std::vector<Entity*> m_bullet2;
	std::vector<Entity*> m_bullet3;
	std::vector<Entity*> m_bullet4;
	std::vector<Entity*> m_enemy1;
	std::vector<Entity*> m_enemy2;
	std::vector<Entity*> m_enemy3;
	std::vector<Entity*> m_enemy4;
	Entity* m_player;

	Renderer m_renderer;


public:

};

#endif // !_ENTITYMANAGER_H
