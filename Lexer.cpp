//Huey Kolowich
//CS_236

#include "Lexer.h"

Lexer::Lexer() 
{
    tokens = vector<Token*>();
    automata = vector<Automaton*>();

    Automaton* COMMA = new MatcherAutomaton(",", "COMMA");
    Automaton* PERIOD = new MatcherAutomaton(".", "PERIOD");
    Automaton* Q_MARK = new MatcherAutomaton("?", "Q_MARK");
    Automaton* LEFT_PAREN = new MatcherAutomaton("(", "LEFT_PAREN");
    Automaton* RIGHT_PAREN = new MatcherAutomaton(")", "RIGHT_PAREN");
    Automaton* COLON = new MatcherAutomaton(":", "COLON");
    Automaton* COLON_DASH = new MatcherAutomaton(":-", "COLON_DASH");
    Automaton* MULTIPLY = new MatcherAutomaton("*", "MULTIPLY");
    Automaton* ADD = new MatcherAutomaton("+", "ADD");
    Automaton* SCHEMES = new MatcherAutomaton("Schemes", "SCHEMES");
    Automaton* FACTS = new MatcherAutomaton("Facts", "FACTS");
    Automaton* RULES = new MatcherAutomaton("Rules", "RULES");
    Automaton* QUERIES = new MatcherAutomaton("Queries", "QUERIES");
    Automaton* COMMENT = new CommentAutomaton("COMMENT");
    Automaton* BLOCK = new BlockAutomaton("BLOCK");

    // Add all of the Automaton instances
    automata.push_back(COMMA);
    automata.push_back(PERIOD);
    automata.push_back(Q_MARK);
    automata.push_back(LEFT_PAREN);
    automata.push_back(RIGHT_PAREN);
    automata.push_back(COLON);
    automata.push_back(COLON_DASH);
    automata.push_back(MULTIPLY);
    automata.push_back(ADD);
    automata.push_back(SCHEMES);
    automata.push_back(FACTS);
    automata.push_back(RULES);
    automata.push_back(QUERIES);
    automata.push_back(COMMENT);
    automata.push_back(BLOCK);

}; 

bool Lexer::run(string input) 
{
    lineNum = 1;

    while (input.size() > 0)
    {
        cout << "input: " << input << endl;
        //set maxRead to 0
        maxRead = 0;
        //set maxAutomaton to the first automaton in automata
        maxAutomaton = automata[0];

        // handle whitespace inbetween and after tokens
        while (input[0] == ' ' || input[0] == '\n')
        {
            if (input[0] == '\n')
            {
                lineNum++;
            }
            
            cout << "Accomadated for whitespace..." << endl;
            if (input.length() == 1) 
            {
                //return EOF token and true
                cout << "input length 1... EOF" << endl;
                newToken = new Token("EOF", "", lineNum);
                tokens.push_back(newToken);
                return true;
            }
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
                maxAutomaton = automaton;
            }
        }
       
       if (maxRead > 0) 
       {
            //set newToken to maxAutomaton.CreateToken(...)
            newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNum);

            //increment lineNumber by maxAutomaton.NewLinesRead()
            lineNum += maxAutomaton->NewLinesRead();

            //add newToken to collection of all tokens
            tokens.push_back(newToken);

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
        cout << "substr: " << input << "substr size: " << input.length() << endl;
    }

    return true;
}

bool Lexer::output()
{
    Token* currentToken;

    for (int j = 0; j < tokens.size(); j++)
    {
        currentToken = tokens[j];
        currentToken->outputToken();
    }

    cout << "Total Tokens = " << tokens.size() << endl;

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