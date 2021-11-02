#pragma once
#include <vector>
#include <string>
#include "Header.h"
#include "Pixel.h"
using namespace std;

class Tga {
public:
    Tga(string filePath);
    Header header;
    vector<Pixel> pixels;
    void WriteTga(string filePath);
    void ChangeColor();
};