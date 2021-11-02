#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include "Ship.h"
using namespace std;

//Prototypes
void LoadFile(string file, vector<Ship>& ships);
void PrintAll(vector<Ship>& ships);
void Print(Ship ship);
Ship FindStrongestWeapon(vector<Ship>& ships);
Ship FindMostPowerful(vector<Ship>& ships);
Ship WeakestShip(vector<Ship>& ships);
void PrintUnarmed(vector<Ship>& ships);

int main()
{
	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;

   /* Load files here */
   vector<Ship> ships;
	switch (option) {
		case 1:
			LoadFile("friendlyships.shp", ships);
			break;
		case 2:
			LoadFile("enemyships.shp", ships);
			break;
		case 3:
			LoadFile("friendlyships.shp", ships);
			LoadFile("enemyships.shp", ships);
			break;
	}

	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;
	
	cin >> option;
	
	/* Work your magic here */
	Ship ship = Ship();
	switch (option) {
		case 1:
			PrintAll(ships);
			break;
		case 2:
			ship = FindStrongestWeapon(ships);
			Print(ship);
			break;
		case 3:
			ship = FindMostPowerful(ships);
			Print(ship);
			break;
		case 4:
			ship = WeakestShip(ships);
			Print(ship);
			break;
		case 5:
			PrintUnarmed(ships);
			break;
	}

   return 0;
}


void LoadFile(string file, vector<Ship>& ships) {
	ifstream inFile(file, ios_base::binary);

	unsigned int count;
	inFile.read((char*)&count, sizeof(count));

	for (unsigned int i = 0; i < count; i++) {
		int length;
		
		// Read name
		inFile.read((char*)&length, sizeof(length));
		char* buffer = new char[length];
		inFile.read(buffer, length);
		string name = buffer;
		delete[] buffer;

		// Read class
		inFile.read((char*)&length, sizeof(length));
		buffer = new char[length];
		inFile.read(buffer, length);
		string type = buffer;
		delete[] buffer;

		// Read length (short)
		short size;
		inFile.read((char*)&size, sizeof(size));

		// Read shieldCap (int)
		int shieldCap;
		inFile.read((char*)&shieldCap, sizeof(shieldCap));
		
		// Read warp (float)
		float maxWarp;
		inFile.read((char*)&maxWarp, sizeof(maxWarp));

		// Read weapon(s)
		vector<Weapon> weapons;
		unsigned int count2;
		inFile.read((char*)&count2, sizeof(count2));
		if (count2 == 0) {
			weapons.push_back(Weapon("Unarmed", 0, 0));
		}
		else {
			for (unsigned int j = 0; j < count2; j++) {
				int length;
				// Read weapon name (string)
				inFile.read((char*)&length, sizeof(length));
				char* buffer = new char[length];
				inFile.read(buffer, length);
				string name = buffer;
				delete[] buffer;

				// Read weapon power (int)
				int power;
				inFile.read((char*)&power, sizeof(power));

				// Read weapon consumption (float)
				float consumption;
				inFile.read((char*)&consumption, sizeof(consumption));

				Weapon newWeapon(name, power, consumption);
				weapons.push_back(newWeapon);
			}
		}

		Ship newShip(name, type, size, shieldCap, maxWarp, weapons);
		ships.push_back(newShip);
	}
	inFile.close();
}

void PrintAll(vector<Ship>& ships) {
	for (Ship ship : ships) {
		cout << "Name: " << ship.GetName() << endl;
		cout << "Class: " << ship.GetClass() << endl;
		cout << "Length: " << ship.GetSize() << endl;
		cout << "Shield capacity: " << ship.GetShield() << endl;
		cout << "Maximum Warp: " << ship.GetWarp() << endl;
		cout << "Armaments: " << endl;
		int total = 0;
		for (Weapon weapon : ship.GetWeapons()) {
			total += weapon.GetPower();
			if (total == 0)
				cout << "Unarmed" << endl << endl;
			else
				cout << weapon.GetName() << ", " << weapon.GetPower() << ", " << weapon.GetConsum() << endl;
		}
		if (total == 0)
			continue;
		else
			cout << "Total firepower: " << total << endl << endl;
	}
}

Ship FindStrongestWeapon(vector<Ship>& ships) {
	int power = INT_MIN;
	Ship result = ships.at(0);
	for (Ship ship : ships) {
		for (Weapon w : ship.GetWeapons()) {
			if (w.GetPower() > power) {
				power = w.GetPower();
				result = ship;
			}
		}
	}
	return result;
}

Ship FindMostPowerful(vector<Ship>& ships) {
	int power = INT_MIN;
	Ship result = ships.at(0);
	for (Ship ship : ships) {
		int total = 0;
		for (Weapon weapon : ship.GetWeapons()) {
			total += weapon.GetPower();
		}
		if (total > power) {
			power = total;
			result = ship;
		}
	}
	return result;
}

void Print(Ship ship) {
	cout << "Name: " << ship.GetName() << endl;
	cout << "Class: " << ship.GetClass() << endl;
	cout << "Length: " << ship.GetSize() << endl;
	cout << "Shield capacity: " << ship.GetShield() << endl;
	cout << "Maximum Warp: " << ship.GetWarp() << endl;
	cout << "Armaments: " << endl;
	int total = 0;
	for (Weapon weapon : ship.GetWeapons()) {
		if (weapon.GetName() == "Unarmed")
			cout << weapon.GetName() << endl;
		else {
			total += weapon.GetPower();
			cout << weapon.GetName() << ", " << weapon.GetPower() << ", " << weapon.GetConsum() << endl;
		}
	}
	cout << "Total firepower: " << total << endl << endl;
}

Ship WeakestShip(vector<Ship>& ships) {
	int power = INT_MAX;
	Ship result = ships.at(0);
	for (Ship ship : ships) {
		for (Weapon w : ship.GetWeapons()) {
			if (w.GetName() == "Unarmed")
				break;
			else
				if (w.GetPower() < power) {
					power = w.GetPower();
					result = ship;
				}
		}
	}
	return result;
}

void PrintUnarmed(vector<Ship>& ships) {
	for (Ship ship : ships) {
		for (Weapon w : ship.GetWeapons()) {
			if (w.GetName() == "Unarmed") {
				cout << "Name: " << ship.GetName() << endl;
				cout << "Class: " << ship.GetClass() << endl;
				cout << "Length: " << ship.GetSize() << endl;
				cout << "Shield capacity: " << ship.GetShield() << endl;
				cout << "Maximum Warp: " << ship.GetWarp() << endl;
				cout << "Armaments: " << endl;
				cout << "Unarmed" << endl << endl;
			}
		}
	}
}
