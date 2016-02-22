#include "Gamelogic/Input.h"

Input::Input()
{

}

Input::~Input()
{

	if (m_Keyboard)
	{
		m_Keyboard->Unacquire();
		m_Keyboard->Release();
		m_Keyboard = 0;
	}

	if (m_Mouse)
	{
		m_Mouse->Unacquire();
		m_Mouse->Release();
		m_Mouse = 0;
	}

	if (m_DirectInput)
	{
		m_DirectInput->Release();
		m_DirectInput = 0;
	}

}

void Input::Update()
{
	m_Keyboard->Acquire();

	ZeroMemory(&m_keyBoardState, sizeof(m_keyBoardState));
	m_Keyboard->GetDeviceState(sizeof(m_keyBoardState), (LPVOID)&m_keyBoardState);

	m_Mouse->Acquire();
	m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrMouse);

}

void Input::Initialize(HINSTANCE hInstance,HWND& hwnd, int ScreenWidth, int ScreenHeight)
{
	HRESULT _hr;
	//Creating the DirectInput
	_hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_DirectInput, NULL);
	//Keyboard
	_hr = m_DirectInput->CreateDevice(GUID_SysKeyboard, &m_Keyboard,NULL);
	//mouse
	_hr = m_DirectInput->CreateDevice(GUID_SysMouse, &m_Mouse, NULL);
	//Setting the input data format for the keyboard as well as the mouse
	_hr = m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	_hr = m_Keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	_hr = m_Mouse->SetDataFormat(&c_dfDIMouse);
	_hr = m_Mouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);


	m_Hwnd = hwnd;

	m_ScreenHeight = ScreenHeight;
	m_ScreenWidth = ScreenWidth;
	ReadInputKeyBindings();

}

BulletType Input::CheckBullet()
{
	
	BulletType _returnType = INPUT_DEFAULT_BULLET;

	if (m_keyBoardState[m_keyBindings[WEAPON_1]] & 0x80)
		return	_returnType = INPUT_BULLET2;

	if (m_keyBoardState[m_keyBindings[WEAPON_2]] & 0x80)
		return	_returnType = INPUT_BULLET3;

	if (m_keyBoardState[m_keyBindings[WEAPON_3]] & 0x80)
		return	_returnType = INPUT_BULLET4;

	if (m_keyBoardState[m_keyBindings[WEAPON_4]] & 0x80)
		return	_returnType = INPUT_BULLET5;

	return _returnType;

}
InputType Input::CheckKeyBoardInput()
{
	if (m_keyBoardState[m_keyBindings[MOVELEFT]] & 0x80)
		return INPUT_MOVE_LEFT;

	else if (m_keyBoardState[m_keyBindings[MOVERIGHT]] & 0x80)
		return INPUT_MOVE_RIGHT;

	else if (m_keyBoardState[m_keyBindings[MOVEUP]] & 0x80)
		return INPUT_MOVE_UP;

	else if (m_keyBoardState[m_keyBindings[MOVEDOWN]] & 0x80)
		return INPUT_MOVE_DOWN;

	return INPUT_DEFAULT;

}

bool Input::CheckReturn()
{
	if (m_keyBoardState[DIK_RETURN] & 0x80)
		return true;
	
	return false;
}

void Input::CheckKeyBoardInput(InputType* returnput)
{
	if (m_keyBoardState[m_keyBindings[MOVELEFT]] & 0x80)
		returnput[0] = INPUT_MOVE_LEFT;

	if (m_keyBoardState[m_keyBindings[MOVERIGHT]] &0x80)
		returnput[1] = INPUT_MOVE_RIGHT;

	if (m_keyBoardState[m_keyBindings[MOVEUP]] & 0x80)
		returnput[2] = INPUT_MOVE_UP;

	if (m_keyBoardState[m_keyBindings[MOVEDOWN]] & 0x80)
		returnput[3] = INPUT_MOVE_DOWN;


}

MouseClicked Input::CheckMouseInput()
{

	MouseClicked _ReturnType;
	_ReturnType.MouseAct = INPUT_DEFAULT;

	POINT _p;
	GetCursorPos(&_p);
	ScreenToClient(m_Hwnd, &_p);

	if (m_CurrMouse.rgbButtons[0] & 0x80)
	{
		_ReturnType.MouseAct = INPUT_MOUSE_LK;
		_ReturnType.Mouse_Position_X = _p.x;
		_ReturnType.Mouse_Position_Y = _p.y;

	}

	return _ReturnType;
}

bool Input::CheckEsc()
{
	if (m_keyBoardState[DIK_ESCAPE] & 0x80)
		return true;

	return false;
}

//Return true if a new button is being pressed, not if a button is released
//bool Input::IsNewButtonPressed(BulletType& checkAgainst)
//{
//	BulletType _current = CheckBullet();
//	
//	if ((_current == INPUT_BULLET2 && checkAgainst != INPUT_BULLET2)
//		|| (_current == INPUT_BULLET3 && checkAgainst != INPUT_BULLET3)
//		|| (_current == INPUT_BULLET4 && checkAgainst != INPUT_BULLET4)
//		|| (_current == INPUT_BULLET5 && checkAgainst != INPUT_BULLET5))
//	{
//		checkAgainst = _current;
//		return true;
//	}
//	checkAgainst = _current;
//	return false;
//}
void Input::SaveInputKeyBindings()
{
	std::fstream _file;
	_file.open("Options/KeyBindings.txt");

	_file << "### KEYBINDINGS\n" << std::endl;
	_file << "weapon1|" << m_keyBindings[WEAPON_1]<<std::endl;
	_file << "weapon2|" << m_keyBindings[WEAPON_2] << std::endl;
	_file << "weapon3|" << m_keyBindings[WEAPON_3] << std::endl;
	_file << "weapon4|" << m_keyBindings[WEAPON_4] << std::endl;
	_file << "moveleft|" << m_keyBindings[MOVELEFT] << std::endl;
	_file << "moveright|" << m_keyBindings[MOVERIGHT] << std::endl;
	_file << "movedown|" << m_keyBindings[MOVEDOWN] << std::endl;
	_file << "moveup|" << m_keyBindings[MOVEUP] << std::endl;
	_file << "combo|" << m_keyBindings[COMBO] << std::endl;
	_file.close();
}

void Input::ReadInputKeyBindings()
{
	std::fstream _file;
	_file.open("Options/KeyBindings.txt");
	std::string _tempLine;
	char _key[100];
	char _value[100];
	if (_file.is_open())
	{
		while (getline(_file, _tempLine))
		{
			int d;

			std::istringstream _ss(_tempLine);
			_ss.get(_key, 100, '|');
			_ss.ignore();
			if (_key[0] != '#')
			{
				_ss.get(_value, 100, '|');
				if (std::string(_key) == "weapon1")
					m_keyBindings[WEAPON_1] = atoi(_value);

				else if (std::string(_key) == "weapon2")
					m_keyBindings[WEAPON_2] = atoi(_value);

				else if (std::string(_key) == "weapon3")
					m_keyBindings[WEAPON_3] = atoi(_value);

				else if (std::string(_key) == "weapon4")
					m_keyBindings[WEAPON_4] = atoi(_value);

				else if (std::string(_key) == "moveleft")
					m_keyBindings[MOVELEFT] = atoi(_value);

				else if (std::string(_key) == "moveright")
					m_keyBindings[MOVERIGHT] = atoi(_value);

				else if (std::string(_key) == "moveup")
					m_keyBindings[MOVEUP] = atoi(_value);

				else if (std::string(_key) == "movedown")
					m_keyBindings[MOVEDOWN] = atoi(_value);

				else if (std::string(_key) == "combo")
					m_keyBindings[COMBO] = atoi(_value);

			}
		}
		_file.close();

	}
}

bool Input::IsNewButtonPressed(bool& checkAgainst)
{
	if (m_keyBoardState[m_keyBindings[COMBO]] & 0x80)
	{
		if (checkAgainst == true)
			return false;
		else {
			checkAgainst = true;
			return true;
		}
	}
	else {
		checkAgainst = false;
		return false;
	}
}