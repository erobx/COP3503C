#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct Set {
    string setNum; // 10195-1
    string theme; // City, Technic, etc.
    string name; // Name of the set
    int parts; // Number of parts the set contains
    int minifigures; // Number of minifigures the set contains
    double price; // Price of the set
};

// Prototypes
void LoadFile(string filePath, vector<Set>& sets);
void Print(Set set);
void PrintLine(vector<Set>& sets);
Set FindMostExpensive(vector<Set>& sets);
Set FindLeastExpensive(vector<Set>& sets);
Set FindMostPieces(vector<Set>& sets);
vector<Set> SearchName(vector<Set>& sets, string name);
vector<Set> SearchTheme(vector<Set>& sets, string theme);
int AvgPartCount(vector<Set>& sets);
double AvgPrice(vector<Set>& sets);
int AvgMinifigures(vector<Set>& sets);
Set FindMostMinis(vector<Set>& sets);
double TotalCost(vector<Set>& sets);
int TotalParts(vector<Set>& sets);
int TotalMinis(vector<Set>& sets);

int main()
{
	cout << std::fixed << setprecision(2);
	cout << "Which file(s) to open?\n";
	cout << "1. lego1.csv" << endl;
	cout << "2. lego2.csv" << endl;
	cout << "3. lego3.csv" << endl;
	cout << "4. All 3 files" << endl;
	int option;
	cin >> option;

   /*======= Load data from file(s) =======*/
    vector<Set> sets;
    switch (option) {
        case 1:
            LoadFile("lego1.csv", sets);
            break;
        case 2:
            LoadFile("lego2.csv", sets);
            break;
        case 3:
            LoadFile("lego3.csv", sets);
            break;
        case 4:
            LoadFile("lego1.csv", sets);
            LoadFile("lego2.csv", sets);
            LoadFile("lego3.csv", sets);
            break;
    }

    cout << "1. Most Expensive set" << endl;
	cout << "2. Largest piece count" << endl;
	cout << "3. Search for set name containing..." << endl;
	cout << "4. Search themes..." << endl;
	cout << "5. Part count information" << endl;
	cout << "6. Price information" << endl;
	cout << "7. Minifigure information" << endl;
	cout << "8. If you bought one of everything..." << endl;
	cout << "0. Exit" << endl;
   
	int choice;
	cin >> choice;
    cin.get();  // Clear newline character for any later input
   
   /*======= Print out how many sets were loaded =======*/
    cout << "Total number of sets: " << sets.size() << endl << endl;

   /*======= Based on the choice, execute the appropriate task and show the results =======*/
    struct Set set;
    vector<Set> temp;
    string input;
    switch (choice) {
        case 1:
            cout << "The most expensive set is:" << endl;
            Print(FindMostExpensive(sets));
            break;
        case 2:
            cout << "The set with the highest parts count:" << endl;
            Print(FindMostPieces(sets));
            break;
        case 3:
            getline(cin, input);
            temp = SearchName(sets, input);
            if (temp.size() == 0)
                cout << "No sets found matching that search term";
            else {
                cout << "Sets matching \"" << input << "\":" << endl;
                PrintLine(temp);
            }
            break;
        case 4:
            getline(cin, input);
            temp = SearchTheme(sets, input);
            if (temp.size() == 0)
                cout << "No sets found matching that search term";
            else {
                cout << "Sets matching \"" << input << "\":" << endl;
                PrintLine(temp);
            }
            break;
        case 5:
            cout << "Average part count for " << sets.size() << " sets: " << AvgPartCount(sets);
            break;
        case 6:
            cout << "Average price for " << sets.size() << " sets: $" << AvgPrice(sets) << endl;
            cout << "Least expensive set:" << endl;
            Print(FindLeastExpensive(sets));
            cout << "Most expensive set:" << endl;
            Print(FindMostExpensive(sets));
            break;
        case 7:
            cout << "Average number of minifigures: " << AvgMinifigures(sets) << endl << endl;
            cout << "Set with the most minifigures:" << endl;
            Print(FindMostMinis(sets));
            break;
        case 8:
            cout << "If you bought one of everything..." << endl;
            cout << "It would cost: $" << TotalCost(sets) << endl;
            cout << "You would have " << TotalParts(sets) << " pieces in your collection" << endl;
            cout << "You would have an army of " << TotalMinis(sets) << " minifigures!";
            break;
    }
	return 0;
}

void LoadFile(string filePath, vector<Set>& sets) {
    ifstream inFile(filePath);

    if (inFile.is_open()) {
        string line;
        getline(inFile, line);

        while (getline(inFile, line)) {
            struct Set set;
            istringstream stream(line);

            getline(stream, set.setNum, ',');
            getline(stream, set.theme, ',');
            getline(stream, set.name, ',');

            string minifigures;
            getline(stream, minifigures, ',');
            set.minifigures = stoi(minifigures);

            string parts;
            getline(stream, parts, ',');
            set.parts = stoi(parts);

            string price;
            getline(stream, price);
            set.price = stod(price);

            sets.push_back(set);
        }
    }
    else cout << "Unable to open file" << endl;
    inFile.close();
}

void Print(Set set) {
    cout << "Name: " << set.name << endl;
    cout << "Number: " << set.setNum << endl;
    cout << "Theme: " << set.theme << endl;
    cout << "Price: $" << set.price << endl;
    cout << "Minifigures: " << set.minifigures << endl;
    cout << "Piece count: " << set.parts << endl;
}

void PrintLine(vector<Set>& sets) {
    for (Set set : sets) {
        cout << set.setNum << " " << set.name << " $" << set.price << endl;
    }
}

Set FindMostExpensive(vector<Set>& sets) {
    double max = sets.at(0).price;
    struct Set result = sets.at(0);
    for (Set set : sets) {
        if (set.price > max) {
            max = set.price;
            result = set;
        }
    }
    return result;
}

Set FindLeastExpensive(vector<Set>& sets) {
    double min = sets.at(0).price;
    struct Set result = sets.at(0);
    for (Set set : sets) {
        if (set.price < min) {
            min = set.price;
            result = set;
        }
    }
    return result;
}

Set FindMostPieces(vector<Set>& sets) {
    int max = sets.at(0).parts;
    struct Set result = sets.at(0);
    for (Set set : sets) {
        if (set.parts > max) {
            max = set.parts;
            result = set;
        }
    }
    return result;
}

vector<Set> SearchName(vector<Set>& sets, string name) {
    vector<Set> result;
    for (Set set : sets) {
        if (set.name.find(name) != string::npos)
            result.push_back(set);
    }
    return result;
}

vector<Set> SearchTheme(vector<Set>& sets, string theme) {
    vector<Set> result;
    for (Set set : sets) {
        if (set.theme.find(theme) != string::npos)
            result.push_back(set);
    }
    return result;
}

int AvgPartCount(vector<Set>& sets) {
    int total = 0;
    int count = 0;
    for (Set set : sets) {
        total += set.parts;
        count++;
    }
    return total / count;
}

double AvgPrice(vector<Set>& sets) {
    double total = 0;
    int count = 0;
    for (Set set : sets) {
        total += set.price;
        count++;
    }
    return total / count;
}

int AvgMinifigures(vector<Set>& sets) {
    int total = 0;
    int count = 0;
    for (Set set : sets) {
        total += set.minifigures;
        count++;
    }
    return total / count;
}

Set FindMostMinis(vector<Set>& sets) {
    int max = sets.at(0).minifigures;
    struct Set result = sets.at(0);
    for (Set set : sets) {
        if (set.minifigures > max) {
            max = set.minifigures;
            result = set;
        }
    }
    return result;
}

double TotalCost(vector<Set>& sets) {
    double total = 0.0;
    for (Set set : sets)
        total += set.price;
    return total;
}

int TotalParts(vector<Set>& sets) {
    int total = 0;
    for (Set set : sets)
        total += set.parts;
    return total;
}

int TotalMinis(vector<Set>& sets) {
    int total = 0;
    for (Set set : sets)
        total += set.minifigures;
    return total;
}