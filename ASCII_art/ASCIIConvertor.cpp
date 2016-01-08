#include "ASCIIConvertor.h"
#include <fstream>
#include <vector>

int calScale(int scale)
{
	int ret = scale / 25;
	return 9 - (ret >= 10 ? 9 : ret);
}

const char ASCIIConvertor::maps[] = " .,:;ox%#@";

ASCIIConvertor::ASCIIConvertor()
{
	FreeImage_Initialise(true);
}

ASCIIConvertor::~ASCIIConvertor()
{
	FreeImage_DeInitialise();
}

void ASCIIConvertor::loadImage(char *fileName)
{
	if (_bitmap)
	{
		FreeImage_Unload(_bitmap);
		_bitmap = nullptr;
	}
	_fileName = fileName;
	size_t _index = _fileName.find_last_of(".");
	if (_index == std::string::npos)
	{
		fprintf(stdout, "%s is not a validate image file name!\n", fileName);
		return;
	}
	_surfix = _fileName.substr(_index);

	if (_surfix.compare("jpg") || _surfix.compare("jpeg") || _surfix.compare("JPG") || _surfix.compare("JPEG"))
	{
		_bitmap = FreeImage_Load(FIF_JPEG, _fileName.c_str(), JPEG_ACCURATE);
	}
	else if (_surfix.compare("png") || _surfix.compare("PNG"))
	{
		_bitmap = FreeImage_Load(FIF_PNG, _fileName.c_str(), PNG_DEFAULT);
	}
	else if (_surfix.compare("bmp") || _surfix.compare("BMP"))
	{
		_bitmap = FreeImage_Load(FIF_BMP, _fileName.c_str(), BMP_DEFAULT);
	}
}

void ASCIIConvertor::convert(float stepX)
{
	if (_bitmap)
	{
		_bitmap = FreeImage_ConvertToGreyscale(_bitmap);
		int width = FreeImage_GetWidth(_bitmap), height = FreeImage_GetHeight(_bitmap);
		int stepY = height * 1.0 / width * stepX, _stepX = static_cast<int>(ceil(stepX));
		stepY = stepY == 0 ? 1 : stepY;
		std::ofstream file(_fileName.substr(0, _index).append(".txt").c_str());
		char *line = (char*)malloc(width / stepX + 1);
		line[width / _stepX] = '\0';

		int scales = 0;
		for (int y = height / stepY * stepY; y > 0; y -= stepY)
		{
			std::vector<BYTE*> bits(stepY);
			for (int i = 0; i < stepY; ++i)
			{
				bits[i] = (BYTE*)FreeImage_GetScanLine(_bitmap, y - i);
			}
			for (int x = 0; x < width; x++)
			{
				for (int j = 0; j < stepY; ++j)
				{
					scales += bits[j][x];
				}
				if (!(x%_stepX) && !(y%stepY))
				{
					line[x / _stepX] = maps[calScale(scales / _stepX / stepY)];
					scales = 0;
				}
			}
			if (!(y%stepY))
			{
				file << line << '\n';
			}
		}
		free(line);
		file.close();
		FreeImage_Unload(_bitmap);
		_bitmap = nullptr;
	}
}