#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    string title, header1, header2, dataPoint, dataString;
    int dataInt = 0;
    vector<string> dataPoints;
    bool flag = true;

    // Get title
    // cout << "Enter a title for the data: " << endl;
    // getline(cin, title);
    // cout << "You entered: " << title << endl;
    // cout << endl;

    // // Column headers 
    // cout << "Enter the column 1 header: " << endl;
    // getline(cin, header1);
    // cout << "You entered: " << header1 << endl;
    // cout << endl;

    // cout << "Enter the column 2 header: " << endl;
    // getline(cin, header2);
    // cout << "You entered: " << header2 << endl;
    // cout << endl;
    while (flag) {
        cout << "Enter a data point (-1 to stop input): " << endl;
        getline(cin, dataPoint);
        int index = dataPoint.find(',');

        // Catch exceptions
        try {
            int end = stoi(dataPoint);
            if (end == -1)
                throw runtime_error("");
            try {
                if (index == string::npos)
                    throw(runtime_error("No comma in string."));

                if (dataPoint.find(index, ',') != string::npos)
                    throw(runtime_error("Too many commas in input."));
                


            }
            catch (runtime_error excpt) {
                cout << "Error: " << excpt.what() << endl;
            }

            dataString = dataPoint.substr(0, index);
            dataInt = stoi(dataPoint.substr(index + 2));

            cout << "Data string: " << dataString << endl;
            cout << "Data integer: " << dataInt << endl;
        }
        catch (runtime_error excpt) {
            flag = false;
        }
    }

        // if (data.find(index, ',') != string::npos) {
        //     cout << "Error: Too many commas in input." << endl;
        // } else if (index != string::npos) {
        //     try {
        //         dataInt = stoi(data.substr(index+2));
        //         if (dataInt+dataInt != dataInt*2)
        //             throw (exception);
        //     } catch ()
        //     dataString = data.substr(0, index);
        // } else {
        //     cout << "Error: No comma in string." << endl;
        // }
        // 
    return 0;
}