#include "OBJloader.h"

OBJLoader::OBJLoader()
{

}

OBJLoader::~OBJLoader()
{

}

VertexInputType* OBJLoader::LoadObj(int& vertexCount, int& textureCount, int& normalCount, int& faceCount, string fileName)
{
	ifstream fileIn;
	VertexInputType* vertexInput;

	fileIn.open(fileName, ifstream::in);

	vector<XMFLOAT3> vPos;
	vector<XMFLOAT3> vNor;
	vector<XMFLOAT2> vTC;

	vector<UINT> indPos;
	vector<UINT> indNor;
	vector<UINT> indTex;
	bool loop = true;
	char _input;

	if (fileIn.is_open())
	{
		cout << "Open" << endl;
		while (loop)
		{
			_input = fileIn.get();

			switch (_input)
			{

			case '#':
				_input = fileIn.get();
				while (_input != '\n')
					_input = fileIn.get();
				break;
			case 'v':
				_input = fileIn.get();
				if (_input == ' ')
				{
					float fx, fy, fz;
					fileIn >> fx >> fy >> fz;
					vPos.push_back(XMFLOAT3(fx, fy, fz));
					vertexCount++;
				}
				if (_input == 't')
				{
					float txx, txz;
					fileIn >> txx >> txz;
					vTC.push_back(XMFLOAT2(txx, txz));
					textureCount++;
				}
				if (_input == 'n')
				{
					float nx, ny, nz;
					fileIn >> nx >> ny >> nz;
					vNor.push_back(XMFLOAT3(nx, ny, nz));
					normalCount++;

				}
				break;
			case 'f':
				_input = fileIn.get();

				if (_input == ' ')
				{

					while (_input != '\n')
					{

						int indP, indT, indN;

						char pop;

						fileIn >> indP >> pop >> indT >> pop >> indN;

						indNor.push_back(indN);

						indTex.push_back(indT);

						indPos.push_back(indP);

						faceCount++;

						_input = fileIn.get();

					}
				}
				break;
			}

			if (fileIn.fail())
			{
				loop = false;
			}
		}

		vertexInput = new VertexInputType[faceCount * 3];
		for (int i = 0; i < faceCount; i++)
		{
			vertexInput[i].position = vPos[indPos[i] - 1];
			vertexInput[i].uv = vTC[indTex[i] - 1];
			vertexInput[i].normal = vNor[indNor[i] - 1];
		}

		fileIn.close();
		return vertexInput;
	}

	return false;
}

//Rastertek random shit
bool OBJLoader::ReadFileCounts(int& vertexCount, int& textureCount, int& normalCount, int& faceCount, string fileName)
{
	ifstream _file;
	char _input;

	// Initialize the counts.
	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	// Open the file.
	_file.open(fileName);

	// Check if it was successful in opening the file.
	if (_file.fail() == true)
	{
		return false;
	}

	// Read from the file and continue to read until the end of the file is reached.
	_file.get(_input);
	while (!_file.eof())
	{
		// If the line starts with 'v' then count either the vertex, the texture coordinates, or the normal vector.
		if (_input == 'v')
		{
			_file.get(_input);
			if (_input == ' ') 
			{ 
				vertexCount++; 
			}
			else if (_input == 't') 
			{ 
				textureCount++; 
			}
			else if (_input == 'n') 
			{ 
				normalCount++; 
			}
		}	
		else if (_input == 'f') // If the line starts with 'f' then increment the face count.
		{
			_file.get(_input);
			if (_input == ' ') 
			{ 
				faceCount++; 
			}
		}

		// Otherwise read in the remainder of the line.
		while (_input != '\n')
		{
			_file.get(_input);
		}

		// Start reading the beginning of the next line.
		_file.get(_input);
	}

	// Close the file.
	_file.close();

	return true;
}

bool OBJLoader::ReadColourCounts(int& kdCount, int& kaCount, int& tfCount, int& niCount, string fileName)
{
	ifstream _file;
	char _input;

	// Initialize the counts.
	kdCount = 0;
	kaCount = 0;
	tfCount = 0;
	niCount = 0;

	// Open the file.
	_file.open(fileName);

	// Check if it was successful in opening the file.
	if (_file.fail() == true)
	{
		return false;
	}

	// Read from the file and continue to read until the end of the file is reached.
	_file.get(_input);
	while (!_file.eof())
	{
		// If the line starts with 'K' then count either the kd or the ka.
		if (_input == 'K')
		{
			_file.get(_input);
			if (_input == 'd') 
			{ 
				kdCount++; 
			}
			else if (_input == 'a') 
			{ 
				kaCount++; 
			}
		}	
		else if (_input == 'T') // If the line starts with 'T' then increment the tf count.
		{
			_file.get(_input);
			if (_input == 'f') 
			{ 
				tfCount++;
			}
		}
		else if (_input == 'N') // If the line starts with 'N' then increment the ni count.
		{
			_file.get(_input);
			if (_input == 'i')
			{
				niCount++;
			}
		}

		// Otherwise read in the remainder of the line.
		while (_input != '\n')
		{
			_file.get(_input);
		}

		// Start reading the beginning of the next line.
		_file.get(_input);
	}

	// Close the file.
	_file.close();

	return true;
}


//loading color and tex
ID3D11ShaderResourceView* OBJLoader::LoadColour(ID3D11Device* device, ID3D11DeviceContext* deviceContext, string fileName, XMFLOAT3 *RGBDeffuse, XMFLOAT3 *RGBAL, XMFLOAT3 *Tf, XMFLOAT3 *Ni)
{
	ifstream _fin;
	ID3D11ShaderResourceView *_ObjTex = nullptr;
	char _input;
	wstring _TexName;
	int _kdIndex, _kaIndex, _tfIndex, _niIndex;

	// Starts the index at 0
	_kdIndex = 0;
	_kaIndex = 0;
	_tfIndex = 0;
	_niIndex = 0;
	
	_fin.open(fileName);

	// Check if it was successful in opening the file.
	if (_fin.fail() == true)
	{
		return false;
	}

	_fin.get(_input);

	while (!_fin.eof())
	{
		if (_input == 'K')
		{
			_fin.get(_input);

			if (_input == 'd')
			{
				_fin >> RGBDeffuse[_kdIndex].x >> RGBDeffuse[_kdIndex].y >> RGBDeffuse[_kdIndex].z;
				_kdIndex++;
			}

			if (_input == 'a')
			{
				_fin >> RGBAL[_kaIndex].x >> RGBAL[_kaIndex].y >> RGBAL[_kaIndex].z;
				_kaIndex++;
			}
		}
		else if (_input == 'T')
		{
			_fin.get(_input);
			if (_input == 'f')
			{
				_fin >> Tf[_tfIndex].x >> Tf[_tfIndex].y >> Tf[_tfIndex].z;
				_tfIndex++;
			}
		}
		else if (_input == 'N')
		{
			_fin.get(_input);
			if (_input == 'i')
			{
				_fin >> Ni[_niIndex].x;
				_niIndex++;
			}
		}
		else if (_input == 'm')
		{
			_fin.get(_input);
			while (_input != '\n' && _input != 'd')
			{
				_fin.get(_input);
			}
			_fin.get(_input);
			_fin.get(_input);

			while (_input != '\n')
			{
				_TexName += _input;
				_fin.get(_input);
			}

			const wchar_t* _name = _TexName.c_str();

			CreateWICTextureFromFile(device, deviceContext, _name, nullptr, &_ObjTex);
		}

		while (_input != '\n')
		{
			_fin.get(_input);
		}

		_fin.get(_input);
	}
	if (_ObjTex != nullptr)
	{
		return _ObjTex;
	}
	return nullptr;
}

bool OBJLoader::LoadDataStructures(XMFLOAT3 *vertices, XMFLOAT3 *normals, XMFLOAT2 *texcoords, FaceType *faces, string fileName)
{
	ifstream _fin;
	int _vertexIndex, _texcoordIndex, _normalIndex, _faceIndex;
	char _input, _input2;

	// Starts the index at 0
	_vertexIndex = 0;
	_texcoordIndex = 0;
	_normalIndex = 0;
	_faceIndex = 0;

	// Opens the obj
	_fin.open(fileName);

	_fin.get(_input);
	while (!_fin.eof())
	{
		if (_input == 'v')
		{
			_fin.get(_input);

			// Read in the vertices.
			if (_input == ' ')
			{
				_fin >> vertices[_vertexIndex].x >> vertices[_vertexIndex].y >> vertices[_vertexIndex].z;
				_vertexIndex++;
			}// Read in the texture uv coordinates.
			else if (_input == 't')
			{
				_fin >> texcoords[_texcoordIndex].x >> texcoords[_texcoordIndex].y;
				texcoords[_texcoordIndex].y = 1 - texcoords[_texcoordIndex].y;
				_texcoordIndex++;
			}// Read in the normals.
			else if (_input == 'n')
			{
				_fin >> normals[_normalIndex].x >> normals[_normalIndex].y >> normals[_normalIndex].z;
				_normalIndex++;
			}
		}
		else if (_input == 'f') // Read in the faces.
		{
			_fin.get(_input);
			if (_input == ' ')
			{
				_fin >> faces[_faceIndex].vIndex1 >> _input2 >> faces[_faceIndex].tIndex1 >> _input2 >> faces[_faceIndex].nIndex1;
				_fin >> faces[_faceIndex].vIndex2 >> _input2 >> faces[_faceIndex].tIndex2 >> _input2 >> faces[_faceIndex].nIndex2;
				_fin >> faces[_faceIndex].vIndex3 >> _input2 >> faces[_faceIndex].tIndex3 >> _input2 >> faces[_faceIndex].nIndex3;
				_faceIndex++;
			}
		}

		// skips unneeded space
		while (_input != '\n')
		{
			_fin.get(_input);
		}

		// starts reading next line
		_fin.get(_input);
	}

	// Close the file.
	_fin.close();

	return true;
}




//Bullshit
XMFLOAT3* OBJLoader::LoadVertices(int vertexCount, string fileName)
{
	// Initialize vertice structure.
	XMFLOAT3* _vertices = new XMFLOAT3[vertexCount];
	if (!_vertices)
	{
		return false;
	}

	ifstream _fin;
	int _vertexIndex;
	char _input;

	// Starts the index at 0
	_vertexIndex = 0;

	// Opens the obj
	_fin.open(fileName);

	_fin.get(_input);
	while (!_fin.eof())
	{
		if (_input == 'v')
		{
			_fin.get(_input);

			// Read in the vertices.
			if (_input == ' ')
			{
				_fin >> _vertices[_vertexIndex].x >> _vertices[_vertexIndex].y >> _vertices[_vertexIndex].z;
				_vertexIndex++;
			}
		}
		// skips unneeded space
		while (_input != '\n')
		{
			_fin.get(_input);
		}

		// starts reading next line
		_fin.get(_input);
	}
	return _vertices;
}

XMFLOAT3* OBJLoader::LoadNormals(int vertexCount, string fileName)
{
	// Initialize normals structure.
	XMFLOAT3* _normals = new XMFLOAT3[vertexCount];
	if (!_normals)
	{
		return false;
	}

	ifstream _fin;
	int _normalIndex;
	char _input;

	// Starts the index at 0
	_normalIndex = 0;

	// Opens the obj
	_fin.open(fileName);

	_fin.get(_input);
	while (!_fin.eof())
	{
		if (_input == 'v')
		{
			_fin.get(_input);

			// Read in the normals.
			if (_input == 'n')
			{
				_fin >> _normals[_normalIndex].x >> _normals[_normalIndex].y >> _normals[_normalIndex].z;
				_normalIndex++;
			}
		}
		// skips unneeded space
		while (_input != '\n')
		{
			_fin.get(_input);
		}

		// starts reading next line
		_fin.get(_input);
	}
	return _normals;
}

XMFLOAT2* OBJLoader::LoadTexcoords(int vertexCount, string fileName)
{
	// Initialize vertice structure.
	XMFLOAT2* _texcoords = new XMFLOAT2[vertexCount];
	if (!_texcoords)
	{
		return false;
	}

	ifstream _fin;
	int _texcoordIndex;
	char _input;

	// Starts the index at 0
	_texcoordIndex = 0;

	// Opens the obj
	_fin.open(fileName);

	_fin.get(_input);
	while (!_fin.eof())
	{
		if (_input == 'v')
		{
			_fin.get(_input);

			// Read in the texture uv coordinates.
			if (_input == 't')
			{
				_fin >> _texcoords[_texcoordIndex].x >> _texcoords[_texcoordIndex].y;
				_texcoords[_texcoordIndex].y = 1 - _texcoords[_texcoordIndex].y;
				_texcoordIndex++;
			}
		}
		// skips unneeded space
		while (_input != '\n')
		{
			_fin.get(_input);
		}

		// starts reading next line
		_fin.get(_input);
	}
	return _texcoords;
}

FaceType* OBJLoader::LoadFace(int faceCount, string fileName)
{
	// Initialize faces data structures.
	FaceType* _faces = new FaceType[faceCount];
	if (!_faces)
	{
		return false;
	}

	ifstream _fin;
	int _faceIndex;
	char _input, _input2;;

	// Starts the index at 0
	_faceIndex = 0;

	// Opens the obj
	_fin.open(fileName);

	_fin.get(_input);
	while (!_fin.eof())
	{
		// Read in the faces.
		if (_input == 'f')
		{
			_fin.get(_input);
			if (_input == ' ')
			{
				_fin >> _faces[_faceIndex].vIndex1 >> _input2 >> _faces[_faceIndex].tIndex1 >> _input2 >> _faces[_faceIndex].nIndex1;
				_fin >> _faces[_faceIndex].vIndex2 >> _input2 >> _faces[_faceIndex].tIndex2 >> _input2 >> _faces[_faceIndex].nIndex2;
				_fin >> _faces[_faceIndex].vIndex3 >> _input2 >> _faces[_faceIndex].tIndex3 >> _input2 >> _faces[_faceIndex].nIndex3;
				_faceIndex++;
			}
		}
		
		// skips unneeded space
		while (_input != '\n')
		{
			_fin.get(_input);
		}

		// starts reading next line
		_fin.get(_input);
	}
	return _faces;
}