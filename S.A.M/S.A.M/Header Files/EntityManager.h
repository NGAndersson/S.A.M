#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H
#include <vector>
#include "Entities\Entity.h"
#include "Entities\Player.h"
#include "Graphics\Renderer.h"
#include "Graphics\ModelHandler.h"
#include "Graphics\ParticleSys.h"
#include "Graphics\FirePart.h"
#include "Graphics\SpacePart.h"
#include "Graphics\PlayerPart.h"
#include "Graphics\LightHandler.h"
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
#include "Entities/Enemies/Enemy_2.h"
#include "Entities/Enemies/Enemy_3.h"
#include "Entities/Enemies/Enemy_4.h"
#include "Graphics\ShaderHandler.h"
#include <random>
#include "Collision.h"
#include "Gamelogic\Stats.h"
#include "Gamelogic/ShootingPatterns.h"

#include <memory>
enum ShaderIndexName { SHADER_PLAYER, SHADER_BULLET, SHADER_ENEMY, SHADER_MENU, SHADER_PLAYERPART, SHADER_ROCKETPART };

class EntityManager
{
	//Functions
private:
	void SpawnEntity(HandlerIndex type);
	void SpawnEnemy();
	void BeatWasDetected();
	vector<Entity*> CheckOutOfBounds(const std::vector<Entity*> &bullet);
	vector<Entity*> CheckIfAlive(const std::vector<Entity*> &bullet);
	void RenderBullets();
	vector<Entity*> RemoveEntity(int RemoveId, vector<Entity*> RemoveType);
	void EnemyFire();
	void RenderEnemies();
	void CheckCombo();
	void ChangeSongData(int bpm);
	void EnemyHealthColourBuffer();

public:
	EntityManager();
	~EntityManager();
	void Initialize(SoundManager* soundManager, Input* input, ID3D11Device* device, ID3D11DeviceContext* deviceContext, Stats* statsManager);
	void Render();
	void Update(double time);
	void InitMusic(const std::string &filename);
	void Reset();
	int GetPlayerHealth();
	int GetOffset();

	//Variables
private:
	//Vectors with all the different types of entities
	ShaderHandler* m_shaderLoad[6];
	ModelHandler* m_modelHandlers[11];
	LightHandler m_light;
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
	std::vector<ExplosionPart*> m_explosion;
	Entity* m_player;
	bool m_renderPlayer = true;
	FirePart* m_rocketPartSys;	//fire for the rockets
	PlayerPart* m_playerPartSys;	//fire for player
	bool m_renderFire = true;
	Collision m_collision;
	Shootingpatterns m_EnemyPatterns;	//holds the shooting patterns for enemies

	std::vector<std::pair<int, std::vector<XMFLOAT3>>> m_enemy1MovPatterns;
	std::vector<std::pair<int, std::vector<XMFLOAT3>>> m_enemy2MovPatterns;
	std::vector<std::pair<int, std::vector<XMFLOAT3>>> m_enemy3MovPatterns;
	std::vector<std::pair<int, std::vector<XMFLOAT3>>> m_enemy4MovPatterns;
	int m_beatPerShot1 = 3;
	int m_beatPerShot2 = 3;
	int m_beatPerShot3 = 3;
	int m_beatPerShot4 = 3;

	std::vector<std::pair<int, int>> m_enemySpawnRate[4];

	XMFLOAT3 m_enemySize1 = { 1, 1, 1 };
	XMFLOAT3 m_enemySize2 = { 1, 1, 1 };
	XMFLOAT3 m_enemySize3 = { 1, 1, 1 };
	XMFLOAT3 m_enemySize4 = { 1, 1, 1 };

	int m_enemyHealth1 = 1000;
	int m_enemyHealth2 = 1000;
	int m_enemyHealth3 = 1000;
	int m_enemyHealth4 = 1000;

	Stats* m_statsManager;

	Renderer* m_renderer;
	SoundManager* m_soundManager;
	BeatDetector* m_beatDetector;
	Input* m_input;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11Buffer* m_enemyHealthColourBuffer = nullptr;
	std::vector<Entity*> m_bulletSphere;
	int m_laserOffset = 0, m_rocketOffset = 0;


	int m_currentBPM, m_beatNumber = 0;
	double m_timeSinceLastBeat = 0.0f;
	int m_offset = 0;				//Beats to skip in the beginning (for intros without music etc)
									//ADD ENDING OFFSETS?
	float* m_beat;
	int m_level;

public:

};

#endif // !_ENTITYMANAGER_H
