#ifndef _DEFERREDBUFFER_H_
#define _DEFERREDBUFFER_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

using namespace std;
using namespace DirectX;

const int g_BUFFER_COUNT = 4;

class DeferredBuffer
{
private:
	
public:
	DeferredBuffer();
	~DeferredBuffer();
	bool Initialize(ID3D11Device* device, int texWidth, int texHeight);
	void SetRenderTargets(ID3D11DeviceContext* deviceContext);
	void ClearRenderTargets(ID3D11DeviceContext* deviceContext);
	void SetShaderResource(ID3D11DeviceContext* deviceContext);
	void SetCleanResource(ID3D11DeviceContext* deviceContext);

private:
	int m_texWidth, m_texHeight;

	ID3D11ShaderResourceView* m_SRVA[g_BUFFER_COUNT], *m_cleanView;	//shaderResourceViewArray
	ID3D11Texture2D* m_RTTA[g_BUFFER_COUNT];	//renderTargetTextureArray
	ID3D11RenderTargetView* m_RTVA[g_BUFFER_COUNT];	//renderTargetViewArray
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11Texture2D* m_depthStencil;
};

#endif