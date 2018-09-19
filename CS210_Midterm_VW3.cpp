/*
 * Built by Richard Deming
 * github.com/obenaf
 * Midterm for CS-210
 * 18 Sep 2018
 */
 //NOTE: I haven't decided how I want to write to the output file
 //yet, will implement that when I am further along.

#include<cstdio>
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
//Global Variables
int charClass;
char activeChar;
char lexeme[63];
int lexLength;
//Function Headers
void analyze();
void readChar(ifstream&);
void lexAdd();
void traverseWhiteSpace();

int main(int argc, char **argv) {
    //sets I/O file names
    string primeInput = argv[1];
    string primeOutput = primeInput + ".cpy";

    //opens I/O files
    ifstream primeRead(primeInput);
    ofstream primeWrite(primeOutput);

    while(primeRead.eof()) { //Writes directly to out file for now
        primeRead.get(activeChar);
        primeWrite << activeChar;
    }
    return 0; //TERMINATES PROGRAM
    //Program not ready for implementation
    readChar(primeRead);
    do {
        analyze();
    } while (activeChar != EOF);
    return 0;
}
//Sorts characters into subgroups
void analyze() {
    lexLength = 0;
    traverseWhiteSpace();
    switch(charClass) { //unimplemented

    }
}
//Reads characters and determines char type
void readChar(ifstream &primeRead) {
    primeRead.get(activeChar);
    if(activeChar != EOF) {
    if(isalpha(activeChar))
        charClass = -1;
    else if(isdigit(activeChar))
        charClass = 0;
    else
        charClass = 1;
    }
    else charClass = EOF;
}
//adds activeChar into the working lexeme
void lexAdd() {
    lexeme[lexLength++] = activeChar;
    lexeme[lexLength] = 0;
}
//finds the next character
void traverseWhiteSpace() {

}

