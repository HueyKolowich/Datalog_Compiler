//Huey Kolowich
//CS_236

#include "Lexer.h"


bool Lexer::run(string input) 
{
    lineNum = 1;

    while (input.size() > 0)
    {
        //set maxRead to 0
        maxRead = 0;
        //set maxAutomaton to the first automaton in automata??

        // TODO: you need to handle whitespace inbetween tokens
        // TODO: cannot handle whitespace after string, throws "out_of_range"
        while (input[0] == ' ' || input[0] == '\n')
        {
            //cout << "Accomadated for whitespace..." << endl;
            input = input.substr(1);
        }
        
        // Each automaton runs with the same input
        Automaton* automaton;
        int inputRead;

        for (int i = 0; i < automata.size(); i++)
        {
            automaton = automata[i];
            inputRead = automaton->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                //set maxAutomaton to automaton
            }
        }
       
       if (maxRead > 0) 
       {
            //set newToken to maxAutomaton.CreateToken(...)
            //increment lineNumber by maxAutomaton.NewLinesRead()
            //add newToken to collection of all tokens

            cout << "maxRead: " << maxRead << endl;
        }// No automaton accepted input; create invalid token
        else 
        {
                //set maxRead to 1
                maxRead = 1;
                //set newToken to a new invalid Token
                //(with first character of input)
                //add newToken to collection of all tokens
        }
        // Update ‘input‘ by removing characters read to create Token
        //remove maxRead characters from input

        input = input.substr(maxRead);
    }

    return true;
}



//Returns string of file formatted to mimick the file
string Lexer::inputToString(string fileName)
{
    ifstream file (fileName.c_str());
    string line;

    string outString = "";

    if (file.is_open())
    {
        while (getline(file, line))
        {
            outString = outString + line + '\n';
        }
    }

    file.close();

    return outString;
}