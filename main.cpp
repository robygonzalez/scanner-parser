#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <ctype.h>
#include "Scanner.h"
#include "Parser.h"

using namespace std;

int main() {

    // Input file
    string linea;
    ifstream archivo;

    archivo.open("prueba.txt"); 

    if (archivo.fail()) {
        cout << "Hubo un problema al abrir el archivo" << endl;
        exit(0);
    }

    // Scanner
    Scanner scanner;
    while (!archivo.eof()) {
        getline(archivo, linea);
        if (!isspace(linea[linea.length()-1])) {
            linea += " ";
        }
        scanner.scan(linea);
    }
    scanner.printTokens();
    cout << endl;

    // Parser
    Parser parser;
    parser.parse(scanner.getTokens());
}