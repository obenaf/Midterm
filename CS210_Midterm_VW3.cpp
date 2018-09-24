/*
 * Built by Richard Deming
 * github.com/obenaf
 * Midterm for CS-210
 * 18 Sep 2018
 */
 //NOTE: I haven't decided how I want to write to the output file
 //yet, will implement that when I am further along

#include<cstdio>
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
string sLexeme;
char lexeme[63];
char nextChar;
int charClass;
int lexLength = 0;
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
    ifstream primeRead;
    ofstream primeWrite;
    //opens I/O files
    primeRead.open(readFile);
    primeWrite.open(writeFile);

    readChar();
    do {
        analyze();
        primeWrite << lexeme << " (" << token << ")\n";
    } while (nextToken != EOF);
    return 0;
}
//Sorts characters into subgroups
void analyze() {
    lexLength = 0; //resets lexLength
    switch(charClass) {
        case ALPHA:
            lexAdd();
            readChar();
            //As long as the chars meet criteria for keywords/identifiers
            while(charClass == ALPHA ||charClass == DIGIT) {
                lexAdd();
                readChar();
            }
            sLexeme = lexeme;
                if(strCompare())//if lexeme matches keyword list
                    token = tokClass[3]; //sets as keyword
                    else //not a keyword
                    token = tokClass[6]; //sets as identifier
                    break;
        case UNK:
            if(activeChar == '/' && nextChar == '*') { //if lexeme is comment
                do {
                    lexAdd();
                    readChar();
                } while (activeChar != '*' && nextChar != '/');
            }
                else if(activeChar == '"') { //if lexeme is string
                    do {
                        lexAdd();
                        readChar();
                    } while(activeChar != '"');
                }
                //else if(activeChar ==  NONFUNCTIONAL
                else
                    unknown();
                  break;
        case EOF:
            nextToken = EOF;
            break;
            }



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
//adds activeChar into the working lexeme
void lexAdd() {
    lexeme[lexLength++] = activeChar;
    lexeme[lexLength] = 0;
}
//finds the next character
void traverseSpace() {
    while(isspace(nextChar))
        nextChar = getc(primeRead);
}

bool strCompare() {
    for(int i = 0; i < 37; i++) {
        if(sLexeme == Keywords[i])
            return true;
    }
    return false;
}

void unknown() {
    sLexeme = activeChar;
    token = "UNK";
}