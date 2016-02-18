#include "Graphics/DeferredBuffer.h"

DeferredBuffer::DeferredBuffer()
{
	for (int i = 0; i < g_BUFFER_COUNT; i++)
	{
		m_RTTA[i] = nullptr;
		m_RTVA[i] = nullptr;
		m_SRVA[i] = nullptr;
	}
	m_depthStencilView = nullptr;
	m_depthStencil = nullptr;
	m_cleanView = nullptr;
}

DeferredBuffer::~DeferredBuffer()
{
	if (m_depthStencil != nullptr)
		m_depthStencil->Release();
	if (m_depthStencilView != nullptr)
		m_depthStencilView->Release();
	for (int i = 0; i < g_BUFFER_COUNT; i++)
	{
		if(m_RTTA[i] != nullptr)
		m_RTTA[i]->Release();
		if (m_SRVA[i] != nullptr)
		m_SRVA[i]->Release();
		if (m_RTVA[i] != nullptr)
		m_RTVA[i]->Release();
	}
}

bool DeferredBuffer::Initialize(ID3D11Device* device, int texWidth, int texHeight)
{
	D3D11_TEXTURE2D_DESC _textureDesc;
	HRESULT _hr;
	D3D11_RENDER_TARGET_VIEW_DESC _renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC _shaderResourceViewDesc;
	int _i;
	//lagrar höjd o bred av render texturen
	m_texWidth = texWidth;
	m_texHeight = texHeight;


	ZeroMemory(&_textureDesc, sizeof(_textureDesc));

	//sätter render target texturens förklaring
	_textureDesc.Width = m_texWidth;
	_textureDesc.Height = m_texHeight;
	_textureDesc.MipLevels = 1;
	_textureDesc.ArraySize = 1;
	_textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	_textureDesc.SampleDesc.Count = 1;
	_textureDesc.SampleDesc.Quality = 0;
	_textureDesc.Usage = D3D11_USAGE_DEFAULT;
	_textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	_textureDesc.CPUAccessFlags = 0;
	_textureDesc.MiscFlags = 0;

	for (_i = 0; _i < g_BUFFER_COUNT; _i++)
	{
		_hr = device->CreateTexture2D(&_textureDesc, NULL, &m_RTTA[_i]);
		if (FAILED(_hr))
		{
			return false;
		}
	}


	ZeroMemory(&_renderTargetViewDesc, sizeof(_renderTargetViewDesc));

	// Sets the description for render target view
	_renderTargetViewDesc.Format = _textureDesc.Format;
	_renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	_renderTargetViewDesc.Texture2D.MipSlice = 0;

	for (_i = 0; _i < g_BUFFER_COUNT; _i++)
	{
		_hr = device->CreateRenderTargetView(m_RTTA[_i], &_renderTargetViewDesc, &m_RTVA[_i]);
		if (FAILED(_hr))
		{
			return false;
		}
	}

	ZeroMemory(&_shaderResourceViewDesc, sizeof(_shaderResourceViewDesc));

	// Sets the description for shader resource view.
	_shaderResourceViewDesc.Format = _textureDesc.Format;
	_shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	_shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	_shaderResourceViewDesc.Texture2D.MipLevels = 1;

	for (_i = 0; _i < g_BUFFER_COUNT; _i++)
	{
		_hr = device->CreateShaderResourceView(m_RTTA[_i], &_shaderResourceViewDesc, &m_SRVA[_i]);
		if (FAILED(_hr))
		{
			return false;
		}
	}

	D3D11_TEXTURE2D_DESC _descDepth;
	_descDepth.Width = m_texWidth;
	_descDepth.Height = m_texHeight;
	_descDepth.MipLevels = 1;
	_descDepth.ArraySize = 1;
	_descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	_descDepth.SampleDesc.Count = 1;
	_descDepth.SampleDesc.Quality = 0;
	_descDepth.Usage = D3D11_USAGE_DEFAULT;
	_descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	_descDepth.CPUAccessFlags = 0;
	_descDepth.MiscFlags = 0;
	device->CreateTexture2D(&_descDepth, NULL, &m_depthStencil);
	device->CreateDepthStencilView(m_depthStencil, NULL, &m_depthStencilView);

	return true;
}

void DeferredBuffer::SetRenderTargets(ID3D11DeviceContext* deviceContext)
{
	// Bind the render target view array and depth stencil buffer to the output render pipeline.

	deviceContext->OMSetRenderTargets(g_BUFFER_COUNT, m_RTVA, m_depthStencilView);

	return;
}

void DeferredBuffer::ClearRenderTargets(ID3D11DeviceContext* deviceContext)
{
	float clearColor[] = { 0, 0, 0, 0 };
	int i;

	// Clear the render target buffers.
	for (i = 0; i<g_BUFFER_COUNT; i++)
	{
		deviceContext->ClearRenderTargetView(m_RTVA[i], clearColor);
	}

	// Clear the depth buffer.
	deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);


	return;
}

void DeferredBuffer::SetShaderResource(ID3D11DeviceContext* deviceContext)
{
	deviceContext->PSSetShaderResources(0, 1, &m_SRVA[0]);
	deviceContext->PSSetShaderResources(1, 1, &m_SRVA[1]);
	deviceContext->PSSetShaderResources(2, 1, &m_SRVA[2]);
	deviceContext->PSSetShaderResources(3, 1, &m_SRVA[3]);
	deviceContext->PSSetShaderResources(4, 1, &m_SRVA[4]);
}

void DeferredBuffer::SetCleanResource(ID3D11DeviceContext* deviceContext)
{
	deviceContext->PSSetShaderResources(0, 1, &m_cleanView);
	deviceContext->PSSetShaderResources(1, 1, &m_cleanView);
	deviceContext->PSSetShaderResources(2, 1, &m_cleanView);
	deviceContext->PSSetShaderResources(3, 1, &m_cleanView);
	deviceContext->PSSetShaderResources(4, 1, &m_cleanView);
}

void DeferredBuffer::SetResourceView(ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView* newResource, int tartgetResource)
{
	m_SRVA[tartgetResource] = newResource;
	deviceContext->PSSetShaderResources(tartgetResource, 1, &m_SRVA[tartgetResource]);
}

ID3D11ShaderResourceView* DeferredBuffer::GetResourceView(int tartgetResource)
{
	return m_SRVA[tartgetResource];
}