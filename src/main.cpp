#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Header.h"
#include "Pixel.h"
#include "Image.h"
using namespace std;

void outputImageTest(Image& output, Image& reference, float partNum)
{
	bool testPass = true;  // Set pass test flag to true

	/*---- HEADER TEST ----*/
	if (output._header._idLength != reference._header._idLength) // Check if each header value matches
	{
		cout << "Header ID Length does not match." << endl;
		testPass = false;
	}
	if (output._header._colorMapType != reference._header._colorMapType)
	{
		cout << "Header Color Map Type does not match.";
		testPass = false;
	}
	if (output._header._dataTypeCode != reference._header._dataTypeCode)
	{
		cout << "Header Data Type does not match." << endl;
		testPass = false;
	}
	if (output._header._colorMapOrigin != reference._header._colorMapOrigin) {
		cout << "Header Color Map Origin does not match." << endl;
		testPass = false;
	}
	if (output._header._colorMapLength != reference._header._colorMapLength) {
		cout << "Header Color Map Length does not match." << endl;
		testPass = false;
	}
	if (output._header._colorMapDepth != reference._header._colorMapDepth) {
		cout << "Header Color Map Depth does not match." << endl;
		testPass = false;
	}
	if (output._header._xOrigin != reference._header._xOrigin) {
		cout << "Header xOrigin does not match." << endl;
		testPass = false;
	}
	if (output._header._yOrigin != reference._header._yOrigin) {
		cout << "Header yOrigin does not match." << endl;
		testPass = false;
	}
	if (output._header._imageWidth != reference._header._imageWidth) {
		cout << "Header Image Width does not match." << endl;
		testPass = false;
	}
	if (output._header._imageHeight != reference._header._imageHeight) {
		cout << "Header Image Height does not match." << endl;
		testPass = false;
	}
	if (output._header._bitsPerPixel != reference._header._bitsPerPixel) {
		cout << "Header Bits Per Pixel does not match." << endl;
		cout << "Output bits: " << (float)output._header._bitsPerPixel << endl;
		cout << "Original bits: " << (float)reference._header._bitsPerPixel << endl;
		testPass = false;
	}
	if (output._header._imageDescriptor != reference._header._imageDescriptor) {
		cout << "Header Image Descriptor does not match." << endl;
		testPass = false;
	}

	/*---- PIXEL TEST ----*/
	int i = 0;
	for (Pixel nextPixel : output._pixelVector)
	{
		if (!(nextPixel == reference._pixelVector[i]))
			testPass = false;

		//if (nextPixel._blueValue != reference._pixelVector[i]._blueValue)
		//{
		//	testPass = false;
		//}

		//if (nextPixel._greenValue != reference._pixelVector[i]._greenValue)
		//{
		//	testPass = false;
		//}

		//if (nextPixel._redValue != reference._pixelVector[i]._redValue)
		//{
		//	testPass = false;
		//}
		i++;
	}

	if (testPass == true)
		cout << "Test " << partNum << " passed!" << endl;
	else
		cout << "Test " << partNum << " failed!" << endl;
}

void partOne(string topPath, string bottomPath, string outputPath, string examplePath)
{
	Image topImage(topPath);
	Image bottomImage(bottomPath);
	Image outputImage;
	Image exampleImage(examplePath);

	topImage.multiplyImage(topImage, bottomImage, outputImage);

	outputImage.writeImageFile(outputPath);

	outputImageTest(outputImage, exampleImage, 1);
}

void partTwo(string topPath, string bottomPath, string outputPath, string examplePath)
{
	Image topImage(topPath);
	Image bottomImage(bottomPath);
	Image outputImage;
	Image exampleImage(examplePath);

	topImage.subtractImage(topImage, bottomImage, outputImage);

	outputImage.writeImageFile(outputPath);

	outputImageTest(outputImage, exampleImage, 2);
}

void partThree(string topPath, string bottomPath, string topPathTwo, string outputPath, string examplePath)
{
	Image topImage(topPath);
	Image bottomImage(bottomPath);
	Image topImageTwo(topPathTwo);
	Image outputImage;
	Image exampleImage(examplePath);

	topImage.multiplyImage(topImage, bottomImage, outputImage);
	topImageTwo.screenImage(topImageTwo, outputImage, outputImage);

	outputImage.writeImageFile(outputPath);

	outputImageTest(outputImage, exampleImage, 3);
}

void partFour(string topPath, string bottomPath, string topPathTwo, string outputPath, string examplePath)
{
	Image topImage(topPath);
	Image bottomImage(bottomPath);
	Image topImageTwo(topPathTwo);
	Image outputImage;
	Image exampleImage(examplePath);

	topImage.multiplyImage(topImage, bottomImage, outputImage);
	topImageTwo.subtractImage(topImageTwo, outputImage, outputImage);

	outputImage.writeImageFile(outputPath);

	outputImageTest(outputImage, exampleImage, 4);
}

void partFive(string topPath, string bottomPath, string outputPath, string examplePath)
{
	Image topImage(topPath);
	Image bottomImage(bottomPath);
	Image outputImage;
	Image exampleImage(examplePath);

	topImage.overlayImage(topImage, bottomImage, outputImage);

	outputImage.writeImageFile(outputPath);

	outputImageTest(outputImage, exampleImage, 5);
}

void partSix(string topPath, string outputPath, string examplePath)
{
	Image topImage(topPath);
	Image exampleImage(examplePath);

	topImage.modifyPixel(topImage, 200, 'g', 'a');

	topImage.writeImageFile(outputPath);

	outputImageTest(topImage, exampleImage, 6);
}

void partSeven(string topPath, string outputPath, string examplePath)
{
	Image topImage(topPath);
	Image exampleImage(examplePath);

	topImage.modifyPixel(topImage, 4, 'r', 'm');
	topImage.modifyPixel(topImage, 0, 'b', 'm');

	topImage.writeImageFile(outputPath);

	outputImageTest(topImage, exampleImage, 7);
}

void partEight(string topPath, string outputPath1, string outputPath2, string outputPath3, string examplePath1, string examplePath2, string examplePath3)
{
	Image topImage(topPath);
	Image exampleImage1(examplePath1);
	Image exampleImage2(examplePath2);
	Image exampleImage3(examplePath3);
	Image outputImage;

	topImage.writeChannelImage(topImage, outputImage, 'r');
	outputImage.writeImageFile(outputPath1);
	outputImageTest(outputImage, exampleImage1, 8.1);

	topImage.writeChannelImage(topImage, outputImage, 'g');
	outputImage.writeImageFile(outputPath2);
	outputImageTest(outputImage, exampleImage2, 8.2);

	topImage.writeChannelImage(topImage, outputImage, 'b');
	outputImage.writeImageFile(outputPath3);
	outputImageTest(outputImage, exampleImage3, 8.3);
}

void partNine(string redPath, string greenPath, string bluePath, string outputPath, string examplePath)
{
	Image redImage(redPath);
	Image greenImage(greenPath);
	Image blueImage(bluePath);
	Image exampleImage(examplePath);

	redImage.stitchImage(redImage, greenImage, blueImage);
	redImage.writeImageFile(outputPath);

	outputImageTest(redImage, exampleImage, 9);

}

void partTen(string imagePath, string outputPath, string examplePath)
{
	Image imageFlipped(imagePath);
	Image exampleImage(examplePath);

	imageFlipped.rotateImage(imageFlipped);
	imageFlipped.writeImageFile(outputPath);

	outputImageTest(imageFlipped, exampleImage, 10);
}

void extraCredit(string imagePath1, string imagePath2, string imagePath3, string imagePath4, string outputPath, string examplePath)
{
	Image image1(imagePath1);
	Image image2(imagePath2);
	Image image3(imagePath3);
	Image image4(imagePath4);
	Image outputImage;
	Image exampleImage(examplePath);

	image1.assembleImage(image1, image2, image3, image4, outputImage);

	outputImage.writeImageFile(outputPath);

	outputImageTest(outputImage, exampleImage, 11);
}

int main()
{
	partOne("input/layer1.tga", "input/pattern1.tga", "output/part1.tga", "examples/EXAMPLE_part1.tga");
	partTwo("input/layer2.tga", "input/car.tga", "output/part2.tga", "examples/EXAMPLE_part2.tga");
	partThree("input/layer1.tga", "input/pattern2.tga", "input/text.tga", "output/part3.tga", "examples/EXAMPLE_part3.tga");
	partFour("input/layer2.tga", "input/circles.tga", "input/pattern2.tga", "output/part4.tga", "examples/EXAMPLE_part4.tga");
	partFive("input/layer1.tga", "input/pattern1.tga", "output/part5.tga", "examples/EXAMPLE_part5.tga");
	partSix("input/car.tga", "output/part6.tga", "examples/EXAMPLE_part6.tga");
	partSeven("input/car.tga", "output/part7.tga", "examples/EXAMPLE_part7.tga");
	partEight("input/car.tga", "output/part8_r.tga", "output/part8_g.tga", "output/part8_b.tga", "examples/EXAMPLE_part8_r.tga", "examples/EXAMPLE_part8_g.tga", "examples/EXAMPLE_part8_b.tga");
	partNine("input/layer_red.tga", "input/layer_green.tga", "input/layer_blue.tga", "output/part9.tga", "examples/EXAMPLE_part9.tga");
	partTen("input/text2.tga", "output/part10.tga", "examples/EXAMPLE_part10.tga");
	extraCredit("input/circles.tga", "input/car.tga", "input/text.tga", "input/pattern1.tga", "output/extracredit.tga", "examples/EXAMPLE_extracredit.tga");

	return 0;
}