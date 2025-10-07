#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string fileName;
    cout << "Enter the file name to read: ";
    cin >> fileName;

    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cout << "Error: Could not open file '" << fileName << "'" << endl;
        return 1;
    }

    cout << "\n--- File Content ---\n";
    string line;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }

    inputFile.close();
    cout << "\n--- End of File ---" << endl;

    return 0;
}
