#pragma once

#ifndef __LOADED_FREE_IMAGE__
#define __LOADED_FREE_IMAGE__
#include "FreeImage.h"
#endif

#include <string>
class ASCIIConvertor
{
public:
	explicit ASCIIConvertor();

	virtual ~ASCIIConvertor();

	void loadImage(char *fileName);

	void convert(float stepX = 4.0f);

private:
	std::string _fileName;

	std::string _surfix;

	size_t _index{ std::string::npos };

	FIBITMAP *_bitmap{ nullptr };

	static const char maps[];
};
