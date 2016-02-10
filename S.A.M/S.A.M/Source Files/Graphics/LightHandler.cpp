#include "Graphics/LightHandler.h"

LightHandler::LightHandler()
{
	m_nummberOfLights = 5;
	Light* _tempLight = nullptr;

	_tempLight = new Light(XMFLOAT4(0, -10, 0, 0), XMFLOAT4(0.4, 0.4, 0.4, 0), XMFLOAT4(5000, float(m_nummberOfLights), 1, 0));
	m_light.push_back(_tempLight);

	_tempLight = new Light(XMFLOAT4(50, 0, 0, 0), XMFLOAT4(0.2, 0.2, 0.2, 0), XMFLOAT4(5000, float(m_nummberOfLights), 1, 0));
	m_light.push_back(_tempLight);

	_tempLight = new Light(XMFLOAT4(0, 0, 50, 0), XMFLOAT4(0.2, 0.2, 0.2, 0), XMFLOAT4(5000, float(m_nummberOfLights), 1, 0));
	m_light.push_back(_tempLight);

	_tempLight = new Light(XMFLOAT4(0, 0, -50, 0), XMFLOAT4(0.2, 0.2, 0.2, 0), XMFLOAT4(5000, float(m_nummberOfLights), 1, 0));
	m_light.push_back(_tempLight);

	_tempLight = new Light(XMFLOAT4(-50, 0, 0, 0), XMFLOAT4(0.2, 0.2, 0.2, 0), XMFLOAT4(5000, float(m_nummberOfLights), 1, 0));
	m_light.push_back(_tempLight);

	m_allLights = new Light[200];
	for (int i = 0; i < 5; i++)
	{
		m_allLights[i].SetPos(m_light[i]->GetPos());
		m_allLights[i].SetColor(m_light[i]->GetColor());
		m_allLights[i].SetRange(m_light[i]->GetRange());
	}
}

LightHandler::~LightHandler()
{
	if(m_lightBuffer)
		m_lightBuffer->Release();
}

void LightHandler::InitializBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC _lightBufferDesc;
	ZeroMemory(&_lightBufferDesc, sizeof(D3D11_BUFFER_DESC));

	_lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	_lightBufferDesc.ByteWidth = sizeof(XMFLOAT4) * 600;
	_lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_lightBufferDesc.MiscFlags = 0;

	//skapar constant buffer
	HRESULT hr = device->CreateBuffer(&_lightBufferDesc, NULL, &m_lightBuffer);

}

void LightHandler::SetConstbuffer(ID3D11DeviceContext* deviceContext)
{
	D3D11_MAPPED_SUBRESOURCE _mappedResource;

	HRESULT hr = deviceContext->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_mappedResource);

	for (int i = 0; i < m_nummberOfLights; i++)
	{
		m_lightningArray.LightPos[i] = m_allLights[i].GetPos();
		m_lightningArray.LightColor[i] = m_allLights[i].GetColor();
		m_lightningArray.LightRange[i] = m_allLights[i].GetRange();
	}

	memcpy(_mappedResource.pData, &m_lightningArray, sizeof(LightData));

	deviceContext->Unmap(m_lightBuffer, 0);

	deviceContext->PSSetConstantBuffers(1, 1, &m_lightBuffer);

	m_nummberOfLights = 5;
}

void LightHandler::addLights(std::vector<Entity*> bullet)
{
	int _numberOfTotLight = m_nummberOfLights + bullet.size();
	
	XMFLOAT4 _pos, _color, _range;
	Light* _tempLight;

	for (int i = 0; i < _numberOfTotLight; i++)
	{
		if (i < m_nummberOfLights)
		{
			_range = m_allLights[i].GetRange();
			m_allLights[i].SetRange(XMFLOAT4(_range.x, _numberOfTotLight, _range.z, _range.w));
		}
		else if (i >= m_nummberOfLights && i < _numberOfTotLight)
		{
			_tempLight = bullet[i - m_nummberOfLights]->GetLight();
			_pos = _tempLight->GetPos();
			_color = _tempLight->GetColor();
			_range = _tempLight->GetRange();
			m_allLights[i].SetPos(_pos);
			m_allLights[i].SetColor(XMFLOAT4(_color.x * m_beatBoost, _color.y * m_beatBoost, _color.z * m_beatBoost, _color.w));
			m_allLights[i].SetRange(XMFLOAT4(_range.x * m_beatBoost, _numberOfTotLight, _range.z, _range.w));
		}
	}
	m_nummberOfLights = _numberOfTotLight;
}

void LightHandler::beatBoost(bool beat, float time, float timeSinceLast, float BPM)
{
	if (beat == true)
	{
		if (timeSinceLast != -1)
		{
			m_beatBoost = 2;
			m_beatTime = timeSinceLast;
		}
		else
		{
			m_beatBoost = 2;
			m_beatTime = BPM / 60;
		}
	}
	else if (beat == false)
	{
			m_beatBoost += -time * m_beatTime * 10;
	}
}