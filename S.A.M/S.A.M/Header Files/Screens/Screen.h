#ifndef _SCREEN_H
#define _SCREEN_H
#include <iostream>

#include "WICTextureLoader.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "SimpleMath.h"
#include <vector>

#include <wrl.h>
using namespace std;
using namespace DirectX;
using namespace Microsoft;
using namespace WRL;

struct Sprite
{
	SimpleMath::Vector2 m_position;
	SimpleMath::Vector2 m_origin;
};


class Screen
{

public:
	void Initialize(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext);
	void Update();
	void Render();

public:
	Sprite t_sprite;
	vector<Sprite*> m_sprite;
	ComPtr<ID3D11ShaderResourceView> m_texture;
	unique_ptr<SpriteBatch> m_spriteBatch;

};


#endif