#ifndef _LIGHTHANDLER_H_
#define _LIGHTHANDLER_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

using namespace std;
using namespace DirectX;

class LightHandler
{
private:
	struct LightData
	{
		XMFLOAT4 LightPos[6];
		XMFLOAT4 LightColor[6];
		XMFLOAT4 LightRange[6];
	};
public:
	LightHandler();
	~LightHandler();
	void AddLight(ID3D11DeviceContext* deviceContext, XMFLOAT3 position, XMFLOAT3 colour, float range);
	void InitializBuffer(ID3D11Device* device);
	void SetConstbuffer(ID3D11DeviceContext* deviceContext);
	

private:
	XMFLOAT4 m_lightPos[6];
	XMFLOAT4 m_lightColor[6];
	XMFLOAT4 m_lightRange[6];
	ID3D11Buffer* m_lightBuffer;
	int m_nummberOfLights;
	LightData m_lightningArray;
};

#endif
