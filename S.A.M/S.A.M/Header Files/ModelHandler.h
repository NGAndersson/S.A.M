#ifndef _MODELHANDLER_H_
#define _MODELHANDLER_H_

#include "OBJloader.h"
#include "ShaderHandler.h"



class ModelHandler
{
private:
	struct OBJColourType
	{
		XMFLOAT3 Deffuse;
		XMFLOAT3 Albi;
		XMFLOAT3 Tf;
		XMFLOAT3 Ni;
	};
public:
	ModelHandler();
	~ModelHandler();
	bool LoadOBJData(string OBJFileName, string colourFileName, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	bool LoadOBJData2(string OBJFileName, string colourFileName, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	bool CreateBuffers(ID3D11Device* device);
	bool CreateBuffers2(ID3D11Device* device);
	bool CreateShaders(ID3D11Device* device, string vertexFile, string geometryFile, string pixelFile);
	bool CreateShadersCompute(ID3D11Device* device, string vertexFile, string geometryFile, string pixelFile, string computeFile);
	bool SetShaders(ID3D11DeviceContext* deviceContext);
	bool SetBuffers(ID3D11DeviceContext* deviceContext);
	int GetVertexCount();

private:
	XMFLOAT3* m_vertices,* m_normals, *m_RGBDeffuse, *m_RGBAL, *m_Tf, *m_Ni;
	XMFLOAT2* m_texcoords;
	int m_vertexCount, m_textureCount, m_normalCount, m_faceCount, m_kdCount, m_kaCount, m_tfCount, m_niCount;
	FaceType* m_faces;
	OBJLoader m_OBJLoad;
	ShaderHandler m_shaderLoad;
	ID3D11Buffer* m_vertexBuffer, *m_OBJColourBuffer;
	ID3D11ShaderResourceView* m_ObjTex;
	ID3D11SamplerState* m_sampleState;
	VertexInputType* m_vertexInput;
};

#endif
