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

char nextChar;

void analyze();
void readChar(ifstream&);
void lexSorting(int);

int main(int argc, char **argv) {
    //sets I/O file names
    string primeInput = argv[1];
    string primeOutput = primeInput + ".cpy";

    //opens I/O files
    ifstream primeRead(primeInput);
    ofstream primeWrite(primeOutput);

    readChar(primeRead);
    do {
        analyze();
    } while (nextChar != EOF);
    return 0;
}

void readChar(ifstream &primeRead) {
    char activeChar;
    int charClass;
    while(!primeRead.eof()) {
        primeRead.get(activeChar);
        if(isalpha(activeChar))
        charClass = -1;
        else if(isdigit(activeChar))
        charClass = 0;
        else
        charClass = 1;
        lexSorting(charClass);
    }
}

void lexSorting(int charClass) {
    switch(charClass) {

    }
}

void analyze() {

}

