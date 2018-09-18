/*
 * Built by Richard Deming
 * github.com/obenaf
 * Midterm for CS-210
 * 17 Sep 2018
 */

#include<cstdio>
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

void readChar(ifstream&);

int main(int argc, char **argv) {
    //sets I/O file names
    string primeInput = argv[1];
    string primeOutput = primeInput + ".cpy";

    //opens I/O files
    ifstream primeRead(primeInput);
    ofstream primeWrite(primeOutput);

    readChar(primeRead);
    return 0;
}

void readChar(ifstream &primeRead) {
    char activeChar;
    string charClass;
    while(!primeRead.eof()) {
        primeRead.get(activeChar);
        if(isalpha(activeChar))
        charClass = "ALPHA";
        else if(isdigit(activeChar))
        charClass = "DIGIT";
        else
        charClass = "UNK";
    }
}

