#include "ASCIIConvertor.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stdout, "missing arg! convert file is required!");
		exit(1);
	}
	ASCIIConvertor convertor;

	convertor.loadImage(argv[1]);
	if (argc == 3)
	{
		float xStep = std::stof(argv[2]);
		convertor.convert(xStep);
	} 
	else
	{
		convertor.convert();
	}

	return 0;
}