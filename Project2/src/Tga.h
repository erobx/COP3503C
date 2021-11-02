#pragma once
#include <vector>
#include <string>
#include "Header.h"
#include "Pixel.h"
using namespace std;

class Tga {
    Header header;
    vector<Pixel> pixels;
public:
    Tga(string filePath);
    void WriteTga(string filePath);
    void ChangeColor(unsigned char red, unsigned char green, unsigned char blue);
    void RandomColor();
    vector<Pixel> GetPixels();
};