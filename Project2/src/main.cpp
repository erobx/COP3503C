#include <iostream>
#include <vector>
#include "TGA.h"
using namespace std;


int main() {
    
    Tga pic = Tga("input/car.tga");
    pic.ChangeColor();

    return 0;
}
