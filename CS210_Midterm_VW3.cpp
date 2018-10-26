/*
 * Built by Richard Deming
 * github.com/obenaf
 * Midterm for CS-210
 * 24 Sep 2018
 * This program takes a file and
 * splits it into individual lexemes
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
int imSorry = 0;
char activeChar;
char nextChar;
char lexeme[1026];
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
bool opCompare2(int);
bool hexCompare();
//Character class definitions
enum cClass{ALPHA, DIGIT, UNK};
cClass charClass;

int main(int argc, char **argv) {
    //sets I/O file names
    string readFile = argv[1];
    string writeFile = readFile + ".lexer";
    //opens files
    primeRead.open(readFile);
    primeWrite.open(writeFile);

    primeRead.get(nextChar);
    traverseSpace(); //Added because trie.cci is a jerk
    while (imSorry < 64) { //I'm sorry this is really dumb but it works
        imSorry = 0;
        readChar();
        analyze();
        primeWrite << sLexeme << " (" << token << ")\n";
        memset(lexeme, 0, sizeof(lexeme)); //resets lexeme array
        lexLength = 0; //resets lexLength
        traverseSpace(); //eliminates whitespace
    }
    primeRead.close();
    primeWrite.close();
    return 0;
}

//Reads characters and determines char type
void readChar() {
    activeChar = nextChar;
    if(primeRead.get(nextChar)) {
        if(isdigit(activeChar))
            charClass = DIGIT;
        else if(isalpha(activeChar))
            charClass = ALPHA;
        else
            charClass = UNK;
    }
}

//Sorts characters into token groups
void analyze() {
    switch(charClass) {
        //FOR NUMERIC LITERALS
        case DIGIT:
            while(!(nextChar == ' ' || nextChar == '\n' || opCompare2(26))) {
                if(isalpha(nextChar) && !hexCompare())
                    break;
                lexAdd();
                readChar();
            }
            lexAdd();
            sLexeme = lexeme;
            token = tokClass[5];
            break;

            //FOR KEYWORDS AND IDENTIFIERS
            case ALPHA:
                //As long as the chars meet criteria for keywords/identifiers
                while (!(nextChar == ' ' || nextChar == '\n' || opCompare2(27))) {
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

            case UNK:
                //FOR COMMENTS
                if (activeChar == '/' && nextChar == '*') {
                    while (!(activeChar == '*' && nextChar == '/')){
                        lexAdd();
                        readChar();
                    }
                    lexAdd();
                    readChar();
                    lexAdd();//adds the final */
                    sLexeme = lexeme;
                    token = tokClass[0]; //sets token to comment
                }
                //FOR STRINGS
                else if (activeChar == '"') { //if lexeme is string
                    do {
                        lexAdd();
                        readChar();
                    } while (nextChar != '"');
                    lexAdd();
                    readChar();
                    lexAdd(); //adds the final "
                    sLexeme = lexeme;
                    token = tokClass[2]; //sets token to string
                }
                //FOR CHARACTER LITERALS
                else if (activeChar == 39) {
                    do {
                        lexAdd();
                        readChar();
                    } while(nextChar != 39);
                    lexAdd();
                    readChar();
                    lexAdd(); //adds the final '
                    sLexeme = lexeme;
                    token = tokClass[4];
                }
                //FOR OPERATORS
                else {
                    //I know this is dirty but I ran in to it last second
                    while(!(nextChar == ' ' || nextChar == '\n' || isalnum(nextChar) || opCompare2(10) || nextChar == '"' || nextChar == 39)) {
                        lexAdd();
                        readChar();
                    }
                    lexAdd();
                    sLexeme = lexeme;
                    if(opCompare())
                        token = tokClass[1]; //sets to operator
                    else
                    token = "UNK";
                }
                break;
        default:
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
    while((nextChar == ' ' || nextChar == '\n') && (imSorry <= 64)) {
        readChar();
        imSorry++;
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
bool strCompare() {
    for(int i = 0; i < 37; i++) {
        if(sLexeme == Keywords[i])
            return true;
    }
    return false;
}

string Operators[27] = {"(", ")", "+", "-", "/",
                        "|", "&", ";", ":", "[", "]", "=", ":=",
                        "..", "<<", ">>", "<>", "<=", ">=", "**",
                        "!=", "=>", "<", ">", "*", ",", "."};
//Compares operators to completed output strings
bool opCompare() {
    for(string i : Operators) {
        if(sLexeme == i)
            return true;
    }

    return false;
}
//Compares operators to single characters
bool opCompare2(int y) {
    string x;
    x = nextChar;
    for(int i = 0; i < y; i++) {
        if(x == Operators[i])
            return true;
    }
    return false;
}
//Checks for hexadecimal letters in numeric literals
char Hexa[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
bool hexCompare() {
    for(char i : Hexa) {
        if(nextChar == i)
            return true;
    }
    return false;
}
