//Huey Kolowich
//CS_236

#include<iostream>
#include<fstream>
#include<vector>
#include<string>


using namespace std;

class Lexer 
{
private:
    //vector<Token*> tokens;
    //vector<Automaton*> automata;

    int lineNum;
    
public:
    Lexer() 
    {
        //tokens = new std::vector<Token*>();
        //automata = new std::vector<Automaton*>();
        // Add all of the Automaton instances
        //automata.push_back(new ColonAutomaton());
        //automata.push_back(new ColonDashAutomaton());
    }

    //Parallel and Max Lexer Function
    //bool run(string);

    string inputToString(string fileName);
};