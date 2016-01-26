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

class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();
	bool ReadFileCounts(int&, int&, int&, int&, string);
	XMFLOAT3* LoadVertices(int, string);
	XMFLOAT3* LoadNormals(int, string);
	XMFLOAT2* LoadTexcoords(int, string);
	FaceType* LoadFace(int, string);
	bool LoadDataStructures(XMFLOAT3 *, XMFLOAT3 *, XMFLOAT2 *, FaceType *, string);
	bool LoadColour(ID3D11Device*, ID3D11DeviceContext*, string, ID3D11ShaderResourceView&, XMFLOAT3, XMFLOAT3, XMFLOAT3, XMFLOAT3);
};

#endif