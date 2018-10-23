/*
 * Built by Richard Deming
 * github.com/obenaf
 * Midterm for CS-210
 * 24 Sep 2018
 * Right now the program considers any block of characters separated by spaces
 * to be a single lexeme. This will change when lex logic is added in.
 * There are also weird issues with sorting out newline characters.
 */

#include"stdio.h"
#include<iostream>
#include<cstring>
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
char lexeme[32];
int lexLength = 0;
string token;
//I/O file streams
ifstream primeRead;
ofstream primeWrite;
//Function Headers in order
void readChar();
void analyze();
void lexAdd();
void traverseSpace();
void cleanUp();
bool strCompare();
//Character class definitions
enum cClass{ALPHA, DIGIT, UNK, END};
cClass charClass;

int main(int argc, char **argv) {
    //sets I/O file names
    string readFile = argv[1];
    string writeFile = readFile + ".cpy";
    //opens I/O files
    primeRead.open(readFile);
    primeWrite.open(writeFile);

    primeRead.get(nextChar);
    while (!(primeRead.eof())) {
        analyze();
        cleanUp();
        primeWrite << sLexeme << " (" << token << ")\n";
        memset(lexeme, 0, sizeof(lexeme));
        lexLength = 0; //resets lexLength
        traverseSpace();
    }
    primeRead.close();
    primeWrite.close();
    return 0;
}

//Reads characters and determines char type
void readChar() {
    activeChar = nextChar;
    primeRead.get(nextChar);
    if(activeChar != EOF) {
        if(isdigit(activeChar))
            charClass = DIGIT;
        else if(isalpha(activeChar))
            charClass = ALPHA;
        else
            charClass = UNK;
    } else
        charClass = END;
}

//Sorts characters into token groups
void analyze() {
    readChar();
    switch(charClass) {
        //if the char is a digit
        case DIGIT: //numeric literal, may need specification
            while(!isspace(activeChar)){
                lexAdd();
                readChar();
            }
            sLexeme = activeChar;
            token = tokClass[5];
            break;

            //if the value is alphabetical
            case ALPHA: //Case for keywords and identifiers
                //As long as the chars meet criteria for keywords/identifiers
                while (!isspace(activeChar)){
                    lexAdd();
                    readChar();
                }
                lexAdd();
                sLexeme = lexeme; //converts lexeme array to string

                if (strCompare())//if lexeme matches keyword list
                    token = tokClass[3]; //sets as keyword
                else //not a keyword
                    token = tokClass[6]; //sets as identifier
                break;

            //if the variable is not alphanumerical
            case UNK:
                if (activeChar == '/' && nextChar == '*') { //if lexeme is comment
                    while (activeChar != '*' && nextChar != '/'){
                        lexAdd();
                        readChar();
                    }
                    token = tokClass[0]; //sets token to comment
                }
                else if (activeChar == '"') { //if lexeme is string
                    while (activeChar != '"'){
                        lexAdd();
                        readChar();
                    }
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
            case END:
                break;
        }
}


//adds activeChar into the working lexeme
void lexAdd() {
    lexeme[lexLength] = activeChar;
    lexLength++;
}

char cleanArr[32];
void cleanUp() {
    int x = 0;
    for(int i = 0; i++; i <= lexLength) {
        if(!isspace(lexeme[i]) && lexeme[i] != '\n') {
            cleanArr[x] = lexeme[i];
            x++;
        }
    }
}

//finds the next character
void traverseSpace() {
    while(activeChar == ' ' || activeChar == '\n') {
            readChar();
        }
}

//compares the lexeme to keyword list
bool strCompare() { //may improve search in future
    for(int i = 0; i < 37; i++) {
        if(sLexeme == Keywords[i])
            return true;
    }
    return false;
}

