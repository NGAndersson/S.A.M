#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::Update(double time)
{
	InputType _currentInput;
	_currentInput = m_input->CheckKeyBoardInput();
	float _rotAngle;
	bool _tiltL,_tiltR = false;
	//Check Input and apply Input to positions
	if (_currentInput & INPUT_MOVE_LEFT)
	{
		m_position.x -= MOVEMENTSPEED;
		_rotAngle += -0.1 * time;
		_tiltL = true;
	}
	if (_currentInput & INPUT_MOVE_RIGHT)
	{
		m_position.x += MOVEMENTSPEED;
		_rotAngle += 0.1 * time;
		_tiltR = true;
	}

	if (_currentInput & INPUT_MOVE_DOWN)
		m_position.z -= MOVEMENTSPEED;

	if (_currentInput & INPUT_MOVE_UP)
		m_position.z += MOVEMENTSPEED;

	//Check position if out of bounds.
	if (m_position.z > m_mapLenght/2)
		m_position.z = m_mapLenght / 2;

	if (m_position.z < -m_mapLenght / 2)
		m_position.z = -m_mapLenght / 2;

	if (m_position.x > m_mapWidth / 2)
		m_position.x = m_mapWidth / 2;
				   
	if (m_position.x < -m_mapWidth / 2)
		m_position.x = -m_mapWidth / 2;

	//Checking if rotation should return to original value...
	if (!_tiltL && _rotAngle > 0.0f)
		_rotAngle += time * 0.1;

	if (!_tiltR && _rotAngle < 0.0f)
		_rotAngle += time * -0.1;
	//Limiting tilting to max 30 degree  
	if (_rotAngle > 30)
		_rotAngle = 30;

	if (_rotAngle < -30)
		_rotAngle = -30;

	XMVECTOR _rotzAxis{ 0,0,1,0 };
	m_rotation = XMMatrixRotationAxis(_rotzAxis, _rotAngle);
}

void Player::Initialize(SoundManager* SoundManager, int MapWidth, int MapLenght,Input* input)
{
	m_soundManager = SoundManager;
	m_input = input;

	m_mapLenght = MapLenght;
	m_mapWidth = MapWidth;

	//Loading death sounds
	m_soundManager->LoadSound("DickbuttSound.mp3", "PlayerDeathSound", "PlayerSound", LOAD_MEMORY);
	
	XMVECTOR _rotzAxis{ 0,0,1,0 };

	m_rotation = XMMatrixRotationAxis(_rotzAxis, 0.0f);

}

void Player::Destroyed()
{
	//Play sound when destoyed..
	m_soundManager->PlayOneShotSound("PlayerDeathSound", 0.5f);
}
