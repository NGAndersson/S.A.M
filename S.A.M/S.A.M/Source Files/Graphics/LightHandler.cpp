#include "Graphics/LightHandler.h"

LightHandler::LightHandler()
{
	m_nummberOfLights = 5;

	m_lightPos[0] = XMFLOAT4(0, -10, 0, 0);
	m_lightColor[0] = XMFLOAT4(0.4, 0.4, 0.4, 0);
	m_lightRange[0] = XMFLOAT4(5000, float(m_nummberOfLights), 1, 0);

	m_lightPos[1] = XMFLOAT4(50, 0, 0, 0);
	m_lightColor[1] = XMFLOAT4(0.2, 0.2, 0.2, 0);
	m_lightRange[1] = XMFLOAT4(5000, float(m_nummberOfLights), 1, 0);

	m_lightPos[2] = XMFLOAT4(0, 0, 50, 0);
	m_lightColor[2] = XMFLOAT4(0.2, 0.2, 0.2, 0);
	m_lightRange[2] = XMFLOAT4(5000, float(m_nummberOfLights), 1, 0);

	m_lightPos[3] = XMFLOAT4(0, 0, -50, 0);
	m_lightColor[3] = XMFLOAT4(0.2, 0.2, 0.2, 0);
	m_lightRange[3] = XMFLOAT4(5000, float(m_nummberOfLights), 1, 0);

	m_lightPos[4] = XMFLOAT4(-50, 0, 0, 0);
	m_lightColor[4] = XMFLOAT4(0.2, 0.2, 0.2, 0);
	m_lightRange[4] = XMFLOAT4(5000, float(m_nummberOfLights), 1, 0);
}

LightHandler::~LightHandler()
{
	if(m_lightBuffer)
		m_lightBuffer->Release();
}

void LightHandler::AddLight(ID3D11DeviceContext* deviceContext, XMFLOAT3 position, XMFLOAT3 colour, float range)
{
	m_nummberOfLights = m_nummberOfLights++;

	if (m_nummberOfLights < 7)
	{
		for (int i = 0; i < m_nummberOfLights - 1; i++)
		{
			m_lightRange[i].y = float(m_nummberOfLights);
		}
		m_lightPos[m_nummberOfLights - 1] = XMFLOAT4(position.x, position.y, position.z, 0.0f);
		m_lightColor[m_nummberOfLights - 1] = XMFLOAT4(colour.x, colour.y, colour.z, 0.0f);
		m_lightRange[m_nummberOfLights - 1] = XMFLOAT4(range, float(m_nummberOfLights), 0.0f, 0.0f);
	}
	else
	{
		m_nummberOfLights = 6;
	}

	SetConstbuffer(deviceContext);

}

void LightHandler::InitializBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC _lightBufferDesc;
	ZeroMemory(&_lightBufferDesc, sizeof(D3D11_BUFFER_DESC));

	_lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	_lightBufferDesc.ByteWidth = sizeof(LightData);
	_lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_lightBufferDesc.MiscFlags = 0;

	//skapar constant buffer
	HRESULT hr = device->CreateBuffer(&_lightBufferDesc, NULL, &m_lightBuffer);

}

void LightHandler::SetConstbuffer(ID3D11DeviceContext* gDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE _mappedResource;

	HRESULT hr = gDeviceContext->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_mappedResource);

	for (int i = 0; i < 6; i++)
	{
		m_lightningArray.LightPos[i] = m_lightPos[i];
		m_lightningArray.LightColor[i] = m_lightColor[i];
		m_lightningArray.LightRange[i] = m_lightRange[i];
	}

	memcpy(_mappedResource.pData, &m_lightningArray, sizeof(LightData));

	gDeviceContext->Unmap(m_lightBuffer, 0);

	gDeviceContext->PSSetConstantBuffers(1, 1, &m_lightBuffer);

}