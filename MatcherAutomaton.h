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

//Does Matcher need to handle newlines??
inline int MatcherAutomaton::Start(const string& input)
{
    //cout << "Entered Matcher with input..." << input.at(0) << "..." << endl;

    overrideMax = false;

    undefined = false;
    
    bool isMatch = true;
    inputRead = 0;

    for (unsigned int i = 0; i < toMatch.length() && isMatch; i++)
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