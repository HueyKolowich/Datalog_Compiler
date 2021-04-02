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
#include "IDAutomaton.h"
#include "StringAutomaton.h"

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
    virtual ~Lexer() 
    {
        for (unsigned int i = 0; i < automata.size(); i++)
        {
            delete automata[i];
        }
        for (unsigned int j = 0; j < tokens.size(); j++)
        {
            delete tokens[j];
        }
    };

    //Parallel and Max Lexer Function
    bool run(string);

    bool output();

    vector<Token*> getTokens();

    string inputToString(string fileName);
};

#endif