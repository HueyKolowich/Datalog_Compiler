//Huey Kolowich
//CS_236

#ifndef LEXER_H
#define LEXER_H

#include<iostream>
#include<fstream>
#include<vector>

#include "MatcherAutomaton.h"
#include "CommentAutomaton.h"
#include "BlockAutomaton.h"

class Lexer 
{
private:
    vector<Token*> tokens;
    vector<Automaton*> automata;

    Token* newToken;
    Automaton* maxAutomaton;

    int lineNum;
    int maxRead;
    
public:
    Lexer();
    //~Lexer();

    //Parallel and Max Lexer Function
    bool run(string);

    bool output();

    string inputToString(string fileName);
};

#endif