#ifndef TEXTCLASS_H
#define TEXTCLASS_H
#include <Windows.h>
#include <string>
#include <iostream>
#include <sstream>



class TextClass
{
	//Functions
private:
protected:
public:


	TextClass();
	~TextClass();
	bool ParseFont(std::istream& stream, TextClass::CharSet& charSetDesc);

	//Variables
private:
protected:
public:


};

#endif TEXTCLASS_H
