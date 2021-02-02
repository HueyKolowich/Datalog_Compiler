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
    //int lineNumber;

public:
    Token(string type, string input) //lineNumber
    {
        this->type = type;
        this->input = input;
    };
    //virtual ~Token();

    void outputToken();
};

inline void Token::outputToken()
{
    cout << "(" << type << ",\"" << input << "\"," << ")" << endl;
}

#endif