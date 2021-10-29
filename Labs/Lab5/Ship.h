#pragma once
#include <string>
#include <vector>
#include "Weapon.h"
using std::string;
using std::vector;

class Ship {
    string name;
	string type;
	short size;
	int shieldCap;
	float maxWarp;
	vector<Weapon> weapons;
public:
    Ship();
    Ship(string name, string type, short size, int shieldCap, float maxWarp, vector<Weapon> weapons);
    string GetName();
    string GetClass();
    short GetSize();
    int GetShield();
    float GetWarp();
    vector<Weapon> GetWeapons();
};