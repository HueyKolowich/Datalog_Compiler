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
};

inline void Token::outputToken()
{
    cout << "(" << type << ",\"" << input << "\"," << lineNumber << ")" << endl;
}

#endif