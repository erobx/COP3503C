#include <iostream>
#include <string>
#include <math.h>
using namespace std;

// Base classes
class Shape {
public:
    virtual void Scale(float scalefactor) = 0;
    virtual void Display() const = 0;
    virtual ~Shape();
};

class Shape2D : virtual public Shape {
public:
    virtual float Area() const = 0;
    void ShowArea() const;
    virtual string GetName2D() const = 0;
    bool operator>(const Shape2D &rhs) const;
    bool operator<(const Shape2D &rhs) const;
    bool operator==(const Shape2D &rhs) const;
};

class Shape3D : virtual public Shape {
public:
    virtual float Volume() const = 0;
    void ShowVolume() const;
    virtual string GetName3D() const = 0;
    bool operator>(const Shape3D &rhs) const;
    bool operator<(const Shape3D &rhs) const;
    bool operator==(const Shape3D &rhs) const;
};

class Square : public Shape2D {
    string name = "Square";
    float length;
public:
    Square();
    Square(float length);
    virtual ~Square();
    void Scale(float scalefactor);
    void Display() const;
    float Area() const;
    string GetName2D() const;
};

class Triangle : public Shape2D {
    string name = "Triangle";
    float base;
    float height;
public:
    Triangle();
    Triangle(float base, float height);
    virtual ~Triangle();
    void Scale(float scalefactor);
    void Display() const;
    float Area() const;
    string GetName2D() const;
};

class Circle : public Shape2D {
    string name = "Circle";
    float radius;
    const float PI = 3.14159f;
public:
    Circle();
    Circle(float radius);
    virtual ~Circle();
    void Scale(float scalefactor);
    void Display() const;
    float Area() const;
    string GetName2D() const;
};