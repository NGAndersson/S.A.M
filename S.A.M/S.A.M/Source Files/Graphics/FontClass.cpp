#include "Graphics/FontClass.h"

FontClass::FontClass()
{

}

FontClass::~FontClass()
{

}

bool FontClass::Initialize(ID3D11Device* device)
{
	//load the file containing the font data
	bool result = LoadFontData();
	if (!result)
	{
		return false;
	}
	//load the file containing the font texture
	result = LoadTexture(device);
	if (!result)
	{
		return false;
	}
	return true;
}

void FontClass::ShutDown()
{
	//Release font texture
	ReleaseTexture();

	//Release font data
	ReleaseFontData();
}

bool FontClass::LoadFontData()
{
	//Open the file with the font data
	fin.open("../../Resources/Fonts/Font03.fnt");
	if (fin.fail())
		return false;

	//Parse the font data file and save the information in a struct array
	ParseFont(fin, m_charSet);

	fin.close();

	return true;
}

void FontClass::ReleaseFontData()
{
	delete[] m_charSet.Chars;
}

bool FontClass::ParseFont(std::istream& stream, CharSet& charSetDesc)
{
	std::string Line;
	std::string Read, Key, Value;
	std::size_t i;
	while (!stream.eof())
	{
		std::stringstream LineStream;
		std::getline(stream, Line);
		LineStream << Line;

		//read the line's type
		LineStream >> Read;
		if (Read == "common")
		{
			//this holds common data
			while (!LineStream.eof())
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find('=');
				Key = Read.substr(0, i);
				Value = Read.substr(i + 1);

				//assign the correct value
				Converter << Value;
				if (Key == "lineHeight")
					Converter >> charSetDesc.LineHeight;
				else if (Key == "base")
					Converter >> charSetDesc.Base;
				else if (Key == "scaleW")
					Converter >> charSetDesc.Width;
				else if (Key == "scaleH")
					Converter >> charSetDesc.Height;
				else if (Key == "pages")
					Converter >> charSetDesc.Pages;
			}
		}
		else if (Read == "char")
		{
			//this is data for a specific char
			unsigned short CharID = 0;

			while (!LineStream.eof())
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find('=');
				Key = Read.substr(0, i);
				Value = Read.substr(i + 1);

				//assign the correct value
				Converter << Value;
				if (Key == "id")
					Converter >> CharID;
				else if (Key == "x")
					Converter >> charSetDesc.Chars[CharID].x;
				else if (Key == "y")
					Converter >> charSetDesc.Chars[CharID].y;
				else if (Key == "width")
					Converter >> charSetDesc.Chars[CharID].Width;
				else if (Key == "height")
					Converter >> charSetDesc.Chars[CharID].Height;
				else if (Key == "xoffset")
					Converter >> charSetDesc.Chars[CharID].XOffset;
				else if (Key == "yoffset")
					Converter >> charSetDesc.Chars[CharID].YOffset;
				else if (Key == "xadvance")
					Converter >> charSetDesc.Chars[CharID].XAdvance;
				else if (Key == "page")
					Converter >> charSetDesc.Chars[CharID].Page;
				else if (Key == "chnl")
					Converter >> charSetDesc.Chars[CharID].Channel;
			}
		}
	}

	return true;
}

bool FontClass::LoadTexture(ID3D11Device* device)
{
	
	HRESULT _hResult;
	
	//Open the font texture file
	_hResult = DirectX::CreateDDSTextureFromFile(device, L"../../Resources/Fonts/Font03_0.dds", NULL, &m_textureResourceView);

	if (FAILED(_hResult))
		return false;
	else
		return true;
}

void FontClass::ReleaseTexture()
{
	if (m_textureResourceView)
	{
		delete m_textureResourceView;
		m_textureResourceView = nullptr;
	}
}

ID3D11ShaderResourceView* FontClass::GetTexture()
{
	return m_textureResourceView;
}

void FontClass::BuildVertexArray(void* vertices, char* sentence, float drawX, float drawY)
{
	VertexType* _vertexType;
	int numLetters, index, i, letter;

	numLetters = (int)strlen(sentence);

	index = 0;

	for (i = 0; i < numLetters; i++)
	{
		letter = ((int)sentence[i]) - 32;

		if (letter == 0)
		{
			drawX += 3.0f;
		}
		else
		{
			//First Triangle in quad
			_vertexType[index].position = DirectX::XMFLOAT3(drawX, drawY, 0.0f); //Top Left
			_vertexType[index].texture = DirectX::XMFLOAT2(m_charSet.Chars[letter].x, 0.0f);
			index++;

			_vertexType[index].position = DirectX::XMFLOAT3((drawX + m_charSet.Chars[letter].Width), (drawY - m_charSet.Chars[letter].Height), 0.0f); //Bottom Right
			_vertexType[index].texture = DirectX::XMFLOAT2((m_charSet.Chars[letter].x + m_charSet.Chars[letter].Width), 1.0f);
			index++;

			_vertexType[index].position = DirectX::XMFLOAT3(drawX, (drawY - m_charSet.Chars[letter].Height), 0.0f); //Bottom Left
			_vertexType[index].texture = DirectX::XMFLOAT2(m_charSet.Chars[letter].x, 1.0f);
			index++;

			//Second Triangle in quad
			_vertexType[index].position = DirectX::XMFLOAT3(drawX, drawY, 0.0f); //Top Left
			_vertexType[index].texture = DirectX::XMFLOAT2(m_charSet.Chars[letter].x, 0.0f);
			index++;

			_vertexType[index].position = DirectX::XMFLOAT3((drawX + m_charSet.Chars[letter].Width), drawY, 0.0f); //Top Right
			_vertexType[index].texture = DirectX::XMFLOAT2((m_charSet.Chars[letter].x + m_charSet.Chars[letter].Width), 0.0f);
			index++;

			_vertexType[index].position = DirectX::XMFLOAT3((drawX + m_charSet.Chars[letter].Width), (drawY - m_charSet.Chars[letter].Height), 0.0f); //Bottom Right
			_vertexType[index].texture = DirectX::XMFLOAT2((m_charSet.Chars[letter].x + m_charSet.Chars[letter].Width), 1.0f);
			index++;

			//Update drawX location to draw the next letter at the next place in the sentence
			drawX = drawX + m_charSet.Chars[letter].Width + 1.0f;

		}
	}
	return;
}