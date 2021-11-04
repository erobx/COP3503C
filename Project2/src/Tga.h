#pragma once
#include <vector>
#include <string>
#include "Image.h"
using namespace std;

class Tga {
    Header header;
    vector<Pixel> pixels;
public:
    Tga(string filePath);
    Header GetHeader();
    vector<Pixel> GetPixels();
    void WriteTga(string filePath);
    // void ChangeColor(unsigned char red, unsigned char green, unsigned char blue);
    // void RandomColor();
    void Multiply(Tga pic, string fileName);
    void Subtract(Tga pic, string fileName);
    int Clamp(int num);
    void Screen(Tga pic, string fileName);
    void Overlay(Tga pic, string fileName);
    void Add(char color, int amount, string fileName);
    void Scale(int redScale, int blueScale, string fileName);
    void WriteChannels(string filePath);
    void CombineFiles(Tga file1, Tga file2, string fileName);
    void Flip(string fileName);
    void Quadrant(Tga topRight, Tga botRight, Tga botLeft, string fileName);
};