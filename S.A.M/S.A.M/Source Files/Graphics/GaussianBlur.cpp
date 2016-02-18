#include "../../Header Files/Graphics/GaussianBlur.h"

GaussianBlur::~GaussianBlur()
{
	m_unAc->Release();
	m_unAc2->Release();
	m_compShaderTexture->Release();
}

GaussianBlur::GaussianBlur(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, ShaderHandler* shaderHandler, int width, int height)
{

	m_screenHeight = height;
	m_screenWidth = width;

	//Create shaders...
	D3D11_TEXTURE2D_DESC _gausDesc;
	HRESULT _hr;
	_gausDesc.Width = m_screenWidth;
	_gausDesc.Height = m_screenHeight;
	_gausDesc.MipLevels = 1;
	_gausDesc.ArraySize = 1;
	_gausDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	_gausDesc.SampleDesc.Count = 1;
	_gausDesc.SampleDesc.Quality = 0;
	_gausDesc.Usage = D3D11_USAGE_DEFAULT;
	_gausDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	_gausDesc.CPUAccessFlags = 0;
	_gausDesc.MiscFlags = 0;

	ID3D11Texture2D* _gausTex;
	ID3D11Texture2D* _gausTex2;
	_hr = Device->CreateTexture2D(&_gausDesc, 0, &_gausTex);
	_hr = Device->CreateTexture2D(&_gausDesc, 0, &_gausTex2);


	D3D11_SHADER_RESOURCE_VIEW_DESC _gST;

	_gST.Format = _gausDesc.Format;
	_gST.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	_gST.Texture2D.MipLevels = 1;
	_gST.Texture2D.MostDetailedMip = 0;

	_hr = Device->CreateShaderResourceView(_gausTex, &_gST, &m_compShaderTexture1);
	_hr = Device->CreateShaderResourceView(_gausTex2, &_gST, &m_compShaderTexture2);
	D3D11_UNORDERED_ACCESS_VIEW_DESC UAVDesc;

	UAVDesc.Format = _gausDesc.Format;
	UAVDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
	UAVDesc.Texture2D.MipSlice = 0;

	Device->CreateUnorderedAccessView(_gausTex, &UAVDesc, &m_unAc);
	Device->CreateUnorderedAccessView(_gausTex2, &UAVDesc, &m_unAc2);

	_gausTex->Release();
	_gausTex2->Release();
	m_shaderHandler = shaderHandler;

}

ID3D11ShaderResourceView* GaussianBlur::Blur(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, UINT ShaderTarget, ID3D11ShaderResourceView* shaderResource)
{
	//Set first pass Shaders
	m_shaderHandler->SetComputeShader(DeviceContext, 1);
	ID3D11ShaderResourceView* _temp = NULL; //No need to release if NULL


	//First pass
	DeviceContext->CSSetUnorderedAccessViews(0, 1, &m_unAc,0);
	DeviceContext->CSSetShaderResources(ShaderTarget, 1, &shaderResource);
	DeviceContext->Dispatch(m_screenWidth / 16, m_screenHeight, 1);

	//Set Second pass Shader
	m_shaderHandler->SetComputeShader(DeviceContext, 2);
	DeviceContext->CSSetUnorderedAccessViews(0, 1, &m_unAc2, 0);
	DeviceContext->CSSetShaderResources(ShaderTarget, 1, &m_compShaderTexture1);

	DeviceContext->Dispatch(m_screenWidth, m_screenHeight / 16, 1);
	DeviceContext->CSSetShaderResources(ShaderTarget, 1, &_temp);

	DeviceContext->PSSetShaderResources(ShaderTarget, 1, &m_compShaderTexture2);
	return m_compShaderTexture2;
}