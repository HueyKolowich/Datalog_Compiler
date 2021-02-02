//Huey Kolowich
//CS_236

#ifndef COMMENTAUTOMATON_H
#define COMMENTAUTOMATON_H

#include "Automaton.h"

class CommentAutomaton: public Automaton
{
public:
    CommentAutomaton(string type)
    {
        this->type = type;
    }

    int Start(const string& input);

    void s0(const string& input);
    void s1(const string& input);
};

inline int CommentAutomaton::Start(const string& input)
{
    inputRead = 0;

    s0(input);
    
    return inputRead;
}

inline void CommentAutomaton::s0(const string& input)
{
    //Start State
    //Needs '#' -> Comment Character

    if (input.at(inputRead) == '#')
    {
        inputRead++;
        s1(input);
    }
}

inline void CommentAutomaton::s1(const string& input)
{
    //Accepts any character
    //Changes state when '\n' or EOF is found
    //Fails if '\n' or EOF are not found

    while (input.at(inputRead) != '\n') //need to accomadate for end of file, diff with lab computer?
    {
        inputRead++;
    }

    //Shouldn't need to update newline.... I think
}

#endif