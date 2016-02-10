#include "EntityManager.h"
#include <iostream>
#define MAPWIDTH 107
#define MAPLENGTH 103

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
	for (int i = 0; i < 10; i++)
	{
		delete m_modelHandlers[i];
		m_modelHandlers[i] = NULL;
	}
	delete m_renderer;
	delete m_beatDetector;

	delete m_player;

	for (int i = 0; i < m_bullet1.size(); i++)
		delete m_bullet1[i];

	for (int i = 0; i < m_bullet2.size(); i++)
		delete m_bullet2[i];

	for (int i = 0; i < m_bullet3.size(); i++)
		delete m_bullet3[i];

	for (int i = 0; i < m_bullet4.size(); i++)
		delete m_bullet4[i];

	for (int i = 0; i < m_bullet5.size(); i++)
		delete m_bullet5[i];

	for (int i = 0; i < m_bullet6.size(); i++)
		delete m_bullet6[i];

	for (int i = 0; i < m_enemy1.size(); i++)
		delete m_enemy1[i];

	for (int i = 0; i < m_enemy2.size(); i++)
		delete m_enemy2[i];

	for (int i = 0; i < m_enemy3.size(); i++)
		delete m_enemy3[i];

	for (int i = 0; i < m_enemy4.size(); i++)
		delete m_enemy4[i];

}

void EntityManager::SpawnEntity(HandlerIndex type)
{
	float _tempX = rand() % 101;

	switch (type) {
	case(PLAYER) :
		//m_player = new Player(m_soundManager, MAPWIDTH,MAPLENGTH,XMFLOAT3(1.0f, 0.0f, 1.0f), XMFLOAT3(0.5f, 0.5f, 0.5f), 1, m_input);
		m_player = new Player(m_soundManager, MAPWIDTH,MAPLENGTH,XMFLOAT3(MAPWIDTH / 2, 0.0f, MAPLENGTH / 2), XMFLOAT3(0.5f, 0.5f, 0.5f), 1, m_input);
		break;
	case(ENEMY1) :
		//temptest = new Enemy_1(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(_tempX, 0.0f, 70.0f),XMFLOAT3(0.5f,0.5f,0.5f));
		m_enemy1.push_back(new Enemy_1(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(_tempX, 0.0f, 110), XMFLOAT3(0.5f, 0.5f, 0.5f),6));
		break;
	//case(ENEMY2) :
	//	Enemy2* tempEntity = new Enemy2;
	//	tempEntity->Initialize();
	//	m_enemy2.push_back(tempEntity);
	//	break;
	//case(ENEMY3) :
	//	Enemy3* tempEntity = new Enemy3;
	//	tempEntity->Initialize();
	//	m_enemy3.push_back(tempEntity);
	//	break;
	//case(ENEMY4) :
	//	Enemy4* tempEntity = new Enemy4;
	//	tempEntity->Initialize();
	//	m_enemy4.push_back(tempEntity);
	//	break;
	case(BULLET1) :
		//tempEntity = new Bullet_p1(m_soundManager, MAPWIDTH, MAPLENGTH, m_player->GetPosition(), XMFLOAT3(1, 1, 1));
		m_bullet1.push_back(new Bullet_p1(m_soundManager, MAPWIDTH, MAPLENGTH, m_player->GetPosition(), XMFLOAT3(1, 1, 1),1));
		m_soundManager->PlayOneShotSound("DefaultBullet", 0.5f);
		break;
	case(BULLET2) :
		//tempEntity = new Bullet_p2(m_soundManager, MAPWIDTH, MAPLENGTH, m_player->GetPosition(), XMFLOAT3(1, 1, 1));
		m_bullet2.push_back(new Bullet_p2(m_soundManager, MAPWIDTH, MAPLENGTH, m_player->GetPosition(), XMFLOAT3(1, 1, 1),1));
		m_soundManager->PlayOneShotSound("Bullet_Q", 0.5f);
		break;
	case(BULLET3) :
		//tempEntity = new Bullet_p3(m_soundManager, MAPWIDTH, MAPLENGTH, m_player->GetPosition(), XMFLOAT3(1, 1, 1));
		m_bullet3.push_back(new Bullet_p3(m_soundManager, MAPWIDTH, MAPLENGTH, m_player->GetPosition(), XMFLOAT3(1, 1, 1),1));
		m_soundManager->PlayOneShotSound("Bullet_W", 0.5f);
		break;
	case(BULLET4) :
		//tempEntity = new Bullet_p4(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x - 1, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(0.5, 0.5, 0.5));
		m_bullet4.push_back(new Bullet_p4(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x - 1, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(0.5, 0.5, 0.5),1));
		//tempEntity = new Bullet_p4(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(0.5, 0.5, 0.5));
		m_bullet4.push_back(new Bullet_p4(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(0.5, 0.5, 0.5),1));
		//tempEntity = new Bullet_p4(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x + 1, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(0.5, 0.5, 0.5));
		m_bullet4.push_back(new Bullet_p4(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x + 1, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(0.5, 0.5, 0.5),1));
		m_soundManager->PlayOneShotSound("Bullet_E", 0.5f);
		break;
	case(BULLET5) :
		//tempEntity = new Bullet_p5(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z + 60), XMFLOAT3(1, 1, 20));
		m_bullet5.push_back(new Bullet_p5(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z + 60), XMFLOAT3(1, 1, 20),1));
		m_soundManager->PlayOneShotSound("Laser_R", 0.5f);
		break;
	}
}

void EntityManager::Initialize(SoundManager* soundManager, Input* input, ID3D11Device* device, ID3D11DeviceContext* deviceContext, Score* scoreManager)
{

	//Set the soundManager pointer which will be used in every entity
	m_soundManager = soundManager;

	m_scoreManager = scoreManager;

	InitMusic("Resources/PixieTrust.txt");

	m_beatDetector = new BeatDetector(m_soundManager);
	m_beatDetector->AudioProcess();

	//Set the input class which will be passed down to Player
	m_input = input;

	//Set device and context
	m_device = device;
	m_deviceContext = deviceContext;

	//Set the renderer
	m_renderer = new Renderer(m_deviceContext, m_device);

	//Create model handlers for each entity type
	m_modelHandlers[PLAYER] = new ModelHandler;
	m_modelHandlers[PLAYER]->LoadOBJData("Resources/Models/TestCube.obj", "Resources/Models/TestCube.mtl", m_device, m_deviceContext);
	m_modelHandlers[PLAYER]->CreateBuffers(m_device);
	m_modelHandlers[PLAYER]->CreateShaders(m_device, "Shaders\\PlayerVS.hlsl", "Shaders\\PlayerGS.hlsl", "Shaders\\PlayerPS.hlsl");
	m_modelHandlers[ENEMY1] = new ModelHandler;
	m_modelHandlers[ENEMY1]->LoadOBJData("Resources/Models/TestCube.obj", "Resources/Models/TestCube.mtl", m_device, m_deviceContext);
	m_modelHandlers[ENEMY1]->CreateBuffers(m_device);
	m_modelHandlers[ENEMY1]->CreateShaders(m_device, "Shaders\\EnemiesVS.hlsl", "Shaders\\EnemiesGS.hlsl", "Shaders\\EnemiesPS.hlsl");
	m_modelHandlers[ENEMY2] = new ModelHandler;
	m_modelHandlers[ENEMY3] = new ModelHandler;
	m_modelHandlers[ENEMY4] = new ModelHandler;
	m_modelHandlers[BULLET1] = new ModelHandler;
	m_modelHandlers[BULLET1]->LoadOBJData("Resources/Models/Bullet1.obj", "Resources/Models/Bullet1.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET1]->CreateBuffers(m_device);
	m_modelHandlers[BULLET1]->CreateShaders(m_device, "Shaders\\BulletVS.hlsl", "Shaders\\BulletGS.hlsl", "Shaders\\BulletPS.hlsl");
	m_modelHandlers[BULLET2] = new ModelHandler;
	m_modelHandlers[BULLET2]->LoadOBJData("Resources/Models/Bullet2.obj", "Resources/Models/Bullet2.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET2]->CreateBuffers(m_device);
	m_modelHandlers[BULLET2]->CreateShaders(m_device, "Shaders\\BulletVS.hlsl", "Shaders\\BulletGS.hlsl", "Shaders\\BulletPS.hlsl");
	m_modelHandlers[BULLET3] = new ModelHandler;
	m_modelHandlers[BULLET3]->LoadOBJData("Resources/Models/Bullet3.obj", "Resources/Models/Bullet3.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET3]->CreateBuffers(m_device);
	m_modelHandlers[BULLET3]->CreateShaders(m_device, "Shaders\\BulletVS.hlsl", "Shaders\\BulletGS.hlsl", "Shaders\\BulletPS.hlsl");
	m_modelHandlers[BULLET4] = new ModelHandler;
	m_modelHandlers[BULLET4]->LoadOBJData("Resources/Models/Bullet4.obj", "Resources/Models/Bullet4.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET4]->CreateBuffers(m_device);
	m_modelHandlers[BULLET4]->CreateShaders(m_device, "Shaders\\BulletVS.hlsl", "Shaders\\BulletGS.hlsl", "Shaders\\BulletPS.hlsl");
	m_modelHandlers[BULLET5] = new ModelHandler;
	m_modelHandlers[BULLET5]->LoadOBJData("Resources/Models/Laser1.obj", "Resources/Models/Laser1.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET5]->CreateBuffers(m_device);
	m_modelHandlers[BULLET5]->CreateShaders(m_device, "Shaders\\BulletVS.hlsl", "Shaders\\BulletGS.hlsl", "Shaders\\BulletPS.hlsl");
	m_modelHandlers[BULLET6] = new ModelHandler;
	m_modelHandlers[BULLET6]->LoadOBJData("Resources/Models/EnemyBullet.obj", "Resources/Models/EnemyBullet.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET6]->CreateBuffers(m_device);
	m_modelHandlers[BULLET6]->CreateShaders(m_device, "Shaders\\BulletVS.hlsl", "Shaders\\BulletGS.hlsl", "Shaders\\BulletPS.hlsl");
	//Temp, create player
	SpawnEntity(PLAYER);
	//Temp, creates partsys
	wstring _texName = L"Resources\\Models\\star3.jpg";
	m_partSys.CreateBuffer(m_device, m_deviceContext, _texName);
	m_partSys.CreateShaders(m_device);

	m_soundManager->PlayMusic(0.5f);
	ChangeSongData(m_beatDetector->GetTempo());
	m_doBeatDet = true;
	m_beat = m_beatDetector->GetBeat();

	//Create Light Buffer
	m_light.InitializBuffer(m_device);
}

void EntityManager::Render()
{

	m_partSys.PartRend(m_deviceContext);
	
	//Render Player
	if(m_player->GetHealth() > 0)
	m_renderer->Render(m_modelHandlers[PLAYER], m_player->GetPosition(), m_player->GetRotation(), m_player->GetScale());
	RenderBullets();

	//Render Enemies
	RenderEnemies();
	}

void EntityManager::Update(double time)
{
		//Regular BPM test
	if (m_doBeatDet == false) 
	{
		m_timeSinceLastBeat += time * 1000;
		if (m_timeSinceLastBeat >= 60000 / m_currentBPM) 
		{
			m_timeSinceLastBeat -= 60000 / m_currentBPM;

			//BEAT WAS DETECTED
			if (m_offsetCount > m_offset)
			{
				BeatWasDetected();

				EnemyFire();
			}
			else
				m_offsetCount++;
		}
	}
	else {
		//BeatDet test
		float _currentPos = m_soundManager->GetCurrentMusicTimePCM() / 1024.f;

		if (m_beat[(int)_currentPos] > 0.0f && m_timeSinceLastBeat > 0.1)		//Small time buffer to prevent it from going off 50 times per beat 
		{
			//BEAT WAS DETECTED
			if (m_offsetCount > m_offset) {
				BeatWasDetected();
				m_timeSinceLastBeat = 0;
				EnemyFire();
			}
			else {
				m_timeSinceLastBeat = 0;
				m_offsetCount++;
			}
		}
		else {
			m_timeSinceLastBeat += time;
		}
	}

	//Do collision checks
	int _addScore = 0;
	//Check Bullet1 agains Enemies
	_addScore += m_collision.CheckCollisionEntity(&m_bullet1, &m_enemy1,BULLET1, ENEMY1);
	//_addScore += m_collision.CheckCollisionEntity(&m_bullet1, &m_enemy2,BULLET1, ENEMY2);
	//_addScore += m_collision.CheckCollisionEntity(&m_bullet1, &m_enemy3,BULLET1, ENEMY3);
	//_addScore += m_collision.CheckCollisionEntity(&m_bullet1, &m_enemy4,BULLET1, ENEMY4);


	//Check Bullet2 agains Enemies
	_addScore += m_collision.CheckCollisionEntity(&m_bullet2, &m_enemy1,BULLET2, ENEMY1);
	//_addScore += m_collision.CheckCollisionEntity(&m_bullet2, &m_enemy2,BULLET2, ENEMY2);
	//_addScore += m_collision.CheckCollisionEntity(&m_bullet2, &m_enemy3,BULLET2, ENEMY3);
	//_addScore += m_collision.CheckCollisionEntity(&m_bullet2, &m_enemy4,BULLET2, ENEMY4);


	//Check Bullet3 agains Enemies
	_addScore += m_collision.CheckCollisionEntity(&m_bullet3, &m_enemy1,BULLET3, ENEMY1);
	//_addScore += m_collision.CheckCollisionEntity(&m_bullet3, &m_enemy2,BULLET3, ENEMY2);
	//_addScore += m_collision.CheckCollisionEntity(&m_bullet3, &m_enemy3,BULLET3, ENEMY3);
	//_addScore += m_collision.CheckCollisionEntity(&m_bullet3, &m_enemy4,BULLET3, ENEMY4);


	//Check Bullet4 agains Enemies
	_addScore += m_collision.CheckCollisionEntity(&m_bullet4, &m_enemy1,BULLET4, ENEMY1);
	//_addScore += m_collision.CheckCollisionEntity(&m_bullet4, &m_enemy2,BULLET4, ENEMY2);
	//_addScore += m_collision.CheckCollisionEntity(&m_bullet4, &m_enemy3,BULLET4, ENEMY3);
	//_addScore += m_collision.CheckCollisionEntity(&m_bullet4, &m_enemy4,BULLET4, ENEMY4);

	//Check Bullet5 agains Enemies
	_addScore += m_collision.CheckCollisionEntity(&m_bullet5, &m_enemy1,BULLET5, ENEMY1);
	//_addScore += m_collision.CheckCollisionEntity(&m_bullet5, &m_enemy2,BULLET5, ENEMY2);
	//_addScore += m_collision.CheckCollisionEntity(&m_bullet5, &m_enemy3,BULLET5, ENEMY3);
	//_addScore += m_collision.CheckCollisionEntity(&m_bullet5, &m_enemy4,BULLET5, ENEMY4);

	m_scoreManager->AddScore(_addScore);

	//Check Player against Enemy Bullet
	if (m_player->GetHealth() > 0 && !m_player->GetDelete())
	{
		std::vector<Entity*> _playerVec = { m_player };
		m_collision.CheckCollisionEntity(&m_bullet6, &_playerVec, BULLET6, PLAYER);
		if (m_player->GetHealth() <= 0)
			m_player->SetDelete(true);
	}
	//Enemies
	for (auto i = 0; i < m_enemy1.size(); i++)
		m_enemy1[i]->Update(time);

	//for (auto i = 0; i < m_enemy2.size(); i++)
	//	m_enemy2[i]->Update(time);

	//for (auto i = 0; i < m_enemy3.size(); i++)
	//	m_enemy3[i]->Update(time);

	//for (auto i = 0; i < m_enemy4.size(); i++)
	//	m_enemy4[i]->Update(time);


	//Update every entity of Bullet1
	for (int i = 0; i < m_bullet1.size(); i++)
		m_bullet1[i]->Update(time);
	//Update every entity of Bullet2
	for (int i = 0; i < m_bullet2.size(); i++)
		m_bullet2[i]->Update(time);
	//Update every entity of Bullet3
	for (int i = 0; i < m_bullet3.size(); i++)
		m_bullet3[i]->Update(time);
	//Update every entity of Bullet4
	for (int i = 0; i < m_bullet4.size(); i++)
		m_bullet4[i]->Update(time);
	//Update every entity of Bullet5
	for (int i = 0; i < m_bullet5.size(); i++)
		m_bullet5[i]->Update(time);
	//Update every entity of Bullet6
	for (int i = 0; i < m_bullet6.size(); i++)
		m_bullet6[i]->Update(time);

	if (!m_player->GetDelete())
	m_player->Update(time);
	else
		m_player->Destroyed(time);
	
	//CheckEnemies Out Of BOUNDS
	m_enemy1 = CheckOutOfBounds(m_enemy1);
	m_enemy2 = CheckOutOfBounds(m_enemy2);
	m_enemy3 = CheckOutOfBounds(m_enemy3);
	m_enemy4 = CheckOutOfBounds(m_enemy4);
	//Out of bounds check, remove immediately
	
	m_bullet1 = CheckOutOfBounds(m_bullet1);
	m_bullet2 = CheckOutOfBounds(m_bullet2);
	m_bullet3 = CheckOutOfBounds(m_bullet3);
	m_bullet4 = CheckOutOfBounds(m_bullet4);
	m_bullet5 = CheckIfAlive(m_bullet5);
	m_bullet6 = CheckOutOfBounds(m_bullet6);

	//sets the lightbuffer
	m_light.SetConstbuffer(m_deviceContext);

	//Update Particle System
	m_partSys.updatePart(m_deviceContext, time, 40);
}

void EntityManager::ChangeSongData(int bpm)
{
	m_currentBPM = bpm;
}

void EntityManager::InitMusic(std::string filename)
{
	ifstream _file;
	_file.open(filename);
	char _key[100];
	char _value[100];
	std::string _tempLine;
	while (getline(_file, _tempLine))
	{

		std::istringstream _ss(_tempLine);

		_ss.get(_key, 1000, '=');		//Get field name
		_ss.ignore();
		_ss.get(_value, 1000, '=');		//Get value
		
		if (std::string(_key) == "music")
			m_soundManager->LoadMusic(_value);		//Load music
		else if (std::string(_key) == "offset")
			m_offset = atoi(_value);				//Load beginning offset
		else if (std::string(_key) == "bulletD")
			m_soundManager->LoadSound(_value, _value, "DefaultBullet", LOAD_MEMORY);
		else if (std::string(_key) == "bulletQ")
			m_soundManager->LoadSound(_value, _value, "Bullet_Q", LOAD_MEMORY);
		else if (std::string(_key) == "bulletW")
			m_soundManager->LoadSound(_value, _value, "Bullet_W", LOAD_MEMORY);
		else if (std::string(_key) == "bulletE")
			m_soundManager->LoadSound(_value, _value, "Bullet_E", LOAD_MEMORY);
		else if (std::string(_key) == "bulletR")
			m_soundManager->LoadSound(_value, _value, "Laser_R", LOAD_MEMORY);
		else if (std::string(_key) == "score")
			m_scoreManager->LoadScore(_value);
	}

}

void EntityManager::BeatWasDetected()
{
	static int _enemySpawRate;
	//Spawn correct bullet (which plays the sound as well) Only if player is alive
	if (m_player->GetHealth() > 0)
	{
	BulletType _bullet = m_input->CheckBullet();
	switch (_bullet)
	{
	case INPUT_DEFAULT_BULLET:
		SpawnEntity(BULLET1); //Default bullet
		break;
	case INPUT_BULLET2:
		SpawnEntity(BULLET2);
		break;
	case INPUT_BULLET3:
		SpawnEntity(BULLET3);
		break;
	case INPUT_BULLET4:
		SpawnEntity(BULLET4);
		break;
	case INPUT_BULLET5:
		SpawnEntity(BULLET5);
		break;
	default:
		break;
	}
	}


	//use time and check that after 30 sec or so increse the level count by some.. int
	
	if (_enemySpawRate == m_beatDetector->GetTempo()/30)
	{
		SpawnEntity(ENEMY1);
		_enemySpawRate = 0;
	}
	else
		_enemySpawRate++;
	
}

vector<Entity*> EntityManager::CheckOutOfBounds(std::vector<Entity*> bullet)
{
	//Out of bounds check, remove immediately
	//bool removed = false;
	vector<Entity*> _tempVec = bullet;			//Can't use the member variable for some reason
	for (int i = 0; i < _tempVec.size() /*&& removed == false*/; i++) {			//REMOVE REMOVED == FALSE AND MAKE LISTS!
		XMFLOAT3 _tempPos = _tempVec[i]->GetPosition();
		if (_tempPos.x > 110 || _tempPos.x < -20 || _tempPos.z > 120 || _tempPos.z < -20) {
			delete _tempVec[i];
			_tempVec.erase(_tempVec.begin() + i);
			i--;
			//removed = true;
		}
	}
	return _tempVec;
}
	
void EntityManager::RenderEnemies()
{
	vector<XMFLOAT3> _instancePosition;
	vector<XMMATRIX> _instanceRotation;
	vector<XMFLOAT3> _instanceScale;

	_instancePosition.clear();
	_instanceScale.clear();
	_instanceRotation.clear();

	if (m_enemy1.size() > 0)
	{
		for (auto i = 0; i < m_enemy1.size(); i++)
		{
			_instancePosition.push_back(m_enemy1[i]->GetPosition());
			_instanceScale.push_back(m_enemy1[i]->GetScale());
			_instanceRotation.push_back(m_enemy1[i]->GetRotation());

		}
		m_modelHandlers[ENEMY1]->SetBuffers(m_deviceContext);
		m_modelHandlers[ENEMY1]->SetShaders(m_deviceContext);
		m_renderer->RenderInstanced(m_modelHandlers[ENEMY1], _instancePosition, _instanceRotation, m_enemy1.size(), _instanceScale);

	}

	if (m_enemy2.size() > 0)
	{
		for (auto i = 0; i < m_enemy2.size(); i++)
		{
			_instancePosition.push_back(m_enemy2[i]->GetPosition());
			_instanceScale.push_back(m_enemy2[i]->GetScale());
			_instanceRotation.push_back(m_enemy2[i]->GetRotation());

		}
		m_modelHandlers[ENEMY2]->SetBuffers(m_deviceContext);
		m_modelHandlers[ENEMY2]->SetShaders(m_deviceContext);
		m_renderer->RenderInstanced(m_modelHandlers[ENEMY2], _instancePosition, _instanceRotation, m_enemy2.size(), _instanceScale);

	}

	if (m_enemy3.size() > 0)
	{
		for (auto i = 0; i < m_enemy3.size(); i++)
		{
			_instancePosition.push_back(m_enemy3[i]->GetPosition());
			_instanceScale.push_back(m_enemy3[i]->GetScale());
			_instanceRotation.push_back(m_enemy3[i]->GetRotation());

		}
		m_modelHandlers[ENEMY3]->SetBuffers(m_deviceContext);
		m_modelHandlers[ENEMY3]->SetShaders(m_deviceContext);
		m_renderer->RenderInstanced(m_modelHandlers[ENEMY3], _instancePosition, _instanceRotation, m_enemy3.size(), _instanceScale);

	}

	if (m_enemy4.size() > 0)
	{
		for (auto i = 0; i < m_enemy4.size(); i++)
		{
			_instancePosition.push_back(m_enemy4[i]->GetPosition());
			_instanceScale.push_back(m_enemy4[i]->GetScale());
			_instanceRotation.push_back(m_enemy4[i]->GetRotation());

		}
		m_modelHandlers[ENEMY4]->SetBuffers(m_deviceContext);
		m_modelHandlers[ENEMY4]->SetShaders(m_deviceContext);
		m_renderer->RenderInstanced(m_modelHandlers[ENEMY4], _instancePosition, _instanceRotation, m_enemy4.size(), _instanceScale);

	}

}
	
void EntityManager::RenderBullets()
{
	vector<XMFLOAT3> _instancePosition;
	vector<XMMATRIX> _instanceRotation;
	vector<XMFLOAT3> _instanceScale;

	_instancePosition.clear();
	_instanceScale.clear();
	_instanceRotation.clear();

	if (m_bullet1.size() > 0)
	{
		for (int i = 0; i < m_bullet1.size(); i++) {
			_instancePosition.push_back(m_bullet1[i]->GetPosition());
			_instanceScale.push_back(m_bullet1[i]->GetScale());
			_instanceRotation.push_back(m_bullet1[i]->GetRotation());
		}
		m_renderer->RenderInstanced(m_modelHandlers[BULLET1], _instancePosition, _instanceRotation, m_bullet1.size(), _instanceScale);
		_instancePosition.clear();
		_instanceScale.clear();
		_instanceRotation.clear();
	}
	if (m_bullet2.size() > 0)
	{
		for (int i = 0; i < m_bullet2.size(); i++) {
			_instancePosition.push_back(m_bullet2[i]->GetPosition());
			_instanceScale.push_back(m_bullet2[i]->GetScale());
			_instanceRotation.push_back(m_bullet2[i]->GetRotation());
		}
		m_renderer->RenderInstanced(m_modelHandlers[BULLET2], _instancePosition, _instanceRotation, m_bullet2.size(), _instanceScale);
		_instancePosition.clear();
		_instanceScale.clear();
		_instanceRotation.clear();
	}
	if (m_bullet3.size() > 0)
	{
		for (int i = 0; i < m_bullet3.size(); i++) {
			_instancePosition.push_back(m_bullet3[i]->GetPosition());
			_instanceScale.push_back(m_bullet3[i]->GetScale());
			_instanceRotation.push_back(m_bullet3[i]->GetRotation());
		}
		m_renderer->RenderInstanced(m_modelHandlers[BULLET3], _instancePosition, _instanceRotation, m_bullet3.size(), _instanceScale);
		_instancePosition.clear();
		_instanceScale.clear();
		_instanceRotation.clear();
	}
	if (m_bullet4.size() > 0)
	{
		for (int i = 0; i < m_bullet4.size(); i++) {
			_instancePosition.push_back(m_bullet4[i]->GetPosition());
			_instanceScale.push_back(m_bullet4[i]->GetScale());
			_instanceRotation.push_back(m_bullet4[i]->GetRotation());
		}
		m_renderer->RenderInstanced(m_modelHandlers[BULLET4], _instancePosition, _instanceRotation, m_bullet4.size(), _instanceScale);
		_instancePosition.clear();
		_instanceScale.clear();
		_instanceRotation.clear();
	}
	if (m_bullet5.size() > 0)
	{
		for (int i = 0; i < m_bullet5.size(); i++) {
			_instancePosition.push_back(m_bullet5[i]->GetPosition());
			_instanceScale.push_back(m_bullet5[i]->GetScale());
			_instanceRotation.push_back(m_bullet5[i]->GetRotation());
		}
		m_renderer->RenderInstanced(m_modelHandlers[BULLET5], _instancePosition, _instanceRotation, m_bullet5.size(), _instanceScale);
		_instancePosition.clear();
		_instanceScale.clear();
		_instanceRotation.clear();
	}
	if (m_bullet6.size() > 0)
	{
		for (int i = 0; i < m_bullet6.size(); i++) {
			_instancePosition.push_back(m_bullet6[i]->GetPosition());
			_instanceScale.push_back(m_bullet6[i]->GetScale());
			_instanceRotation.push_back(m_bullet6[i]->GetRotation());
		}
		m_renderer->RenderInstanced(m_modelHandlers[BULLET6], _instancePosition, _instanceRotation, m_bullet6.size(), _instanceScale);
		_instancePosition.clear();
		_instanceScale.clear();
		_instanceRotation.clear();
	}

}

vector<Entity*> EntityManager::CheckIfAlive(std::vector<Entity*> bullet)
{
	//If Alive check, remove immediately
	bool removed = false;
	vector<Entity*> _tempVec = bullet;			//Can't use the member variable for some reason
	for (int i = 0; i < _tempVec.size() && removed == false; i++) 
	{
		bool _temp = _tempVec[i]->GetDelete();
		if (_temp == true) 
		{
			delete _tempVec[i];
			_tempVec.erase(_tempVec.begin() + i);
			removed = true;
		}
		else
		{
			_tempVec[i]->SetPosition(XMFLOAT3(m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z + 60));
		}
	}
	return _tempVec;
}

void EntityManager::EnemyFire()
{
	for (auto i = 0; i < m_enemy1.size(); i++)
	{
		if (m_enemy1[i]->GetFireTime()>3.0f){
			m_bullet6.push_back(new Bullet_e(m_soundManager, MAPWIDTH, MAPLENGTH, m_enemy1[i]->GetPosition(), XMFLOAT3(0.5, 0.5, 0.5), 1));
			m_enemy1[i]->SetFireTime(0);
		}

		m_enemy1[i]->SetFireTime(m_enemy1[i]->GetFireTime() + 0.5);
	}
}