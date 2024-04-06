#pragma once

using namespace std;

struct Header
{
	char _idLength = 0;
	char _colorMapType = 0;
	char _dataTypeCode = 0;
	short _colorMapOrigin = 0;
	short _colorMapLength = 0;
	char _colorMapDepth = 0;
	short _xOrigin = 0;
	short _yOrigin = 0;
	short _imageWidth = 0;
	short _imageHeight = 0;
	char _bitsPerPixel = 0;
	char _imageDescriptor = 0;
};

