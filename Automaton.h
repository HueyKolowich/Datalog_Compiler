//Huey Kolowich
//CS_236

#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "Token.h"

class Automaton
{
protected:
    int inputRead = 0;
    int newLines = 0;

    bool overrideMax = false;
    bool undefined = false;

    //TokenType type;
    string type;

public:
    Automaton(string type) { this->type = type; };
    Automaton() = default;
    //virtual ~Automaton();

    // Start the automaton and return the number of characters read
    // read == 0 indicates the input was rejected
    // read > 0 indicates the input was accepted
    virtual int Start(const string& input) = 0;

    
    virtual Token* CreateToken(string input, int lineNumber) 
    {
        return new Token(type, input, lineNumber);
    }
    
    virtual Token* CreateUndefinedToken(string input, int lineNumber) 
    {
        return new Token("UNDEFINED", input, lineNumber);
    }

   virtual int NewLinesRead() const { return newLines; }

   virtual string getType() const { return type; }

   virtual bool getOverride() const { return overrideMax; }

   virtual bool getUndefined() const { return undefined; }

};

#endif