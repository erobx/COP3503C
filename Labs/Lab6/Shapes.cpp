#include "Shapes.h"
#include <math.h>
#include <iostream>
using namespace std;

void Shape2D::ShowArea() const {
    cout << GetName2D() << endl;
    cout << Area() << endl;
}

bool Shape2D::operator>(const Shape2D &rhs) const {
    return this->Area() > rhs.Area();
}

bool Shape2D::operator<(const Shape2D &rhs) const {
    return this->Area() < rhs.Area();
}

bool Shape2D::operator==(const Shape2D &rhs) const {
    return this->Area() == rhs.Area();
}

Square::Square() {
    length = 0;
}

Square::Square(float length) {
    this->length = length;
}

void Square::Scale(float scalefactor) {
    length *= scalefactor;
}

void Square::Display() const {
    cout << "The area of the Square is : " << Area() << endl;
    cout << "Length of a side: " << length << endl;
}

float Square::Area() const {
    return pow(length, 2.0);
}

string Square::GetName2D() const {
    return name;
}

Triangle::Triangle() {
    base = 0;
    height = 0;
}

Triangle::Triangle(float base, float height) {
    this->base = base;
    this->height = height;
}

void Triangle::Scale(float scalefactor) {
    base *= scalefactor;
    height *= scalefactor;
}

void Triangle::Display() const {
    cout << "The area of the Triangle is : " << Area() << endl;
    cout << "Base: " << base << endl;
    cout << "Height: " << height << endl;
}

float Triangle::Area() const {
    return base * height * 0.5f;
}

string Triangle::GetName2D() const {
    return name;
}

Circle::Circle() {
    radius = 0;
}

Circle::Circle(float radius) {
    this->radius = radius;
}

void Circle::Scale(float scalefactor) {
    radius *= scalefactor;
}

void Circle::Display() const {
    cout << "The area of the Circle is : " << Area() << endl;
    cout << "Radius: " << radius << endl;
}

float Circle::Area() const {
    return PI * pow(radius, 2.0);
}

string Circle::GetName2D() const {
    return name;
}

