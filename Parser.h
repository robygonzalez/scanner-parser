#ifndef Parser_h
#define Parser_h

#include <iostream>
#include <vector>
#include "Scanner.h"

using namespace std;

class Parser {
public:
    //constructor
    Parser();
    void parse(vector<Token> tokens);
private:
    bool match(vector<Token> &tokens, Token expectedToken);
    void parseS(vector<Token> tokens);
};

Parser::Parser() {

}

bool Parser::match(vector<Token> &tokens, Token expectedToken) {

    if (!tokens.empty()) {
        if (tokens[0].getType() == expectedToken.getType()) {
            cout << expectedToken.getType() << endl;
            tokens.erase(tokens.begin());
            return true;
        } else {
            cout << "ERROR: Expecting '" << expectedToken.getType() 
                 << "', found '" << tokens[0].getType() << "'." << endl;
            cout << "The system will halt." << endl;
            exit(0);
        }
    } else {
            cout << "ERROR: Expecting '" << expectedToken.getType()
                 << "', found nothing." << endl;
            cout << "The system will halt." << endl;
            exit(0);
    }
        

}

void Parser::parseS(vector<Token> tokens) {
    
    if (tokens.empty()) {
        cout << "SYNTACTIC ERROR: Expecting a token, found nothing." << endl;
        cout << "The system will halt." << endl;
        exit(0);
    }

    string type = tokens[0].getType();

    if (type == "EOF") {
        match(tokens, Token("EOF", ";"));
        return;

    } else if (type == "operation") {
        match(tokens, Token("operation", ""));
        match(tokens, Token("register", ""));

    } else if (type == "assignment") {
        match(tokens, Token("assignment", ""));
        if (tokens[0].getType() == "register") {
            match(tokens, Token("register", ""));
        } else if (tokens[0].getType() == "integer") {
            match(tokens, Token("integer", ""));
        }

    } else {
        cout << "ERROR: Unexpected '" << type << "'." << endl;
        cout << "The system will halt." << endl;
        exit(0);
    }

    match(tokens, Token("register", ""));
    cout << endl;
    parseS(tokens);

}

void Parser::parse(vector<Token> tokens) {

    parseS(tokens);
    cout << "The input is a well formed expression." << endl;

}

#endif /* Parser_h */
