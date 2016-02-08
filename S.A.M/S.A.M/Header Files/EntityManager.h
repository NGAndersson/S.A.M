#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H
#include <vector>
#include "Entities\Entity.h"
#include "Entities\Player.h"
#include "Graphics\Renderer.h"
#include "Graphics\ModelHandler.h"
#include "Graphics\ParticleSys.h"
#include "Gamelogic\Input.h"
#include "Audio\BeatDetector.h"
#include <d3d11.h>
#include "Entities\Bullets\Bullet_p1.h"
#include "Entities\Bullets\Bullet_p2.h"
#include "Entities\Bullets\Bullet_p3.h"
#include "Entities\Bullets\Bullet_p4.h"
#include "Entities\Bullets\Bullet_p5.h"
#include "Entities\Enemies\Enemy.h"
#include "Entities\Enemies\Enemy_1.h"
#include <random>
#include "Collision.h"

enum HandlerIndex { PLAYER, BULLET1, BULLET2, BULLET3, BULLET4, BULLET5, BULLET6, ENEMY1, ENEMY2, ENEMY3, ENEMY4};
class EntityManager
{
	//Functions
private:
	void SpawnEntity(HandlerIndex type);
	void BeatWasDetected();
	vector<Entity*> CheckOutOfBounds(std::vector<Entity*> bullet);
	void RenderBullets();
	vector<Entity*> RemoveEntity(int RemoveId, vector<Entity*> RemoveType);
	//Collision functions needed
public:
	EntityManager();
	~EntityManager();
	void Initialize(SoundManager* soundManager, Input* input, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Render();
	void Update(double time);
	void ChangeSongData(int bpm);

	//Variables
private:
	//Vectors with all the different types of entities
	ModelHandler* m_modelHandlers[10];
	std::vector<Entity*> m_bullet1;
	std::vector<Entity*> m_bullet2;
	std::vector<Entity*> m_bullet3;
	std::vector<Entity*> m_bullet4;
	std::vector<Entity*> m_bullet5;
	std::vector<Entity*> m_bullet6;
	std::vector<Entity*> m_enemy1;
	std::vector<Entity*> m_enemy2;
	std::vector<Entity*> m_enemy3;
	std::vector<Entity*> m_enemy4;
	Entity* m_player;

	PartSys m_partSys;
	Collision m_collision;

	Renderer* m_renderer;
	SoundManager* m_soundManager;
	BeatDetector* m_beatDetector;
	Input* m_input;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;

	int m_currentBPM;
	double m_timeSinceLastBeat = 0.0f;

	bool m_doBeatDet;
	float* m_beat;
	int m_level;
public:

};

#endif // !_ENTITYMANAGER_H
