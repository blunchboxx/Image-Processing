#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Header.h"
#include "Pixel.h"
#include "Image.h"
using namespace std;
using namespace std;

// CONSTRUCTORS
Image::Image()
{
	readImageFile("input/text.tga");
}

Image::Image(string filepath)
{
	readImageFile(filepath);
}

// IMAGE FILE READ & WRITE
void Image::readImageFile(string filepath)
{
	// Open binary file
	ifstream binImageFile(filepath, ios_base::binary);

	if (binImageFile.is_open())
	{
		// Read in all header file values
		binImageFile.read(&_header._idLength, 1);
		binImageFile.read(&_header._colorMapType, 1);
		binImageFile.read(&_header._dataTypeCode, 1);
		binImageFile.read(reinterpret_cast<char*>(&_header._colorMapOrigin), 2);
		binImageFile.read(reinterpret_cast<char*>(&_header._colorMapLength), 2);
		binImageFile.read(&_header._colorMapDepth, 1);
		binImageFile.read(reinterpret_cast<char*>(&_header._xOrigin), 2);
		binImageFile.read(reinterpret_cast<char*>(&_header._yOrigin), 2);
		binImageFile.read(reinterpret_cast<char*>(&_header._imageWidth), 2);
		binImageFile.read(reinterpret_cast<char*>(&_header._imageHeight), 2);
		binImageFile.read(&_header._bitsPerPixel, 1);
		binImageFile.read(&_header._imageDescriptor, 1);

		for (int i = 0; i < (_header._imageHeight * _header._imageWidth); i++)
		{
			Pixel newPixel;  // Initialize new pixel object

			binImageFile.read(reinterpret_cast<char*>(&newPixel._blueValue), 1);  // Read in pixel data
			binImageFile.read(reinterpret_cast<char*>(&newPixel._greenValue), 1);
			binImageFile.read(reinterpret_cast<char*>(&newPixel._redValue), 1);

			newPixel.setNorm();

			_pixelVector.push_back(newPixel);  // Add pixel to vector
		}
	}
	else
	{
		cout << "Invalid image file path: " << filepath << endl;
	}
}

void Image::writeImageFile(string filepath)
{
	ofstream binImageFile(filepath, ios_base::binary);

	if (binImageFile.is_open())
	{
		binImageFile.write(&_header._idLength, 1);
		binImageFile.write(&_header._colorMapType, 1);
		binImageFile.write(&_header._dataTypeCode, 1);
		binImageFile.write(reinterpret_cast<char*>(&_header._colorMapOrigin), 2);
		binImageFile.write(reinterpret_cast<char*>(&_header._colorMapLength), 2);
		binImageFile.write(&_header._colorMapDepth, 1);
		binImageFile.write(reinterpret_cast<char*>(&_header._xOrigin), 2);
		binImageFile.write(reinterpret_cast<char*>(&_header._yOrigin), 2);
		binImageFile.write(reinterpret_cast<char*>(&_header._imageWidth), 2);
		binImageFile.write(reinterpret_cast<char*>(&_header._imageHeight), 2);
		binImageFile.write(&_header._bitsPerPixel, 1);
		binImageFile.write(&_header._imageDescriptor, 1);


		for (Pixel& nextPixel : _pixelVector)
		{
			binImageFile.write(reinterpret_cast<char*>(&nextPixel._blueValue), 1);  // Write out pixel data
			binImageFile.write(reinterpret_cast<char*>(&nextPixel._greenValue), 1);
			binImageFile.write(reinterpret_cast<char*>(&nextPixel._redValue), 1);
		}
	}
	else
	{
		cout << "Can't open file to write." << endl;
	}
}

// BLENDING OPERATION FUNCTIONS
int Image::clampValue(int value, int min, int max)
{
	if (value < 0)
		return 0;
	else if (value > 255)
		return 255;
	else
		return value;
}

void Image::writeChannelImage(Image& image, Image& output, char channel)
{
	int pixelCount = 0;

	if (channel == 'r')  // Red channel loop
	{
		for (Pixel& nextPixel : image._pixelVector)
		{
			output._pixelVector[pixelCount]._redValue = nextPixel._redValue;
			output._pixelVector[pixelCount]._blueValue = nextPixel._redValue;
			output._pixelVector[pixelCount]._greenValue = nextPixel._redValue;
			image._pixelVector[pixelCount].setNorm();
			pixelCount++;
		}
	}

	if (channel == 'g')  // Green channel loop
	{
		for (Pixel& nextPixel : image._pixelVector)
		{
			output._pixelVector[pixelCount]._redValue = nextPixel._greenValue;
			output._pixelVector[pixelCount]._blueValue = nextPixel._greenValue;
			output._pixelVector[pixelCount]._greenValue = nextPixel._greenValue;
			image._pixelVector[pixelCount].setNorm();
			pixelCount++;
		}
	}

	if (channel == 'b')  // Blue channel loop
	{
		for (Pixel& nextPixel : image._pixelVector)
		{
			output._pixelVector[pixelCount]._redValue = nextPixel._blueValue;
			output._pixelVector[pixelCount]._blueValue = nextPixel._blueValue;
			output._pixelVector[pixelCount]._greenValue = nextPixel._blueValue;
			image._pixelVector[pixelCount].setNorm();
			pixelCount++;
		}
	}
}

void Image::stitchImage(Image& redChannel, Image& greenChannel, Image& blueChannel)
{

	for (unsigned int pixelCount = 0; pixelCount < redChannel._pixelVector.size(); pixelCount++)
	{
		redChannel._pixelVector[pixelCount]._greenValue = greenChannel._pixelVector[pixelCount]._greenValue;
		redChannel._pixelVector[pixelCount]._blueValue = blueChannel._pixelVector[pixelCount]._blueValue;
		redChannel._pixelVector[pixelCount].setNorm();
	}
}

void Image::rotateImage(Image& image)
{
	reverse(image._pixelVector.begin(), image._pixelVector.end());  // Swap first and last pixel positions throughout image
}

void Image::assembleImage(Image& image1, Image& image2, Image& image3, Image& image4, Image& outputImage)
{
	outputImage._pixelVector.clear();
	outputImage._header._imageHeight = 1024;
	outputImage._header._imageWidth = 1024;

	unsigned int pixelCount1 = 0;
	unsigned int pixelCount2 = 0;
	unsigned int pixelCount3 = 0;
	unsigned int pixelCount4 = 0;

	for (unsigned int row = 0; row < 1024; row++)
	{
		if (row < 512)
		{					
			for (unsigned int col = 0; col < 1024; col++)
			{
				if (col < 512)
				{
					outputImage._pixelVector.push_back(image3._pixelVector[pixelCount1]);
					pixelCount1++;
				}
				else if (col >= 512)
				{
					outputImage._pixelVector.push_back(image4._pixelVector[pixelCount2]);
					pixelCount2++;
				}
			}
		}
		else if (row >= 512)
		{
			for (unsigned int col = 0; col < 1024; col++)
			{
				if (col < 512)
				{
					outputImage._pixelVector.push_back(image2._pixelVector[pixelCount3]);
					pixelCount3++;
				}
				else if (col >= 512)
				{
					outputImage._pixelVector.push_back(image1._pixelVector[pixelCount4]);
					pixelCount4++;
				}
			}
		}
	}
}

void Image::modifyPixel(Image& image, int adjustment, char channel, char operation)
{
	int pixelCount = 0;

	if (operation == 'a')  // Addition loop
	{
		if (channel == 'r')  // Red channel loop
		{
			for (Pixel& nextPixel : image._pixelVector)
			{
				image._pixelVector[pixelCount]._redValue = clampValue(nextPixel._redValue + adjustment);
				image._pixelVector[pixelCount].setNorm();
				pixelCount++;
			}
		}
		else if (channel == 'g')  // Green channel loop
		{
			for (Pixel& nextPixel : image._pixelVector)
			{
				image._pixelVector[pixelCount]._greenValue = clampValue(nextPixel._greenValue + adjustment);
				image._pixelVector[pixelCount].setNorm();
				pixelCount++;
			}
		}
		else if (channel == 'b')  // Blue channel loop
		{
			for (Pixel& nextPixel : image._pixelVector)
			{
				image._pixelVector[pixelCount]._blueValue = clampValue(nextPixel._blueValue + adjustment);
				image._pixelVector[pixelCount].setNorm();
				pixelCount++;
			}
		}
	}

	if (operation == 's')  // Subtraction loop
	{
		if (channel == 'r')  // Red channel loop
		{
			for (Pixel& nextPixel : image._pixelVector)
			{
				image._pixelVector[pixelCount]._redValue = clampValue(nextPixel._redValue - adjustment);
				image._pixelVector[pixelCount].setNorm();
				pixelCount++;
			}
		}
		else if (channel == 'g')  // Green channel loop
		{
			for (Pixel& nextPixel : image._pixelVector)
			{
				image._pixelVector[pixelCount]._greenValue = clampValue(nextPixel._greenValue - adjustment);
				image._pixelVector[pixelCount].setNorm();
				pixelCount++;
			}
		}
		else if (channel == 'b')  // Blue channel loop
		{
			for (Pixel& nextPixel : image._pixelVector)
			{
				image._pixelVector[pixelCount]._blueValue = clampValue(nextPixel._blueValue - adjustment);
				image._pixelVector[pixelCount].setNorm();
				pixelCount++;
			}
		}
	}

	if (operation == 'm')  // Scale or multiply loop
	{
		if (channel == 'r')  // Red channel loop
		{
			for (Pixel& nextPixel : image._pixelVector)
			{
				image._pixelVector[pixelCount]._redValue = clampValue(nextPixel._redValue * adjustment);
				image._pixelVector[pixelCount].setNorm();
				pixelCount++;
			}
		}
		else if (channel == 'g')  // Green channel loop
		{
			for (Pixel& nextPixel : image._pixelVector)
			{
				image._pixelVector[pixelCount]._greenValue = clampValue(nextPixel._greenValue * adjustment);
				image._pixelVector[pixelCount].setNorm();
				pixelCount++;
			}
		}
		else if (channel == 'b')  // Blue channel loop
		{
			for (Pixel& nextPixel : image._pixelVector)
			{
				image._pixelVector[pixelCount]._blueValue = clampValue(nextPixel._blueValue * adjustment);
				image._pixelVector[pixelCount].setNorm();
				pixelCount++;
			}
		}
	}
}

void Image::multiplyImage(Image& topLayer, Image& bottomLayer, Image& outputLayer)
{
	int pixelCount = 0;

	for (Pixel& nextPixel : topLayer._pixelVector)
	{
		outputLayer._pixelVector[pixelCount]._blueValue = (unsigned char)((((float)nextPixel._blueValue * (float)bottomLayer._pixelVector[pixelCount]._blueValue) / 255.0f) + 0.5f);
		outputLayer._pixelVector[pixelCount]._redValue = (unsigned char)((((float)nextPixel._redValue * (float)bottomLayer._pixelVector[pixelCount]._redValue) / 255.0f) + 0.5f);
		outputLayer._pixelVector[pixelCount]._greenValue = (unsigned char)((((float)nextPixel._greenValue * (float)bottomLayer._pixelVector[pixelCount]._greenValue) / 255.0f) + 0.5f);

		outputLayer._pixelVector[pixelCount].setNorm();

		pixelCount++;
	}
}

void Image::screenImage(Image& topLayer, Image& bottomLayer, Image& outputLayer)
{
	int pixelCount = 0;
		
	for (Pixel& nextPixel : topLayer._pixelVector)
	{	
		outputLayer._pixelVector[pixelCount]._blueValue = (unsigned char)((255.0 * (1.0f - (1.0f - nextPixel._blueValueNorm) * (1.0f - bottomLayer._pixelVector[pixelCount]._blueValueNorm))) + 0.5f);
		outputLayer._pixelVector[pixelCount]._redValue = (unsigned char)((255.0 * (1.0f - (1.0f - nextPixel._redValueNorm) * (1.0f - bottomLayer._pixelVector[pixelCount]._redValueNorm))) + 0.5f);
		outputLayer._pixelVector[pixelCount]._greenValue = (unsigned char)((255.0 * (1.0f - (1.0f - nextPixel._greenValueNorm) * (1.0f - bottomLayer._pixelVector[pixelCount]._greenValueNorm))) + 0.5f);
		pixelCount++;
	}
}

void Image::overlayImage(Image& topLayer, Image& bottomLayer, Image& outputLayer)
{
	int pixelCount = 0;

	for (Pixel& nextPixel : bottomLayer._pixelVector)
	{
		if (nextPixel._blueValue < 128)
		{
			nextPixel.muliplyPixel(topLayer._pixelVector[pixelCount], nextPixel, outputLayer._pixelVector[pixelCount], 'b');
		}
		else 
		{
			nextPixel.screenPixel(topLayer._pixelVector[pixelCount], nextPixel, outputLayer._pixelVector[pixelCount], 'b');
		}

		if (nextPixel._greenValue < 128)
		{
			nextPixel.muliplyPixel(topLayer._pixelVector[pixelCount], nextPixel, outputLayer._pixelVector[pixelCount], 'g');
		}
		else
		{
			nextPixel.screenPixel(topLayer._pixelVector[pixelCount], nextPixel, outputLayer._pixelVector[pixelCount], 'g');
		}

		if (nextPixel._redValue < 128)
		{
			nextPixel.muliplyPixel(topLayer._pixelVector[pixelCount], nextPixel, outputLayer._pixelVector[pixelCount], 'r');
		}
		else
		{
			nextPixel.screenPixel(topLayer._pixelVector[pixelCount], nextPixel, outputLayer._pixelVector[pixelCount], 'r');
		}

		pixelCount++;
	}
}

void Image::subtractImage(Image& topLayer, Image& bottomLayer, Image& outputLayer)
{
	int pixelCount = 0;

	for (Pixel& nextPixel : topLayer._pixelVector)
	{
		outputLayer._pixelVector[pixelCount]._blueValue = (unsigned char)(clampValue((int)bottomLayer._pixelVector[pixelCount]._blueValue - (int)nextPixel._blueValue));
		outputLayer._pixelVector[pixelCount]._redValue = (unsigned char)(clampValue((int)bottomLayer._pixelVector[pixelCount]._redValue - (int)nextPixel._redValue));
		outputLayer._pixelVector[pixelCount]._greenValue = (unsigned char)(clampValue((int)bottomLayer._pixelVector[pixelCount]._greenValue - (int)nextPixel._greenValue));

		outputLayer._pixelVector[pixelCount].setNorm();

		pixelCount++;
	}
}

void Image::addImage(Image& topLayer, Image& bottomLayer, Image& outputLayer)
{
	int pixelCount = 0;

	for (Pixel& nextPixel : topLayer._pixelVector)
	{
		outputLayer._pixelVector[pixelCount]._blueValue = (unsigned char)(clampValue((int)bottomLayer._pixelVector[pixelCount]._blueValue + (int)nextPixel._blueValue));
		outputLayer._pixelVector[pixelCount]._redValue = (unsigned char)(clampValue((int)bottomLayer._pixelVector[pixelCount]._redValue + (int)nextPixel._redValue));
		outputLayer._pixelVector[pixelCount]._greenValue = (unsigned char)(clampValue((int)bottomLayer._pixelVector[pixelCount]._greenValue + (int)nextPixel._greenValue));

		outputLayer._pixelVector[pixelCount].setNorm();

		pixelCount++;
	}
}