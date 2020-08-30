#ifndef Scanner_h
#define Scanner_h

#include "Token.h"

using namespace std;

int E = 999;
int trans[5][6] = {
    {0, 1, 4, 2, 104, E},
    {101, 1, E, E, E, E},
    {E, E, 3, E, E, E},
    {102, E, E, E, E, E},
    {103, E, 4, E, E, E}
};

class Scanner {
public:
    Scanner();
    vector<Token> getTokens();
    void scan(string linea);
    int filter(char c);
    bool isValid(char i);
    void printTokens();
private:
    int state;
    vector<Token> tokens;
};

Scanner::Scanner() {
    state = 0;
}

vector<Token> Scanner::getTokens() {
    return tokens;
}

void Scanner::printTokens() {
    for (int i = 0; i < tokens.size(); i++) {
        tokens[i].toString();
    }
}

bool Scanner::isValid(char i) {
    if (isdigit(i) || isspace(i)) {
        return true;
    } else if (i == '#' || i == ';') {
        return true;
    } else if (i == 'A' || i == 'B' || i == 'C' || i == 'D' ||
               i == 'S' || i == 'U' || i == 'M' || i == 'I' ||  
               i == 'V' || i == 'L' || i == 'O' ) {
        return true;
    } else {
        cout << "The character " << i << " is invalid, exiting the program" <<endl;
        exit(0);
    }
}

int Scanner::filter(char c) {
    if (c == ' ' || c == '\t' || c == '\n') {
        return 0; 
    } else if (c > 47 && c < 58) {
        return 1;
    } else if (c > 64 && c < 91) {
        return 2;
    } else if (c == '#' ) {
        return 3;
    } else if (c == ';' ) {
        return 4;
    } else {
        return 5;
    }
}

//MOV 2 #A
void Scanner::scan(string linea) {
    state = 0;
    string currTok = "";
    Token tok("type", "value");

    for (int index = 0; index < linea.size(); index++) {

        char i = linea[index];
        isValid(i); 
        state = trans[state][filter(i)];
        
        switch (state) {
        case 999:
            cout << "The character " << i << " is invalid in this point, exiting the program" <<endl;
            exit(0);
            break;
        case 101:
            tok.update("integer", currTok);
            tokens.push_back(tok);
            currTok = "";
            state = 0;
            break;
        case 102:
            tok.update("register", currTok);
            tokens.push_back(tok);
            currTok = "";
            state = 0;
            break;
        case 103:
            if (currTok == "MOV") {
                tok.update("assignment", currTok);
            } else {
                tok.update("operation", currTok);
            }
            tokens.push_back(tok);
            currTok = "";
            state = 0;
            break;
        case 104:
            currTok += i;
            tok.update("EOF", currTok);
            tokens.push_back(tok);
            currTok = "";
            state = 0;
            break;
        case 0:
            //do nothing
            break;
        default:
            currTok += i;
            break;
        }
    }
}



#endif /* Scanner_h */
