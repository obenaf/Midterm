/*
 * Built by Richard Deming
 * github.com/obenaf
 * Midterm for CS-210
 * 24 Sep 2018
 */
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
//Function Headers in order
void readChar();
void analyze();
void lexAdd();
void traverseSpace();
bool strCompare();
//Character class definitions
#define ALPHA 0
#define DIGIT 1
#define UNK 2

int main(int argc, char **argv) {
    //sets I/O file names
    string readFile = argv[1];
    string writeFile = readFile + ".unk";
    //opens I/O files
    ifstream primeRead(readFile);
    ofstream primeWrite(writeFile);

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
    if((nextChar = fgetc(primeRead)) != EOF) {
        if(isdigit(activeChar))
            charClass = DIGIT;
        else if(isalpha(activeChar))
            charClass = ALPHA;
        else
            charClass = UNK;
    }
    else charClass = EOF;
}
//Sorts characters into subgroups
void analyze() {
    lexLength = 0; //resets lexLength
    switch(charClass) {
        //if the char is a digit
        case DIGIT:
            while(nextChar != ' ') {
                lexAdd();
                readChar();
            }
            sLexeme = activeChar;
            token = "UNK";
            break;
            //if the value is alphabetical
        case ALPHA: //Case for keywords and identifiers
            //As long as the chars meet criteria for keywords/identifiers
            while (charClass == ALPHA || charClass == DIGIT) {
                lexAdd();
                readChar();
            }
            sLexeme = lexeme; //converts lexeme array to string
            if (strCompare())//if lexeme matches keyword list
                token = tokClass[3]; //sets as keyword
            else //not a keyword
                token = tokClass[6]; //sets as identifier
            break;
            //if the variable is not alphanumerical
        case UNK:
            if (activeChar == '/' && nextChar == '*') { //if lexeme is comment
                do {
                    lexAdd();
                    readChar();
                } while (activeChar != '*' && nextChar != '/');
                token = tokClass[0]; //sets token to comment
            } else if (activeChar == '"') { //if lexeme is string
                do {
                    lexAdd();
                    readChar();
                } while (activeChar != '"');
            }
                //else if(activeChar ==  NONFUNCTIONAL
            else {
                while(nextChar != ' ') {
                    lexAdd();
                    readChar();
                }
                sLexeme = activeChar;
                token = "UNK";
            }
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
    while(nextChar != ' ')
nextChar = fgetc(primeRead);
}
//compares the lexeme to keyword list
bool strCompare() { //may improve search in future
    for(int i = 0; i < 37; i++) {
        if(sLexeme == Keywords[i])
            return true;
    }
    return false;
}

