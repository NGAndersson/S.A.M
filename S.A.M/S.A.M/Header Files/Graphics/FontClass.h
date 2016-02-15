#ifndef FONTCLASS_H
#define FONTCLASS_H
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>
#include <sstream>
#include <DDSTextureLoader.h>

class FontClass
{
	//Functions
private:
	struct CharDescriptor
	{
		//clean 16 bytes
		float x, y;
		float Width, Height;
		float XOffset, YOffset;
		float XAdvance;
		float Page;
		float Channel;

		CharDescriptor() : x(0), y(0), Width(0), Height(0), XOffset(0), YOffset(0),
			XAdvance(0), Page(0)
		{ }
	};

	struct CharSet
	{
		unsigned short LineHeight;
		unsigned short Base;
		unsigned short Width, Height;
		unsigned short Pages;
		CharDescriptor Chars[64];
	};

	bool LoadFontData(char* fontFileName);
	void ReleaseFontData();
	bool LoadTexture();
	void ReleaseTexture();
	
	bool ParseFont(std::istream& stream, CharSet& charSetDesc);
protected:
public:
	FontClass();
	FontClass(const FontClass& other);
	~FontClass();

	bool Initialize(ID3D11Device* device, char* fontFileName, WCHAR* textureFileName);
	void ShutDown();

	ID3D11ShaderResourceView* GetTexture();

	void BuildVertexArray(void* vertices, char* sentence, float drawX, float drawY);

	//Variables
private:
	CharSet m_charSet;
	std::ifstream fin;
protected:
public:

};

#endif FONTCLASS_H