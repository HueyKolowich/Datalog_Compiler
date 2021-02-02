//Huey Kolowich
//CS 236

#include "Lexer.h"

bool lexerTests(bool argv1, char* argv1_c);

int main(int argc, char* argv[]) 
{
    
    if (argv[1])
    {
        lexerTests(true, argv[1]);
    } else {
        lexerTests(false, nullptr);
    }

    return 0;
}

bool lexerTests(bool argv1, char* argv1_c)
{
    //Testing for lexer
    cout << "Begin Testing for Lexer..." << endl;

    Lexer* lexy = new Lexer();

    cout << "######################################" << endl;

    if (argv1)
    {
        cout << "Testing toString..." << endl;

        string testInput = lexy->inputToString(argv1_c);

        cout << "String: " << testInput << endl;
    }
    
    cout << "Testing run..." << endl;

    bool testRun = lexy->run("Hello");

    cout << "Run output: " << testRun << endl;

    //delete lexy;
    cout << "Testing Complete." << endl;

    return true;
}