/*
 * Built by Richard Deming
 * github.com/obenaf
 * Midterm for CS-210
 * 24 Sep 2018
 *
 */

#include<cctype>
#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;

//Token class array
string tokClass[8] = {"comment", "operator", "string", "keyword", "character literal",
                      "numeric literal", "identifier", "UNK"};
//Global Variables
char activeChar;
char nextChar;
char lexeme[128];
string sLexeme;
string token;
int lexLength = 0;
//I/O file streams
ifstream primeRead;
ofstream primeWrite;
//Function Headers in order
void readChar();
void analyze();
void lexAdd();
void traverseSpace();
bool strCompare();
bool opCompare();
bool opCompare2();
//Character class definitions
enum cClass{ALPHA, DIGIT, UNK, END};
cClass charClass;

int main(int argc, char **argv) {
    //sets I/O file names
    string readFile = argv[1];
    string writeFile = readFile + ".cpy";
    //opens files
    primeRead.open(readFile);
    primeWrite.open(writeFile);

    primeRead.get(nextChar);
    while (charClass != END) {
        readChar();
        analyze();
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
        if(isdigit(activeChar))
            charClass = DIGIT;
        else if(isalpha(activeChar))
            charClass = ALPHA;
        else if(activeChar != EOF)
            charClass = UNK;
        else
            charClass = END;
}

//Sorts characters into token groups
void analyze() {
    switch(charClass) {
        //if the char is a digit
        //FOR NUMERIC LITERALS    WORKS
        case DIGIT:
            while(!(activeChar == ' ' || activeChar == '\n')) {
                lexAdd();
                readChar();
            }
            sLexeme = lexeme;
            token = tokClass[5];
            break;

            //FOR KEYWORDS AND IDENTIFIERS    ALMOST WORKS
            case ALPHA:
                //As long as the chars meet criteria for keywords/identifiers
                while (!(activeChar == ' ' || activeChar == '\n' || opCompare2())) {
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
                //FOR COMMENTS    WORKS
                if (activeChar == '/' && nextChar == '*') {
                    while (!(activeChar == '*' && nextChar == '/')){
                        lexAdd();
                        readChar();
                    }
                    lexAdd();
                    readChar();
                    lexAdd();
                    readChar(); //I know this is dirty but it works for now
                    sLexeme = lexeme;
                    token = tokClass[0]; //sets token to comment
                }
                //FOR STRINGS    WORKS
                else if (activeChar == '"') { //if lexeme is string
                    do {
                        lexAdd();
                        readChar();
                    } while (activeChar != '"');
                    lexAdd();
                    readChar();
                    sLexeme = lexeme;
                    token = tokClass[2]; //sets token to string
                }
                //FOR OPERATORS
                else {
                    while(!(activeChar == ' ' || activeChar == '\n' || charClass != UNK)) {
                        lexAdd();
                        readChar();
                    }
                    sLexeme = lexeme;
                    if(opCompare())
                        token = tokClass[1]; //sets to operator
                    else
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

//finds the next character
void traverseSpace() {
    while(nextChar == ' ' || nextChar == '\n') {
        readChar();
        }
}

string Keywords[37] = {"accessor", "and", "array", "begin", "bool",
                       "case", "character", "constant", "else", "elsif",
                       "end", "exit", "function", "if", "in", "integer",
                       "interface", "is", "loop", "module", "mutator",
                       "natural", "null", "of", "or", "others", "out",
                       "positive", "procedure", "range", "return", "struct",
                       "subtype", "then", "type", "when", "while"};
//compares the lexeme to keyword list
bool strCompare() { //may improve search in future
    for(int i = 0; i < 37; i++) {
        if(sLexeme == Keywords[i])
            return true;
    }
    return false;
}

string Operators[27] = {".", "<", ">", "(", ")", "+", "-", "*", "/",
                        "|", "&", ";", ",", ":", "[", "]", "=", ":=",
                        "..", "<<", ">>", "<>", "<=", ">=", "**",
                        "!=", "=>"};

bool opCompare() {
    for(int i = 0; i < 27; i++) {
        if(sLexeme == Operators[i])
            return true;
    }
    return false;
}

bool opCompare2() {
    string x;
    x = activeChar;
    for(int i = 0; i < 27; i++) {
        if(x == Operators[i])
            return true;
    }
    return false;
}