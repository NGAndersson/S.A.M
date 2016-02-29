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
}

void Input::Initialize(HINSTANCE hInstance,HWND& hwnd)
{
	HRESULT _hr;
	//Creating the DirectInput
	_hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_DirectInput, NULL);
	//Keyboard
	_hr = m_DirectInput->CreateDevice(GUID_SysKeyboard, &m_Keyboard,NULL);
	//Setting the input data format for the keyboard as well as the mouse
	_hr = m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	_hr = m_Keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	m_Hwnd = hwnd;

	ReadInputKeyBindings();

	PairKeys();
}

void Input::PairKeys()
{
	m_dikToString[0].first = DIK_1;
	m_dikToString[0].second = to_wstring(1);
	m_dikToString[1].first = DIK_2;
	m_dikToString[1].second = to_wstring(2);
	m_dikToString[2].first = DIK_3;
	m_dikToString[2].second = to_wstring(3);
	m_dikToString[3].first = DIK_4;
	m_dikToString[3].second = to_wstring(4);
	m_dikToString[4].first = DIK_5;
	m_dikToString[4].second = to_wstring(5);
	m_dikToString[5].first = DIK_6;
	m_dikToString[5].second = to_wstring(6);
	m_dikToString[6].first = DIK_7;
	m_dikToString[6].second = to_wstring(7);
	m_dikToString[7].first = DIK_8;
	m_dikToString[7].second = to_wstring(8);
	m_dikToString[8].first = DIK_9;
	m_dikToString[8].second = to_wstring(9);
	m_dikToString[9].first = DIK_0;
	m_dikToString[9].second = to_wstring(0);

	m_dikToString[10].first = DIK_Q;
	m_dikToString[10].second = L"Q";
	m_dikToString[11].first = DIK_W;
	m_dikToString[11].second = L"W";
	m_dikToString[12].first = DIK_E;
	m_dikToString[12].second = L"E";
	m_dikToString[13].first = DIK_R;
	m_dikToString[13].second = L"R";
	m_dikToString[14].first = DIK_T;
	m_dikToString[14].second = L"T";
	m_dikToString[15].first = DIK_Y;
	m_dikToString[15].second = L"Y";
	m_dikToString[16].first = DIK_U;
	m_dikToString[16].second = L"U";
	m_dikToString[17].first = DIK_I;
	m_dikToString[17].second = L"I";
	m_dikToString[18].first = DIK_O;
	m_dikToString[18].second = L"O";
	m_dikToString[19].first = DIK_P;
	m_dikToString[19].second = L"P";
	m_dikToString[20].first = DIK_A;
	m_dikToString[20].second = L"A";
	m_dikToString[21].first = DIK_S;
	m_dikToString[21].second = L"S";
	m_dikToString[22].first = DIK_D;
	m_dikToString[22].second = L"D";
	m_dikToString[23].first = DIK_F;
	m_dikToString[23].second = L"F";
	m_dikToString[24].first = DIK_G;
	m_dikToString[24].second = L"G";
	m_dikToString[25].first = DIK_H;
	m_dikToString[25].second = L"H";
	m_dikToString[26].first = DIK_J;
	m_dikToString[26].second = L"J";
	m_dikToString[27].first = DIK_K;
	m_dikToString[27].second = L"K";
	m_dikToString[28].first = DIK_L;
	m_dikToString[28].second = L"L";
	m_dikToString[29].second = DIK_Z;
	m_dikToString[29].second = L"Z";
	m_dikToString[30].first = DIK_X;
	m_dikToString[30].second = L"X";
	m_dikToString[31].first = DIK_C;
	m_dikToString[31].second = L"C";
	m_dikToString[32].first = DIK_V;
	m_dikToString[32].second = L"V";
	m_dikToString[33].first = DIK_B;
	m_dikToString[33].second = L"B";
	m_dikToString[34].first = DIK_N;
	m_dikToString[34].second = L"N";
	m_dikToString[35].first = DIK_M;
	m_dikToString[35].second = L"M";

	m_dikToString[36].first = DIK_NUMPAD1;
	m_dikToString[36].second = L"Numpad ";
	m_dikToString[37].first = DIK_NUMPAD2;
	m_dikToString[37].second = L"Numpad ";
	m_dikToString[38].first = DIK_NUMPAD3;
	m_dikToString[38].second = L"Numpad ";
	m_dikToString[39].first = DIK_NUMPAD4;
	m_dikToString[39].second = L"Numpad ";
	m_dikToString[40].first = DIK_NUMPAD5;
	m_dikToString[40].second = L"Numpad ";
	m_dikToString[41].first = DIK_NUMPAD6;
	m_dikToString[41].second = L"Numpad ";
	m_dikToString[42].first = DIK_NUMPAD7;
	m_dikToString[42].second = L"Numpad ";
	m_dikToString[43].first = DIK_NUMPAD8;
	m_dikToString[43].second = L"Numpad ";
	m_dikToString[44].first = DIK_NUMPAD9;
	m_dikToString[44].second = L"Numpad ";
	m_dikToString[45].first = DIK_NUMPAD0;
	m_dikToString[45].second = L"Numpad ";

	m_dikToString[46].first = DIK_RIGHT;
	m_dikToString[46].second = L"R_Arrow ";
	m_dikToString[47].first = DIK_LEFT;
	m_dikToString[47].second = L"L_Arrow ";
	m_dikToString[48].first = DIK_UP;
	m_dikToString[48].second = L"U_Arrow ";
	m_dikToString[49].first = DIK_DOWN;
	m_dikToString[49].second = L"D_Arrow ";
	m_dikToString[50].first = DIK_SPACE;
	m_dikToString[50].second = L"Space";

}

int Input::CheckInputInt()
{
	for (int i = 0; i < 51; i++)
	{
		if (m_keyBoardState[m_dikToString[i].first] & 0x80)
			return m_dikToString[i].first;
	}
}

wstring Input::CheckInputWString()
{
	for (int i = 0; i < 51; i++)
	{
		if (m_keyBoardState[m_dikToString[i].first] & 0x80)
			return m_dikToString[i].second;
	}
}

bool Input::CheckIfInput()
{
	for (int i = 0; i < 51; i++)
	{
		if (m_keyBoardState[m_dikToString[i].first] & 0x80)
			return true;
	}
	return false;
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
	else if (m_keyBoardState[DIK_RETURN] & 0x80)
		return INPUT_ENTER;

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