//Huey Kolowich
//CS_236

#ifndef IDAUTOMATON_H
#define IDAUTOMATON_H

#include "Automaton.h"

class IDAutomaton: public Automaton
{
public:
    IDAutomaton(string type)
    {
        this->type = type;
    }

    int Start(const string& input);

    void s0(const string& input); 
    void s1(const string& input);      
};

inline int IDAutomaton::Start(const string& input)
{
    inputRead = 0;

    overrideMax = false;

    undefined = false;

    s0(input);
    
    return inputRead;
}

inline void IDAutomaton::s0(const string& input)
{
    //Start State
    //Needs a letter character

    //cout << "Entered ID with input..." << input.at(0) << "..." << endl;

    if (isalpha(input.at(inputRead)))
    {
        inputRead++;
        s1(input);
    }
}

inline void IDAutomaton::s1(const string& input)
{
    //Start State
    //Needs a letter character

    while (!isspace(input.at(inputRead))  
                && ( (input.at(inputRead) != ':') 
                && (input.at(inputRead) != '+') 
                && (input.at(inputRead) != '*')
                && (input.at(inputRead) != ')')
                && (input.at(inputRead) != '(')
                && (input.at(inputRead) != '?')
                && (input.at(inputRead) != '.')
                && (input.at(inputRead) != ',')
                && (input.at(inputRead) != '#')) ) //need to accomadate for end of file, diff with lab computer?
    {
        inputRead++;
        //cout << "While Input..." << input.at(inputRead) << "..." << endl;
    }
}

#endif