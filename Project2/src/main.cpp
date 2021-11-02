#include <iostream>
#include <vector>
#include "TGA.h"
using namespace std;


int main() {
    
    Tga pic = Tga("input/car.tga");
    pic.RandomColor();
    pic.WriteTga("output/car2.tga");
    Tga pic2 = Tga("output/car2.tga");

    return 0;
}
