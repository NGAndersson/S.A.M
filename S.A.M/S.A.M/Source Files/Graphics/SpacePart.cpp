#include "Graphics\SpacePart.h"

SpacePart::SpacePart()
{
	m_amountOfPart = 600;
	m_partPos = new XMFLOAT4[m_amountOfPart];
	for (int i = 0; i < m_amountOfPart; i++)
	{
		m_partPos[i] = XMFLOAT4(((float(rand() % 600) - 250)), float(rand() % 200) - 400, float(rand() % 900) - float(0), 1.0f);
	}
}

SpacePart::~SpacePart()
{
	delete[] m_partPos;
	if (m_partTex != nullptr)
		m_partTex->Release();

	if (m_vertexBuffer != nullptr)
		m_vertexBuffer->Release();

	if (m_instancePartBuffer != nullptr)
		m_instancePartBuffer->Release();
}

void SpacePart::Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed)
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

void SpacePart::Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed, std::vector<Entity*> entity)
{

}

bool SpacePart::CreateBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, wstring texName)
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

bool SpacePart::Render(ID3D11DeviceContext* deviceContext)
{
	UINT32 vertexSize = sizeof(float) * 4;
	UINT32 offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &vertexSize, &offset);

	deviceContext->PSSetShaderResources(0, 1, &m_partTex);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	deviceContext->Draw(m_amountOfPart, 0);

	return true;
}

void SpacePart::AddPartSys(std::vector<Entity*> entity, XMFLOAT4 addPos)
{
	
}

void SpacePart::SetBuffer(ID3D11DeviceContext* deviceContext)
{
	
}