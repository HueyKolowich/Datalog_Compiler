//Huey Kolowich
//CS_236

#ifndef BLOCKAUTOMATON_H
#define BLOCKAUTOMATON_H

#include "Automaton.h"

class BlockAutomaton: public Automaton
{
private:
    bool backtrack = false;    
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
};

inline int BlockAutomaton::Start(const string& input)
{
    inputRead = 0;

    overrideMax = false;

    undefined = false;

    backtrack = false;

    newLines = 0;

    s0(input);
    
    return inputRead;
}

inline void BlockAutomaton::s0(const string& input)
{
    //Start State
    //Needs '#' -> Comment Character

    if (backtrack)
    {
        return;
    }

    //cout << "Entered Block with input..." << input.at(0) << "..." << endl;

    if (input.at(inputRead) == '#')
    {
        inputRead++;
        s1(input);
    }
}

inline void BlockAutomaton::s1(const string& input)
{
    //Needs '|' -> Comment Character

    if (backtrack)
    {
        return;
    }

    //cout << "Entered s1 with input..." << input.at(inputRead) << "..." << endl;

    if (input.at(inputRead) == '|')
    {
        inputRead++;
        s2(input);
    }
}

inline void BlockAutomaton::s2(const string& input)
{
    //Needs '|' -> Comment Character

    if (backtrack)
    {
        return;
    }

    //cout << "Entered s2 with input..." << input.at(inputRead) << "..." << endl;

    while (input.at(inputRead) != '|')
    {
        //cout << "s2:" << input.at(inputRead) << ":" << endl;

        // if EOF return error
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
    s3(input);
}

inline void BlockAutomaton::s3(const string& input)
{
    //Needs '#' -> Comment Character

    if (backtrack)
    {
        return;
    }

    //cout << "Entered s3 with input..." << input.at(inputRead) << "..." << endl;

    if (input.at(inputRead) == '#')
    {
        inputRead++;
        overrideMax = true;
    } else
    {
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
        } else 
        {
            inputRead++; 
            s2(input);
        }
    }
}

#endif