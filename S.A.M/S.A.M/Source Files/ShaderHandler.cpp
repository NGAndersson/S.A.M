#include "ShaderHandler.h"

ShaderHandler::ShaderHandler()
{

}

ShaderHandler::~ShaderHandler()
{
	if (m_vertexLayout)
	{
		m_vertexLayout->Release();
	}
	if (m_vertexShader)
	{
		m_vertexShader->Release();
	}
	if (m_geometryShader)
	{
		m_geometryShader->Release();
	}
	if (m_pixelShader)
	{
		m_pixelShader->Release();
	}
	if (m_computeShader)
	{
		m_computeShader->Release();
	}
}

std::wstring s2ws(const std::string& s)
{
	int _len;
	int _slength = (int)s.length() + 1;
	_len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), _slength, 0, 0);
	wchar_t* _buf = new wchar_t[_len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), _slength, _buf, _len);
	std::wstring r(_buf);
	delete[] _buf;
	return r;
}

bool ShaderHandler::CreateShaders(ID3D11Device* device, string vertexFile, string geometryFile, string pixelFile)
{
	wstring vertexVSTemp = s2ws(vertexFile);
	wstring vertexGSTemp = s2ws(geometryFile);
	wstring vertexPSTemp = s2ws(pixelFile);

	//create vertex shader
	ID3DBlob* _vs = nullptr;
	D3DCompileFromFile(vertexVSTemp.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS_main", "vs_5_0", 0, NULL, &_vs, nullptr);

	HRESULT _hr = device->CreateVertexShader(_vs->GetBufferPointer(), _vs->GetBufferSize(), nullptr, &m_vertexShader);
	if (!_hr)
	{
		_vs->Release();
		return false;
	}

	//create input layout (verified with vertex shader)
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	_hr = device->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), _vs->GetBufferPointer(), _vs->GetBufferSize(), &m_vertexLayout);
	_vs->Release();
	if (!_hr)
	{
		return false;
	}


	if (geometryFile != "")
	{
		//create geometry shader
		ID3DBlob* _gs = nullptr;
		D3DCompileFromFile(vertexGSTemp.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "GS_main", "gs_5_0", 0, NULL, &_gs, nullptr);
		_hr = device->CreateGeometryShader(_gs->GetBufferPointer(), _gs->GetBufferSize(), nullptr, &m_geometryShader);
		_gs->Release();
		if (!_hr)
		{
			return false;
		}
	}

	//create pixel shader
	ID3DBlob* _ps = nullptr;
	D3DCompileFromFile(vertexPSTemp.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS_main", "ps_5_0", 0, NULL, &_ps, nullptr);
	_hr = device->CreatePixelShader(_ps->GetBufferPointer(), _ps->GetBufferSize(), nullptr, &m_pixelShader);
	_ps->Release();
	if (!_hr)
	{
		return false;
	}

	return true;
}

bool ShaderHandler::CreateShadersCompute(ID3D11Device* device, string vertexFile, string geometryFile, string pixelFile, string computeFile)
{
	wstring vertexVSTemp = s2ws(vertexFile);
	wstring vertexGSTemp = s2ws(geometryFile);
	wstring vertexPSTemp = s2ws(pixelFile);
	wstring vertexCSTemp = s2ws(computeFile);

	//create vertex shader
	ID3DBlob* _vs = nullptr;
	D3DCompileFromFile(vertexVSTemp.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS_main", "vs_5_0", 0, NULL, &_vs, nullptr);

	HRESULT _hr = device->CreateVertexShader(_vs->GetBufferPointer(), _vs->GetBufferSize(), nullptr, &m_vertexShader);
	if (!_hr)
	{
		_vs->Release();
		return false;
	}

	//create input layout (verified with vertex shader)
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	_hr = device->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), _vs->GetBufferPointer(), _vs->GetBufferSize(), &m_vertexLayout);
	_vs->Release();
	if (!_hr)
	{
		return false;
	}


	if (geometryFile != "")
	{
		//create geometry shader
		ID3DBlob* _gs = nullptr;
		D3DCompileFromFile(vertexGSTemp.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "GS_main", "gs_5_0", 0, NULL, &_gs, nullptr);
		_hr = device->CreateGeometryShader(_gs->GetBufferPointer(), _gs->GetBufferSize(), nullptr, &m_geometryShader);
		_gs->Release();
		if (!_hr)
		{
			return false;
		}
	}

	//create pixel shader
	ID3DBlob* _ps = nullptr;
	D3DCompileFromFile(vertexPSTemp.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS_main", "ps_5_0", 0, NULL, &_ps, nullptr);
	_hr = device->CreatePixelShader(_ps->GetBufferPointer(), _ps->GetBufferSize(), nullptr, &m_pixelShader);
	_ps->Release();
	if (!_hr)
	{
		return false;
	}

	// Create compute shader
	ID3DBlob *_cs = nullptr;
	D3DCompileFromFile(vertexCSTemp.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "CS_main", "cs_5_0", 0, NULL, &_cs, nullptr);
	_hr = device->CreateComputeShader(_cs->GetBufferPointer(), _cs->GetBufferSize(), nullptr, &m_computeShader);
	_cs->Release();
	if (!_hr)
	{
		return false;
	}

	return true;
}

bool ShaderHandler::SetShaders(ID3D11DeviceContext* deviceContext)
{
	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->HSSetShader(nullptr, nullptr, 0);
	deviceContext->DSSetShader(nullptr, nullptr, 0);
	if (m_geometryShader)
	{
		deviceContext->GSSetShader(m_geometryShader, nullptr, 0);
	}
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	if (m_computeShader)
	{
		deviceContext->CSSetShader(m_computeShader, nullptr, 0);
	}

	deviceContext->IASetInputLayout(m_vertexLayout);

	return true;
}