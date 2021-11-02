#include <fstream>
#include <iostream>
#include "TGA.h"
using namespace std;

Tga::Tga(string filePath) {
    ifstream file(filePath, ios_base::binary);

    Header headerObj;
    // Read header (18 bytes)
    file.read(&headerObj.idLength, sizeof(headerObj.idLength));
    file.read(&headerObj.colorMapType, sizeof(headerObj.colorMapType));
    file.read(&headerObj.dataTypeCode, sizeof(headerObj.dataTypeCode));
    file.read((char*)&headerObj.colorMapOrigin, sizeof(headerObj.colorMapOrigin));
    file.read((char*)&headerObj.colorMapLength, sizeof(headerObj.colorMapLength));
    file.read(&headerObj.colorMapDepth, sizeof(headerObj.colorMapDepth));
    file.read((char*)&headerObj.xOrigin, sizeof(headerObj.xOrigin));
    file.read((char*)&headerObj.yOrigin, sizeof(headerObj.yOrigin));
    file.read((char*)&headerObj.width, sizeof(headerObj.width));
    file.read((char*)&headerObj.height, sizeof(headerObj.height));
    file.read(&headerObj.bitsPerPixel, sizeof(headerObj.bitsPerPixel));
    file.read(&headerObj.imageDescriptor, sizeof(headerObj.imageDescriptor));

    header = headerObj;

    // Read pixels
    int size = headerObj.width * headerObj.height;
    int currentPixel = 0;
    while (currentPixel < size) {
        Pixel pixel;
        file.read((char*)&pixel.blue, sizeof(pixel.blue));
        file.read((char*)&pixel.green, sizeof(pixel.green));
        file.read((char*)&pixel.red, sizeof(pixel.red));
        pixels.push_back(pixel);
        currentPixel++;
    }
    file.close();
}

void Tga::WriteTga(string filePath) {
    ofstream file(filePath, ios_base::binary);
    if (file.is_open()) {
        file.write(&header.idLength, sizeof(header.idLength));
        file.write(&header.colorMapType, sizeof(header.colorMapType));
        file.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
        file.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        file.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        file.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
        file.write((char*)&header.xOrigin, sizeof(header.xOrigin));
        file.write((char*)&header.yOrigin, sizeof(header.yOrigin));
        file.write((char*)&header.width, sizeof(header.width));
        file.write((char*)&header.height, sizeof(header.height));
        file.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        file.write(&header.imageDescriptor, sizeof(header.imageDescriptor));
        for (int i = 0; i < pixels.size(); i++) {
            file.write((char*)&pixels.at(i).blue, sizeof(pixels.at(i).blue));
            file.write((char*)&pixels.at(i).green, sizeof(pixels.at(i).green));
            file.write((char*)&pixels.at(i).red, sizeof(pixels.at(i).red));
        }
        file.close();
    }
}

void Tga::ChangeColor(unsigned char red, unsigned char green, unsigned char blue) {
    for (int i = 0; i < pixels.size(); i++) {
        pixels.at(i).red = red;
        pixels.at(i).green = green;
        pixels.at(i).blue = blue;
    }
}

void Tga::RandomColor() {
    for (int i = 0; i < pixels.size(); i++) {
        int rndRed = rand() % 256;
        int rndGreen = rand() % 256;
        int rndBlue = rand() % 256;
        pixels.at(i).red = (unsigned char) rndRed;
        pixels.at(i).green = (unsigned char) rndGreen;
        pixels.at(i).blue = (unsigned char) rndBlue;
    }
}



vector<Pixel> Tga::GetPixels() {
    return pixels;
}
