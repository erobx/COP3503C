#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;

mt19937 random_mt;

// Test change

struct State {
	string name;
	int capitaIncome;
	int pop;
	int householdIncome;
	int numHouseholds;
};

int Random(int min, int max) {
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

void RollDice(int numberOfRolls, int numberOfSides);
void LoadStates(string filePath, map<string,State>& states);
void PrintMap(map<string,State>& states);
void SearchMap(string state, map<string,State>& states);

int main() {
	cout << "1. Random Numbers\n";
	cout << "2. State Info\n";

	int option;
	cin >> option;

	if (option == 1) {
		int randomSeed;
		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);

		cout << "Number of times to roll the die: ";
      	// user input
	  	int rolls;
		cin >> rolls;

		cout << "Number of sides on this die: ";
      	// user input
	  	int sides;
		cin >> sides;
		cout << endl;

		// Roll Dice
		RollDice(rolls, sides);
	}
	else if (option == 2) {
	   	// Load the states
		map<string, State> states;
	   	LoadStates("states.csv", states);
	   	// Get input for option 1 (show all states) or 2 (do a search for a particular state)
		int input;
		cout << "1. Print all states" << endl;
		cout << "2. Search for a state" << endl;
		cin >> input;

		if (input == 1) {
			PrintMap(states);
		} else if (input == 2) {
			string state;
			cin >> state;
			SearchMap(state, states);
		}
	}

	return 0;
}

void RollDice(int numberOfRolls, int numberOfSides) {
	map<int, int> rolls;
	int roll = 0;

	// initilize
	for (int i = 0; i < numberOfSides; i++)
		rolls[i+1] = 0;

	// roll
	for (int i = 0; i < numberOfRolls; i++) {
		roll = Random(1, numberOfSides);
		rolls.emplace(roll, rolls.at(roll)++);
	}
	
	// print
	auto it = rolls.begin();
	for (; it != rolls.end(); it++)
		cout << it->first << ": " << it->second << endl;
}

void LoadStates(string filePath, map<string,State>& states) {
	ifstream inFile(filePath);
	if (inFile.is_open()) {
		string line;
		getline(inFile, line);

		while (getline(inFile, line)) {
			struct State state;
			istringstream stream(line);

			getline(stream, state.name, ',');

			string capitaIncome;
			getline(stream, capitaIncome, ',');
			state.capitaIncome = stoi(capitaIncome);

			string pop;
			getline(stream, pop, ',');
			state.pop = stoi(pop);

			string householdIncome;
			getline(stream, householdIncome, ',');
			state.householdIncome = stoi(householdIncome);

			string numHouseholds;
			getline(stream, numHouseholds, ',');
			state.numHouseholds = stoi(numHouseholds);

			states.emplace(state.name, state);
		}
	} else cout << "Unable to open file" << endl;
	inFile.close();
}

void PrintMap(map<string,State>& states) {
	auto it = states.begin();
	for (; it != states.end(); it++) {
		cout << it->second.name << endl;
		cout << "Population: " << it->second.pop << endl;
		cout << "Per Capita Income: " << it->second.capitaIncome << endl;
		cout << "Median Household Income: " << it->second.householdIncome << endl;
		cout << "Number of Households: " << it->second.numHouseholds << endl;
	}
}

void SearchMap(string state, map<string,State>& states) {
	auto it = states.find(state);
	if (it == states.end()) cout << "No match found for " << state;
	else {
		cout << it->second.name << endl;
		cout << "Population: " << it->second.pop << endl;
		cout << "Per Capita Income: " << it->second.capitaIncome << endl;
		cout << "Median Household Income: " << it->second.householdIncome << endl;
		cout << "Number of Households: " << it->second.numHouseholds << endl;
	}
}
