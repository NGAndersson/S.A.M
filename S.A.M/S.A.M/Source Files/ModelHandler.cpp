#include "ModelHandler.h"

ModelHandler::ModelHandler()
{
	
}

ModelHandler::~ModelHandler()
{
	
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
	}
	if (m_OBJColourBuffer)
	{
		m_OBJColourBuffer->Release();
	}
	if (m_ObjTex)
	{
		m_ObjTex->Release();
	}
	if(m_vertices)
	{
		delete[] m_vertices;
	}
	if (m_normals)
	{
		delete[] m_normals;
	}
	if (m_texcoords)
	{
		delete[] m_texcoords;
	}	
	if (m_faces)
	{
		delete[] m_faces;
	}
}

bool ModelHandler::LoadOBJData(string OBJFileName, string colourFileName, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	bool _ifOK;

	//Sets amount of vertices, texture, normals and face counts for the file
	_ifOK = m_OBJLoad.ReadFileCounts(m_vertexCount, m_textureCount, m_normalCount, m_faceCount, OBJFileName);
	if (_ifOK == false)
	{
		return false;
	}

	// Initialize the four data structures.
	m_vertices = new XMFLOAT3[m_vertexCount];
	if (!m_vertices)
	{
		return false;
	}

	m_texcoords = new XMFLOAT2[m_textureCount];
	if (!m_texcoords)
	{
		return false;
	}

	m_normals = new XMFLOAT3[m_normalCount];
	if (!m_normals)
	{
		return false;
	}

	m_faces = new FaceType[m_faceCount];
	if (!m_faces)
	{
		return false;
	}

	//Loads the OBJ data from file
	_ifOK = m_OBJLoad.LoadDataStructures(m_vertices, m_normals, m_texcoords, m_faces, OBJFileName);;
	if (_ifOK == false)
	{
		return false;
	}

	//Sets amount of kd, ka, tf and ni counts for the file
	_ifOK = m_OBJLoad.ReadColourCounts(m_kdCount, m_kaCount, m_tfCount, m_niCount, colourFileName);
	if (_ifOK == false)
	{
		return false;
	}

	// Initialize the four data structures.
	m_RGBDeffuse = new XMFLOAT3[m_kdCount];
	if (!m_vertices)
	{
		return false;
	}

	m_RGBAL = new XMFLOAT3[m_kaCount];
	if (!m_texcoords)
	{
		return false;
	}

	m_Tf = new XMFLOAT3[m_tfCount];
	if (!m_normals)
	{
		return false;
	}

	m_Ni = new XMFLOAT3[m_niCount];
	if (!m_faces)
	{
		return false;
	}

	//Loads the colour data from file
	_ifOK = m_OBJLoad.LoadColour(device, deviceContext, colourFileName, m_ObjTex, m_RGBDeffuse, m_RGBAL, m_Tf, m_Ni);
	if (_ifOK == false)
	{
		return false;
	}
	return true;
}

bool ModelHandler::CreateBuffers(ID3D11Device* device)
{
	D3D11_BUFFER_DESC _OBJvertexBufferDesc, _OBJColDesc;
	D3D11_SUBRESOURCE_DATA _OBJvertexData, _OBJColourData;
	VertexInputType* _vertexInput;
	OBJColourType* _OBJColour;

	_vertexInput = new VertexInputType[m_faceCount * 3];

	for (int i = 0; i < (m_faceCount * 3); i += 3)
	{
		_vertexInput[i].position = XMFLOAT3(m_vertices[m_faces[i / 3].vIndex1 - 1].x, m_vertices[m_faces[i / 3].vIndex1 - 1].y, m_vertices[m_faces[i / 3].vIndex1 - 1].z);
		_vertexInput[i].uv = XMFLOAT2(m_texcoords[m_faces[i / 3].tIndex1 - 1].x, m_texcoords[m_faces[i / 3].tIndex1 - 1].y);
		_vertexInput[i].normal = XMFLOAT3(m_normals[m_faces[i / 3].nIndex1 - 1].x, m_normals[m_faces[i / 3].nIndex1 - 1].y, m_normals[m_faces[i / 3].nIndex1 - 1].z);

		_vertexInput[i + 1].position = XMFLOAT3(m_vertices[m_faces[i / 3].vIndex2 - 1].x, m_vertices[m_faces[i / 3].vIndex2 - 1].y, m_vertices[m_faces[i / 3].vIndex2 - 1].z);
		_vertexInput[i + 1].uv = XMFLOAT2(m_texcoords[m_faces[i / 3].tIndex2 - 1].x, m_texcoords[m_faces[i / 3].tIndex2 - 1].y);
		_vertexInput[i + 1].normal = XMFLOAT3(m_normals[m_faces[i / 3].nIndex2 - 1].x, m_normals[m_faces[i / 3].nIndex2 - 1].y, m_normals[m_faces[i / 3].nIndex2 - 1].z);

		_vertexInput[i + 2].position = XMFLOAT3(m_vertices[m_faces[i / 3].vIndex3 - 1].x, m_vertices[m_faces[i / 3].vIndex3 - 1].y, m_vertices[m_faces[i / 3].vIndex3 - 1].z);
		_vertexInput[i + 2].uv = XMFLOAT2(m_texcoords[m_faces[i / 3].tIndex3 - 1].x, m_texcoords[m_faces[i / 3].tIndex3 - 1].y);
		_vertexInput[i + 2].normal = XMFLOAT3(m_normals[m_faces[i / 3].nIndex3 - 1].x, m_normals[m_faces[i / 3].nIndex3 - 1].y, m_normals[m_faces[i / 3].nIndex3 - 1].z);
	}

	// description for vertexbuffer
	_OBJvertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	_OBJvertexBufferDesc.ByteWidth = sizeof(float) * 8 * (m_faceCount * 3);
	_OBJvertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	_OBJvertexBufferDesc.CPUAccessFlags = 0;
	_OBJvertexBufferDesc.MiscFlags = 0;
	_OBJvertexBufferDesc.StructureByteStride = 0;


	_OBJvertexData.pSysMem = _vertexInput;
	_OBJvertexData.SysMemPitch = 0;
	_OBJvertexData.SysMemSlicePitch = 0;

	// Creates vertex buffern
	device->CreateBuffer(&_OBJvertexBufferDesc, &_OBJvertexData, &m_vertexBuffer);

	_OBJColour = new OBJColourType[m_kdCount];

	for (int _i = 0; _i < m_kdCount; _i++)
	{
		_OBJColour[_i].Deffuse = m_RGBDeffuse[_i];
		_OBJColour[_i].Albi = m_RGBAL[_i];
		_OBJColour[_i].Ni = m_Tf[_i];
		_OBJColour[_i].Tf = m_Ni[_i];
	}

	ZeroMemory(&_OBJColDesc, sizeof(D3D11_BUFFER_DESC));

	_OBJColDesc.Usage = D3D11_USAGE_DEFAULT;
	_OBJColDesc.ByteWidth = sizeof(OBJColourType);
	_OBJColDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_OBJColDesc.CPUAccessFlags = 0;
	_OBJColDesc.MiscFlags = 0;

	_OBJColourData.pSysMem = _OBJColour;
	_OBJColourData.SysMemPitch = 0;
	_OBJColourData.SysMemSlicePitch = 0;

	//skapar constant buffer
	device->CreateBuffer(&_OBJColDesc, &_OBJColourData, &m_OBJColourBuffer);

	// description for sampler
	D3D11_SAMPLER_DESC samplDesc;
	ZeroMemory(&samplDesc, sizeof(D3D11_SAMPLER_DESC));

	samplDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplDesc.MinLOD = 0;
	samplDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// create the sampler
	device->CreateSamplerState(&samplDesc, &m_sampleState);

	return true;
}

bool ModelHandler::CreateShaders(ID3D11Device* device, string vertexFile, string geometryFile, string pixelFile)
{
	bool _ifOK;

	_ifOK = m_shaderLoad.CreateShaders(device, vertexFile, geometryFile, pixelFile);
	if (_ifOK == false)
	{
		return false;
	}
	return true;
}

bool ModelHandler::CreateShadersCompute(ID3D11Device* device, string vertexFile, string geometryFile, string pixelFile, string computeFile)
{
	bool _ifOK;

	_ifOK = m_shaderLoad.CreateShadersCompute(device, vertexFile, geometryFile, pixelFile, computeFile);
	if (_ifOK == false)
	{
		return false;
	}
	return true;
}

bool ModelHandler::SetShaders(ID3D11DeviceContext* deviceContext)
{
	bool _ifOK;

	_ifOK = m_shaderLoad.SetShaders(deviceContext);
	if (_ifOK == false)
	{
		return false;
	}
	return true;
}

bool ModelHandler::SetBuffers(ID3D11DeviceContext* deviceContext)
{
	UINT32 vertexSize = sizeof(float) * 8;
	UINT32 offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &vertexSize, &offset);

	deviceContext->PSSetConstantBuffers(0, 1, &m_OBJColourBuffer);
	deviceContext->PSSetSamplers(0, 1, &m_sampleState);
	deviceContext->PSSetShaderResources(0, 1, &m_ObjTex);

	return true;
}

