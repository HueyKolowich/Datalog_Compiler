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
    Automaton* BLOCK = new BlockAutomaton("COMMENT");
    Automaton* ID = new IDAutomaton("ID");
    Automaton* STRING = new StringAutomaton("STRING");

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
    automata.push_back(ID);
    automata.push_back(COMMENT);
    automata.push_back(BLOCK);
    automata.push_back(STRING);

}; 

bool Lexer::run(string input) 
{
    lineNum = 1;

    string undToString;

    while (input.size() > 0)
    {
        //cout << "input: " << input[0] << " lineNumber: " << lineNum << endl;

        //set maxRead to 0
        maxRead = 0;
        //set maxAutomaton to the first automaton in automata
        maxAutomaton = automata[0];

        // handle whitespace inbetween and after tokens
        while (input[0] == ' ' || input[0] == '\n' || input[0] == '\t')
        {
            if (input[0] == '\n' && (input.length() != 1))
            {
                //cout << "LineNum increment" << endl;
                lineNum++;
            }
            
            //cout << "Accomadated for whitespace..." << endl;
            if (input.length() == 1) 
            {
                //return EOF token and true
                //cout << "input length 1... EOF" << endl;
                //cout << "LineNum increment" << endl;
                lineNum++;
                newToken = new Token("EOF", "", lineNum);
                tokens.push_back(newToken);
                return true;
            }

            input = input.substr(1);
            //cout << "New Input: " << input.at(0) << endl;
        }
        //cout << "Broke While" << endl;
        
        // Each automaton runs with the same input
        Automaton* automaton;
        int inputRead;

        for (unsigned int i = 0; i < automata.size(); i++)
        {
            automaton = automata[i];
            inputRead = automaton->Start(input);

            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automaton;
            } else if ((i == 15) && (automaton->getOverride()))
            {
                maxRead = inputRead;
                maxAutomaton = automaton;
            }
        }
       
       if (maxRead > 0) 
       {    
            //cout << "\nMaxAutomaton: " << maxAutomaton->getType() << " : " << input.substr(0, maxRead) << endl;

            if (maxAutomaton->getUndefined())
            {
                newToken = maxAutomaton->CreateUndefinedToken(input.substr(0, maxRead), lineNum);
            } else
            {
                newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNum);
            }

            tokens.push_back(newToken);

            //cout << "New Lines: " << maxAutomaton->NewLinesRead() << endl;
            lineNum += maxAutomaton->NewLinesRead();

            //cout << "maxRead: " << maxRead << endl;
        } else // No automaton accepted input; create invalid token 
        { 
            //cout << "Undefined Token:" << input.at(0) << endl;

            //set maxRead to 1
            maxRead = 1;
            //set newToken to a new invalid Token (with first character of input)
            undToString = input.at(0);

            newToken = new Token("UNDEFINED", undToString, lineNum);
            //add newToken to collection of all tokens
            tokens.push_back(newToken);
        }

        // Update ‘input‘ by removing characters read to create Token
        //remove maxRead characters from input 
        input = input.substr(maxRead);
        //cout << "substr: " << input[0] << "substr size: " << input.length() << "\n\n" << endl;
    }

    Token* eofToken;

    if (tokens.size() > 0) 
    {
        int lastTokenNum = (tokens.size() - 1);

        eofToken = tokens[lastTokenNum];

        if (eofToken->getTokenType() != "EOF") 
        {
            newToken = new Token("EOF", "", lineNum);
            tokens.push_back(newToken);
        }
    } else 
    {
        newToken = new Token("EOF", "", lineNum);
        tokens.push_back(newToken);
    }

    return true;
}

bool Lexer::output()
{
    Token* currentToken;

    for (unsigned int j = 0; j < tokens.size(); j++)
    {
        currentToken = tokens[j];
        currentToken->outputToken();
    }

    cout << "Total Tokens = " << tokens.size();

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