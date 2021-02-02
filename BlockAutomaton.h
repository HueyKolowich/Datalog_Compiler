//Huey Kolowich
//CS_236

#ifndef BLOCKAUTOMATON_H
#define BLOCKAUTOMATON_H

#include "Automaton.h"

class BlockAutomaton: public Automaton
{
public:
    BlockAutomaton(string type)
    {
        this->type = type;
    };

    int Start(const string& input);

    void s0(const string& input);
    void s1(const string& input);
    void s2(const string& input);
    void s3(const string& input);
    void s4(const string& input);
};

inline int BlockAutomaton::Start(const string& input)
{
    inputRead = 0;

    s0(input);
    
    return inputRead;
}

inline void BlockAutomaton::s0(const string& input)
{
    //Start State
    //Needs '#' -> Comment Character

    if (input.at(inputRead) == '#')
    {
        inputRead++;
        s1(input);
    }
}

inline void BlockAutomaton::s1(const string& input)
{
    //Needs '|' -> Comment Character

    if (input.at(inputRead) == '|')
    {
        inputRead++;
        s2(input);
    }
}

inline void BlockAutomaton::s2(const string& input)
{
    //Needs '|' -> Comment Character

    while (input.at(inputRead) != '|')
    {
        // if EOF return error
        if (input.at(inputRead) == '\n')
        {
            newLines++;
        }

        inputRead++;
    }

    s3(input);
}

inline void BlockAutomaton::s3(const string& input)
{
    //Needs '|' -> Comment Character

    if (input.at(inputRead) == '|')
    {
        inputRead++;
        s4(input);
    }
}

inline void BlockAutomaton::s4(const string& input)
{
    //Needs '#' -> Comment Character

    if (input.at(inputRead) == '#')
    {
        inputRead++;
    }
}

#endif