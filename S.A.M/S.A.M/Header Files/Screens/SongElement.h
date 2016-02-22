#ifndef _SONGELEMENT_H_
#define _SONGELEMENT_H_
#include <string>
#include <fstream>
#include <sstream>
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "SimpleMath.h"
#include <d3d11.h>
#include <memory>
#include "WICTextureLoader.h"
#include "wrl.h"
#include <CommonStates.h>
#include "../Audio/SoundManager.h"
#include "../Audio/BeatDetector.h"
#include <stdlib.h>

class SongElement {
private:
public:
	SongElement();
	SongElement(std::string filename, ID3D11Device* device, ID3D11DeviceContext* DeviceContext, SoundManager* soundManager);
	~SongElement();
	void Render(int offsetX, int offsetZ);
	char* GetFile() { return m_file; }
	std::string GetDataFile() { return m_dataFile; }
private:
	SoundManager* m_soundManager;
	std::wstring m_songName;
	std::wstring m_artist;
	std::wstring m_arranger;
	char* m_file = (char *)malloc(200);
	std::string m_dataFile;
	std::wstring m_bpm = L"N/A";			//Load music and get only when selected
	std::wstring m_length = L"N/A";		//Load music and get only when selected
	std::unique_ptr<DirectX::SpriteFont> m_font;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::CommonStates> m_states;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_backGround;
public:
};

#endif // !_SONGELEMENT_H_
