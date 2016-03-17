#include "Graphics\ExplosionPart.h"

XMFLOAT3 NormalizeFloat3(XMFLOAT3 pos)
{
	float _divider = sqrt((pos.x * pos.x) + (pos.y * pos.y) + (pos.z * pos.z));
	XMFLOAT3 _normalized = XMFLOAT3(pos.x / _divider, pos.y / _divider, pos.z / _divider);

	return _normalized;
}

ExplosionPart::ExplosionPart()
{

}

ExplosionPart::~ExplosionPart()
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

	delete[] m_movementVec;
	if (m_lightShiftPartBuffer != nullptr)
		m_lightShiftPartBuffer->Release();
}

ExplosionPart::ExplosionPart(float offset, float lifeLenght)
{
	m_amountOfPart = 2000;
	m_partPos = new XMFLOAT4[m_amountOfPart];
	m_partLifeLenght = lifeLenght;
	m_sourcePos = new XMFLOAT4[m_amountOfPart];
	m_timeToLive = new float[m_amountOfPart];
	m_movementVec = new XMFLOAT3[m_amountOfPart];
	m_inputData = new VertexInput[m_amountOfPart];
	m_partOffset = offset;
	for (int i = 0; i < m_amountOfPart; i++)
	{
		m_partPos[i] = XMFLOAT4((((float(rand() % int(m_partOffset * 10000)) / 10000) - ((m_partOffset / 2)))), ((float(rand() % int(m_partOffset * 10000)) / 10000)), (((float(rand() % int(m_partOffset * 10000)) / 10000) - ((m_partOffset / 2)))), 1.0f);
		if (((m_partPos[i].x * m_partPos[i].x) + (m_partPos[i].z * m_partPos[i].z)) < (m_partOffset * m_partOffset))
		{
			m_movementVec[i] = NormalizeFloat3(XMFLOAT3(m_partPos[i].x, m_partPos[i].y, m_partPos[i].z));
			m_sourcePos[i] = m_partPos[i];
			m_timeToLive[i] = m_partLifeLenght;
		}
		else
		{
			i--;
		}
	}
}

bool ExplosionPart::CreateBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, wstring texName)
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

	D3D11_BUFFER_DESC _explosionBufferDesc;
	ZeroMemory(&_explosionBufferDesc, sizeof(D3D11_BUFFER_DESC));

	_explosionBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	_explosionBufferDesc.ByteWidth = sizeof(XMFLOAT4) * 20;
	_explosionBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_explosionBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_explosionBufferDesc.MiscFlags = 0;

	//skapar constant buffer
	device->CreateBuffer(&_explosionBufferDesc, NULL, &m_instancePartBuffer);

	D3D11_BUFFER_DESC _lightShiftBufferDesc;
	ZeroMemory(&_lightShiftBufferDesc, sizeof(D3D11_BUFFER_DESC));

	_lightShiftBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	_lightShiftBufferDesc.ByteWidth = sizeof(XMFLOAT4);
	_lightShiftBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_lightShiftBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	_lightShiftBufferDesc.MiscFlags = 0;

	//skapar constant buffer
	device->CreateBuffer(&_lightShiftBufferDesc, NULL, &m_lightShiftPartBuffer);

	const wchar_t* _name = texName.c_str();

	CreateWICTextureFromFile(device, deviceContext, _name, nullptr, &m_partTex);

	return true;
}

bool ExplosionPart::Render(ID3D11DeviceContext* deviceContext)
{
	UINT32 vertexSize = sizeof(float) * 8;
	UINT32 offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &vertexSize, &offset);

	deviceContext->PSSetShaderResources(0, 1, &m_partTex);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	deviceContext->DrawInstanced(m_amountOfPart, 1, 0, 0);

	m_nrOfPositions = 0;

	return true;
}

void ExplosionPart::Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed)
{
	for (int i = 0; i < m_amountOfPart; i++)
	{
		
		if (m_partLifeLenght == 1)
			m_partPos[i] = XMFLOAT4(m_partPos[i].x + (m_movementVec[i].x * partSpeed * time * m_partOffset), m_partPos[i].y + (m_movementVec[i].y * partSpeed * time * m_partOffset), m_partPos[i].z + (m_movementVec[i].z * partSpeed * time * m_partOffset) - ((partSpeed * 5) * time), 1.0f);
		else
			m_partPos[i] = XMFLOAT4(m_partPos[i].x + (m_movementVec[i].x * partSpeed * time * m_partOffset), m_partPos[i].y + (m_movementVec[i].y * partSpeed * time * m_partOffset), m_partPos[i].z + (m_movementVec[i].z * partSpeed * time * m_partOffset), 1.0f);
		m_timeToLive[i] = m_timeToLive[i] - (time);

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

void ExplosionPart::Update(ID3D11DeviceContext* deviceContext, float time, float partSpeed, std::vector<Entity*> entity)
{

}

void ExplosionPart::AddPartSys(std::vector<Entity*> entity, XMFLOAT4 addPos)
{
	m_ExplosionPos = addPos;
}

void ExplosionPart::SetBuffer(ID3D11DeviceContext* deviceContext)
{
	D3D11_MAPPED_SUBRESOURCE _mappedResource, _lightShiftMapRes;

	HRESULT hr = deviceContext->Map(m_instancePartBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_mappedResource);

	memcpy(_mappedResource.pData, &m_ExplosionPos, sizeof(XMFLOAT4));

	deviceContext->Unmap(m_instancePartBuffer, 0);

	deviceContext->VSSetConstantBuffers(1, 1, &m_instancePartBuffer);

	hr = deviceContext->Map(m_lightShiftPartBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &_lightShiftMapRes);
	m_lightShift = XMFLOAT4(m_timeToLive[0] * 3, m_timeToLive[0] * 3, m_timeToLive[0] * 3, 1);
	memcpy(_lightShiftMapRes.pData, &m_lightShift, sizeof(XMFLOAT4));

	deviceContext->Unmap(m_lightShiftPartBuffer, 0);

	deviceContext->PSSetConstantBuffers(3, 1, &m_lightShiftPartBuffer);
	
}