#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Header.h"
#include "Pixel.h"

using namespace std;

struct Image {
	Header header;
	vector<Pixel> pixels;
};

Image readImageFile(string path)
{

	ifstream binImageFile(path, ios_base::binary);
	Image newImage;

	if (!binImageFile.is_open()) {

		// Read in all header file values
		binImageFile.read(&newImage.header._idLength, 1);
		binImageFile.read(&newImage.header._colorMapType, 1);
		binImageFile.read(&newImage.header._dataTypeCode, 1);
		binImageFile.read(reinterpret_cast<char*>(&newImage.header._colorMapOrigin), 2);
		binImageFile.read(reinterpret_cast<char*>(&newImage.header._colorMapLength), 2);
		binImageFile.read(&newImage.header._colorMapDepth, 1);
		binImageFile.read(reinterpret_cast<char*>(&newImage.header._xOrigin), 2);
		binImageFile.read(reinterpret_cast<char*>(&newImage.header._yOrigin), 2);
		binImageFile.read(reinterpret_cast<char*>(&newImage.header._imageWidth), 2);
		binImageFile.read(reinterpret_cast<char*>(&newImage.header._imageHeight), 2);
		binImageFile.read(&newImage.header._bitsPerPixel, 1);
		binImageFile.read(&newImage.header._imageDescriptor, 1);

		

		cout << "Image Color Map Type: " << (int)newImage.header._colorMapType << endl;
		cout << "Image Descriptor: " << (int)newImage.header._imageDescriptor << endl;
		cout << "Image Width: " << newImage.header._imageWidth << endl;
		cout << "Image Height: " << newImage.header._imageHeight << endl;
		cout << "X origin: " << newImage.header._xOrigin << endl;
		cout << "Pixel Depth: " << (int)(newImage.header._bitsPerPixel) << endl;

		for (int i = 0; i < 512 * 512; i++)
		{
			Pixel newPixel;  // Initialize new pixel object

			binImageFile.read(reinterpret_cast<char*>(&newPixel._blueValue), 1);  // Read in pixel data
			binImageFile.read(reinterpret_cast<char*>(&newPixel._greenValue), 1);
			binImageFile.read(reinterpret_cast<char*>(&newPixel._redValue), 1);

			newImage.pixels.push_back(newPixel);  // Add pixel to vector

		}


	}
	else {
		cout << "file can't open to read" << endl;
	}

	return newImage;

}

void writeImageFile(string path, Image& img)
{
	ofstream binImageFile(path, ios_base::binary);

	if (binImageFile.is_open()) {
		
		binImageFile.write(&img.header._idLength, 1);
		binImageFile.write(&img.header._colorMapType, 1);
		binImageFile.write(&img.header._dataTypeCode, 1);
		binImageFile.write(reinterpret_cast<char*>(&img.header._colorMapOrigin), 2);
		binImageFile.write(reinterpret_cast<char*>(&img.header._colorMapLength), 2);
		binImageFile.write(&img.header._colorMapDepth, 1);
		binImageFile.write(reinterpret_cast<char*>(&img.header._xOrigin), 2);
		binImageFile.write(reinterpret_cast<char*>(&img.header._yOrigin), 2);
		binImageFile.write(reinterpret_cast<char*>(&img.header._imageWidth), 2);
		binImageFile.write(reinterpret_cast<char*>(&img.header._imageHeight), 2);
		binImageFile.write(&img.header._bitsPerPixel, 1);
		binImageFile.write(&img.header._imageDescriptor, 1);
		
		for (Pixel& pixel : img.pixels) {
			binImageFile.write(reinterpret_cast<char*>(&pixel._blueValue), 1);  // Write out pixel data
			binImageFile.write(reinterpret_cast<char*>(&pixel._greenValue), 1);
			binImageFile.write(reinterpret_cast<char*>(&pixel._redValue), 1);
		}
	}
	else {
		cout << "Can't open file to write" << endl;
	}

}

int main()
{

	

	Image car = readImageFile("input/layer2.tga");

	cout << "Pixel Num: " << car.pixels.size() << endl;
	cout << car.header._imageHeight << endl;
	//for (Pixel& pixel : imageData) {
	//	pixel._blueValue = 255;
	//	pixel._greenValue = 0;
	//	pixel._redValue = 0;
	//}

	writeImageFile("output/test.tga", car);
	

	return 0;

}
