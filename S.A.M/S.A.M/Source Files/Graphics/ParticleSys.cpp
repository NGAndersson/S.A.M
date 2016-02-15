#include "Graphics/ParticleSys.h"

PartSys::PartSys()
{
	m_amountOfPart = 0;
	m_partPos = &XMFLOAT4(0, 0, 0, 0);
	m_timeToLive = 0;
	m_partLifeLenght = 0;
	m_partOffset = 0;
}

PartSys::~PartSys()
{
	delete[] m_partPos;
	delete[] m_timeToLive;
	//delete[] m_rocketPos;
	if(m_partTex != nullptr)
		m_partTex->Release();

	if (m_vertexBuffer != nullptr)
		m_vertexBuffer->Release();

	if (m_instancePartBuffer != nullptr)
		m_instancePartBuffer->Release();

}

void PartSys::BackGround()
{
	m_amountOfPart = 600;
	m_partPos = new XMFLOAT4[m_amountOfPart];
	for (int i = 0; i < m_amountOfPart; i++)
	{
		m_partPos[i] = XMFLOAT4(((float(rand() % 600) - 250)), float(rand() % 200) - 400, float(rand() % 900) - float(500), 1.0f);
	}
}

void PartSys::BackGroundUpdatePart(ID3D11DeviceContext* deviceContext, float time, float partSpeed)
{
	for (int i = 0; i < m_amountOfPart; i++)
	{
		if (m_partPos[i].z <= -400)
		{
			m_partPos[i] = XMFLOAT4(((float(rand() % 600)) - 250.0f), float(rand() % 200) - 400, float(rand() % 150) + float(400), 1.0f);
		}
		else
		{
			m_partPos[i] = XMFLOAT4(m_partPos[i].x, m_partPos[i].y, m_partPos[i].z - (partSpeed * time), 1.0f);
		}
	}

	D3D11_MAPPED_SUBRESOURCE mappResource;
	deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappResource);

	memcpy(mappResource.pData, &m_partPos[0], sizeof(float) * (m_amountOfPart * 4));

	deviceContext->Unmap(m_vertexBuffer, 0);

}

bool PartSys::CreateBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const wstring &texName)
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

	const wchar_t* _name = texName.c_str();

	CreateWICTextureFromFile(device, deviceContext, _name, nullptr, &m_partTex);

	return true;
}

bool PartSys::CreateRocketBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const wstring &texName)
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

bool PartSys::PartRend(ID3D11DeviceContext* deviceContext)
{
	UINT32 vertexSize = sizeof(float) * 4;
	UINT32 offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &vertexSize, &offset);

	deviceContext->PSSetShaderResources(0, 1, &m_partTex);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	deviceContext->Draw(m_amountOfPart, 0);

	return true;
}

bool PartSys::InstancePartRend(ID3D11DeviceContext* deviceContext)
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

void PartSys::RocketPartSys(float offset, float lifeLenght)
{
	m_amountOfPart = 6000;
	m_partPos = new XMFLOAT4[m_amountOfPart];
	m_partLifeLenght = lifeLenght;
	m_timeToLive = new float[m_amountOfPart];
	m_partOffset = offset;
	for (int i = 0; i < m_amountOfPart; i++)
	{
		m_partPos[i] = XMFLOAT4((((float(rand() % (int(m_partOffset) * 10000)) / 10000) + ((m_partOffset / 2)))), ((float(rand() % (int(m_partOffset) * 10000)) / 10000) + ((m_partOffset / 2))), (float(rand() % int(m_partOffset / 2))), 1.0f);
		if (((m_partPos[i].x * m_partPos[i].x) + (m_partPos[i].z * m_partPos[i].z)) < (m_partOffset * m_partOffset))
		{
			m_timeToLive[i] = m_partLifeLenght;
		}
		else
		{
			i--;
		}
	}
}

void PartSys::UpdateRocketPartSys(ID3D11DeviceContext* deviceContext, float time, float partSpeed)
{
	for (int i = 0; i < m_amountOfPart; i++)
	{
		if (m_timeToLive[i] <= 0)
		{
			m_partPos[i] = XMFLOAT4((((float(rand() % (int(m_partOffset) * 10000)) / 10000) - ((m_partOffset / 2)))), (((float(rand() % (int(m_partOffset) * 10000)) / 10000) - ((m_partOffset / 2)))), float(rand() % int(m_partOffset / 2)), 1.0f);
			if (((m_partPos[i].x * m_partPos[i].x) + (m_partPos[i].z * m_partPos[i].z)) < (m_partOffset))
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
			m_partPos[i] = XMFLOAT4(m_partPos[i].x, m_partPos[i].y, m_partPos[i].z - (partSpeed * time), 1.0f);
			m_timeToLive[i] = m_timeToLive[i] - ((m_partPos[i].x * m_partPos[i].x) * 50)  - ((m_partPos[i].y * m_partPos[i].y) * 50) - ((m_partPos[i].z * m_partPos[i].z) * 2 - float(rand() % 200));
		}
	}

	D3D11_MAPPED_SUBRESOURCE mappResource;
	deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappResource);

	memcpy(mappResource.pData, &m_partPos[0], sizeof(float) * (m_amountOfPart * 4));

	deviceContext->Unmap(m_vertexBuffer, 0);
}

void PartSys::AddRocketPartSys(std::vector<Entity*> entity, const XMFLOAT4 &addPos)
{
	int _size = entity.size() + m_nrOfPositions;
	int _offset = m_nrOfPositions;
	for (int i = m_nrOfPositions; i < _size; i++)
	{
		m_rocketPos[i] = XMFLOAT4(entity[i - _offset]->GetPosition().x + addPos.x, entity[i - _offset]->GetPosition().y + addPos.y, entity[i - _offset]->GetPosition().z + addPos.z, 1.0f);
		m_nrOfPositions++;
	}
}

void PartSys::SetRocketBuffer(ID3D11DeviceContext* deviceContext)
{
	D3D11_MAPPED_SUBRESOURCE _mappedResource;

	HRESULT hr = deviceContext->Map(m_instancePartBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_mappedResource);
	

	memcpy(_mappedResource.pData, &m_rocketPos, sizeof(XMFLOAT4) * 20);

	deviceContext->Unmap(m_instancePartBuffer, 0);

	deviceContext->VSSetConstantBuffers(1, 1, &m_instancePartBuffer);
}