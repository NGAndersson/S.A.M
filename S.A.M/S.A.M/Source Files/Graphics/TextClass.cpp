#include "Graphics/TextClass.h"

TextClass::TextClass()
{
	
}

TextClass::~TextClass()
{

}

bool TextClass::ParseFont(std::istream& stream, TextClass::CharSet& charSetDesc)
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