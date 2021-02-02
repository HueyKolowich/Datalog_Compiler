//Huey Kolowich
//CS_236

#ifndef LEXER_H
#define LEXER_H

#include<iostream>
#include<fstream>
#include<vector>

#include "MatcherAutomaton.h"

class Lexer 
{
private:
    vector<Token*> tokens;
    vector<Automaton*> automata;

    int lineNum;
    int maxRead;
    
public:
    Lexer() 
    {
        tokens = vector<Token*>();
        automata = vector<Automaton*>();

        Automaton* Hello = new MatcherAutomaton("Hello");

        // Add all of the Automaton instances
        //automata.push_back(new ColonAutomaton());
        //automata.push_back(new ColonDashAutomaton());
        automata.push_back(Hello);
    }
    //~Lexer();

    //Parallel and Max Lexer Function
    bool run(string);

    string inputToString(string fileName);
};

#endif