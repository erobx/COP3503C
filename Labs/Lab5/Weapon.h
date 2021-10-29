#pragma once
#include <string>
using std::string;

class Weapon {
	string name;
	int power;
	float consumption;
public:
	Weapon(string name, int power, float consumption);
    string GetName();
    int GetPower();
    float GetConsum();
};

Weapon::Weapon(string _name, int _power, float _consumption) {
	name = _name;
	power = _power;
	consumption = _consumption;
}

string Weapon::GetName() {
    return name;
}

int Weapon::GetPower() {
    return power;
}

float Weapon::GetConsum() {
    return consumption;
}