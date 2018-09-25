/*
 * Built by Richard Deming
 * github.com/obenaf
 * Midterm for CS-210
 * 24 Sep 2018
 */
 //NOTE: I haven't decided how I want to write to the output file
 //yet, will implement that when I am further along
#include<stdio.h>
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
//Keyword array
string Keywords[37] = {"accessor", "and", "array", "begin", "bool",
                       "case", "character", "constant", "else", "elsif",
                       "end", "exit", "function", "if", "in", "integer",
                       "interface", "is", "loop", "module", "mutator",
                       "natural", "null", "of", "or", "others", "out",
                       "positive", "procedure", "range", "return", "struct",
                       "subtype", "then", "type", "when", "while"};
//Operators array
string Operators[27] = {".", "<", ">", "(", ")", "+", "-", "*", "/",
                        "|", "&", ";", ",", ":", "[", "]", "=", ":=",
                        "..", "<<", ">>", "<>", "<=", ">=", "**",
                        "!=", "=>"};
//Token class array
string tokClass[8] = {"comment", "operator", "string", "keyword", "character literal",
                      "numeric literal", "identifier", "UNK"};
//Global Variables
char activeChar;
char nextChar;
string sLexeme;
char lexeme[64];
int charClass;
int lexLength;
string token;
int nextToken;
FILE *primeRead;
//Function Headers
bool strCompare();
void analyze();
void readChar();
void lexAdd();
void traverseSpace();
void unknown();
//Classes
#define ALPHA 0
#define DIGIT 1
#define UNK 2

int main(int argc, char **argv) {
    //sets I/O file names
    string readFile = argv[1];
    string writeFile = readFile + ".unk";
    //opens I/O files
    ifstream primeRead(readFile, ios::in);
    ofstream primeWrite(writeFile, ios::out);

    primeRead.get(nextChar);
    readChar();
    while (nextToken != EOF) {
        analyze();
        primeWrite << lexeme << " (" << token << ")\n";
        traverseSpace();
        readChar();
    }
    primeRead.close();
    primeWrite.close();
    return 0;
}
//Reads characters and determines char type
void readChar() {
    activeChar = nextChar;
    if((nextChar = getc(primeRead)) != EOF) {
        if(isalpha(activeChar))
            charClass = ALPHA;
        else if(isdigit(activeChar))
            charClass = DIGIT;
        else
            charClass = UNK;
    }
    else charClass = EOF;
}
//Sorts characters into subgroups
void analyze() {
    lexLength = 0; //resets lexLength
    switch(charClass) {
        case DIGIT:
            while(nextChar != ' ') {
                lexAdd();
                readChar();
            }
            sLexeme = activeChar;
            token = "UNK";
            break;
        case ALPHA: //Case for keywords and identifiers
            //As long as the chars meet criteria for keywords/identifiers
            while (charClass == ALPHA || charClass == DIGIT) {
                lexAdd();
                readChar();
            }
            sLexeme = lexeme;
            if (strCompare())//if lexeme matches keyword list
                token = tokClass[3]; //sets as keyword
            else //not a keyword
                token = tokClass[6]; //sets as identifier
            break;
        case UNK:
            if (activeChar == '/' && nextChar == '*') { //if lexeme is comment
                do {
                    lexAdd();
                    readChar();
                } while (activeChar != '*' && nextChar != '/');
            } else if (activeChar == '"') { //if lexeme is string
                do {
                    lexAdd();
                    readChar();
                } while (activeChar != '"');
            }
                //else if(activeChar ==  NONFUNCTIONAL
            else
                while(nextChar != ' ') {
                    lexAdd();
                    readChar();
                }
            sLexeme = activeChar;
            token = "UNK";
            break;
        case EOF:
            nextToken = EOF;
            break;
    }


    }
//adds activeChar into the working lexeme
void lexAdd() {
    lexeme[lexLength++] = activeChar;
    lexeme[lexLength] = 0;
}
//finds the next character
void traverseSpace() {

primeRead get(nextChar);
}

bool strCompare() {
    for(int i = 0; i < 37; i++) {
        if(sLexeme == Keywords[i])
            return true;
    }
    return false;
}

