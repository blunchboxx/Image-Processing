#include <vector>
#include "Header.h"
#include "Pixel.h"
#pragma once


struct Image
{
	Header _header;
	vector<Pixel> _pixelVector;

	// Constructors
	Image();
	Image(string filepath);

	// Image read and write
	void readImageFile(string filepath);
	void writeImageFile(string filepath);

	// Blending Operations
	void multiplyImage(Image& topLayer, Image& bottomLayer, Image& outputLayer);
	void screenImage(Image& topLayer, Image& bottomLayer, Image& outputLayer);
	void overlayImage(Image& topLayer, Image& bottomLayer, Image& outputLayer);
	void subtractImage(Image& topLayer, Image& bottomLayer, Image& outputLayer);
	void addImage(Image& topLayer, Image& bottomLayer, Image& outputLayer);
	void modifyPixel(Image& image, int adjustment, char channel, char operation);
	void writeChannelImage(Image& image, Image& output, char channel);
	void stitchImage(Image& redChannel, Image& greenChannel, Image& blueChannel);
	void rotateImage(Image& image);
	void assembleImage(Image& image1, Image& image2, Image& image3, Image& image4, Image& outputImage);
	int clampValue(int value, int min = 0, int max = 255);
};

