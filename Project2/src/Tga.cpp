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

Header Tga::GetHeader() {
    return header;
}

vector<Pixel> Tga::GetPixels() {
    return pixels;
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

// void Tga::ChangeColor(unsigned char red, unsigned char green, unsigned char blue) {
//     for (int i = 0; i < pixels.size(); i++) {
//         pixels.at(i).red = red;
//         pixels.at(i).green = green;
//         pixels.at(i).blue = blue;
//     }
// }

// void Tga::RandomColor() {
//     for (int i = 0; i < pixels.size(); i++) {
//         int rndRed = rand() % 256;
//         int rndGreen = rand() % 256;
//         int rndBlue = rand() % 256;
//         pixels.at(i).red = (unsigned char) rndRed;
//         pixels.at(i).green = (unsigned char) rndGreen;
//         pixels.at(i).blue = (unsigned char) rndBlue;
//     }
// }

void Tga::Multiply(Tga pic, string fileName) {
    vector<Pixel> topPixels = pixels;
    vector<Pixel> botPixels = pic.GetPixels();
    vector<Pixel> newPixels;

    int size = pic.GetHeader().width * pic.GetHeader().height;
    int i = 0;
    while (i < size) {
        Pixel pixel;
        // Convert RGB 0-255 to 0-1
        float red = (float) topPixels.at(i).red / 255;
        float green = (float) topPixels.at(i).green / 255;
        float blue = (float) topPixels.at(i).blue / 255;
        float red2 = (float) botPixels.at(i).red / 255;
        float green2 = (float) botPixels.at(i).green / 255;
        float blue2 = (float) botPixels.at(i).blue / 255;
        // Multiply 0-1 values and round to int
        int redProduct = (int) ((red * red2 * 255) + 0.5f);
        int greenProduct = (int) ((green * green2 * 255) + 0.5f);
        int blueProduct = (int) ((blue * blue2 * 255) + 0.5f);
        // Convert ints back to unsigned char to assign to pixel
        pixel.red = (unsigned char) redProduct;
        pixel.green = (unsigned char) greenProduct;
        pixel.blue = (unsigned char) blueProduct;
        newPixels.push_back(pixel);
        i++;
    }
    remove("output/temp.tga");
    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");
}

void Tga::Subtract(Tga pic, string fileName) {
    vector<Pixel> topPixels = pixels;
    vector<Pixel> botPixels = pic.GetPixels();
    vector<Pixel> newPixels;

    int size = pic.GetHeader().width * pic.GetHeader().height;
    int i = 0;
    while (i < size) {
        Pixel pixel;
        // Get values
        int red = (int) topPixels.at(i).red;
        int green = (int) topPixels.at(i).green;
        int blue = (int) topPixels.at(i).blue;
        int red2 = (int) botPixels.at(i).red;
        int green2 = (int) botPixels.at(i).green;
        int blue2 = (int) botPixels.at(i).blue;
        // Subtract top values from bot values and clamp to bounds
        int redDif = Clamp(red2 - red);
        int greenDif = Clamp(green2 - green);
        int blueDif = Clamp(blue2 - blue);
        // Convert ints back to unsigned char to assign to pixel
        pixel.red = (unsigned char) redDif;
        pixel.green = (unsigned char) greenDif;
        pixel.blue = (unsigned char) blueDif;
        newPixels.push_back(pixel);
        i++;
    }
    remove("output/temp.tga");
    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");
}

int Tga::Clamp(int num) {
    return max(0, min(num, 255));
}

void Tga::Screen(Tga pic, string fileName) {
    vector<Pixel> topPixels = pixels;
    vector<Pixel> botPixels = pic.GetPixels();
    vector<Pixel> newPixels;

    int size = pic.GetHeader().width * pic.GetHeader().height;
    int i = 0;
    while (i < size) {
        Pixel pixel;
        // Get values
        float red = (float) topPixels.at(i).red / 255;
        float green = (float) topPixels.at(i).green / 255;
        float blue = (float) topPixels.at(i).blue / 255;
        float red2 = (float) botPixels.at(i).red / 255;
        float green2 = (float) botPixels.at(i).green / 255;
        float blue2 = (float) botPixels.at(i).blue / 255;
        // 1-(1-A)*(1-B)
        int redFinal = (int) ((1 - (1-red) * (1-red2)) * 255 + 0.5f);
        int greenFinal = (int) ((1 - (1-green) * (1-green2)) * 255 + 0.5f);
        int blueFinal = (int) ((1 - (1-blue) * (1-blue2)) * 255 + 0.5f);
        // Convert ints back to unsigned char to assign to pixel
        pixel.red = (unsigned char) redFinal;
        pixel.green = (unsigned char) greenFinal;
        pixel.blue = (unsigned char) blueFinal;
        newPixels.push_back(pixel);
        i++;
    }
    remove("output/temp.tga");
    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");
}

void Tga::Overlay(Tga pic, string fileName) {
    Tga bot = pic;
    vector<Pixel> topPixels = pixels;
    vector<Pixel> botPixels = bot.pixels;
    vector<Pixel> newPixels;

    int size = bot.header.width * bot.header.height;
    int i = 0;
    while (i < size) {
        Pixel pixel;
        // Get values
        float red = (float) topPixels.at(i).red / 255;
        float green = (float) topPixels.at(i).green / 255;
        float blue = (float) topPixels.at(i).blue / 255;
        float red2 = (float) botPixels.at(i).red / 255;
        float green2 = (float) botPixels.at(i).green / 255;
        float blue2 = (float) botPixels.at(i).blue / 255;
        // Compare values
        int redFinal = 0;
        int greenFinal = 0;
        int blueFinal = 0;
        if (red2 <= 0.5) {
            redFinal = (int) ((2 * red * red2 * 255) + 0.5f);
        } else {
            redFinal = (int) ((1 - 2*(1-red) * (1-red2)) * 255 + 0.5f);
        }
        if (green2 <= 0.5) {
            greenFinal = (int) ((2 * green * green2 * 255) + 0.5f);
        } else {
            greenFinal = (int) ((1 - 2*(1-green) * (1-green2)) * 255 + 0.5f);
        }
        if (blue2 <= 0.5) {
            blueFinal = (int) ((2 * blue * blue2 * 255) + 0.5f);
        } else {
            blueFinal = (int) ((1 - 2*(1-blue) * (1-blue2)) * 255 + 0.5f);
        }
        // Convert ints back to unsigned char to assign to pixel
        pixel.red = (unsigned char) redFinal;
        pixel.green = (unsigned char) greenFinal;
        pixel.blue = (unsigned char) blueFinal;
        newPixels.push_back(pixel);
        i++;
    }
    remove("output/temp.tga");
    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");
}

void Tga::Add(char color, int amount, string fileName) {
    vector<Pixel> newPixels;
    int size = header.width * header.height;
    if (color == 'R') {
        for (int i = 0; i < size; i++) {
            Pixel pixel;
            int red = (int) pixels.at(i).red;
            int redFinal = Clamp(red + amount);
            pixel.red = redFinal;
            pixel.green = pixels.at(i).green;
            pixel.blue = pixels.at(i).blue;
            newPixels.push_back(pixel);
        }
    } else if (color == 'G') {
        for (int i = 0; i < size; i++) {
            Pixel pixel;
            int green = (int) pixels.at(i).green;
            int greenFinal = Clamp(green + amount);
            pixel.red = pixels.at(i).red;
            pixel.green = greenFinal;
            pixel.blue = pixels.at(i).blue;
            newPixels.push_back(pixel);
        }
    } else if (color == 'B') {
        for (int i = 0; i < size; i++) {
            Pixel pixel;
            int blue = (int) pixels.at(i).blue;
            int blueFinal = Clamp(blue + amount);
            pixel.red = pixels.at(i).red;
            pixel.green = pixels.at(i).green;
            pixel.blue = blueFinal;
            newPixels.push_back(pixel);
        }
    }
    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");
}

void Tga::Scale(int redScale, int blueScale, string fileName) {
    vector<Pixel> newPixels;
    int size = header.width * header.height;

    for (int i = 0; i < size; i++) {
        Pixel pixel;
        int red = (int) pixels.at(i).red;
        int redFinal = Clamp(red * redScale);
        int blue = (int) pixels.at(i).blue;
        int blueFinal = Clamp(blue * blueScale);
        pixel.red = redFinal;
        pixel.green = pixels.at(i).green;
        pixel.blue = blueFinal;
        newPixels.push_back(pixel);
    }
    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");
}

void Tga::WriteChannels(string filePath) {
    ofstream blueFile("output/" + filePath + "_b.tga", ios_base::binary);
    if (blueFile.is_open()) {
        blueFile.write(&header.idLength, sizeof(header.idLength));
        blueFile.write(&header.colorMapType, sizeof(header.colorMapType));
        blueFile.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
        blueFile.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        blueFile.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        blueFile.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
        blueFile.write((char*)&header.xOrigin, sizeof(header.xOrigin));
        blueFile.write((char*)&header.yOrigin, sizeof(header.yOrigin));
        blueFile.write((char*)&header.width, sizeof(header.width));
        blueFile.write((char*)&header.height, sizeof(header.height));
        blueFile.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        blueFile.write(&header.imageDescriptor, sizeof(header.imageDescriptor));
        for (int i = 0; i < pixels.size(); i++) {
            blueFile.write((char*)&pixels.at(i).blue, sizeof(pixels.at(i).blue));
            blueFile.write((char*)&pixels.at(i).blue, sizeof(pixels.at(i).blue));
            blueFile.write((char*)&pixels.at(i).blue, sizeof(pixels.at(i).blue));
        }
        blueFile.close();
    }

    ofstream greenFile("output/" + filePath + "_g.tga", ios_base::binary);
    if (greenFile.is_open()) {
        greenFile.write(&header.idLength, sizeof(header.idLength));
        greenFile.write(&header.colorMapType, sizeof(header.colorMapType));
        greenFile.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
        greenFile.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        greenFile.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        greenFile.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
        greenFile.write((char*)&header.xOrigin, sizeof(header.xOrigin));
        greenFile.write((char*)&header.yOrigin, sizeof(header.yOrigin));
        greenFile.write((char*)&header.width, sizeof(header.width));
        greenFile.write((char*)&header.height, sizeof(header.height));
        greenFile.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        greenFile.write(&header.imageDescriptor, sizeof(header.imageDescriptor));
        for (int i = 0; i < pixels.size(); i++) {
            greenFile.write((char*)&pixels.at(i).green, sizeof(pixels.at(i).green));
            greenFile.write((char*)&pixels.at(i).green, sizeof(pixels.at(i).green));
            greenFile.write((char*)&pixels.at(i).green, sizeof(pixels.at(i).green));
        }
        greenFile.close();
    }

    ofstream redFile("output/" + filePath + "_r.tga", ios_base::binary);
    if (redFile.is_open()) {
        redFile.write(&header.idLength, sizeof(header.idLength));
        redFile.write(&header.colorMapType, sizeof(header.colorMapType));
        redFile.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
        redFile.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        redFile.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        redFile.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
        redFile.write((char*)&header.xOrigin, sizeof(header.xOrigin));
        redFile.write((char*)&header.yOrigin, sizeof(header.yOrigin));
        redFile.write((char*)&header.width, sizeof(header.width));
        redFile.write((char*)&header.height, sizeof(header.height));
        redFile.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        redFile.write(&header.imageDescriptor, sizeof(header.imageDescriptor));
        for (int i = 0; i < pixels.size(); i++) {
            redFile.write((char*)&pixels.at(i).red, sizeof(pixels.at(i).red));
            redFile.write((char*)&pixels.at(i).red, sizeof(pixels.at(i).red));
            redFile.write((char*)&pixels.at(i).red, sizeof(pixels.at(i).red));
        }
        redFile.close();
    }
}

void Tga::CombineFiles(Tga file1, Tga file2, string fileName) {
    vector<Pixel> redChannel = pixels;
    vector<Pixel> greenChannel = file1.GetPixels();
    vector<Pixel> blueChannel = file2.GetPixels();
    vector<Pixel> newPixels;

    int size = header.width * header.height;
    int i = 0;
    while (i < size) {
        Pixel pixel;
        pixel.red = redChannel.at(i).red;
        pixel.green = greenChannel.at(i).green;
        pixel.blue = blueChannel.at(i).blue;
        newPixels.push_back(pixel);
        i++;
    }
    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");
}

void Tga::Flip(string fileName) {
    vector<Pixel> newPixels;

    for (int i = pixels.size()-1; i >=0; i--) {
        Pixel pixel;
        pixel.blue = pixels.at(i).blue;
        pixel.green = pixels.at(i).green;
        pixel.red = pixels.at(i).red;
        newPixels.push_back(pixel);
    }
    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");
}

void Tga::Quadrant(Tga topRight, Tga botRight, Tga botLeft, string fileName) {
    vector<Pixel> topRightPixels = topRight.GetPixels();
    vector<Pixel> botRightPixels = botRight.GetPixels();
    vector<Pixel> topLeftPixels = pixels;
    vector<Pixel> botLeftPixels = botLeft.GetPixels();
    vector<Pixel> newPixels;

    int total_pixels = 0;
    int size = header.width * header.height * 4;
    int i = 0;
    int j = 0;
    int k = 0;
    int z = 0;
    int index = 512;

    while (total_pixels < size/2) {
        while (k < index) {
            newPixels.push_back(botLeftPixels.at(k));
            total_pixels++;
            k++;
        }
        while (z < index) {
            newPixels.push_back(botRightPixels.at(z));
            total_pixels++;
            z++;
        }
        index += 512;
    }
    index = 512;
    while (total_pixels < size) {
        while (i < index) {
            newPixels.push_back(topLeftPixels.at(i));
            total_pixels++;
            i++;
        }
        while (j < index) {
            newPixels.push_back(topRightPixels.at(j));
            total_pixels++;
            j++;
        }
        index += 512;
    }
    header.width = 1024;
    header.height = 1024;
    pixels = newPixels;
    WriteTga("output/" + fileName + ".tga");
}

