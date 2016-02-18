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

class SongElement {
private:
public:
	SongElement();
	SongElement(std::string filename, ID3D11Device* device, int ScreenHeight, int ScreenWidth);
	~SongElement();
	void Render(int offsetX, int offsetZ);
private:
	std::wstring m_songName;
	std::wstring m_artist;
	std::wstring m_arranger;
	std::wstring m_file;
	std::wstring m_bpm;			//Load music and get only when selected
	std::wstring m_length;		//Load music and get only when selected
	std::unique_ptr<DirectX::SpriteFont> m_font;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_backGround;
public:
};

#endif // !_SONGELEMENT_H_
