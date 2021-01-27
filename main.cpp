//Huey Kolowich
//CS 236

#include <iostream>

#include "Lexer.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    //Testing for lexer
    cout << "Begin Testing for Lexer..." << endl;

    Lexer lexy = Lexer();

    cout << "argc: " << argc << endl;
    cout << "argv: " << argv[1] << endl;

    cout << "######################################" << endl;

    cout << "Testing toString..." << endl;

    string testInput = lexy.inputToString(argv[1]);

    cout << "String: " << testInput << endl;
    

    cout << "Testing Complete." << endl;
    return 0;
}