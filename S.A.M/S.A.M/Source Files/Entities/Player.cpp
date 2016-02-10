#include "Entities/Player.h"

Player::Player()
{

}

Player::Player(SoundManager* SoundManager, int MapWidth, int MapLength,XMFLOAT3 Position, XMFLOAT3 Scale, int Health, Input* input) : Entity(SoundManager, MapWidth, MapLength, Position, Scale, Health)
{
	m_input = input;
	//Loading death sounds FIX LATER :)
	//m_soundManager->LoadSound("DickbuttSound.mp3", "PlayerDeathSound", "PlayerSound", LOAD_MEMORY);

	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);
}

Player::~Player()
{
	
}

void Player::Update(double time)
{
	InputType _currentInput[4];
	ZeroMemory(&_currentInput, sizeof(_currentInput));
	m_input->CheckKeyBoardInput(_currentInput);

	//Check Input and apply Input to positions
	m_rotAngle = 0.f;
	if (_currentInput[0] == INPUT_MOVE_LEFT)
	{
		m_position.x -= MOVEMENTSPEEDX*(time*1500);
		m_rotAngle = XM_PI/8;
	}

	if (_currentInput[1] == INPUT_MOVE_RIGHT)
	{
		m_position.x += MOVEMENTSPEEDX*(time * 1500);
		m_rotAngle = -XM_PI / 8;
	}

	if (_currentInput[2] == INPUT_MOVE_UP)
		m_position.z += MOVEMENTSPEEDZ*(time * 1500);

	if (_currentInput[3] == INPUT_MOVE_DOWN)
		m_position.z -= MOVEMENTSPEEDZ*(time * 1500);

	//Check position if out of bounds.
	if (m_position.z > (float)m_mapLength)
		m_position.z = (float)m_mapLength;

	if (m_position.z < 1)
		m_position.z = 1;

	if (m_position.x >(float)m_mapWidth)
		m_position.x = (float)m_mapWidth;
				   
	if (m_position.x < 1)
		m_position.x = 1;


	m_entityBox.Center = m_position;


	//Add time to alivetimer (used for invulnerability after death)
	m_aliveTimer += time;
	if (m_aliveTimer > 3 && m_invulnerable == true) {
		m_destructionTimer = 0;
		m_invulnerable = false;
	}
}

void Player::Destroyed(double time)
{
	if (m_destructionTimer == 0)
	{
		//Play sound when destroyed..
		//m_soundManager->PlayOneShotSound("PlayerDeathSound", 0.5f);

		m_invulnerable = true;
		m_aliveTimer = 0;
		SetPosition(XMFLOAT3(m_mapWidth/2, 0, -5)); //Move beneath the map, as soon as ship blows up
	}

	m_destructionTimer += time;
	m_position.z += MOVEMENTSPEEDZ * (time * 200);
	if (m_position.z > 8) {
		m_delete = false;
		m_health = 1;
	}
}
