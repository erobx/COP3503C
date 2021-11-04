#include <iostream>
#include <vector>
#include "TGA.h"
using namespace std;

bool CompareHeader(Tga pic1, Tga pic2);
bool ComparePixels(Tga pic1, Tga pic2);
void Test1();
void Test2();
void Test3();
void Test4();
void Test5();
void Test6();
void Test7();
void Test8();
void Test9();
void Test10();
void Test11();
void TestAll();

int main() {
    TestAll();
    return 0;
}

bool CompareHeader(Tga pic1, Tga pic2) {
    if ((int)pic1.GetHeader().idLength != (int)pic2.GetHeader().idLength)
        return false;
    if ((int)pic1.GetHeader().colorMapType != (int)pic2.GetHeader().colorMapType)
        return false;
    if ((int)pic1.GetHeader().dataTypeCode != (int)pic2.GetHeader().dataTypeCode)
        return false;
    if ((short)pic1.GetHeader().colorMapOrigin != (short)pic2.GetHeader().colorMapOrigin)
        return false;
    if ((short)pic1.GetHeader().colorMapLength != (short)pic2.GetHeader().colorMapLength)
        return false;
    if ((int)pic1.GetHeader().colorMapDepth != (int)pic2.GetHeader().colorMapDepth)
        return false;
    if ((short)pic1.GetHeader().xOrigin != (short)pic2.GetHeader().xOrigin)
        return false;
    if ((short)pic1.GetHeader().yOrigin != (short)pic2.GetHeader().yOrigin)
        return false;
    if ((short)pic1.GetHeader().width != (short)pic2.GetHeader().width)
        return false;
    if ((short)pic1.GetHeader().height != (short)pic2.GetHeader().height)
        return false;
    if ((int)pic1.GetHeader().bitsPerPixel != (int)pic2.GetHeader().bitsPerPixel)
        return false;
    if ((int)pic1.GetHeader().imageDescriptor != (int)pic2.GetHeader().imageDescriptor)
        return false;
    return true;
}

bool ComparePixels(Tga pic1, Tga pic2) {
    vector<Pixel> pixels1 = pic1.GetPixels();
    vector<Pixel> pixels2 = pic2.GetPixels();
    for (int i = 0; i < pixels1.size(); i++) {
        if ((int)pixels1.at(i).red != (int)pixels2.at(i).red)
            return false;
        if ((int)pixels1.at(i).green != (int)pixels2.at(i).green)
            return false;
        if ((int)pixels1.at(i).blue != (int)pixels2.at(i).blue)
            return false;
    }
    return true;
}

void Test1() {
    Tga top = Tga("input/layer1.tga");
    Tga bot = Tga("input/pattern1.tga");
    top.Multiply(bot, "part1");
    
    Tga pic = Tga("output/part1.tga");
    Tga pic2 = Tga("examples/EXAMPLE_part1.tga");

    if (CompareHeader(pic, pic2) && ComparePixels(pic, pic2))
        cout << "Test 1 Passed" << endl;
    else cout << "Test 1 Failed" << endl;
}

void Test2() {
    Tga top = Tga("input/layer2.tga");
    Tga bot = Tga("input/car.tga");
    top.Subtract(bot, "part2");
    Tga pic = Tga("output/part2.tga");
    Tga pic2 = Tga("examples/EXAMPLE_part2.tga");

    if (CompareHeader(pic, pic2) && ComparePixels(pic, pic2))
        cout << "Test 2 Passed" << endl;
    else cout << "Test 2 Failed" << endl;
}

void Test3() {
    Tga top = Tga("input/layer1.tga");
    Tga bot = Tga("input/pattern2.tga");
    top.Multiply(bot, "temp");

    Tga top2 = Tga("input/text.tga");
    Tga temp = Tga("output/temp.tga");
    top2.Screen(temp, "part3");

    Tga pic = Tga("output/part3.tga");
    Tga pic2 = Tga("examples/EXAMPLE_part3.tga");
    
    if (CompareHeader(pic, pic2) && ComparePixels(pic, pic2))
        cout << "Test 3 Passed" << endl;
    else cout << "Test 3 Failed" << endl;
}

void Test4() {
    Tga top = Tga("input/layer2.tga");
    Tga bot = Tga("input/circles.tga");
    top.Multiply(bot, "temp");

    Tga top2 = Tga("input/pattern2.tga");
    Tga temp = Tga("output/temp.tga");
    top2.Subtract(temp, "part4");

    Tga pic = Tga("output/part4.tga");
    Tga pic2 = Tga("examples/EXAMPLE_part4.tga");
    
    if (CompareHeader(pic, pic2) && ComparePixels(pic, pic2))
        cout << "Test 4 Passed" << endl;
    else cout << "Test 4 Failed" << endl;
}

void Test5() {
    Tga top = Tga("input/layer1.tga");
    Tga bot = Tga("input/pattern1.tga");
    top.Overlay(bot, "part5");
    
    Tga pic = Tga("output/part5.tga");
    Tga pic2 = Tga("examples/EXAMPLE_part5.tga");

    if (CompareHeader(pic, pic2) && ComparePixels(pic, pic2))
        cout << "Test 5 Passed" << endl;
    else cout << "Test 5 Failed" << endl;
}

void Test6() {
    Tga top = Tga("input/car.tga");
    top.Add('G', 200, "part6");

    Tga pic = Tga("output/part6.tga");
    Tga pic2 = Tga("examples/EXAMPLE_part6.tga");

    if (CompareHeader(pic, pic2) && ComparePixels(pic, pic2))
        cout << "Test 6 Passed" << endl;
    else cout << "Test 6 Failed" << endl;
}

void Test7() {
    Tga car = Tga("input/car.tga");
    car.Scale(4, 0, "part7");

    Tga pic = Tga("output/part7.tga");
    Tga pic2 = Tga("examples/EXAMPLE_part7.tga");

    if (CompareHeader(pic, pic2) && ComparePixels(pic, pic2))
        cout << "Test 7 Passed" << endl;
    else cout << "Test 7 Failed" << endl;
}

void Test8() {
    Tga car = Tga("input/car.tga");
    car.WriteChannels("part8");

    Tga blue = Tga("output/part8_b.tga");
    Tga blue2 = Tga("examples/EXAMPLE_part8_b.tga");

    Tga green= Tga("output/part8_g.tga");
    Tga green2 = Tga("examples/EXAMPLE_part8_g.tga");

    Tga red = Tga("output/part8_r.tga");
    Tga red2 = Tga("examples/EXAMPLE_part8_r.tga");

    if (CompareHeader(blue, blue2) && ComparePixels(blue, blue2) && 
        CompareHeader(green, green2) && ComparePixels(green, green2) &&
        CompareHeader(red, red2) && ComparePixels(red, red2))
        cout << "Test 8 Passed" << endl;
    else cout << "Test 8 Failed" << endl;
}

void Test9() {
    Tga redFile = Tga("input/layer_red.tga");
    Tga greenFile = Tga("input/layer_green.tga");
    Tga blueFile = Tga("input/layer_blue.tga");

    redFile.CombineFiles(greenFile, blueFile, "part9");

    Tga pic = Tga("output/part9.tga");
    Tga pic2 = Tga("examples/EXAMPLE_part9.tga");

    if (CompareHeader(pic, pic2) && ComparePixels(pic, pic2))
        cout << "Test 9 Passed" << endl;
    else cout << "Test 9 Failed" << endl;
}

void Test10() {
    Tga file = Tga("input/text2.tga");
    file.Flip("part10");

    Tga pic = Tga("output/part10.tga");
    Tga pic2 = Tga("examples/EXAMPLE_part10.tga");

    if (CompareHeader(pic, pic2) && ComparePixels(pic, pic2))
        cout << "Test 10 Passed" << endl;
    else cout << "Test 10 Failed" << endl;
}

void Test11() {
    Tga car = Tga("input/car.tga");
    Tga circles = Tga("input/circles.tga");
    Tga pattern = Tga("input/pattern1.tga");
    Tga text = Tga("input/text.tga");

    car.Quadrant(circles, pattern, text, "extracredit");

    Tga pic = Tga("output/extracredit.tga");
    Tga pic2 = Tga("examples/EXAMPLE_extracredit.tga");

    if (CompareHeader(pic, pic2) && ComparePixels(pic, pic2))
        cout << "Test 11 Passed" << endl;
    else cout << "Test 11 Failed" << endl;
}

void TestAll() {
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    Test9();
    Test10();
    Test11();
}