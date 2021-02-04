//Huey Kolowich
//CS_236

#ifndef STRINGAUTOMATON_H
#define STRINGAUTOMATON_H

#include "Automaton.h"

class StringAutomaton: public Automaton
{
private:
    bool backtrack = false;
public:
    StringAutomaton(string type)
    {
        this->type = type;
    }

    int Start(const string& input);

    void s0(const string& input); 
    void s1(const string& input);
    void s2(const string& input);
};

inline int StringAutomaton::Start(const string& input)
{
    inputRead = 0;

    overrideMax = false;

    undefined = false;

    backtrack = false;

    newLines = 0;

    s0(input);
    
    return inputRead;
}

inline void StringAutomaton::s0(const string& input)
{
    //Start State
    //Needs '\'' -> Comment Character

    //cout << "Entered String with input..." << input.at(0) << "..." << endl;

    if (backtrack)
    {
        return;
    }

    if (input.at(inputRead) == '\'')
    {
        inputRead++;
        s1(input);
    }
}

inline void StringAutomaton::s1(const string& input)
{
    //Needs '\'' -> Comment Character to advance

    //cout << "Entered s1 with input..." << input.at(inputRead) << "..." << endl;

    while (input.at(inputRead) != '\'')
    {
        //cout << "In while:" << input.at(inputRead) << ":" << endl;

        if (input.at(inputRead) == '\n') 
        {
            newLines++;
        }
        if ((input.at(inputRead) == '\n') && ((input.length() - inputRead) == 1))
        {
            //cout << "Set Undefined..." << endl;
            undefined = true;
            backtrack = true;

            inputRead++;
            return;
        }

        inputRead++;
    }

    inputRead++;
    s2(input);
}

inline void StringAutomaton::s2(const string& input)
{
    //Needs '\'' -> Comment Character to return

    //cout << "Entered s2 with input..." << input.at(0) << "..." << endl;

    if (input.at(inputRead) == '\'')
    {
        inputRead++;
        s1(input);
    }
    //cout << "Newlines: " << newLines << endl;
}

#endif