#ifndef _LIGHTHANDLER_H_
#define _LIGHTHANDLER_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <vector>
#include <iostream>
#include <Graphics/Light.h>
#include <Entities/Entity.h>

using namespace std;
using namespace DirectX;

class LightHandler
{
private:
	struct LightData
	{
		XMFLOAT4 LightPos[200];
		XMFLOAT4 LightColor[200];
		XMFLOAT4 LightRange[200];
	};
public:
	LightHandler();
	~LightHandler();
	void InitializBuffer(ID3D11Device* device);
	void SetConstbuffer(ID3D11DeviceContext* deviceContext);
	void addLights(std::vector<Entity*> bullet);
	void beatBoost(bool beat, float time, float timeSinceLast, float BPM);
	

private:
	ID3D11Buffer* m_lightBuffer = nullptr;
	int m_nummberOfLights;
	LightData m_lightningArray = {};
	//Light* m_light = nullptr;
	Light* m_allLights = nullptr;
	float m_beatBoost = 1;
	float m_beatTime = 0;
};

#endif
