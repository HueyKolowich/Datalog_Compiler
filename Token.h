//Huey Kolowich
//CS_236

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

class Token 
{
private:
    string type;
    string input;
    int lineNumber;

public:
    Token(string type, string input, int lineNumber)
    {
        this->type = type;
        this->input = input;
        this->lineNumber = lineNumber;
    };
    //virtual ~Token();

    void outputToken();
    string getTokenType() { return type; }
};

inline void Token::outputToken()
{
    //Handle comment with newline afterwards
    cout << "(" << type << ",\"" << input << "\"," << lineNumber << ")" << endl;
}

#endif