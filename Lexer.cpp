//Huey Kolowich
//CS_236

#include "Lexer.h"

/*
bool Lexer::run(string input) 
{
    //Initialize two variables: maximum read value to 0 
    //and corresponding maximum finitestate automaton 
    //(denoted as the “max automaton”) to the first finite-state automaton
    //in the collection

    //For each finite-state automaton
        /*
        Give it the input string and have it return whether or not it accepts the string
        (first n-symbols of the string)
        – Get the number of symbols (characters) read by it
        – Update the maximum read value if more than the current value and then update
        max automaton to reference the current finite-state automaton
        */

    //Now that we’ve found the finite-state automaton that will read the maximum amount
    //of characters, tell it to generate a Token given the input it could accept

    //Store new Token and update the input string (remove the characters read – remember
    //the number of characters in stored in our variable

    //While the input has more characters repeat

    /*
        set lineNumber to 1
        // While there are more characters to tokenize
        loop on input.size() > 0 {
            set maxRead to 0
            set maxAutomaton to the first automaton in automata
            // TODO: you need to handle whitespace inbetween tokens

            // Here is the "Parallel" part of the algorithm
            // Each automaton runs with the same input
            foreach automaton in automata {
                inputRead = automaton.Start(input)
                if (inputRead > maxRead) {
                    set maxRead to inputRead
                    set maxAutomaton to automaton
                }
            }
            // Here is the "Max" part of the algorithm
            if maxRead > 0 {
                set newToken to maxAutomaton.CreateToken(...)
                increment lineNumber by maxAutomaton.NewLinesRead()
                add newToken to collection of all tokens
            }
            // No automaton accepted input; create invalid token
            else {
                set maxRead to 1
                set newToken to a new invalid Token
                (with first character of input)
                add newToken to collection of all tokens
            }
            // Update ‘input‘ by removing characters read to create Token
            remove maxRead characters from input
        }
    */
//}




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