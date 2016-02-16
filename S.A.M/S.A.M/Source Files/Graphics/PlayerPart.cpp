#include "Graphics\PlayerPart.h"

PlayerPart::PlayerPart()
{

}

PlayerPart::~PlayerPart()
{
	delete[] m_timeToLive;
	delete[] m_partPos;
	delete[] m_sourcePos;
	delete[] m_inputData;
	if (m_partTex != nullptr)
		m_partTex->Release();

	if (m_vertexBuffer != nullptr)
		m_vertexBuffer->Release();

	if (m_instancePartBuffer != nullptr)
		m_instancePartBuffer->Release();
}

PlayerPart::PlayerPart(float offset, float lifeLenght, std::vector<Entity*> entity)
{
	m_amountOfPart = 6000;
	m_partPos = new XMFLOAT4[m_amountOfPart];
	m_inputData = new VertexInput[m_amountOfPart];
	m_sourcePos = new XMFLOAT4[m_amountOfPart];
	m_partLifeLenght = lifeLenght;
	m_timeToLive = new float[m_amountOfPart];
	m_partOffset = offset;
	for (int i = 0; i < m_amountOfPart; i++)
	{
		m_partPos[i] = XMFLOAT4((((float(rand() % int(m_partOffset * 10000)) / 10000) + ((m_partOffset / 2)))), ((float(rand() % int(m_partOffset * 10000)) / 10000) + ((m_partOffset / 2))), (float(rand() % int(m_partOffset / 2))), 1.0f);
		if (((m_partPos[i].x * m_partPos[i].x) + (m_partPos[i].z * m_partPos[i].z)) < (m_partOffset * m_partOffset))
		{
			m_sourcePos[i] = m_partPos[i];
			m_partPos[i] = XMFLOAT4(m_partPos[i].x + entity[0]->GetPosition().x, m_partPos[i].y + entity[0]->GetPosition().y, m_partPos[i].z + entity[0]->GetPosition().z - 3.5, 1.0f);
			m_timeToLive[i] = m_partLifeLenght;
		}
		else
		{
			i--;
		}
	}
}

bool PlayerPart::CreateBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, wstring texName)
{
	D3D11_BUFFER_DESC _OBJvertexBufferDesc;

	ZeroMemory(&_OBJvertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	// description för vertex buffern
	_OBJvertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	_OBJvertexBufferDesc.ByteWidth = sizeof(float) * (m_amountOfPart * 8);
	_OBJvertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	_OBJvertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_OBJvertexBufferDesc.MiscFlags = 0;

	// Skapar vertex buffern
	device->CreateBuffer(&_OBJvertexBufferDesc, NULL, &m_vertexBuffer);

	const wchar_t* _name = texName.c_str();

	CreateWICTextureFromFile(device, deviceContext, _name, nullptr, &m_partTex);

	return true;
}

bool PlayerPart::Render(ID3D11DeviceContext* deviceContext)
{
	UINT32 vertexSize = sizeof(float) * 8;
	UINT32 offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &vertexSize, &offset);

	deviceContext->PSSetShaderResources(0, 1, &m_partTex);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	deviceContext->Draw(m_amountOfPart, 0);

	return true;
}

void PlayerPart::Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed)
{

}

void PlayerPart::Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed, std::vector<Entity*> entity)
{
	for (int i = 0; i < m_amountOfPart; i++)
	{
		if (m_timeToLive[i] <= 0)
		{
			m_partPos[i] = XMFLOAT4((((float(rand() % int(m_partOffset * 10000)) / 10000) - ((m_partOffset / 2)))), (((float(rand() % int(m_partOffset * 10000)) / 10000) - ((m_partOffset / 2)))), float(rand() % int(m_partOffset / 2)), 1.0f);
			if (((m_partPos[i].x * m_partPos[i].x) + (m_partPos[i].y * m_partPos[i].y)) < (m_partOffset))
			{
				m_sourcePos[i] = m_partPos[i];
				m_partPos[i] = XMFLOAT4(m_partPos[i].x + entity[0]->GetPosition().x, m_partPos[i].y + entity[0]->GetPosition().y, m_partPos[i].z + entity[0]->GetPosition().z - 3.5, 1.0f);
				m_timeToLive[i] = m_partLifeLenght;
			}
			else
			{
				i--;
			}
		}
		else
		{
			m_sourcePos[i] = XMFLOAT4(m_sourcePos[i].x, m_sourcePos[i].y, m_sourcePos[i].z - (partSpeed * time), 1.0f);
			m_partPos[i] = XMFLOAT4(m_partPos[i].x, m_partPos[i].y, m_partPos[i].z - (partSpeed * time), 1.0f);
			m_timeToLive[i] = m_timeToLive[i] - ((m_sourcePos[i].x * m_sourcePos[i].x) * 120) - ((m_sourcePos[i].y * m_sourcePos[i].y) * 120) - ((m_sourcePos[i].z * m_sourcePos[i].z) * 10 - float(rand() % 200));
		}
	}

	D3D11_MAPPED_SUBRESOURCE mappResource;
	deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappResource);

	for (int i = 0; i < m_amountOfPart; i++)
	{
		m_inputData[i].Pos = m_partPos[i];
		m_inputData[i].Source = m_sourcePos[i];
	}

	memcpy(mappResource.pData, &m_inputData[0], sizeof(float) * (m_amountOfPart * 8));

	deviceContext->Unmap(m_vertexBuffer, 0);
}

void PlayerPart::AddPartSys(std::vector<Entity*> entity, XMFLOAT4 addPos)
{
	
}

void PlayerPart::SetBuffer(ID3D11DeviceContext* deviceContext)
{
	
}