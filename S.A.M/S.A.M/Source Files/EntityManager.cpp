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

	for (int i = 0; i < m_bulletSphere.size(); i++)
		delete m_bulletSphere[i];

	for (int i = 0; i < m_explosion.size(); i++)
		delete m_explosion[i];

	m_enemyHealthColourBuffer->Release();
	

}

void EntityManager::SpawnEntity(HandlerIndex type)
{
	float _tempX = rand() % MAPWIDTH;

	switch (type) {
	case(PLAYER) :
		m_player = new Player(m_soundManager, MAPWIDTH,MAPLENGTH,XMFLOAT3(MAPWIDTH / 2, 0.0f, MAPLENGTH / 4), XMFLOAT3(0.8f, 0.8f, 0.8f), 1, m_input);
		break;
	case(ENEMY1) :
		for (int i = m_enemy1MovPatterns.size() - 1; i >= 0; i--)
		{
			if (m_enemy1MovPatterns[i].first <= m_statsManager->GetBeat())
			{
				m_enemy1.push_back(new Enemy_1(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(_tempX, 0.0f, 110), m_enemySize1, m_enemyHealth1, m_enemy1MovPatterns[i].second));
				i = -1;
			}
		}
		break;
	case(ENEMY2) :
		for (int i = m_enemy2MovPatterns.size() - 1; i >= 0; i--)
		{
			if (m_enemy2MovPatterns[i].first <= m_statsManager->GetBeat())
			{
				m_enemy2.push_back(new Enemy_2(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(_tempX, 0.0f, 110), m_enemySize2, m_enemyHealth2, m_enemy2MovPatterns[i].second));
				i = -1;
			}
		}
		break;
	case(ENEMY3) :
		for (int i = m_enemy3MovPatterns.size() - 1; i >= 0; i--)
		{
			if (m_enemy3MovPatterns[i].first <= m_statsManager->GetBeat())
			{
				m_enemy3.push_back(new Enemy_3(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(_tempX, 0.0f, 110), m_enemySize3, m_enemyHealth3, m_enemy3MovPatterns[i].second));
				i = -1;
			}
		}
		break;
	case(ENEMY4) :
		for (int i = m_enemy4MovPatterns.size() - 1; i >= 0; i--)
		{
			if (m_enemy4MovPatterns[i].first <= m_statsManager->GetBeat())
			{
				m_enemy4.push_back(new Enemy_4(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(_tempX, 0.0f, 110), m_enemySize4, m_enemyHealth4, m_enemy4MovPatterns[i].second));
				i = -1;
			}
		}
		break;
	case(BULLET1) :
		m_bullet1.push_back(new Bullet_p1(m_soundManager, MAPWIDTH, MAPLENGTH, m_player->GetPosition(), XMFLOAT3(0.5, 0.5, 0.5), 1, m_modelHandlers[BULLET1]->GetDeffuse()));
		m_soundManager->PlayOneShotSound("DefaultBullet", 0.5f);
		break;
	case(BULLET2) :
		m_bullet2.push_back(new Bullet_p2(m_soundManager, MAPWIDTH, MAPLENGTH, m_player->GetPosition(), XMFLOAT3(0.3, 0.3, 0.3), 1, m_rocketOffset));
		m_soundManager->PlayOneShotSound("Bullet_Q", 0.5f);
		break;
	case(BULLET3) :
		m_bullet3.push_back(new Bullet_p3(m_soundManager, MAPWIDTH, MAPLENGTH, m_player->GetPosition(), XMFLOAT3(2.0, 2.0, 2.0),1 , m_modelHandlers[BULLET3]->GetDeffuse()));
		m_soundManager->PlayOneShotSound("Bullet_W", 0.5f);
		break;
	case(BULLET4) :
		m_bullet4.push_back(new Bullet_p4(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x - 1, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(0.5, 0.5, 0.5), 1, m_modelHandlers[BULLET4]->GetDeffuse(), 0));
		m_bullet4.push_back(new Bullet_p4(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(0.5, 0.5, 0.5), 1, m_modelHandlers[BULLET4]->GetDeffuse(), 1));
		m_bullet4.push_back(new Bullet_p4(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x + 1, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(0.5, 0.5, 0.5), 1, m_modelHandlers[BULLET4]->GetDeffuse(), 2));
		m_soundManager->PlayOneShotSound("Bullet_E", 0.5f);
		break;
	case(BULLET5) :
		for (int i = 0; i < 18; i++)
		{
			m_bullet5.push_back(new Bullet_p5(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(2.0, 2.0, 5.0), 0, XMFLOAT3(-0.55f, 0.0f, 5.0f + i*6)));
			m_bullet5.push_back(new Bullet_p5(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z), XMFLOAT3(2.0, 2.0, 5.0), 1, XMFLOAT3(0.55f, 0.0f, 5.0f + i * 6)));
		}
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
	m_modelHandlers[PLAYER]->LoadOBJData("Resources/Models/Player.obj", "Resources/Models/Player.mtl", m_device, m_deviceContext);
	m_modelHandlers[PLAYER]->CreateBuffers(m_device);
	m_modelHandlers[BULLET1] = new ModelHandler();
	m_modelHandlers[BULLET1]->LoadOBJData("Resources/Models/Bullet1.obj", "Resources/Models/Bullet1.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET1]->CreateBuffers(m_device);
	m_modelHandlers[BULLET2] = new ModelHandler();
	m_modelHandlers[BULLET2]->LoadOBJData("Resources/Models/Rocket.obj", "Resources/Models/Rocket.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET2]->CreateBuffers(m_device);
	m_modelHandlers[BULLET3] = new ModelHandler();
	m_modelHandlers[BULLET3]->LoadOBJData("Resources/Models/TronDonut.obj", "Resources/Models/TronDonut.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET3]->CreateBuffers(m_device);
	m_modelHandlers[BULLET4] = new ModelHandler();
	m_modelHandlers[BULLET4]->LoadOBJData("Resources/Models/Bullet4.obj", "Resources/Models/Bullet4.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET4]->CreateBuffers(m_device);
	m_modelHandlers[BULLET5] = new ModelHandler();
	m_modelHandlers[BULLET5]->LoadOBJData("Resources/Models/Note_01.obj", "Resources/Models/Note_01.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET5]->CreateBuffers(m_device);
	m_modelHandlers[BULLET6] = new ModelHandler();
	m_modelHandlers[BULLET6]->LoadOBJData("Resources/Models/EnemyBullet.obj", "Resources/Models/EnemyBullet.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET6]->CreateBuffers(m_device);
	m_modelHandlers[ENEMY1] = new ModelHandler();
	m_modelHandlers[ENEMY1]->LoadOBJData("Resources/Models/Ship_01.obj", "Resources/Models/Ship_01.mtl", m_device, m_deviceContext);
	m_modelHandlers[ENEMY1]->CreateBuffers(m_device);
	m_modelHandlers[ENEMY2] = new ModelHandler;
	m_modelHandlers[ENEMY2]->LoadOBJData("Resources/Models/Ship_02.obj", "Resources/Models/Ship_02.mtl", m_device, m_deviceContext);
	m_modelHandlers[ENEMY2]->CreateBuffers(m_device);
	m_modelHandlers[ENEMY3] = new ModelHandler;
	m_modelHandlers[ENEMY3]->LoadOBJData("Resources/Models/Ship_03.obj", "Resources/Models/Ship_03.mtl", m_device, m_deviceContext);
	m_modelHandlers[ENEMY3]->CreateBuffers(m_device);
	m_modelHandlers[ENEMY4] = new ModelHandler;
	m_modelHandlers[ENEMY4]->LoadOBJData("Resources/Models/Boss_Ship.obj", "Resources/Models/Boss_Ship.mtl", m_device, m_deviceContext);
	m_modelHandlers[ENEMY4]->CreateBuffers(m_device);
	//Temp, create player
	SpawnEntity(PLAYER);
	//Temp, creates partsys
	wstring _texName = L"Resources\\Models\\star.jpg";
	m_rocketPartSys = new FirePart(0.25, 200);
	m_rocketPartSys->CreateBuffer(m_device, m_deviceContext, _texName);

	std::vector<Entity*> _playerVec = { m_player };
	m_playerPartSys = new PlayerPart(0.8, 200, _playerVec);
	m_playerPartSys->CreateBuffer(m_device, m_deviceContext, _texName);

	EnemyHealthColourBuffer();

	//Create Light Buffer
	m_light.InitializBuffer(m_device);
}

void EntityManager::Render()
{
	if (m_bullet2.size() > 0)
	{
		m_rocketPartSys->AddPartSys(m_bullet2, XMFLOAT4(0, 0, -1, 0));
		m_shaderLoad[SHADER_ROCKETPART]->SetShaders(m_deviceContext);
		m_rocketPartSys->SetBuffer(m_deviceContext);
		m_rocketPartSys->Render(m_deviceContext);
	}

	if (m_renderFire == true)
	{
		m_shaderLoad[SHADER_PLAYERPART]->SetShaders(m_deviceContext);
		m_playerPartSys->SetBuffer(m_deviceContext);
		m_playerPartSys->Render(m_deviceContext);
	}

	for (int i = 0; i < m_explosion.size(); i++)
	{
		m_explosion[i]->SetBuffer(m_deviceContext);
		m_explosion[i]->Render(m_deviceContext);
	}

	//Render Player
	if (m_renderPlayer == true)
	{
		if (m_player->GetHealth() > 0)			//Invulnerability-blinking
		{
			m_shaderLoad[SHADER_PLAYER]->SetShaders(m_deviceContext);
			m_renderer->Render(m_modelHandlers[PLAYER], m_player->GetPosition(), m_player->GetRotation(), m_player->GetScale());
		}
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

		//BeatDet test
		float _currentPos = m_soundManager->GetCurrentMusicTimePCM() / 1024.f;
		if (m_beat[(int)_currentPos] > 0.0f && m_timeSinceLastBeat > 100)		//Small time buffer to prevent it from going off 50 times per beat 
		{
			//BEAT WAS DETECTED
			if (m_beatNumber > m_offset) {
				BeatWasDetected();
				m_light.beatBoost(true, time, m_timeSinceLastBeat/1000, 0);
			for (int i = 1; i < 7; i++)			//bullets start at modelhandlers[1]
				m_modelHandlers[i]->beatBoost(true, time, m_timeSinceLastBeat/1000, 0);
				m_prevBeatTime = m_timeSinceLastBeat;
				m_timeSinceLastBeat = 0;
				m_beatNumber += 1;
				m_statsManager->AddBeat();
			}
			else {
				m_prevBeatTime = m_timeSinceLastBeat;
				m_timeSinceLastBeat = 0;
				m_beatNumber++;
				m_statsManager->AddBeat();
			}
		SpawnEnemy();
		}
		else {
			m_timeSinceLastBeat += time * 1000;
			m_light.beatBoost(false, time, m_timeSinceLastBeat/1000, 0);
		for (int i = 1; i < 7; i++)				//bullets start at modelhandlers[1]
			m_modelHandlers[i]->beatBoost(false, time, m_timeSinceLastBeat/1000, 0);
		}


	//Do collision checks
	int _addScore = 0;
	vector<Entity*>* _bullets[6] = { &m_bullet1, &m_bullet2, &m_bullet3, &m_bullet4, &m_bullet5 };
	vector<Entity*>* _enemies[4] = { &m_enemy1, &m_enemy2, &m_enemy3, &m_enemy4 };

	for (int i = 0; i < 5; i++)		//For each bullettype
	{
		for (int j = 0; j < 4; j++) //For each enemytype
		{
			_addScore += m_collision.CheckCollisionEntity(_bullets[i], _enemies[j], HandlerIndex(i+1), HandlerIndex(j+7), &m_explosion, m_device, m_deviceContext, time, &m_bulletSphere); //+1 to get to bullets, +7 to get to enemies
		}
	}

	for (int j = 0; j < 4; j++) //Explosin radius For each enemytype
	{
		_addScore += m_collision.CheckCollisionEntity(&m_bulletSphere, _enemies[j], HandlerIndex(SPHERE), HandlerIndex(j + 7), &m_explosion, m_device, m_deviceContext, time, &m_bulletSphere); //+7 to get to enemies
	}

	m_statsManager->AddScore(_addScore*(m_statsManager->GetCombo()+1));

	//Check Player against Enemy Bullet
	if (!m_player->GetInvulnerable())			//Only check if the player is alive and well
	{
		std::vector<Entity*> _playerVec = { m_player };
		m_collision.CheckCollisionEntity(&m_bullet6, &_playerVec, BULLET6, PLAYER, &m_explosion, m_device, m_deviceContext, time, &m_bulletSphere);
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

	for (auto i = 0; i < m_enemy2.size(); i++)
		m_enemy2[i]->Update(time);

	for (auto i = 0; i < m_enemy3.size(); i++)
		m_enemy3[i]->Update(time);

	for (auto i = 0; i < m_enemy4.size(); i++)
		m_enemy4[i]->Update(time);


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
	m_bullet5 = CheckIfAlive(m_bullet5);
	for (int i = 0; i < m_bullet5.size(); i++)
		m_bullet5[i]->Update(time);
	//Update every entity of Bullet6
	for (int i = 0; i < m_bullet6.size(); i++)
		m_bullet6[i]->Update(time);

	if (!m_player->GetDelete())
		m_player->Update(time);
	else
		m_player->Destroyed(time);
	
	for (int i = 0; i < m_explosion.size(); i++)
	{
		m_explosion[i]->Update(m_deviceContext, time, 5);
		float* _lifeTime = m_explosion[i]->GetTimeToLive();
		if (_lifeTime[0] <= 0)
		{
			vector<ExplosionPart*> _tempVec = m_explosion;

			delete _tempVec[i];
			_tempVec.erase(_tempVec.begin() + i);
			m_explosion = _tempVec;
			i--;
		}
	}

	for (int i = 0; i < m_bulletSphere.size(); i++)
	{
		m_bulletSphere[i]->Update(time);
		if (m_bulletSphere[i]->GetDelete() == true)
		{
			vector<Entity*> _tempVec = m_bulletSphere;

			delete _tempVec[i];
			_tempVec.erase(_tempVec.begin() + i);
			m_bulletSphere = _tempVec;
			i--;
		}
	}

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
	m_bullet6 = CheckOutOfBounds(m_bullet6);

	m_light.addLights(m_bullet1);
	m_light.addLights(m_bullet3);
	m_light.addLights(m_bullet4);
	m_light.addLights(m_bullet6);

	//sets the lightbuffer
	m_light.SetConstbuffer(m_deviceContext);

	//Update Particle System
	std::vector<Entity*> _playerVec = { m_player };

	m_rocketPartSys->Update(m_deviceContext, time, 35);
	
	if (m_playerPartSys != NULL)
	{
		if (m_input->CheckKeyBoardInput() == INPUT_MOVE_DOWN)
		{
			m_playerPartSys->Update(m_deviceContext, time, 75, _playerVec);
		}
		else if (m_input->CheckKeyBoardInput() == INPUT_MOVE_UP)
		{
			m_playerPartSys->Update(m_deviceContext, time, 35, _playerVec);
		}
		else
		{
			m_playerPartSys->Update(m_deviceContext, time, 25, _playerVec);
		}
	}
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

			else if (std::string(_key) == "BeatPerShot1")
				m_beatPerShot1 = atoi(_value);
			else if (std::string(_key) == "BeatPerShot2")
				m_beatPerShot2 = atoi(_value);
			else if (std::string(_key) == "BeatPerShot3")
				m_beatPerShot3 = atoi(_value);
			else if (std::string(_key) == "BeatPerShot4")
				m_beatPerShot4 = atoi(_value);

			else if (std::string(_key).find("EnemySpawnRate") != string::npos) //Mov compilations
			{
				pair<int, int> _spawnDiv;
				_ss = istringstream(_value);

				string _startBeat;
				getline(_ss, _startBeat, '|');		// Get at what beat enemies will spawn with this compilation
				_spawnDiv.first = stoi(_startBeat);

				string _rate;
				getline(_ss, _rate, ',');
				_spawnDiv.second = stoi(_rate);

				//Add to the relevant final vector once done loading
				if (std::string(_key) == "EnemySpawnRate1")
					m_enemySpawnRate[0].push_back(_spawnDiv);
				if (std::string(_key) == "EnemySpawnRate2")
					m_enemySpawnRate[1].push_back(_spawnDiv);
				if (std::string(_key) == "EnemySpawnRate3")
					m_enemySpawnRate[2].push_back(_spawnDiv);
				if (std::string(_key) == "EnemySpawnRate4")
					m_enemySpawnRate[3].push_back(_spawnDiv);
			}

			else if (std::string(_key).find("EnemySize") != string::npos)
			{
				XMFLOAT3* _sizePTR;
				if (std::string(_key) == "EnemySize1")
					_sizePTR = &m_enemySize1;
			else if (std::string(_key) == "EnemySize2")
					_sizePTR = &m_enemySize2;
			else if (std::string(_key) == "EnemySize3")
					_sizePTR = &m_enemySize3;
			else if (std::string(_key) == "EnemySize4")
					_sizePTR = &m_enemySize4;

				_ss = istringstream(_value);
				string _floatVec;				//For keeping xmfloat3 string
				while (getline(_ss, _floatVec, '|'))
				{
					istringstream _ssfloatVec = istringstream(_floatVec);
					string _coord;
					getline(_ssfloatVec, _coord, ',');		//Get x coord
					_sizePTR->x = stof(_coord);

					getline(_ssfloatVec, _coord, ',');		//Get y coord
					_sizePTR->y = stof(_coord);

					getline(_ssfloatVec, _coord, ',');		//Get z coord
					_sizePTR->z = stof(_coord);
				}
			}

			else if (std::string(_key) == "EnemyHealth1")
				m_enemyHealth1 = atoi(_value);
			else if (std::string(_key) == "EnemyHealth2")
				m_enemyHealth2 = atoi(_value);
			else if (std::string(_key) == "EnemyHealth3")
				m_enemyHealth3 = atoi(_value);
			else if (std::string(_key) == "EnemyHealth4")
				m_enemyHealth4 = atoi(_value);

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
	m_beat = m_beatDetector->GetBeat();
	m_EnemyPatterns.LoadPatterns(filename);

	m_renderFire = true;
	m_renderPlayer = true;
}

void EntityManager::Reset()
{
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

	for (int i = 0; i < 4; i++)
		_enemySpawnBeat[i] = 0;

	m_bullet1.clear();
	m_bullet2.clear();
	m_bullet3.clear();
	m_bullet4.clear();
	m_bullet5.clear();
	m_bullet6.clear();
	m_enemy1.clear();
	m_enemy2.clear();
	m_enemy3.clear();
	m_enemy4.clear();
	m_enemy1MovPatterns.clear();
	m_enemy2MovPatterns.clear();
	m_enemy3MovPatterns.clear();
	m_enemy4MovPatterns.clear();
	for (int i = 0; i < 4; i++) m_enemySpawnRate[i].clear();
	m_explosion.clear();
	m_beatNumber = 0;
	m_statsManager->ResetCombo();
	m_statsManager->ResetScore();
	m_statsManager->SetLives();
	m_currentBPM, m_beatNumber = 0;
	m_timeSinceLastBeat = 0.0f;
	m_offset = 0;
	m_beatNumber = 0;
	m_player->SetDelete(true);
	m_renderFire = false;
	m_renderPlayer = false;
}

void EntityManager::BeatWasDetected()
{
	//Spawn correct bullet (which plays the sound as well) Only if player is alive
	if (!m_player->GetDelete())
	{
	BulletType _bullet = m_input->CheckBullet();
	switch (_bullet)
	{
		case INPUT_DEFAULT_BULLET:
			SpawnEntity(BULLET1); //Default bullet
			m_laserOffset = 0;
			m_rocketOffset = 0;
			break;
		case INPUT_BULLET2:
			if (m_rocketOffset != 2)
			{
				SpawnEntity(BULLET2);
				m_rocketOffset++;
			}
			else
				m_rocketOffset = 0;
			m_laserOffset = 0;
			break;
		case INPUT_BULLET3:
			SpawnEntity(BULLET3);
			m_laserOffset = 0;
			m_rocketOffset = 0;
			break;
		case INPUT_BULLET4:
			SpawnEntity(BULLET4);
			m_laserOffset = 0;
			m_rocketOffset = 0;
			break;
		case INPUT_BULLET5:
			if (m_laserOffset == 0)
			{
				SpawnEntity(BULLET5);
				m_laserOffset = 1;
			}
			else
				m_laserOffset = 0;
			m_rocketOffset = 0;
			break;
		default:
			break;
	}
	} 
	EnemyFire();
	} 

void EntityManager::SpawnEnemy() 
{
	for (int j = 0; j < 4; j++)							//For each enemy's spawn rate vectors
	{ 
		for (int i = m_enemySpawnRate[j].size() - 1; i >= 0; i--)	//For each spawn rate
		{
			if (m_enemySpawnRate[j][i].first <= m_statsManager->GetBeat())	//Get correct frequency-span
			{
				if (_enemySpawnBeat[j] >= m_enemySpawnRate[j][i].second && m_enemySpawnRate[j][i].second != 0)
				{
					switch (j) {
					case 0: SpawnEntity(ENEMY1); break;
					case 1: SpawnEntity(ENEMY2); break;
					case 2: SpawnEntity(ENEMY3); break;
					case 3: SpawnEntity(ENEMY4); break;
					}
					_enemySpawnBeat[j] = 1;
				}
				else
					_enemySpawnBeat[j]++;

				i = 0;		//Breaks the for loop if spawn rate span was found
			}
		}
	}

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

void EntityManager::EnemyHealthColourBuffer()
{
	D3D11_BUFFER_DESC _HealthColourDesc;

	ZeroMemory(&_HealthColourDesc, sizeof(D3D11_BUFFER_DESC));

	_HealthColourDesc.Usage = D3D11_USAGE_DYNAMIC;
	_HealthColourDesc.ByteWidth = sizeof(XMFLOAT4) * 100;
	_HealthColourDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_HealthColourDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_HealthColourDesc.MiscFlags = 0;

	//skapar constant buffer
	m_device->CreateBuffer(&_HealthColourDesc, NULL, &m_enemyHealthColourBuffer);
}
	
void EntityManager::RenderEnemies()
{
	vector<XMFLOAT3> _instancePosition;
	vector<XMMATRIX> _instanceRotation;
	vector<XMFLOAT3> _instanceScale;
	XMFLOAT4 _healthColour[100];

	_instancePosition.clear();
	_instanceScale.clear();
	_instanceRotation.clear();

	vector<Entity*> _enemies[4] = { m_enemy1, m_enemy2, m_enemy3, m_enemy4 };
	int _enemyHealth[4] = { m_enemyHealth1, m_enemyHealth2, m_enemyHealth3, m_enemyHealth4 };

	for (int j = 0; j < 4; j++)
		{
		if (_enemies[j].size() > 0)
	{
			for (auto i = 0; i < _enemies[j].size(); i++)
		{
				_instancePosition.push_back(_enemies[j][i]->GetPosition());
				_instanceScale.push_back(_enemies[j][i]->GetScale());
				_instanceRotation.push_back(_enemies[j][i]->GetRotation());
				_healthColour[i] = XMFLOAT4(1.f - (float(_enemies[j][i]->GetHealth()) / float(_enemyHealth[j])), (float(_enemies[j][i]->GetHealth()) / float(_enemyHealth[j])), (float(_enemies[j][i]->GetHealth()) / float(_enemyHealth[j])), 1);
		}
		D3D11_MAPPED_SUBRESOURCE _mappedResource;

		HRESULT hr = m_deviceContext->Map(m_enemyHealthColourBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_mappedResource);

		memcpy(_mappedResource.pData, &_healthColour, sizeof(XMFLOAT4) * 100);

		m_deviceContext->Unmap(m_enemyHealthColourBuffer, 0);
		m_deviceContext->VSSetConstantBuffers(2, 1, &m_enemyHealthColourBuffer);
			m_modelHandlers[7+j]->SetBuffers(m_deviceContext);	//+7 to get to enemies
			m_renderer->RenderInstanced(m_modelHandlers[7+j], _instancePosition, _instanceRotation, _enemies[j].size(), _instanceScale);
	}

	_instancePosition.clear();
	_instanceScale.clear();
	_instanceRotation.clear();
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

	vector<Entity*> _bullets[6] = { m_bullet1, m_bullet2, m_bullet3, m_bullet4, m_bullet5, m_bullet6 };

	for (int j = 0; j < 6; j++)
	{
		if (_bullets[j].size() > 0)
	{
			if ((j == 4 && !m_player->GetDelete()) || j != 4) {	//On lasers, only render if player didn't just die
			
				for (int i = 0; i < _bullets[j].size(); i++) {
					_instancePosition.push_back(_bullets[j][i]->GetPosition());
					_instanceScale.push_back(_bullets[j][i]->GetScale());
					_instanceRotation.push_back(_bullets[j][i]->GetRotation());
		}
				m_renderer->RenderInstanced(m_modelHandlers[j + 1], _instancePosition, _instanceRotation, _bullets[j].size(), _instanceScale);
		_instancePosition.clear();
		_instanceScale.clear();
		_instanceRotation.clear();
	}
		}
	}
}

vector<Entity*> EntityManager::CheckIfAlive(const std::vector<Entity*> &bullet)
{
	//If Alive check, remove immediately
	bool removed = false;
	vector<Entity*> _tempVec = bullet;			//Can't use the member variable for some reason
	for (int i = 0; i < _tempVec.size(); i++) 
	{
		bool _temp = _tempVec[i]->GetDelete();
		if (_temp == true) 
		{
			delete _tempVec[i];
			_tempVec.erase(_tempVec.begin() + i);
			i--;
		}
		else
		{
			_tempVec[i]->SetPosition(XMFLOAT3(m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z));
		}
	}
	return _tempVec;
}

void EntityManager::EnemyFire()
{
	std::vector<Entity*> _enemyVec[4] = { m_enemy1, m_enemy2, m_enemy3, m_enemy4 };
	int _beatPerShot[4] = { m_beatPerShot1, m_beatPerShot2, m_beatPerShot3, m_beatPerShot4 };

	for (int j = 0; j < 4; j++)
		{
		for (auto i = 0; i < _enemyVec[j].size(); i++)
	{
			if (_enemyVec[j][i]->GetFireTime() > _beatPerShot[j])
		{
				_enemyVec[j][i]->SetPatternNr(m_EnemyPatterns.AddShot(&m_bullet6, m_soundManager, MAPWIDTH, MAPLENGTH, _enemyVec[j][i]->GetPosition(), XMFLOAT3(0.4, 0.4, 0.4), 1, m_modelHandlers[BULLET6]->GetDeffuse(), j, _enemyVec[j][i]->GetPatternNr()));
				_enemyVec[j][i]->SetFireTime(0);
	}

			_enemyVec[j][i]->SetFireTime(_enemyVec[j][i]->GetFireTime() + 1.0f);
		}
	}
}

void EntityManager::CheckCombo()
{
	if (m_beatNumber % 2 == 0)
		m_statsManager->SetPercentage(XM_PI * (m_timeSinceLastBeat / m_prevBeatTime));		//Sets a value that the UI combometer uses to determine position
	else 
		m_statsManager->SetPercentage(XM_PI * (m_timeSinceLastBeat / m_prevBeatTime) + XM_PI);		//Sets a value that the UI combometer uses to determine position

	// Check key presses near the beat, for combo
	static bool _registeredCombo = true;
	static BulletType _currentBulletType;
	static bool _spacebar = false;
	if (m_beatNumber > m_offset && m_player->GetDelete() == false) {						//Only check for combos after the beats have actually started
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

int EntityManager::GetPlayerHealth()
{
	return m_player->GetHealth();
}

int EntityManager::GetOffset()
{
	return m_offset;
}