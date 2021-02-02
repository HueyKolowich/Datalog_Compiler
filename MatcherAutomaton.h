// Huey Kolowich
// CS_236

#ifndef MATCHERAUTOMATON_H
#define MATCHERAUTOMATON_H

#include "Automaton.h"

class MatcherAutomaton: public Automaton
{
private:
    string toMatch;

public:
    MatcherAutomaton(string toMatch, string type) 
    {
        this->toMatch = toMatch; 
        this->type = type;
    };
    //~MatcherAutomaton();

    int Start(const string& input);
};

inline int MatcherAutomaton::Start(const string& input)
{
    bool isMatch = true;
    int inputRead = 0;

    for (int i = 0; i < toMatch.length() && isMatch; i++)
    {
        if (input[i] != toMatch[i])
        {
            isMatch = false;
        }
    }

    if (isMatch)
    {
        inputRead = toMatch.length();
    }

    return inputRead;
}

#endif