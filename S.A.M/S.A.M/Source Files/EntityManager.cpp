#include "EntityManager.h"

void EntityManager::SpawnEntity(HandlerIndex type)
{
	switch (type) {
	case(PLAYER) :
		m_player = new Player;
		break;
	case(ENEMY1) :
		Enemy1* tempEntity = new Enemy1;
		m_enemy1.push_back(tempEnemy);
	case(ENEMY2) :
		Enemy2* tempEntity = new Enemy2;
		m_enemy2.push_back(tempEnemy);
	case(ENEMY3) :
		Enemy3* tempEntity = new Enemy3;
		m_enemy3.push_back(tempEnemy);
	case(ENEMY4) :
		Enemy4* tempEntity = new Enemy4;
		m_enemy4.push_back(tempEnemy);
	case(BULLET1) :
		Bullet1* tempEntity = new Bullet1;
		m_enemy1.push_back(tempEnemy);
	case(BULLET2) :
		Bullet2* tempEntity = new Bullet2;
		m_enemy1.push_back(tempEnemy);
	case(BULLET3) :
		Bullet3* tempEntity = new Bullet3;
		m_enemy1.push_back(tempEnemy);
	case(BULLET4) :
		Bullet4* tempEntity = new Bullet4;
		m_enemy1.push_back(tempEnemy);
	}


}

void EntityManager::Initialize()
{

	//Create model handlers for each entity type
	m_modelHandlers[PLAYER] = new ModelHandler;
	m_modelHandlers[ENEMY1] = new ModelHandler;
	m_modelHandlers[ENEMY2] = new ModelHandler;
	m_modelHandlers[ENEMY3] = new ModelHandler;
	m_modelHandlers[ENEMY4] = new ModelHandler;
	m_modelHandlers[BULLET1] = new ModelHandler;
	m_modelHandlers[BULLET2] = new ModelHandler;
	m_modelHandlers[BULLET3] = new ModelHandler;
	m_modelHandlers[BULLET4] = new ModelHandler;

}

void EntityManager::Render()
{
	//Render Player
	m_renderer.Render(m_modelHandlers[PLAYER], m_player->GetPosition(), m_player->GetRotation());

	//Render Enemies
	for (int i = 0; i < m_enemy1.size(); i++)
		m_renderer.Render(m_modelHandlers[ENEMY1], m_enemy1[i]->GetPosition(), m_enemy1[i]->GetRotation());
	for (int i = 0; i < m_enemy2.size(); i++)
		m_renderer.Render(m_modelHandlers[ENEMY2], m_enemy2[i]->GetPosition(), m_enemy2[i]->GetRotation());
	for (int i = 0; i < m_enemy3.size(); i++)												   
		m_renderer.Render(m_modelHandlers[ENEMY3], m_enemy3[i]->GetPosition(), m_enemy3[i]->GetRotation());
	for (int i = 0; i < m_enemy4.size(); i++)												   
		m_renderer.Render(m_modelHandlers[ENEMY4], m_enemy4[i]->GetPosition(), m_enemy4[i]->GetRotation());

	//Render Bullets
	for (int i = 0; i < m_bullet1.size(); i++)
		m_renderer.Render(m_modelHandlers[BULLET1], m_bullet1[i]->GetPosition(), m_bullet1[i]->GetRotation());
	for (int i = 0; i < m_bullet2.size(); i++)
		m_renderer.Render(m_modelHandlers[BULLET2], m_bullet2[i]->GetPosition(), m_bullet2[i]->GetRotation());
	for (int i = 0; i < m_bullet3.size(); i++)
		m_renderer.Render(m_modelHandlers[BULLET3], m_bullet3[i]->GetPosition(), m_bullet3[i]->GetRotation());
	for (int i = 0; i < m_bullet4.size(); i++)
		m_renderer.Render(m_modelHandlers[BULLET4], m_bullet4[i]->GetPosition(), m_bullet4[i]->GetRotation());

}

void EntityManager::Update(double time)
{
	//Do collision checks


	//Update every entity
	//for (int i = 0; i < m_enemies.size(); i++)
	//	m_enemies[i]->Update();
	//
	//for (int i = 0; i < m_bullets.size(); i++)
	//	m_bullets[i]->Update();
	//
	//m_player->Update();
}
