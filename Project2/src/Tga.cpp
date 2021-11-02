#include <fstream>
#include <iostream>
#include "TGA.h"
using namespace std;

Tga::Tga(string filePath) {
    ifstream inFile(filePath, ios_base::binary);

    Header headerObj;
    // Read header (18 bytes)
    inFile.read(&headerObj.idLength, sizeof(headerObj.idLength));
    inFile.read(&headerObj.colorMapType, sizeof(headerObj.colorMapType));
    inFile.read(&headerObj.dataTypeCode, sizeof(headerObj.dataTypeCode));
    inFile.read((char*)&headerObj.colorMapOrigin, sizeof(headerObj.colorMapOrigin));
    inFile.read((char*)&headerObj.colorMapLength, sizeof(headerObj.colorMapLength));
    inFile.read(&headerObj.colorMapDepth, sizeof(headerObj.colorMapDepth));
    inFile.read((char*)&headerObj.xOrigin, sizeof(headerObj.xOrigin));
    inFile.read((char*)&headerObj.yOrigin, sizeof(headerObj.yOrigin));
    inFile.read((char*)&headerObj.width, sizeof(headerObj.width));
    inFile.read((char*)&headerObj.height, sizeof(headerObj.height));
    inFile.read(&headerObj.bitsPerPixel, sizeof(headerObj.bitsPerPixel));
    inFile.read(&headerObj.imageDescriptor, sizeof(headerObj.imageDescriptor));

    header = headerObj;

    // Read color data
    int size = headerObj.width * headerObj.height;
    int currentPixel = 0;
    while (currentPixel < size) {
        Pixel pixel;
        inFile.read((char*)&pixel.blue, sizeof(pixel.blue));
        inFile.read((char*)&pixel.green, sizeof(pixel.green));
        inFile.read((char*)&pixel.red, sizeof(pixel.red));
        pixels.push_back(pixel);
        currentPixel++;
    }

    inFile.close();
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

void Tga::ChangeColor() {
    for (Pixel p : pixels) {
        p.blue = '0';
        p.green = '0';
        p.red;
    }
}