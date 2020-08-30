#ifndef Token_h
#define Token_h
using namespace std;

class Token {
public:
    Token(string type, string value);
    string getType();
    string getValue();
    void update(string type, string value);
    void toString();

private:
    string type;
    string value;
};

Token::Token(string type, string value) {
    this -> type = type;
    this ->  value = value;
}

void Token::update(string type, string value) {
    this -> type = type;
    this ->  value = value;
}

string Token::getType() {
    return type;
}

string Token::getValue() {
    return value;
}

void Token::toString() {
    cout << "<" << type << ", " << value << ">" << endl;
}

#endif /* Token_h */
