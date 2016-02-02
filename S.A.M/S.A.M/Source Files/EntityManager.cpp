#include "EntityManager.h"
#define MAPWIDTH 100;	//Change this
#define MAPLENGTH 100;	//Change this

void EntityManager::SpawnEntity(HandlerIndex type)
{
	/*
	switch (type) {
	case(PLAYER) :
		m_player = new Player;
		m_player->Initialize(m_soundManager, MAPWIDTH, MAPLENGTH, m_input);
		break;
	case(ENEMY1) :
		Enemy1* tempEntity = new Enemy1;
		tempEntity->Initialize();
		m_enemy1.push_back(tempEntity);
		break;
	case(ENEMY2) :
		Enemy2* tempEntity = new Enemy2;
		tempEntity->Initialize();
		m_enemy2.push_back(tempEntity);
		break;
	case(ENEMY3) :
		Enemy3* tempEntity = new Enemy3;
		tempEntity->Initialize();
		m_enemy3.push_back(tempEntity);
		break;
	case(ENEMY4) :
		Enemy4* tempEntity = new Enemy4;
		tempEntity->Initialize();
		m_enemy4.push_back(tempEntity);
		break;
	case(BULLET1) :
		Bullet1* tempEntity = new Bullet1;
		tempEntity->Initialize();
		m_bullet1.push_back(tempEntity);
		//Set infront of player
		//Spawn correct sound
		break;
	case(BULLET2) :
		Bullet2* tempEntity = new Bullet2;
		tempEntity->Initialize();
		m_bullet2.push_back(tempEntity);
		//Set infront of player
		//Spawn correct sound
		break;
	case(BULLET3) :
		Bullet3* tempEntity = new Bullet3;
		tempEntity->Initialize();
		m_bullet3.push_back(tempEntity);
		//Set infront of player
		//Spawn correct sound
		break;
	case(BULLET4) :
		Bullet4* tempEntity = new Bullet4;
		tempEntity->Initialize();
		m_bullet4.push_back(tempEntity);
		break;
	case(BULLET5) :
		Bullet5* tempEntity = new Bullet5;
		tempEntity->Initialize();
		m_bullet5.push_back(tempEntity);
		//Set infront of player
		//Spawn correct sound
		break;
	case(BULLET6) :
		Bullet6* tempEntity = new Bullet6;
		tempEntity->Initialize();
		m_bullet6.push_back(tempEntity);
		//Set infront of ENEMY
		//Don't spawn sound for enemy bullets?
	}

	*/
}

void EntityManager::Initialize(SoundManager* soundManager, Input* input, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	//Set the soundManager pointer which will be used in every entity
	m_soundManager = soundManager;

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
	m_modelHandlers[BULLET2] = new ModelHandler;
	m_modelHandlers[BULLET3] = new ModelHandler;
	m_modelHandlers[BULLET4] = new ModelHandler;
	m_modelHandlers[BULLET5] = new ModelHandler;
	m_modelHandlers[BULLET6] = new ModelHandler;

	//Temp, create player
	SpawnEntity(PLAYER);
	//m_player->SetPosition(XMFLOAT3(1.0f, 0.0f, 1.0f));

	ChangeSongData(128);
}

void EntityManager::Render()
{
	
	//Render Player
	m_modelHandlers[PLAYER]->SetBuffers(m_deviceContext);
	m_modelHandlers[PLAYER]->SetShaders(m_deviceContext);
	XMVECTOR _rotzAxis{ 0,0,1,0 };
	XMMATRIX m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
	m_renderer->Render(m_modelHandlers[PLAYER], XMFLOAT3(0.0f, 0.0f, 0.0f), &m_rotation);

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
	m_timeSinceLastBeat += time * 1000;
	if (m_timeSinceLastBeat >= 60000 / m_currentBPM) {
		m_timeSinceLastBeat -= 60000 / m_currentBPM;
		m_soundManager->PlayOneShotSound("DefaultBullet", 0.5f);
	}


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

void EntityManager::ChangeSongData(int bpm)
{
	m_currentBPM = bpm;
}
