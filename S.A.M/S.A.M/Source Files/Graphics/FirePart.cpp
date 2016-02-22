#include "Graphics\FirePart.h"

FirePart::FirePart()
{

}

FirePart::~FirePart()
{
	delete[] m_timeToLive;
	delete[] m_partPos;
	if (m_partTex != nullptr)
		m_partTex->Release();

	if (m_vertexBuffer != nullptr)
		m_vertexBuffer->Release();

	if (m_instancePartBuffer != nullptr)
		m_instancePartBuffer->Release();
}

FirePart::FirePart(float offset, float lifeLenght)
{
	m_amountOfPart = 2000;
	m_partPos = new XMFLOAT4[m_amountOfPart];
	m_partLifeLenght = lifeLenght;
	m_timeToLive = new float[m_amountOfPart];
	m_partOffset = offset;
	for (int i = 0; i < m_amountOfPart; i++)
	{
		m_partPos[i] = XMFLOAT4((((float(rand() % int(m_partOffset * 10000)) / 10000) - ((m_partOffset / 2)))), ((float(rand() % int(m_partOffset * 10000)) / 10000) - ((m_partOffset / 2))), (float(rand() % int(m_partOffset / 2 * 10000)) / 10000), 1.0f);
		if (((m_partPos[i].x * m_partPos[i].x) + (m_partPos[i].z * m_partPos[i].z)) < (m_partOffset))
		{
			m_timeToLive[i] = m_partLifeLenght;
		}
		else
		{
			i--;
		}
	}
}

bool FirePart::CreateBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, wstring texName)
{
	D3D11_BUFFER_DESC _OBJvertexBufferDesc;

	ZeroMemory(&_OBJvertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	// description för vertex buffern
	_OBJvertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	_OBJvertexBufferDesc.ByteWidth = sizeof(float) * (m_amountOfPart * 4);
	_OBJvertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	_OBJvertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_OBJvertexBufferDesc.MiscFlags = 0;

	// Skapar vertex buffern
	device->CreateBuffer(&_OBJvertexBufferDesc, NULL, &m_vertexBuffer);

	D3D11_BUFFER_DESC _rocketBufferDesc;
	ZeroMemory(&_rocketBufferDesc, sizeof(D3D11_BUFFER_DESC));

	_rocketBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	_rocketBufferDesc.ByteWidth = sizeof(XMFLOAT4) * 20;
	_rocketBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_rocketBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_rocketBufferDesc.MiscFlags = 0;

	//skapar constant buffer
	device->CreateBuffer(&_rocketBufferDesc, NULL, &m_instancePartBuffer);

	const wchar_t* _name = texName.c_str();

	CreateWICTextureFromFile(device, deviceContext, _name, nullptr, &m_partTex);

	return true;
}

bool FirePart::Render(ID3D11DeviceContext* deviceContext)
{
	UINT32 vertexSize = sizeof(float) * 4;
	UINT32 offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &vertexSize, &offset);

	deviceContext->PSSetShaderResources(0, 1, &m_partTex);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	deviceContext->DrawInstanced(m_amountOfPart, m_nrOfPositions, 0, 0);

	m_nrOfPositions = 0;

	return true;
}

void FirePart::Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed)
{
	for (int i = 0; i < m_amountOfPart; i++)
	{
		if (m_timeToLive[i] <= 0)
		{
			m_partPos[i] = XMFLOAT4((((float(rand() % int(m_partOffset * 10000)) / 10000) - ((m_partOffset / 2)))), ((float(rand() % int(m_partOffset * 10000)) / 10000) - ((m_partOffset / 2))), (float(rand() % int((m_partOffset * 3) / 2 * 10000)) / 10000), 1.0f);
			if (((m_partPos[i].x * m_partPos[i].x) + (m_partPos[i].y * m_partPos[i].y)) < (m_partOffset / 2))
			{
				m_timeToLive[i] = m_partLifeLenght;
			}
			else
			{
				i--;
			}
		}
		else
		{
			float _x = ((float(rand() % 10000) / 9500) * time), _y = ((float(rand() % 10000) / 9500) * time);
			if (m_partPos[i].x < 0 && m_partPos[i].y < 0)
			{
				m_partPos[i] = XMFLOAT4(m_partPos[i].x - _x, m_partPos[i].y - _y, m_partPos[i].z - (partSpeed * time), 1.0f);
			}
			else if (m_partPos[i].x > 0 && m_partPos[i].y < 0)
			{
				m_partPos[i] = XMFLOAT4(m_partPos[i].x + _x, m_partPos[i].y - _y, m_partPos[i].z - (partSpeed * time), 1.0f);
			}
			else if (m_partPos[i].x > 0 && m_partPos[i].y > 0)
			{
				m_partPos[i] = XMFLOAT4(m_partPos[i].x + _x, m_partPos[i].y + _y, m_partPos[i].z - (partSpeed * time), 1.0f);
			}
			else if (m_partPos[i].x < 0 && m_partPos[i].y > 0)
			{
				m_partPos[i] = XMFLOAT4(m_partPos[i].x - _x, m_partPos[i].y + _y, m_partPos[i].z - (partSpeed * time), 1.0f);
			}
			else
			{
				m_partPos[i] = XMFLOAT4(m_partPos[i].x, m_partPos[i].y, m_partPos[i].z - (partSpeed * time), 1.0f);
			}
			m_timeToLive[i] = m_timeToLive[i] - (((m_partPos[i].x * m_partPos[i].x) * 2) + ((m_partPos[i].y * m_partPos[i].y) * 2) + ((m_partPos[i].z * m_partPos[i].z) / 2) + (float(rand() % 2)) * (time / 2));
		}
	}

	D3D11_MAPPED_SUBRESOURCE mappResource;
	deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappResource);

	memcpy(mappResource.pData, &m_partPos[0], sizeof(float) * (m_amountOfPart * 4));

	deviceContext->Unmap(m_vertexBuffer, 0);
}

void FirePart::Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed, std::vector<Entity*> entity)
{

}

void FirePart::AddPartSys(std::vector<Entity*> entity, XMFLOAT4 addPos)
{
	int _size = entity.size() + m_nrOfPositions;
	int _offset = m_nrOfPositions;
	for (int i = m_nrOfPositions; i < _size; i++)
	{
		m_rocketPos[i] = XMFLOAT4(entity[i - _offset]->GetPosition().x + addPos.x, entity[i - _offset]->GetPosition().y + addPos.y, entity[i - _offset]->GetPosition().z + addPos.z, 1.0f);
		m_nrOfPositions++;
	}
}

void FirePart::SetBuffer(ID3D11DeviceContext* deviceContext)
{
	D3D11_MAPPED_SUBRESOURCE _mappedResource;

	HRESULT hr = deviceContext->Map(m_instancePartBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_mappedResource);


	memcpy(_mappedResource.pData, &m_rocketPos, sizeof(XMFLOAT4) * 20);

	deviceContext->Unmap(m_instancePartBuffer, 0);

	deviceContext->VSSetConstantBuffers(1, 1, &m_instancePartBuffer);
}