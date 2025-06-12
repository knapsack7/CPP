#include <fstream>
#include <iostream>
using namespace std;


void writeFile(){
    ofstream outFile{"data.txt"};
    outFile << "Hello World!" << endl;
    outFile << 10 << endl;
    outFile.close();
}

void readFile(){
    ifstream inFile;//{"data.txt"};
    inFile.open("data.txt");
    // if (!inFile.is_open()){
    //     cout << "Error opening file" << endl;
    //     return;
    // }
    if (inFile.fail()){
        cout << "Error opening file" << endl;
        return;
    }
    string str;
    std::getline(inFile, str);
    int x{};
    inFile >> x;
    if (inFile.good()){
        cout << str << endl;
        cout << x << endl;
    }
    else{
        cout << "Error reading file" << endl;
    }
    inFile.setstate(std::ios::failbit);
    inFile.clear(); // clear the error state
    inFile.seekg(0); // move the cursor to the beginning of the file
    inFile.close();
}

int main(){
    writeFile();
    readFile();
    return 0;
}