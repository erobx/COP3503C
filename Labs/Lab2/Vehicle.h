#pragma once
#include <string>
using std::string;

class Vehicle {
   string _make;
   string _model;
   unsigned int _year;
   float _price;
   unsigned int _mileage;
   
public:
    // Constructors
    Vehicle();
    Vehicle(string make, string model, int year, float price, int mileage);

    // Prototypes
    void Display();
    string GetYearMakeModel();
    float GetPrice();
};