#include "EntityManager.h"
#define MAPWIDTH 100
#define MAPLENGTH 100

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
	delete[] m_modelHandlers;
	delete m_player;
}

void EntityManager::SpawnEntity(HandlerIndex type)
{

	switch (type) {
	case(PLAYER) :
		m_player = new Player(m_soundManager, MAPWIDTH, MAPLENGTH, XMFLOAT3(1.0f, 0.0f, 1.0f), m_input);
		break;
		//case(ENEMY1) :
		//	Enemy1* tempEntity = new Enemy1;
		//	tempEntity->Initialize();
		//	m_enemy1.push_back(tempEntity);
		//	break;
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
		Bullet_p1* tempEntity = new Bullet_p1(m_soundManager, MAPWIDTH, MAPLENGTH, m_player->GetPosition());
		m_bullet1.push_back(tempEntity);
		m_soundManager->PlayOneShotSound("DefaultBullet", 0.05f);
		break;
		//case(BULLET2) :
		//	Bullet2* tempEntity = new Bullet2;
		//	tempEntity->Initialize();
		//	m_bullet2.push_back(tempEntity);
		//	//Set infront of player
		//	//Spawn correct sound
		//	break;
		//case(BULLET3) :
		//	Bullet3* tempEntity = new Bullet3;
		//	tempEntity->Initialize();
		//	m_bullet3.push_back(tempEntity);
		//	//Set infront of player
		//	//Spawn correct sound
		//	break;
		//case(BULLET4) :
		//	Bullet4* tempEntity = new Bullet4;
		//	tempEntity->Initialize();
		//	m_bullet4.push_back(tempEntity);
		//	break;
		//case(BULLET5) :
		//	Bullet5* tempEntity = new Bullet5;
		//	tempEntity->Initialize();
		//	m_bullet5.push_back(tempEntity);
		//	//Set infront of player
		//	//Spawn correct sound
		//	break;
		//case(BULLET6) :
		//	Bullet6* tempEntity = new Bullet6;
		//	tempEntity->Initialize();
		//	m_bullet6.push_back(tempEntity);
		//	//Set infront of ENEMY
		//Don't spawn sound for enemy bullets?
	}


}

void EntityManager::Initialize(SoundManager* soundManager, Input* input, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{

	//Set the soundManager pointer which will be used in every entity
	m_soundManager = soundManager;
	m_soundManager->LoadMusic("Resources/Ignition.mp3");
	m_soundManager->PlayMusic(0.5f);

	m_beatDetector = new BeatDetector(m_soundManager);
	m_beatDetector->AudioProcess();

	//Load the sounds for every entity
	m_soundManager->LoadSound("Resources/DefaultBullet1.wav", "DefaultBullet1", "DefaultBullet", LOAD_MEMORY);
	//m_soundManager->LoadSound("Resources/DefaultBullet2.wav", "DefaultBullet2", "DefaultBullet", LOAD_MEMORY);

	//Set the input class which will be passed down to Player
	m_input = input;

	//Set device and context
	m_device = device;
	m_deviceContext = deviceContext;

	//Set the renderer
	m_renderer = new Renderer(m_deviceContext, m_device);

	//Create model handlers for each entity type
	m_modelHandlers[PLAYER] = new ModelHandler;
	m_modelHandlers[PLAYER]->LoadOBJData("Resources/TestCube.obj", "Resources/TestCube.mtl", m_device, m_deviceContext);
	m_modelHandlers[PLAYER]->CreateBuffers(m_device);
	m_modelHandlers[PLAYER]->CreateShaders(m_device, "Shaders\\PlayerVS.hlsl", "Shaders\\PlayerGS.hlsl", "Shaders\\PlayerPS.hlsl");
	m_modelHandlers[ENEMY1] = new ModelHandler;
	m_modelHandlers[ENEMY2] = new ModelHandler;
	m_modelHandlers[ENEMY3] = new ModelHandler;
	m_modelHandlers[ENEMY4] = new ModelHandler;
	m_modelHandlers[BULLET1] = new ModelHandler;
	m_modelHandlers[BULLET1]->LoadOBJData("Resources/TestCube.obj", "Resources/TestCube.mtl", m_device, m_deviceContext);
	m_modelHandlers[BULLET1]->CreateBuffers(m_device);
	m_modelHandlers[BULLET1]->CreateShaders(m_device, "Shaders\\BulletVS.hlsl", "Shaders\\BulletGS.hlsl", "Shaders\\BulletPS.hlsl");
	m_modelHandlers[BULLET2] = new ModelHandler;
	m_modelHandlers[BULLET3] = new ModelHandler;
	m_modelHandlers[BULLET4] = new ModelHandler;
	m_modelHandlers[BULLET5] = new ModelHandler;
	m_modelHandlers[BULLET6] = new ModelHandler;
	//Temp, create player
	SpawnEntity(PLAYER);

	//Temp, creates partsys
	wstring _texName = L"Resources\\star3.jpg";
	m_partSys.CreateBuffer(m_device, m_deviceContext, _texName);
	m_partSys.CreateShaders(m_device);

	ChangeSongData(m_beatDetector->GetTempo());
	m_doBeatDet = true;
}

void EntityManager::Render()
{
	m_partSys.PartRend(m_deviceContext);

	//Render Player
	m_modelHandlers[PLAYER]->SetBuffers(m_deviceContext);
	m_modelHandlers[PLAYER]->SetShaders(m_deviceContext);
	m_renderer->Render(m_modelHandlers[PLAYER], m_player->GetPosition(), m_player->GetRotation());


	XMFLOAT3 bulletpos[4];
	bulletpos[0] = XMFLOAT3(4, 0, 5);
	bulletpos[1] = XMFLOAT3(6, 0, 9);
	bulletpos[2] = XMFLOAT3(-9, 0, 78);
	bulletpos[3] = XMFLOAT3(56, 0, 0);

	m_modelHandlers[BULLET1]->SetBuffers(m_deviceContext);
	m_modelHandlers[BULLET1]->SetShaders(m_deviceContext);
	m_renderer->RenderInstanced(m_modelHandlers[BULLET1], bulletpos, m_player->GetRotation(), 4);

	//m_renderer->Render(m_modelHandlers[PLAYER], m_player->GetPosition(), &m_player->GetRotation());
	/*
	//Render Enemies
	for (int i = 0; i < m_enemy1.size(); i++)
	{
	m_modelHandlers[ENEMY1]->SetBuffers(m_deviceContext);
	m_modelHandlers[ENEMY1]->SetShaders(m_deviceContext);
	m_renderer->Render(m_modelHandlers[ENEMY1], m_enemy1[i]->GetPosition(), m_enemy1[i]->GetRotation());
	}
	for (int i = 0; i < m_enemy2.size(); i++)
	{
	m_modelHandlers[ENEMY2]->SetBuffers(m_deviceContext);
	m_modelHandlers[ENEMY2]->SetShaders(m_deviceContext);
	m_renderer->Render(m_modelHandlers[ENEMY2], m_enemy2[i]->GetPosition(), m_enemy2[i]->GetRotation());
	}
	for (int i = 0; i < m_enemy3.size(); i++)
	{
	m_modelHandlers[ENEMY3]->SetBuffers(m_deviceContext);
	m_modelHandlers[ENEMY3]->SetShaders(m_deviceContext);
	m_renderer->Render(m_modelHandlers[ENEMY3], m_enemy3[i]->GetPosition(), m_enemy3[i]->GetRotation());
	}
	for (int i = 0; i < m_enemy4.size(); i++)
	{
	m_modelHandlers[ENEMY4]->SetBuffers(m_deviceContext);
	m_modelHandlers[ENEMY4]->SetShaders(m_deviceContext);
	m_renderer->Render(m_modelHandlers[ENEMY4], m_enemy4[i]->GetPosition(), m_enemy4[i]->GetRotation());
	}

	//Render Bullets
	for (int i = 0; i < m_bullet1.size(); i++)
	{
	m_modelHandlers[BULLET1]->SetBuffers(m_deviceContext);
	m_modelHandlers[BULLET1]->SetShaders(m_deviceContext);
	m_renderer->Render(m_modelHandlers[BULLET1], m_bullet1[i]->GetPosition(), m_bullet1[i]->GetRotation());
	}
	for (int i = 0; i < m_bullet2.size(); i++)
	{
	m_modelHandlers[BULLET2]->SetBuffers(m_deviceContext);
	m_modelHandlers[BULLET2]->SetShaders(m_deviceContext);
	m_renderer->Render(m_modelHandlers[BULLET2], m_bullet2[i]->GetPosition(), m_bullet2[i]->GetRotation());
	}
	for (int i = 0; i < m_bullet3.size(); i++)
	{
	m_modelHandlers[BULLET3]->SetBuffers(m_deviceContext);
	m_modelHandlers[BULLET3]->SetShaders(m_deviceContext);
	m_renderer->Render(m_modelHandlers[BULLET3], m_bullet3[i]->GetPosition(), m_bullet3[i]->GetRotation());
	}
	for (int i = 0; i < m_bullet4.size(); i++)
	{
	m_modelHandlers[BULLET4]->SetBuffers(m_deviceContext);
	m_modelHandlers[BULLET4]->SetShaders(m_deviceContext);
	m_renderer->Render(m_modelHandlers[BULLET4], m_bullet4[i]->GetPosition(), m_bullet4[i]->GetRotation());
	}
	for (int i = 0; i < m_bullet5.size(); i++)
	{
	m_modelHandlers[BULLET5]->SetBuffers(m_deviceContext);
	m_modelHandlers[BULLET5]->SetShaders(m_deviceContext);
	m_renderer->Render(m_modelHandlers[BULLET5], m_bullet4[i]->GetPosition(), m_bullet5[i]->GetRotation());
	}
	for (int i = 0; i < m_bullet6.size(); i++)
	{
	m_modelHandlers[BULLET6]->SetBuffers(m_deviceContext);
	m_modelHandlers[BULLET6]->SetShaders(m_deviceContext);
	m_renderer->Render(m_modelHandlers[BULLET6], m_bullet4[i]->GetPosition(), m_bullet6[i]->GetRotation());
	}
	*/
}

void EntityManager::Update(double time)
{
	//Regular BPM test
	if (m_doBeatDet == false) {
		m_timeSinceLastBeat += time * 1000;
		if (m_timeSinceLastBeat >= 60000 / m_currentBPM) {
			m_timeSinceLastBeat -= 60000 / m_currentBPM;

			//BEAT WAS DETECTED
			BeatWasDetected();
		}
	}
	else {
		//BeatDet test
		float* _beat = m_beatDetector->GetBeat();

		float _currentPos = m_soundManager->GetCurrentMusicTimePCM() / 1024.f;

		if (_beat[(int)_currentPos] > 0) {

			//BEAT WAS DETECTED
			BeatWasDetected();

		}
	}
	//Do collision checks


	//Update every entity
	for (int i = 0; i < m_bullet1.size(); i++)
		m_bullet1[i]->Update(time);
	m_player->Update(time);


	//Out of bounds check, remove immediately
	for (int i = m_bullet1.size() - 1; i >= 0; i--) {
		XMFLOAT3 _tempPos = m_bullet1[i]->GetPosition();
		if (_tempPos.x > 100 || _tempPos.x < 0 || _tempPos.z > 100 || _tempPos.z < 0) {
			delete m_bullet1[i];
			m_bullet1.erase(m_bullet1.begin() + i);
		}
	}

	//Update Particle System
	m_partSys.updatePart(m_deviceContext, time, 40);
}

void EntityManager::ChangeSongData(int bpm)
{
	m_currentBPM = bpm;
}

void EntityManager::BeatWasDetected()
{
	//Spawn correct bullet (which plays the sound as well)
	BulletType _bullet = m_input->CheckBullet();

	switch (_bullet)
	{
	case INPUT_DEFAULT_BULLET:
		SpawnEntity(BULLET1);
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
