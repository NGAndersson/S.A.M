#include "Entities/Player.h"

Player::Player()
{

}

Player::Player(SoundManager* SoundManager, int MapWidth, int MapLength,XMFLOAT3 Position, XMFLOAT3 Scale, Input* input) : Entity(SoundManager, MapWidth, MapLength, Position, Scale)
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
	if (m_position.z > (float)m_mapLength/2)
		m_position.z = (float)m_mapLength / 2;

	if (m_position.z < (float)-m_mapLength / 2)
		m_position.z = (float)-m_mapLength / 2;

	if (m_position.x >(float)m_mapWidth / 2)
		m_position.x = (float)m_mapWidth / 2;
				   
	if (m_position.x < (float)-m_mapWidth / 2)
		m_position.x = (float)-m_mapWidth / 2;

}

void Player::Destroyed()
{
	//Play sound when destroyed..
	m_soundManager->PlayOneShotSound("PlayerDeathSound", 0.5f);
}
