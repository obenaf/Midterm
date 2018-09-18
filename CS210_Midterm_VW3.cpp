/*
 * Built by Richard Deming
 * github.com/obenaf
 * Midterm for CS-210
 * 17 Sep 2018
 */

#include<iostream>
#include<fstream>
using namespace std;

void fileManager(char*[]);

int main(int argc, char **argv) {
    fileManager(argv);
    return 0;
}

void fileManager(char *argv[]) {
    //sets I/O file names
    string primeInput = argv[1];
    string primeOutput = primeInput + ".cpy";

    //opens I/O files
    ifstream primeRead(primeInput);
    ofstream primeWrite(primeOutput);

    //copies line by line to new file
    string readLine;
    while(!primeRead.eof()) {
        getline(primeRead, readLine);
        primeWrite << readLine << endl;
    }
}
