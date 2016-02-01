#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <iostream>
#include <vector>
#include <d3dcompiler.h>
#include "WICTextureLoader.h"
using namespace std;
using namespace DirectX;


typedef struct
{
	int vIndex1, vIndex2, vIndex3;
	int tIndex1, tIndex2, tIndex3;
	int nIndex1, nIndex2, nIndex3;
}FaceType;

typedef struct
{
	XMFLOAT3 position;
	XMFLOAT2 uv;
	XMFLOAT3 normal;
}VertexInputType;

class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();
	VertexInputType* LoadObj(int& vertexCount, int& textureCount, int& normalCount, int& faceCount, string fileName);
	bool ReadFileCounts(int& vertexCount, int& textureCount, int& normalCount, int& faceCount, string fileName);
	bool ReadColourCounts(int& vertexCount, int& textureCount, int& normalCount, int& faceCount, string fileName);
	XMFLOAT3* LoadVertices(int vertexCount, string fileName);
	XMFLOAT3* LoadNormals(int textureCount, string fileName);
	XMFLOAT2* LoadTexcoords(int normalCount, string fileName);
	FaceType* LoadFace(int faceCount, string fileName);
	bool LoadDataStructures(XMFLOAT3 *vertices, XMFLOAT3 *normals, XMFLOAT2 *texcoords, FaceType *faces, string fileName);
	bool LoadColour(ID3D11Device* device, ID3D11DeviceContext* deviceContext, string fileName, ID3D11ShaderResourceView* ObjTex, XMFLOAT3 *RGBDeffuse, XMFLOAT3 *RGBAL, XMFLOAT3 *Tf, XMFLOAT3 *Ni);
};

#endif