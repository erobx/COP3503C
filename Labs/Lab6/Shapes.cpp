#include "Shapes.h"
#include <math.h>

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

void Shape3D::ShowVolume() const {
    cout << GetName3D() << endl;
    cout << Volume() << endl;
}

bool Shape3D::operator>(const Shape3D &rhs) const {
    return this->Volume() > rhs.Volume();
}

bool Shape3D::operator<(const Shape3D &rhs) const {
    return this->Volume() < rhs.Volume();
}

bool Shape3D::operator==(const Shape3D &rhs) const {
    return this->Volume() == rhs.Volume();
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
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
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
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
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
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
    cout << "Radius: " << radius << endl;
}

float Circle::Area() const {
    return PI * pow(radius, 2.0);
}

string Circle::GetName2D() const {
    return name;
}

TriangularPyramid::TriangularPyramid() : Triangle() {
    height = 0;
}

TriangularPyramid::TriangularPyramid(float height, float base, float height2) : Triangle(base, height2) {
    this->height = height;
}

void TriangularPyramid::Scale(float scalefactor) {
    height *= scalefactor;
    Triangle::Scale(scalefactor);
}

void TriangularPyramid::Display() const {
    cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
    cout << "The height is: " << height << endl;
    Triangle::Display();
}

float TriangularPyramid::Volume() const {
    return Area() * height / 3;
}

string TriangularPyramid::GetName3D() const {
    return name;
}

Cylinder::Cylinder() : Circle() {
    height = 0;
}

Cylinder::Cylinder(float height, float radius) : Circle(radius) {
    this->height = height;
}

void Cylinder::Scale(float scalefactor) {
    height *= scalefactor;
    Circle::Scale(scalefactor);
}

void Cylinder::Display() const {
    cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
    cout << "The height is: " << height << endl;
    Circle::Display();
}

float Cylinder::Volume() const {
    return Area() * height;
}

string Cylinder::GetName3D() const {
    return name;
}

Sphere::Sphere() : Circle() {
    radius = 0;
}

Sphere::Sphere(float radius) : Circle(radius) {
    this->radius = radius;
}

void Sphere::Scale(float scalefactor) {
    radius *= scalefactor;
    Circle::Scale(scalefactor);
}

void Sphere::Display() const {
    cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
    Circle::Display();
}

float Sphere::Volume() const {
    return 4* pow(radius, 3.0) * PI / 3;
}

string Sphere::GetName3D() const {
    return name;
}