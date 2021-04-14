//Huey Kolowich
//CS 236

#include "Lexer.h"
#include "Parser.h"

// vector<Token*> lexerTests(bool argv1, char* argv1_c);
// bool parserTests(vector<Token*> &tokens);

int main(int argc, char* argv[]) 
{
    // vector<Token*> _tokens;
    
    // if (argv[1])
    // {    
    //     _tokens = lexerTests(true, argv[1]);

    //     parserTests(_tokens);
    // } else {
    //     cout << "No input file found..." << endl;

    //     _tokens = lexerTests(true, nullptr);

    //     parserTests(_tokens);
    // }

    //Lexer
    Lexer* lexy = new Lexer();
    string testInput;
    vector<Token*> tokens;

    if (argv[1])
    {
        testInput = lexy->inputToString(argv[1]);
    } else {
        testInput = "";
    }

    lexy->run(testInput);

    tokens = lexy->getTokens();

    //Parser
    Parser* parsy = new Parser(tokens);

    parsy->run();

    delete lexy;
    delete parsy;
    return 0;
}

// vector<Token*> lexerTests(bool argv1, char* argv1_c)
// {
//     //Testing for lexer
//     // cout << "Begin Testing for Lexer..." << endl;

//     Lexer* lexy = new Lexer();
//     string testInput;
//     vector<Token*> tokens;

//     // cout << "######################################\n\n" << endl;

//     if (argv1)
//     {
//         // cout << "Testing toString..." << endl;

//         testInput = lexy->inputToString(argv1_c);

//         // cout << "String: " << testInput << endl;
//     } else
//     {
//         testInput = "";
//     }

//     // cout << "######################################\n\n" << endl;
    
//     // cout << "Testing run..." << endl;

//     // bool testRun = lexy->run(testInput);
    
//     lexy->run(testInput);

//     // cout << "Run output: " << testRun << endl;

//     // cout << "######################################\n\n" << endl;

//     // cout << "Testing output..." << endl;

//     // bool testOutput = lexy->output();

//     // lexy->output();

//     tokens = lexy->getTokens();

//     // cout << "Output's output: " << testOutput << endl;

//     // cout << "######################################\n\n" << endl;

//     delete lexy;

//     // cout << "Testing Complete." << endl;

//     return tokens;
// }

// bool parserTests(vector<Token*> &tokens)
// {
//     Parser* parsy = new Parser(tokens);

//     parsy->run();

//     // delete parsy;

//     return true;
// }