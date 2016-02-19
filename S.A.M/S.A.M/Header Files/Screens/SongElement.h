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
using namespace DirectX;
class SongElement {
private:
public:
	SongElement();
	SongElement(std::string filename, ID3D11Device* device, ID3D11DeviceContext* DeviceContext,  int ScreenHeight, int ScreenWidth);
	~SongElement();
	void Render(int offsetX, int offsetZ);
private:
	std::wstring m_songName;
	std::wstring m_artist;
	std::wstring m_arranger;
	std::wstring m_file;
	std::wstring m_bpm = L"N/A";			//Load music and get only when selected
	std::wstring m_length = L"N/A";		//Load music and get only when selected
	std::unique_ptr<DirectX::SpriteFont> m_font;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::CommonStates> m_states;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_backGround;
public:
};

#endif // !_SONGELEMENT_H_
