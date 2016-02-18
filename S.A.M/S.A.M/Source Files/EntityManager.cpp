#include "EntityManager.h"
#include <iostream>
#define MAPWIDTH 77
#define MAPLENGTH 103
#define BEATLENIENCY 100

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
	for (int i = 0; i < 11; i++)
	{
		delete m_modelHandlers[i];
		m_modelHandlers[i] = NULL;
	}
	for (int i = 0; i < 6; i++)
	{
		delete m_shaderLoad[i];
		m_shaderLoad[i] = NULL;
	}
	delete m_renderer;
	delete m_beatDetector;
	delete m_rocketPartSys;
	delete m_playerPartSys;

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
	float _tempX = rand() % MAPWIDTH;

	switch (type) {
	case(PLAYER) :
		m_player = new Player(m_soundManager, MAPWIDTH,MAPLENGTH,XMFLOAT3(MAPWIDTH / 2, 0.0f, MAPLENGTH / 2), XMFLOAT3(0.5f, 0.5f, 0.5f), 1, m_input);
		break;
	case(ENEMY1) :
		//temptest = new Enemy_1(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(_tempX, 0.0f, 70.0f),XMFLOAT3(0.5f,0.5f,0.5f));
		m_enemy1.push_back(new Enemy_1(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(_tempX, 0.0f, 110), XMFLOAT3(0.5f, 0.5f, 0.5f),1000,m_enemy1MovPatterns[0].second));
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
		m_bullet1.push_back(new Bullet_p1(m_soundManager, MAPWIDTH, MAPLENGTH, m_player->GetPosition(), XMFLOAT3(1, 1, 1), 1, m_modelHandlers[BULLET1]->GetDeffuse()));
		m_soundManager->PlayOneShotSound("DefaultBullet", 0.5f);
		break;
	case(BULLET2) :
		//tempEntity = new Bullet_p2(m_soundManager, MAPWIDTH, MAPLENGTH, m_player->GetPosition(), XMFLOAT3(1, 1, 1));
		m_bullet2.push_back(new Bullet_p2(m_soundManager, MAPWIDTH, MAPLENGTH, m_player->GetPosition(), XMFLOAT3(1, 1, 1),1));
		m_soundManager->PlayOneShotSound("Bullet_Q", 0.5f);
		break;
	case(BULLET3) :
		//tempEntity = new Bullet_p3(m_soundManager, MAPWIDTH, MAPLENGTH, m_player->GetPosition(), XMFLOAT3(1, 1, 1));
		m_bullet3.push_back(new Bullet_p3(m_soundManager, MAPWIDTH, MAPLENGTH, m_player->GetPosition(), XMFLOAT3(1, 1, 1),1 , m_modelHandlers[BULLET3]->GetDeffuse()));
		m_soundManager->PlayOneShotSound("Bullet_W", 0.5f);
		break;
	case(BULLET4) :
		//tempEntity = new Bullet_p4(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x - 1, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(0.5, 0.5, 0.5));
		m_bullet4.push_back(new Bullet_p4(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x - 1, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(0.5, 0.5, 0.5), 1, m_modelHandlers[BULLET4]->GetDeffuse(), 0));
		//tempEntity = new Bullet_p4(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(0.5, 0.5, 0.5));
		m_bullet4.push_back(new Bullet_p4(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(0.5, 0.5, 0.5), 1, m_modelHandlers[BULLET4]->GetDeffuse(), 1));
		//tempEntity = new Bullet_p4(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x + 1, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(0.5, 0.5, 0.5));
		m_bullet4.push_back(new Bullet_p4(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x + 1, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(0.5, 0.5, 0.5), 1, m_modelHandlers[BULLET4]->GetDeffuse(), 2));
		m_soundManager->PlayOneShotSound("Bullet_E", 0.5f);
		break;
	case(BULLET5) :
		//tempEntity = new Bullet_p5(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z + 60), XMFLOAT3(1, 1, 20));
		m_bullet5.push_back(new Bullet_p5(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z + 60), XMFLOAT3(1, 1, 20),1));
		m_soundManager->PlayOneShotSound("Laser_R", 0.5f);
		break;
	}
}

void EntityManager::Initialize(SoundManager* soundManager, Input* input, ID3D11Device* device, ID3D11DeviceContext* deviceContext, Stats* statsManager)
{

	//Set the soundManager pointer which will be used in every entity
	m_soundManager = soundManager;

	m_statsManager = statsManager;
	m_statsManager->SetLives();

	//Set the input class which will be passed down to Player
	m_input = input;

	//Set device and context
	m_device = device;
	m_deviceContext = deviceContext;

	//Set the renderer
	m_renderer = new Renderer(m_deviceContext, m_device);

	//create shaders
	m_shaderLoad[SHADER_PLAYER] = new ShaderHandler();
	m_shaderLoad[SHADER_PLAYER]->CreateShaders(m_device, "Shaders\\PlayerVS.hlsl", "Shaders\\PlayerGS.hlsl", "Shaders\\PlayerPS.hlsl");
	m_shaderLoad[SHADER_BULLET] = new ShaderHandler();
	m_shaderLoad[SHADER_BULLET]->CreateShaders(m_device, "Shaders\\BulletVS.hlsl", "Shaders\\BulletGS.hlsl", "Shaders\\BulletPS.hlsl");
	m_shaderLoad[SHADER_ENEMY] = new ShaderHandler();
	m_shaderLoad[SHADER_ENEMY]->CreateShaders(m_device, "Shaders\\EnemiesVS.hlsl", "Shaders\\EnemiesGS.hlsl", "Shaders\\EnemiesPS.hlsl");
	m_shaderLoad[SHADER_MENU] = new ShaderHandler();
	m_shaderLoad[SHADER_PLAYERPART] = new ShaderHandler();
	m_shaderLoad[SHADER_PLAYERPART]->CreatePlayerFireShaders(m_device, "Shaders\\PlayerPartVS.hlsl", "Shaders\\PlayerPartGS.hlsl", "Shaders\\PlayerPartPS.hlsl");
	m_shaderLoad[SHADER_ROCKETPART] = new ShaderHandler();
	m_shaderLoad[SHADER_ROCKETPART]->CreateShadersPosOnly(m_device, "Shaders\\InstancePartVS.hlsl", "Shaders\\InstancePartGS.hlsl", "Shaders\\InstancePartPS.hlsl");

	//Create model handlers for each entity type
	m_modelHandlers[PLAYER] = new ModelHandler();
	m_modelHandlers[PLAYER]->LoadOBJData("Resources/Models/TestCube.obj", "Resources/Models/TestCube.mtl", m_device, m_deviceContext);
	m_modelHandlers[PLAYER]->CreateBuffers(m_device);
	m_modelHandlers[BULLET1] = new ModelHandler();
	m_modelHandlers[BULLET1]->LoadOBJData("Resources/Models/Bullet1.obj", "Resources/Models/Bullet1.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET1]->CreateBuffers(m_device);
	m_modelHandlers[BULLET2] = new ModelHandler();
	m_modelHandlers[BULLET2]->LoadOBJData("Resources/Models/Bullet2.obj", "Resources/Models/Bullet2.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET2]->CreateBuffers(m_device);
	m_modelHandlers[BULLET3] = new ModelHandler();
	m_modelHandlers[BULLET3]->LoadOBJData("Resources/Models/Bullet3.obj", "Resources/Models/Bullet3.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET3]->CreateBuffers(m_device);
	m_modelHandlers[BULLET4] = new ModelHandler();
	m_modelHandlers[BULLET4]->LoadOBJData("Resources/Models/Bullet4.obj", "Resources/Models/Bullet4.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET4]->CreateBuffers(m_device);
	m_modelHandlers[BULLET5] = new ModelHandler();
	m_modelHandlers[BULLET5]->LoadOBJData("Resources/Models/Laser1.obj", "Resources/Models/Laser1.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET5]->CreateBuffers(m_device);
	m_modelHandlers[BULLET6] = new ModelHandler();
	m_modelHandlers[BULLET6]->LoadOBJData("Resources/Models/EnemyBullet.obj", "Resources/Models/EnemyBullet.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET6]->CreateBuffers(m_device);
	m_modelHandlers[ENEMY1] = new ModelHandler();
	m_modelHandlers[ENEMY1]->LoadOBJData("Resources/Models/TestCube.obj", "Resources/Models/TestCube.mtl", m_device, m_deviceContext);
	m_modelHandlers[ENEMY1]->CreateBuffers(m_device);
	m_modelHandlers[ENEMY2] = new ModelHandler;
	m_modelHandlers[ENEMY3] = new ModelHandler;
	m_modelHandlers[ENEMY4] = new ModelHandler;
	//Temp, create player
	SpawnEntity(PLAYER);
	//Temp, creates partsys
	wstring _texName = L"Resources\\Models\\star.jpg";
	m_rocketPartSys = new FirePart(2, 1000);
	m_rocketPartSys->CreateBuffer(m_device, m_deviceContext, _texName);

	std::vector<Entity*> _playerVec = { m_player };
	m_playerPartSys = new PlayerPart(2, 500, _playerVec);
	m_playerPartSys->CreateBuffer(m_device, m_deviceContext, _texName);



	//Create Light Buffer
	m_light.InitializBuffer(m_device);
}

void EntityManager::Render()
{
	if (m_bullet2.size() > 0)
	{
		m_rocketPartSys->AddPartSys(m_bullet2, XMFLOAT4(0, 0, -7, 0));
		m_shaderLoad[SHADER_ROCKETPART]->SetShaders(m_deviceContext);
		m_rocketPartSys->SetBuffer(m_deviceContext);
		m_rocketPartSys->Render(m_deviceContext);
	}

	m_shaderLoad[SHADER_PLAYERPART]->SetShaders(m_deviceContext);
	m_playerPartSys->Render(m_deviceContext);


	//Render Player
	if (m_player->GetHealth() > 0)			//Invulnerability-blinking
	{
		m_shaderLoad[SHADER_PLAYER]->SetShaders(m_deviceContext);
		m_renderer->Render(m_modelHandlers[PLAYER], m_player->GetPosition(), m_player->GetRotation(), m_player->GetScale());
	}
	m_shaderLoad[SHADER_BULLET]->SetShaders(m_deviceContext);
	RenderBullets();

	//Render Enemies
	m_shaderLoad[SHADER_ENEMY]->SetShaders(m_deviceContext);
	RenderEnemies();
	}

void EntityManager::Update(double time)
{
	CheckCombo();

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
				m_light.beatBoost(true, time, -1, m_currentBPM);
				m_modelHandlers[BULLET1]->beatBoost(true, time, -1, m_currentBPM);
				m_modelHandlers[BULLET3]->beatBoost(true, time, -1, m_currentBPM);
				m_modelHandlers[BULLET4]->beatBoost(true, time, -1, m_currentBPM);
				m_modelHandlers[BULLET5]->beatBoost(true, time, -1, m_currentBPM);
				m_modelHandlers[BULLET6]->beatBoost(true, time, -1, m_currentBPM);
			}
			else
				m_offsetCount++;
		}
		else
		{
			m_light.beatBoost(false, time, -1, m_currentBPM);
			m_modelHandlers[BULLET1]->beatBoost(false, time, -1, m_currentBPM);
			m_modelHandlers[BULLET3]->beatBoost(false, time, -1, m_currentBPM);
			m_modelHandlers[BULLET4]->beatBoost(false, time, -1, m_currentBPM);
			m_modelHandlers[BULLET5]->beatBoost(false, time, -1, m_currentBPM);
			m_modelHandlers[BULLET6]->beatBoost(false, time, -1, m_currentBPM);
		}
	}
	else {
		//BeatDet test
		float _currentPos = m_soundManager->GetCurrentMusicTimePCM() / 1024.f;

		if (m_beat[(int)_currentPos] > 0.0f && m_timeSinceLastBeat > 100)		//Small time buffer to prevent it from going off 50 times per beat 
		{
			//BEAT WAS DETECTED
			if (m_offsetCount > m_offset) {
				BeatWasDetected();
				m_light.beatBoost(true, time, m_timeSinceLastBeat/1000, 0);
				m_modelHandlers[BULLET1]->beatBoost(true, time, m_timeSinceLastBeat/1000, 0);
				m_modelHandlers[BULLET3]->beatBoost(true, time, m_timeSinceLastBeat/1000, 0);
				m_modelHandlers[BULLET4]->beatBoost(true, time, m_timeSinceLastBeat/1000, 0);
				m_modelHandlers[BULLET5]->beatBoost(true, time, m_timeSinceLastBeat/1000, 0);
				m_modelHandlers[BULLET6]->beatBoost(true, time, m_timeSinceLastBeat/1000, 0);
				m_timeSinceLastBeat = 0;
				EnemyFire();
				
			}
			else {
				m_timeSinceLastBeat = 0;
				m_offsetCount++;
			}
		}
		else {
			m_timeSinceLastBeat += time * 1000;
			m_light.beatBoost(false, time, m_timeSinceLastBeat/1000, 0);
			m_modelHandlers[BULLET1]->beatBoost(false, time, m_timeSinceLastBeat/1000, 0);
			m_modelHandlers[BULLET3]->beatBoost(false, time, m_timeSinceLastBeat/1000, 0);
			m_modelHandlers[BULLET4]->beatBoost(false, time, m_timeSinceLastBeat/1000, 0);
			m_modelHandlers[BULLET5]->beatBoost(false, time, m_timeSinceLastBeat/1000, 0);
			m_modelHandlers[BULLET6]->beatBoost(false, time, m_timeSinceLastBeat/1000, 0);
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

	m_statsManager->AddScore(_addScore*(m_statsManager->GetCombo()+1));

	//Check Player against Enemy Bullet
	if (!m_player->GetInvulnerable())			//Only check if the player is alive and well
	{
		std::vector<Entity*> _playerVec = { m_player };
		m_collision.CheckCollisionEntity(&m_bullet6, &_playerVec, BULLET6, PLAYER);
		if (m_player->GetHealth() <= 0)
		{
			m_statsManager->ResetCombo();
			m_player->SetDelete(true);				//Set player to run destruction update
			m_statsManager->AddLives(-1);			//Reduce remaining lives
		}
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

	m_light.addLights(m_bullet1);
	m_light.addLights(m_bullet3);
	m_light.addLights(m_bullet4);
	m_light.addLights(m_bullet6);

	//sets the lightbuffer
	m_light.SetConstbuffer(m_deviceContext);

	//Update Particle System
	std::vector<Entity*> _playerVec = { m_player };
	m_rocketPartSys->Update(m_deviceContext, time, 10);
	m_playerPartSys->Update(m_deviceContext, time, 35, _playerVec);
}

void EntityManager::ChangeSongData(int bpm)
{
	m_currentBPM = bpm;
}

void EntityManager::InitMusic(const std::string &filename)
{
	vector<vector<XMFLOAT3>> _movPatterns;

	ifstream _file;
	_file.open(filename);

	char _key[100];
	char _value[100];
	std::string _tempLine;
	while (getline(_file, _tempLine))
	{

		std::istringstream _ss(_tempLine);

		_ss.get(_key, 100, '=');		//Get field name
		_ss.ignore();
		if (_key[0] != '#') {
			_ss.get(_value, 100, '=');		//Get value
						//Skip comment lines
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
				m_statsManager->LoadScore(_value);

			else if (std::string(_key) == "BeatPerShot1")
				m_beatPerShot1 = atoi(_value);
			else if (std::string(_key) == "BeatPerShot2")
				m_beatPerShot2 = atoi(_value);
			else if (std::string(_key) == "BeatPerShot3")
				m_beatPerShot3 = atoi(_value);
			else if (std::string(_key) == "BeatPerShot4")
				m_beatPerShot4 = atoi(_value);

			else if (std::string(_key) == "mov")	//Mov patterns
			{
				vector<XMFLOAT3> _pattern;
				_ss = istringstream(_value);
				string _floatVec;				//For keeping xmfloat3 string
				while (getline(_ss, _floatVec, '|')) 
				{
					XMFLOAT3 _splinePoint;
					istringstream _ssfloatVec = istringstream(_floatVec);
					string _coord;
					getline(_ssfloatVec, _coord, ',');		//Get x coord
					_splinePoint.x = stoi(_coord);

					_splinePoint.y = 0;

					getline(_ssfloatVec, _coord, ',');		//Get z coord
					_splinePoint.z = stoi(_coord);
					
					_pattern.push_back(_splinePoint);
				}
				_movPatterns.push_back(_pattern);	//Put the new pattern into the vector
			}
			else if (std::string(_key).find("movcomp") != string::npos) //Mov compilations
			{
				pair<int, vector<XMFLOAT3>> _movComp;
				_ss = istringstream(_value);
				
				string _startBeat;				
				getline(_ss, _startBeat, '|');		// Get at what beat enemies will spawn with this compilation
				_movComp.first = stoi(_startBeat);

				string _compSegment;
				while (getline(_ss, _compSegment, '|'))
				{
					istringstream _compSegmentSS(_compSegment);
					string _nrOfRepeats;
					getline(_compSegmentSS, _nrOfRepeats, ',');
					
					string _nrOfPattern;
					getline(_compSegmentSS, _nrOfPattern, ',');

					for (int i = 0; i < stoi(_nrOfRepeats); i++)			//Add to a temp full vector
						_movComp.second.insert(_movComp.second.end(), _movPatterns[stoi(_nrOfPattern)].begin(), _movPatterns[stoi(_nrOfPattern)].end());
				}

				//Add to the relevant final vector once done loading
				if (std::string(_key) == "movcomp1")
					m_enemy1MovPatterns.push_back(_movComp);
				if (std::string(_key) == "movcomp2")
					m_enemy2MovPatterns.push_back(_movComp);
				if (std::string(_key) == "movcomp3")
					m_enemy3MovPatterns.push_back(_movComp);
				if (std::string(_key) == "movcomp4")
					m_enemy4MovPatterns.push_back(_movComp);
			}
		}
	}

	//Init beatdetector
	m_beatDetector = new BeatDetector(m_soundManager);
	m_beatDetector->AudioProcess();

	//Start playing music
	m_soundManager->PlayMusic(0.5f);
	ChangeSongData(m_beatDetector->GetTempo());
	m_doBeatDet = true;				//Make this changable at song select
	m_beat = m_beatDetector->GetBeat();
}

void EntityManager::BeatWasDetected()
{
	static int _enemySpawnRate;
	//Spawn correct bullet (which plays the sound as well) Only if player is alive
	if (!m_player->GetDelete())
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
	
	if (_enemySpawnRate == m_beatDetector->GetTempo()/30)
	{
		SpawnEntity(ENEMY1);
		_enemySpawnRate = 0;
	}
	else
		_enemySpawnRate++;
	
}

vector<Entity*> EntityManager::CheckOutOfBounds(const std::vector<Entity*> &entity)
{
	//Out of bounds check, remove immediately
	//bool removed = false;
	vector<Entity*> _tempVec = entity;			//Can't use the member variable for some reason
	for (int i = 0; i < _tempVec.size() /*&& removed == false*/; i++) {			//REMOVE REMOVED == FALSE AND MAKE LISTS!
		XMFLOAT3 _tempPos = _tempVec[i]->GetPosition();
		if (_tempPos.x > MAPWIDTH+10 || _tempPos.x < -20 || _tempPos.z > MAPLENGTH+20 || _tempPos.z < -20) {
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
	//Don't render the lazer if the player just died
	if (m_bullet5.size() > 0 && !m_player->GetDelete())
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

vector<Entity*> EntityManager::CheckIfAlive(const std::vector<Entity*> &bullet)
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
		if (m_enemy1[i]->GetFireTime()>m_beatPerShot1){
			m_bullet6.push_back(new Bullet_e(m_soundManager, MAPWIDTH, MAPLENGTH, m_enemy1[i]->GetPosition(), XMFLOAT3(0.5, 0.5, 0.5), 1, m_modelHandlers[BULLET6]->GetDeffuse()));
			m_enemy1[i]->SetFireTime(0);
		}

		m_enemy1[i]->SetFireTime(m_enemy1[i]->GetFireTime() + 1.0f);
	}
}

void EntityManager::CheckCombo()
{
	// Check key presses near the beat, for combo
	static bool _registeredCombo = true;
	static BulletType _currentBulletType;
	static bool _spacebar = false;
	if (m_offsetCount > m_offset && m_player->GetDelete() == false) {						//Only check for combos after the beats have actually started
		if (m_timeSinceLastBeat < 25000 / m_currentBPM)
		{
			if (m_input->IsNewButtonPressed(_spacebar)) //If button is pressed
			{
				if (m_timeSinceLastBeat < BEATLENIENCY && _registeredCombo == false)	//If key was pressed during sweet spot and key hadn't been pressed earlier
				{
					m_statsManager->AddCombo();
					_registeredCombo = true;
				}
				else					//Reset combo if pressed more than once or after sweetspot
				{
					m_statsManager->ResetCombo();
				}
			}
			if (m_timeSinceLastBeat > BEATLENIENCY && m_timeSinceLastBeat < 30000 / m_currentBPM && _registeredCombo == false)	//If a key wasn't pressed at all during a beat, reset combo
				m_statsManager->ResetCombo();
		}
		else if (m_timeSinceLastBeat > 25000 / m_currentBPM && m_timeSinceLastBeat < 35000 / m_currentBPM)	//Switch to new beat, Allow a new key to be pressed 
			_registeredCombo = false;
		else if (m_timeSinceLastBeat > 35000 / m_currentBPM)
		{
			if (m_input->IsNewButtonPressed(_spacebar)) //If button is pressed
			{
				if (m_timeSinceLastBeat > 60000 / m_currentBPM - BEATLENIENCY && _registeredCombo == false)	//If key was pressed during sweet spot and key hadn't been pressed earlier
				{
					m_statsManager->AddCombo();
					_registeredCombo = true;
				}
				else					//Reset combo if pressed more than once or after sweetspot
				{
					m_statsManager->ResetCombo();
				}
			}
		}
	}
}