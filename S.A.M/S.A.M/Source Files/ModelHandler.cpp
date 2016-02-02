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
	if (m_RGBDeffuse)
	{
		delete[] m_RGBDeffuse;
	}
	if (m_RGBAL)
	{
		delete[] m_RGBAL;
	}
	if (m_Tf)
	{
		delete[] m_Tf;
	}
	if (m_Ni)
	{
		delete[] m_Ni;
	}
	if (m_faces)
	{
		delete[] m_faces;
	}
	if (m_vertexInput)
	{
		delete[] m_vertexInput;
	}
}

bool ModelHandler::LoadOBJData(string OBJFileName, string colourFileName, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	bool _ifOK;

	m_vertexInput = m_OBJLoad.LoadObj(m_vertexCount, m_textureCount, m_normalCount, m_faceCount, OBJFileName);

	//Sets amount of kd, ka, tf and ni counts for the file
	_ifOK = m_OBJLoad.ReadColourCounts(m_kdCount, m_kaCount, m_tfCount, m_niCount, colourFileName);
	if (_ifOK == false)
	{
		return false;
	}

	// Initialize the four data structures.
	m_RGBDeffuse = new XMFLOAT3[m_kdCount];
	if (!m_RGBDeffuse)
	{
		return false;
	}

	m_RGBAL = new XMFLOAT3[m_kaCount];
	if (!m_RGBAL)
	{
		return false;
	}

	m_Tf = new XMFLOAT3[m_tfCount];
	if (!m_Tf)
	{
		return false;
	}

	m_Ni = new XMFLOAT3[m_niCount];
	if (!m_Ni)
	{
		return false;
	}

	//Loads the colour data from file
	m_ObjTex = m_OBJLoad.LoadColour(device, deviceContext, colourFileName, m_RGBDeffuse, m_RGBAL, m_Tf, m_Ni);
	return true;
}

bool ModelHandler::CreateBuffers(ID3D11Device* device)
{
	D3D11_BUFFER_DESC _OBJvertexBufferDesc, _OBJColDesc;
	D3D11_SUBRESOURCE_DATA _OBJvertexData, _OBJColourData;
	OBJColourType* _OBJColour;

	// description for vertexbuffer
	_OBJvertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	_OBJvertexBufferDesc.ByteWidth = sizeof(float) * 8 * (m_faceCount * 3);
	_OBJvertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	_OBJvertexBufferDesc.CPUAccessFlags = 0;
	_OBJvertexBufferDesc.MiscFlags = 0;
	_OBJvertexBufferDesc.StructureByteStride = 0;


	_OBJvertexData.pSysMem = m_vertexInput;
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
	UINT32 _vertexSize = sizeof(float) * 8;
	UINT32 _offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &_vertexSize, &_offset);

	deviceContext->PSSetConstantBuffers(0, 1, &m_OBJColourBuffer);
	deviceContext->PSSetShaderResources(0, 1, &m_ObjTex);

	return true;
}

int ModelHandler::GetVertexCount()
{
	return m_faceCount;
}

