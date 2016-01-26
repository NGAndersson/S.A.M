#include "OBJloader.h"

OBJLoader::OBJLoader()
{

}

OBJLoader::~OBJLoader()
{

}

bool OBJLoader::ReadFileCounts(int& vertexCount, int& textureCount, int& normalCount, int& faceCount, string fileName)
{
	ifstream file;
	char input;

	// Initialize the counts.
	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	// Open the file.
	file.open(fileName);

	// Check if it was successful in opening the file.
	if (file.fail() == true)
	{
		return false;
	}

	// Read from the file and continue to read until the end of the file is reached.
	file.get(input);
	while (!file.eof())
	{
		// If the line starts with 'v' then count either the vertex, the texture coordinates, or the normal vector.
		if (input == 'v')
		{
			file.get(input);
			if (input == ' ') { vertexCount++; }
			if (input == 't') { textureCount++; }
			if (input == 'n') { normalCount++; }
		}

		// If the line starts with 'f' then increment the face count.
		if (input == 'f')
		{
			file.get(input);
			if (input == ' ') { faceCount++; }
		}

		// Otherwise read in the remainder of the line.
		while (input != '\n')
		{
			file.get(input);
		}

		// Start reading the beginning of the next line.
		file.get(input);
	}

	// Close the file.
	file.close();

	return true;
}

bool OBJLoader::LoadColour(ID3D11Device* gDevice, ID3D11DeviceContext* gDeviceContext, string fileName, ID3D11ShaderResourceView &ObjTex, XMFLOAT3 RGBDeffuse, XMFLOAT3 RGBAL, XMFLOAT3 Tf, XMFLOAT3 Ni)
{
	ifstream _fin;
	char _input;
	wstring _TexName;
	
	_fin.open(fileName);

	_fin.get(_input);

	while (!_fin.eof())
	{
		if (_input == 'K')
		{
			_fin.get(_input);

			if (_input == 'd')
			{
				_fin >> RGBDeffuse.x >> RGBDeffuse.y >> RGBDeffuse.z;
			}

			if (_input == 'a')
			{
				_fin >> RGBAL.x >> RGBAL.y >> RGBAL.z;
			}
		}

		if (_input == 'T')
		{
			if (_input == 'f')
			{
				_fin >> Tf.x >> Tf.y >> Tf.z;
			}
		}

		if (_input == 'N')
		{
			if (_input == 'i')
			{
				_fin >> Ni.x >> Ni.y >> Ni.z;
			}
		}

		if (_input == 'm')
		{
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

			CreateWICTextureFromFile(gDevice, gDeviceContext, _name, nullptr, &ObjTex);
		}

		while (_input != '\n')
		{
			_fin.get(_input);
		}

		_fin.get(_input);
	}
	return true;
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
			}

			// Read in the texture uv coordinates.
			if (_input == 't')
			{
				_fin >> texcoords[_texcoordIndex].x >> texcoords[_texcoordIndex].y;
				texcoords[_texcoordIndex].y = 1 - texcoords[_texcoordIndex].y;
				_texcoordIndex++;
			}

			// Read in the normals.
			if (_input == 'n')
			{
				_fin >> normals[_normalIndex].x >> normals[_normalIndex].y >> normals[_normalIndex].z;
				_normalIndex++;
			}
		}

		// Read in the faces.
		if (_input == 'f')
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