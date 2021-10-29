#include "Ship.h"
#include <iostream>
#include <vector>

Ship::Ship() {
	name = "";
	type = "";
	size = 0;
	shieldCap = 0;
	maxWarp = 0;
}

Ship::Ship(string _name, string _type, short _size, int _shieldCap, float _maxWarp, vector<Weapon> _weapons) {
	name = _name;
	type = _type;
	size = _size;
	shieldCap = _shieldCap;
	maxWarp = _maxWarp;
	weapons = _weapons;
}

string Ship::GetName() {
    return name;
}

string Ship::GetClass() {
    return type;
}

short Ship::GetSize() {
    return size;
}

int Ship::GetShield() {
    return shieldCap;
}

float Ship::GetWarp() {
    return maxWarp;
}

vector<Weapon> Ship::GetWeapons() {
    return weapons;
}