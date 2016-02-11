#ifndef TEXTCLASS_H
#define TEXTCLASS_H
#include "Graphics/FontClass.h"
#include "Graphics/ShaderHandler.h"

class TextClass
{
	//Functions
private:
	struct SentenceType
	{
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		float red, green, blue;
	};
	struct VertexType
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texture;
	};

	bool InitializeSentence(SentenceType** sentence, int maxLength, ID3D11Device* device);
	bool UpdateSentence(SentenceType* sentence, char* text, int positionX, int positionY, float red, float green, float blue, ID3D11DeviceContext* deviceContext);
	void ReleaseSentence(SentenceType** sentence);
	bool RenderSentence(ID3D11DeviceContext* deviceContext, SentenceType* sentence, DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX orthoMatrix);
protected:
public:
	TextClass();
	~TextClass();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND hWnd, int screenWidth, int screenHeight, DirectX::XMMATRIX baseViewMatrix);
	void ShutDown();
	bool Render(ID3D11DeviceContext* deviceContext, DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX orthoMatrix);

	//Variables
private:
	FontClass* m_font;
	ShaderHandler* m_shader;
	int m_screenWidth;
	int m_screenHeight;
	DirectX::XMMATRIX m_baseViewMatrix;

	SentenceType* m_sentence1;
	SentenceType* m_sentence2;
protected:
public:

};

#endif TEXTCLASS_H
